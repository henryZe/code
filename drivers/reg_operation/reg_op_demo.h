/****************************************************************************

Copyright(c) 2020 by WuQi Technologies. ALL RIGHTS RESERVED.

This Information is proprietary to WuQi Technologies and MAY NOT
be copied by any method or incorporated into another program without
the express written consent of WuQi. This Information or any portion
thereof remains the property of WuQi. The Information contained herein
is believed to be accurate and WuQi assumes no responsibility or
liability for its use in any way and conveys no license or title under
any patent or copyright and makes no representation or warranty that this
Information is free from patent or copyright infringement.

****************************************************************************/

#ifndef REG_WDT_H
#define REG_WDT_H

/* ------------------------- BASE H ------------------------- */

#define WDG0_BASEADDR 0x101B0000
#define WDG1_BASEADDR 0x101C0000
#define WDG2_BASEADDR 0x101D0000

/* ------------------------- IP H ------------------------- */

#define WDT_IP_VERSION 1

union wdt_ctrl1_union {
    uint32_t data;
    struct {
        /* description */
        uint32_t inter_en:1;    // [0]

        uint32_t rsvd1:7;       // [1:7]

        /* description */
        uint32_t timeout_en:1;  // [8]

        uint32_t rsvd2:7;       // [9:15]

        /* description */
        uint32_t cpurst_en:1;   // [16]

        uint32_t rsvd3:7;       // [16:23]

        /* description */
        uint32_t fullrst_en:1;  // [24]

        uint32_t rsvd4:7;       // [25:31]
    } b;
};

struct wdt_reg {
    /* IP version */
    uint32_t version;

    /* description */
    union wdt_ctrl1_union reg1; // offset 0

    /* description */
    union wdt_ctrl1_union reg2; // offset 4

    uint32_t rsvd[2];

    /* description */
    union wdt_ctrl1_union reg3; // offset 16
};

#endif
