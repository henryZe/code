typedef unsigned int uint32_t;

#include "wdg_reg.h"
#include "reg_opt.h"

static volatile struct wdg_reg * const wdt_bases[3] = {
    (volatile struct wdg_reg *)WDG0_BASEADDR,
    (volatile struct wdg_reg *)WDG1_BASEADDR,
    (volatile struct wdg_reg *)WDG2_BASEADDR,
};

/* ------------------------- C ------------------------- */
void wdt_ctrl_set(int port, uint32_t val)
{
    WR_REG_FIELD(wdt_bases[port]->reg2,
                wdg_inter_en, val,
                wdg_timeout_inter_en, val);
}

uint32_t wdt_ctrl_status(int port)
{
    return RD_REG_FIELD(wdt_bases[port]->reg2, wdg_inter_en);
}

int main(void)
{
    wdt_ctrl_set(1, 1);
    return wdt_ctrl_status(1);
}
