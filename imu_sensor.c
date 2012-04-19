#include "common.h"
#include "twi_master_driver.h"
#include "imu_sensor.h"
#include "io.h"

#include "tilt.h"
#include "gibbon.h"

TWI_Master_t imu_twi;
extern volatile GIBBON_COMMON_t gibbon;


////////////////
////////////////


ISR (IMU_GYRO_vect)
{
    imu_gyro_read(&(gibbon.g_rev));

    tilt_state_update(&(gibbon.tilt_state), gibbon.g_rev.z * DEG_RAD_OP / 100);
    
    gibbon.gyro_updated++;
}

ISR (IMU_ACCEL_vect)
{
    // LEDPORT.OUTTGL = LED4;

    imu_accel_read(&(gibbon.a_rev));
    
    tilt_kalman_update(&(gibbon.tilt_state), atan2(gibbon.a_rev.x, gibbon.a_rev.y));
    
    gibbon.accel_updated++;
}


ISR (IMU_TWI_vect)
{
    twi_master_irq_handler(&imu_twi);
}

unsigned char imu_read_reg(unsigned char part_addr, unsigned char reg)
{
    unsigned char cmd_buf[] = { reg };
    
    twi_master_writeread(&imu_twi, part_addr, cmd_buf, 1, 1);
    while (imu_twi.status != TWIM_STATUS_READY)
    {
    }

    return imu_twi.read_data[0];
}

unsigned char imu_write_reg(unsigned char part_addr,
                            unsigned char reg, unsigned char val)
{
    unsigned char cmd_buf[] = { reg, val };

    twi_master_write(&imu_twi, part_addr, cmd_buf, 2);
    while (imu_twi.status != TWIM_STATUS_READY)
    {
    }

    return 0;
}

////////////////
////////////////

void imu_init(void)
{
    IMU_PORT.DIRCLR = IMU_GYRO_INT_bm | IMU_ACCEL_INT_bm;

    IMU_PORT.INT0MASK |= IMU_GYRO_INT_bm;
    IMU_PORT.INT1MASK |= IMU_ACCEL_INT_bm;
    
    IMU_PORT.IMU_GYRO_PINCTRL |= PORT_ISC_RISING_gc | PORT_OPC_PULLDOWN_gc;
    IMU_PORT.IMU_ACCEL_PINCTRL |= PORT_ISC_RISING_gc | PORT_OPC_PULLDOWN_gc;
    IMU_PORT.INTCTRL |= PORT_INT0LVL_LO_gc | PORT_INT1LVL_LO_gc;

    /*
    twi_master_init(&imu_twi, &IMU_TWI,
                    TWI_MASTER_INTLVL_LO_gc, TWI_BAUD(F_CPU, 400000));
    */

    twi_master_init(&imu_twi, &IMU_TWI,
                    TWI_MASTER_INTLVL_MED_gc, TWI_BAUD(F_CPU, 400000));

    ////////////////
    ////////////////
    

    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL2, 0x37); /* HPF autoreset, cut-off @ 0.1hz when ODR=200 */
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL3, 0x00); /*  */
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL4, 0x80); /* block data update, FS = 250dps */
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_REF, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_XH, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_XL, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_YH, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_YL, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_ZH, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_THS_ZL, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_DURATION, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_INT1_CFG, 0x00);
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL5, 0x13); /* HPF and LPF2 enable */
    
    // imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1, 0x60); /* power off, LPF1->54hz, LPF2->50hz, ODR->200hz */
    imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1, 0x30); /* power off, LPF1->54hz, LPF2->25hz, ODR->100hz */


    ////////////////
    ////////////////
    ////////////////
    ////////////////

    // imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL1, 0x0f); /* power off, ODR->100hz, LPF->74hz */
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL1, 0x07); /* power off, ODR->50hz, LPF->37hz */

    // imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL2, 0x12); /* enable FDS, HPF cut-off @ 0.5hz */
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL2, 0x00); /* disable FDS */
    
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL3, 0x00); /* data ready on INT1 */
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL4, 0x80); /* block data update, FS = 2g */
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL5, 0x00); /* disable sleep to wake */
    imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_INT1_CFG, 0x40); /* 6 direction movement */


    ////////////////
    ////////////////
    imu_accel_dump(1);
    _delay_ms(25);
    imu_gyro_dump(1);
    _delay_ms(10);
}


////////////////
////////////////

unsigned char imu_gyro_read(IMU_GYRO_RESULT_t *rev)
{
    /*
    unsigned char cmd_buf[] = { IMU_GYRO_X_L };
    twi_master_writeread(&imu_twi, IMU_GYRO_ADDR, cmd_buf, 1, 6);
    memcpy((void *)rev, (const void *)imu_twi.read_data, 6);
    */

    unsigned char tmp;
    unsigned char *p = (unsigned char *)(rev);
    
    for (unsigned char i=0; i<6; i++)
    {
        tmp = imu_read_reg(IMU_GYRO_ADDR, IMU_GYRO_X_L + i);
        *p = tmp;
        p++;

        // printf("tmp: 0x%02x, ", tmp);
    }
    // printf("\n");

    return 0;
}

void imu_gyro_power(unsigned char sel)
{
    unsigned char oldval = imu_read_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1);
    
    switch(sel)
    {
    case IMU_GYRO_POWER_ON:
        imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1, oldval | 0x0f);
        
        break;
    case IMU_GYRO_POWER_SLEEP:
        imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1, oldval & 0xf8);
        
        break;
    case IMU_GYRO_POWER_OFF:
        imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL1, oldval & 0xf0);
        
        break;
    default:
        break;
    }
}

void imu_gyro_dump(unsigned char on)
{
    if (on)
    {
        imu_gyro_power(IMU_GYRO_POWER_ON);
        _delay_ms(1);
        
        imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL3, 0x08);
    }
    else
    {
        imu_write_reg(IMU_GYRO_ADDR, IMU_GYRO_CTRL3, 0x00);

        imu_gyro_power(IMU_GYRO_POWER_OFF);
    }
}


////////////////
////////////////

void imu_accel_power(unsigned char sel)
{
    unsigned char oldval = imu_read_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL1);
    
    if (sel == IMU_GYRO_POWER_ON)
    {
        imu_write_reg(IMU_ACCEL_ADDR, IMU_GYRO_CTRL1, (oldval & 0x1f) | 0x20);
    }
    else
    {
        imu_write_reg(IMU_ACCEL_ADDR, IMU_GYRO_CTRL1, oldval & 0x1f);
    }
}

unsigned char imu_accel_read(IMU_ACCEL_RESULT_t *rev)
{
    unsigned char tmp;
    unsigned char *p = (unsigned char *)(rev);
    
    for (unsigned char i=0; i<6; i++)
    {
        tmp = imu_read_reg(IMU_ACCEL_ADDR, IMU_ACCEL_OUT_X_L + i);
        // printf("%d, ", tmp);
        
        *p = tmp;
        p++;
    }
    // printf("\n");

    return 0;
}

void imu_accel_dump(unsigned char on)
{
    if (on)
    {
        imu_accel_power(IMU_ACCEL_POWER_ON);
        _delay_ms(1);
        
        imu_write_reg(IMU_ACCEL_ADDR, IMU_ACCEL_CTRL3, 0x02);
    }
    else
    {
        imu_write_reg(IMU_GYRO_ADDR, IMU_ACCEL_CTRL3, 0x00);

        imu_accel_power(IMU_ACCEL_POWER_OFF);
    }
}


// void imu_filter(IMU_GYRO_RESULT_t *g_rev, IMU_ACCEL_RESULT_t *a_rev)
unsigned char imu_dump(void)
{
    float angle, angle_est;
    float rate, rate_est;
    float bias;

    unsigned char rev = 0;
    unsigned char wl_buf[64];
    
    // IMU_GYRO_RESULT_t *g_rev;
    // IMU_ACCEL_RESULT_t *a_rev;
    // g_rev = &(gibbon.g_rev);
    // a_rev = &(gibbon.a_rev);

    // angle = atan2(a_rev->x, a_rev->y);
    // rate = g_rev->z * DEG_RAD_OP / 100;
    
    if (gibbon.accel_updated)
    {
        gibbon.accel_updated = 0;
        // tilt_kalman_update(&(gibbon.tilt_state), angle);
    }

    if (gibbon.gyro_updated)
    {
        rev = 1;
        
        gibbon.gyro_updated = 0;
        // tilt_state_update(&(gibbon.tilt_state), rate);
    
        if (gibbon.tilt_dump)
        {
            angle_est = tilt_get_angle(&(gibbon.tilt_state));
            rate_est = tilt_get_rate(&(gibbon.tilt_state));
            bias = tilt_get_bias(&(gibbon.tilt_state));

            snprintf(wl_buf, 64, "tilt:%f,%f,%f\n", angle_est, rate_est, bias);
#ifdef UART_DEBUG
            printf("tilt:%f,%f,%f\n", angle_est, rate_est, bias);
#endif
            wl_send(wl_buf, strlen(wl_buf));
            
        }
    }

    return rev;
}
