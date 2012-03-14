#include "task.h"
#include "common.h"
#include "disp.h"
#include "bitchar.h"
#include "gps.h"


void task_screen(void)
{
    if (gps_gga_updated())
    {
        disp_string(10, 10, &BM_FONT_8x8THIN,
                    disp_16color(20, 20, 20), 0xffff, gps.utc);
    }
}
