#include "task.h"
#include "common.h"
#include "disp.h"
#include "bitchar.h"
#include "gps.h"
#include "ds1302.h"
#include "ff/src/ff.h"

FATFS g_sFatFs;
DIR g_sDirObject;
FILINFO g_sFileInfo;
FIL g_sFILEObject;


char task_init(void)
{
    FRESULT fresult;
    unsigned char rev;
    
    fresult = f_mount(0, &g_sFatFs);

    if (fresult != FR_OK)
    {
        printf("mount error!!\n");
        return -1;
    }

    fresult = f_opendir(&g_sDirObject, "/");

    if(fresult != FR_OK)
    {
        printf("opendir error\n");
        return -1;
    }
    
    fresult = f_open(&g_sFILEObject, "VBOX.LOG", FA_OPEN_ALWAYS | FA_WRITE);
    fresult = f_lseek(&g_sFILEObject, g_sFILEObject.fsize);
    
    fresult = f_write(&g_sFILEObject, "!!!!!!!!!!!!!!!!\n\n\n\n", 20, &rev);
    printf("wrote: %d\n", rev);
    f_sync(&g_sFILEObject);

    return 0;
}

void task_screen(void)
{
    static unsigned char count=250;
    unsigned char buf[16];
    
    if (gps_gga_updated())
    {
        disp_string(5, 5, &BM_FONT_7x8,
                    disp_16color(220, 20, 20), disp_16color(128, 64, 160), &(gps.utc));

        disp_string(10, 20, &BM_FONT_8x8THIN,
                    disp_16color(20, 20, 20), 0xffff, gps.latitude);
        disp_string(88, 20, &BM_FONT_8x8THIN,
                    disp_16color(20, 20, 20), 0x0fff, gps.ns_indicator);

        disp_string(5, 30, &BM_FONT_8x8THIN,
                    disp_16color(20, 20, 20), 0xffff, gps.longitude);
        disp_string(88, 30, &BM_FONT_8x8THIN,
                    disp_16color(20, 20, 20), 0x0fff, gps.ew_indicator);

        disp_string(100, 25, &BM_FONT_8x8,
                    disp_16color(20, 255, 20), 0x1111, gps.satellites_used);


        snprintf(buf, 16, "v-box|%03d", count++);
        disp_string(55, 150, &BM_FONT_8x8,
                    disp_16color(255, 255, 255), 0x0000, buf);
    }
}
