#include "common.h"
#include "spi.h"
#include "ff/src/diskio.h"
#include "io.h"



/*
 * Module Private Functions
 */

/*
 * port controls  (platform dependent)
 */
#define SD_SPI      SPIE
#define CS_LOW()	TFT_SD_PORT.OUTCLR = SD_CS_bm
#define	CS_HIGH()	TFT_SD_PORT.OUTSET = SD_CS_bm
#define SOCKWP		1           /* write protect */
#define SOCKINS		1           /* card in detector */

#define FCLK_SLOW() do { SD_SPI.CTRL |= 0x03; /*SD_SPI.CTRL &= ~0x80;*/ } while (0)
#define FCLK_FAST() do { SD_SPI.CTRL &= ~0x03; /*SD_SPI.CTRL |= 0x80;*/ } while (0)

/*
 * definitions for MMC/SDC command
 */
#define CMD0	(0)			/* GO_IDLE_STATE */
#define CMD1	(1)			/* SEND_OP_COND (MMC) */
#define	ACMD41	(0x80+41)	/* SEND_OP_COND (SDC) */
#define CMD8	(8)			/* SEND_IF_COND */
#define CMD9	(9)			/* SEND_CSD */
#define CMD10	(10)		/* SEND_CID */
#define CMD12	(12)		/* STOP_TRANSMISSION */
#define ACMD13	(0x80+13)	/* SD_STATUS (SDC) */
#define CMD16	(16)		/* SET_BLOCKLEN */
#define CMD17	(17)		/* READ_SINGLE_BLOCK */
#define CMD18	(18)		/* READ_MULTIPLE_BLOCK */
#define CMD23	(23)		/* SET_BLOCK_COUNT (MMC) */
#define	ACMD23	(0x80+23)	/* SET_WR_BLK_ERASE_COUNT (SDC) */
#define CMD24	(24)		/* WRITE_BLOCK */
#define CMD25	(25)		/* WRITE_MULTIPLE_BLOCK */
#define CMD55	(55)		/* APP_CMD */
#define CMD58	(58)		/* READ_OCR */

/*
 * card type flags (cardtype)
 */
#define CT_MMC		0x01            /* MMC ver 3 */
#define CT_SD1		0x02            /* SD ver 1 */
#define CT_SD2		0x04            /* SD ver 2 */
#define CT_SDC		(CT_SD1|CT_SD2)	/* SD */
#define CT_BLOCK	0x08            /* Block addressing */


static volatile DSTATUS Stat = STA_NOINIT; /* disk status */

static volatile BYTE Timer1, Timer2; /* 100hz decrement timer */

static BYTE CardType;			/* card type flags */


/*
 * wait for card ready
 */
static int wait_ready (void)	/* 1:OK, 0:Timeout */
{
	BYTE d;

	Timer2 = 50;	/* Wait for ready in timeout of 500ms */
	do
    {
		d = spi_writeread(&SD_SPI, 0xff);
    }
    while (d != 0xFF && Timer2);

	return (d == 0xFF) ? 1 : 0;
}

/*
 * deselect the card and release SPI bus
 */
static void deselect (void)
{
	CS_HIGH();
	spi_writeread(&SD_SPI, 0xff);	/* force DO hi-z for multiple slave SPI */
}



/*
 * select the card and wait for ready
 */
static int select (void)	/* 1:Successful, 0:Timeout */
{
	CS_LOW();
	spi_writeread(&SD_SPI, 0xff);	/* Dummy clock (force DO enabled) */

	if (wait_ready())
    {
        return 1;	/* OK */
    }
    
	deselect();
	return 0;	/* Timeout */
}



/*
* Power Control  (Platform dependent)
*/
static int power_status(void)		/* socket power state: 0=off, 1=on */
{
	return 1;
}


static void power_on (void)
{
    return;
}


static void power_off (void)
{
    return;
}



/*
 * receive a data packet from MMC
 */ 
static int rcvr_datablock (
                           BYTE *buff, /* Data buffer to store received data */
                           UINT btr /* Byte count (must be multiple of 4) */
                           )
{
	BYTE token;

	Timer1 = 20;
	do {							/* Wait for data packet in timeout of 200ms */
		token = spi_writeread(&SD_SPI, 0xff);
	} while ((token == 0xFF) && Timer1);
    
	if(token != 0xFE) return 0;		/* If not valid data token, retutn with error */

	do {							/* Receive the data block into buffer */
        *buff = spi_writeread(&SD_SPI, 0xff); buff++;
        *buff = spi_writeread(&SD_SPI, 0xff); buff++;
        *buff = spi_writeread(&SD_SPI, 0xff); buff++;
        *buff = spi_writeread(&SD_SPI, 0xff); buff++;
	} while (btr -= 4);
	spi_writeread(&SD_SPI, 0xff);						/* discard CRC */
	spi_writeread(&SD_SPI, 0xff);

	return 1;						/* Return with success */
}



/*
 * Send a data packet to MMC
 */ 
static int xmit_datablock (
                           const BYTE *buff, /* 512 byte data block to be transmitted */
                           BYTE token        /* Data/Stop token */
                           )
{
	BYTE resp, wc;

	if (!wait_ready()) return 0;

	spi_writeread(&SD_SPI, token);					/* Xmit data token */
	if (token != 0xFD) {	/* Is data token */
		wc = 0;
		do {							/* Xmit the 512 byte data block to MMC */
			spi_writeread(&SD_SPI, *buff++);
			spi_writeread(&SD_SPI, *buff++);
		} while (--wc);
		spi_writeread(&SD_SPI, 0xFF);					/* CRC (Dummy) */
		spi_writeread(&SD_SPI, 0xFF);
		resp = spi_writeread(&SD_SPI, 0xff);				/* Reveive data response */
		if ((resp & 0x1F) != 0x05)		/* If not accepted, return with error */
			return 0;
	}

	return 1;
}



/*
 * send a command packet to MMC
 */ 

static BYTE send_cmd (     /* Returns R1 resp (bit7==1:Send failed) */
                      BYTE cmd, /* Command index */
                      DWORD arg /* Argument */
                           )
{
	BYTE n, res;

	if (cmd & 0x80) {	/* ACMD<n> is the command sequense of CMD55-CMD<n> */
		cmd &= 0x7F;
		res = send_cmd(CMD55, 0);
		if (res > 1) return res;
	}

	/* Select the card and wait for ready */
	deselect();
	if (!select()) return 0xFF;

	/* Send command packet */
	spi_writeread(&SD_SPI, 0x40 | cmd);				/* Start + Command index */
	spi_writeread(&SD_SPI, (BYTE)(arg >> 24));		/* Argument[31..24] */
	spi_writeread(&SD_SPI, (BYTE)(arg >> 16));		/* Argument[23..16] */
	spi_writeread(&SD_SPI, (BYTE)(arg >> 8));			/* Argument[15..8] */
	spi_writeread(&SD_SPI, (BYTE)arg);				/* Argument[7..0] */
	n = 0x01;							/* Dummy CRC + Stop */
	if (cmd == CMD0) n = 0x95;			/* Valid CRC for CMD0(0) */
	if (cmd == CMD8) n = 0x87;			/* Valid CRC for CMD8(0x1AA) */
	spi_writeread(&SD_SPI, n);

	/* Receive command response */
	if (cmd == CMD12) spi_writeread(&SD_SPI, 0xff);		/* Skip a stuff byte when stop reading */
	n = 10;								/* Wait for a valid response in timeout of 10 attempts */
	do
		res = spi_writeread(&SD_SPI, 0xff);
	while ((res & 0x80) && --n);

	return res;			/* Return with the response value */
}



/*--------------------------------------------------------------------------
   Public Functions
---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
                         BYTE drv		/* Physical drive nmuber (0) */
                         )
{
	BYTE n, cmd, ty, ocr[4];


	if (drv) return STA_NOINIT;			/* Supports only single drive */
	if (Stat & STA_NODISK) return Stat;	/* No card in the socket */

	power_on();							/* Force socket power on */
	FCLK_SLOW();
	for (n = 10; n; n--) spi_writeread(&SD_SPI, 0xff);	/* 80 dummy clocks */

	ty = 0;
	if (send_cmd(CMD0, 0) == 1) {			/* Enter Idle state */
		Timer1 = 100;						/* Initialization timeout of 1000 msec */
		if (send_cmd(CMD8, 0x1AA) == 1) {	/* SDv2? */
			for (n = 0; n < 4; n++) ocr[n] = spi_writeread(&SD_SPI, 0xff);		/* Get trailing return value of R7 resp */
			if (ocr[2] == 0x01 && ocr[3] == 0xAA) {				/* The card can work at vdd range of 2.7-3.6V */
				while (Timer1 && send_cmd(ACMD41, 1UL << 30));	/* Wait for leaving idle state (ACMD41 with HCS bit) */
				if (Timer1 && send_cmd(CMD58, 0) == 0) {		/* Check CCS bit in the OCR */
					for (n = 0; n < 4; n++) ocr[n] = spi_writeread(&SD_SPI, 0xff);
					ty = (ocr[0] & 0x40) ? CT_SD2 | CT_BLOCK : CT_SD2;	/* SDv2 */
				}
			}
		} else {							/* SDv1 or MMCv3 */
			if (send_cmd(ACMD41, 0) <= 1) 	{
				ty = CT_SD1; cmd = ACMD41;	/* SDv1 */
			} else {
				ty = CT_MMC; cmd = CMD1;	/* MMCv3 */
			}
			while (Timer1 && send_cmd(cmd, 0));			/* Wait for leaving idle state */
			if (!Timer1 || send_cmd(CMD16, 512) != 0)	/* Set R/W block length to 512 */
				ty = 0;
		}
	}
	CardType = ty;
	deselect();

	if (ty) {			/* Initialization succeded */
		Stat &= ~STA_NOINIT;		/* Clear STA_NOINIT */
		FCLK_FAST();
	} else {			/* Initialization failed */
		power_off();
	}

	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0) */
)
{
	if (drv) return STA_NOINIT;		/* Supports only single drive */
	return Stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,			/* Physical drive nmuber (0) */
	BYTE *buff,			/* Pointer to the data buffer to store read data */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;

	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	if (count == 1) {	/* Single block read */
		if ((send_cmd(CMD17, sector) == 0)	/* READ_SINGLE_BLOCK */
			&& rcvr_datablock(buff, 512))
			count = 0;
	}
	else {				/* Multiple block read */
		if (send_cmd(CMD18, sector) == 0) {	/* READ_MULTIPLE_BLOCK */
			do {
				if (!rcvr_datablock(buff, 512)) break;
				buff += 512;
			} while (--count);
			send_cmd(CMD12, 0);				/* STOP_TRANSMISSION */
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0) */
	const BYTE *buff,	/* Pointer to the data to be written */
	DWORD sector,		/* Start sector number (LBA) */
	BYTE count			/* Sector count (1..255) */
)
{
	if (drv || !count) return RES_PARERR;
	if (Stat & STA_NOINIT) return RES_NOTRDY;
	if (Stat & STA_PROTECT) return RES_WRPRT;

	if (!(CardType & CT_BLOCK)) sector *= 512;	/* Convert to byte address if needed */

	if (count == 1) {	/* Single block write */
		if ((send_cmd(CMD24, sector) == 0)	/* WRITE_BLOCK */
			&& xmit_datablock(buff, 0xFE))
			count = 0;
	}
	else {				/* Multiple block write */
		if (CardType & CT_SDC) send_cmd(ACMD23, count);
		if (send_cmd(CMD25, sector) == 0) {	/* WRITE_MULTIPLE_BLOCK */
			do {
				if (!xmit_datablock(buff, 0xFC)) break;
				buff += 512;
			} while (--count);
			if (!xmit_datablock(0, 0xFD))	/* STOP_TRAN token */
				count = 1;
		}
	}
	deselect();

	return count ? RES_ERROR : RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	BYTE n, csd[16], *ptr = buff;
	WORD csize;


	if (drv) return RES_PARERR;

	res = RES_ERROR;

	if (ctrl == CTRL_POWER) {
		switch (ptr[0]) {
		case 0:		/* Sub control code (POWER_OFF) */
			power_off();		/* Power off */
			res = RES_OK;
			break;
		case 1:		/* Sub control code (POWER_GET) */
			ptr[1] = (BYTE)power_status();
			res = RES_OK;
			break;
		default :
			res = RES_PARERR;
		}
	}
	else {
		if (Stat & STA_NOINIT) return RES_NOTRDY;

		switch (ctrl) {
		case CTRL_SYNC :		/* Make sure that no pending write process. Do not remove this or written sector might not left updated. */
			if (select()) {
				deselect();
				res = RES_OK;
			}
			break;

		case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
			if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {
				if ((csd[0] >> 6) == 1) {	/* SDC ver 2.00 */
					csize = csd[9] + ((WORD)csd[8] << 8) + 1;
					*(DWORD*)buff = (DWORD)csize << 10;
				} else {					/* SDC ver 1.XX or MMC*/
					n = (csd[5] & 15) + ((csd[10] & 128) >> 7) + ((csd[9] & 3) << 1) + 2;
					csize = (csd[8] >> 6) + ((WORD)csd[7] << 2) + ((WORD)(csd[6] & 3) << 10) + 1;
					*(DWORD*)buff = (DWORD)csize << (n - 9);
				}
				res = RES_OK;
			}
			break;

		case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
			*(WORD*)buff = 512;
			res = RES_OK;
			break;

		case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
			if (CardType & CT_SD2) {	/* SDv2? */
				if (send_cmd(ACMD13, 0) == 0) {	/* Read SD status */
					spi_writeread(&SD_SPI, 0xff);
					if (rcvr_datablock(csd, 16)) {				/* Read partial block */
						for (n = 64 - 16; n; n--) spi_writeread(&SD_SPI, 0xff);	/* Purge trailing data */
						*(DWORD*)buff = 16UL << (csd[10] >> 4);
						res = RES_OK;
					}
				}
			} else {					/* SDv1 or MMCv3 */
				if ((send_cmd(CMD9, 0) == 0) && rcvr_datablock(csd, 16)) {	/* Read CSD */
					if (CardType & CT_SD1) {	/* SDv1 */
						*(DWORD*)buff = (((csd[10] & 63) << 1) + ((WORD)(csd[11] & 128) >> 7) + 1) << ((csd[13] >> 6) - 1);
					} else {					/* MMCv3 */
						*(DWORD*)buff = ((WORD)((csd[10] & 124) >> 2) + 1) * (((csd[11] & 3) << 3) + ((csd[11] & 224) >> 5) + 1);
					}
					res = RES_OK;
				}
			}
			break;

		case MMC_GET_TYPE :		/* Get card type flags (1 byte) */
			*ptr = CardType;
			res = RES_OK;
			break;

		case MMC_GET_CSD :		/* Receive CSD as a data block (16 bytes) */
			if (send_cmd(CMD9, 0) == 0		/* READ_CSD */
				&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_CID :		/* Receive CID as a data block (16 bytes) */
			if (send_cmd(CMD10, 0) == 0		/* READ_CID */
				&& rcvr_datablock(ptr, 16))
				res = RES_OK;
			break;

		case MMC_GET_OCR :		/* Receive OCR as an R3 resp (4 bytes) */
			if (send_cmd(CMD58, 0) == 0) {	/* READ_OCR */
				for (n = 4; n; n--) *ptr++ = spi_writeread(&SD_SPI, 0xff);
				res = RES_OK;
			}
			break;

		case MMC_GET_SDSTAT :	/* Receive SD statsu as a data block (64 bytes) */
			if (send_cmd(ACMD13, 0) == 0) {	/* SD_STATUS */
				spi_writeread(&SD_SPI, 0xff);
				if (rcvr_datablock(ptr, 64))
					res = RES_OK;
			}
			break;

		default:
			res = RES_PARERR;
		}

		deselect();
	}

	return res;
}

DWORD get_fattime (void)
{


    return    ((2007UL-1980) << 25)    // Year = 2007
        | (6UL << 21)            // Month = June
        | (5UL << 16)            // Day = 5
        | (11U << 11)            // Hour = 11
        | (38U << 5)            // Min = 38
        | (0U >> 1)                // Sec = 0
        ;
}


/*-----------------------------------------------------------------------*/
/* Device Timer Interrupt Procedure                                      */
/*-----------------------------------------------------------------------*/
/* This function must be called in period of 10ms                        */

void disk_timerproc (void)
{
	BYTE n, s;


	n = Timer1;				/* 100Hz decrement timer */
	if (n) Timer1 = --n;
	n = Timer2;
	if (n) Timer2 = --n;

	s = Stat;

	if (SOCKWP)				/* Write protected */
		s |= STA_PROTECT;
	else					/* Write enabled */
		s &= ~STA_PROTECT;

	if (SOCKINS)			/* Card inserted */
		s &= ~STA_NODISK;
	else					/* Socket empty */
		s |= (STA_NODISK | STA_NOINIT);

	Stat = s;				/* Update MMC status */
}
