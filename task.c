#include "task.h"
#include "common.h"
#include "disp.h"
#include "bitchar.h"
#include "gps.h"


void task_screen(void)
{
    if (gps_gga_updated())
    {
        disp_string(5, 5, &BM_FONT_7x8,
                    disp_16color(220, 20, 20), disp_16color(128, 64, 160), gps.utc);

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
    }
}
