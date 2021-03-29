
#ifndef REG_WDG_H
#define REG_WDG_H

#define WDG0_BASEADDR 0x012c0000
#define WDG1_BASEADDR 0x108C0000
#define WDG2_BASEADDR 0x208C0000

/* WDT interrupt vector */
enum WDT_INTR_VECTOR {
    HAL_VECTOR_WDG3_TO = 11,
    HAL_VECTOR_WDG3,
    HAL_VECTOR_WDG2_TO,
    HAL_VECTOR_WDG2,
    HAL_VECTOR_WDG1_TO,
    HAL_VECTOR_WDG1,
    HAL_VECTOR_WDG_TO,
    HAL_VECTOR_WDG,
};

#define WDT_IP_VERSION 1

union wdg_rver_union {
    uint32_t data;
    struct {
        /* INTC register file version */
        uint32_t wdg_rf_ver:16;                   // [15:0]
        uint32_t reserved:16;                     // [31:16]
    } b;
};

union wdg_ctl0_union {
    uint32_t data;
    struct {
        uint32_t wdg_cnt_en:1;                    // [0]
        uint32_t reserved_4:7;                      // [7:1]
        uint32_t wdg_timeout_cnt_en:1;            // [8]
        uint32_t reserved_3:7;                      // [15:9]
        uint32_t wdg_cpurst_cnt_en:1;             // [16]
        uint32_t reserved_2:7;                      // [23:17]
        uint32_t wdg_fullrst_cnt_en:1;            // [24]
        uint32_t reserved:7;                      // [31:25]
    } b;
};

union wdg_ctl1_union {
    uint32_t data;
    struct {
        uint32_t wdg_inter_en:1;                  // [0]
        uint32_t reserved_4:7;                      // [7:1]
        uint32_t wdg_timeout_inter_en:1;          // [8]
        uint32_t reserved_3:7;                      // [15:9]
        uint32_t wdg_cpurst_en:1;                 // [16]
        uint32_t reserved_2:7;                      // [23:17]
        uint32_t wdg_fullrst_en:1;                // [24]
        uint32_t reserved:7;                      // [31:25]
    } b;
};

union wdg_ctl2_union {
    uint32_t data;
    struct {
        /* write 32'hFEED_FEED */
        uint32_t feed_dog_code:32;                // [31:0]
    } b;
};

union wdg_cnt_union {
    uint32_t data;
    struct {
        /* 500K clock counter */
        uint32_t wdg_cnt:32;                      // [31:0]
    } b;
};

union wdg_cmp_union {
    uint32_t data;
    struct {
        uint32_t wdg_cmp:32;                      // [31:0]
    } b;
};

union wdg_int_rst_cnt_union {
    uint32_t data;
    struct {
        uint32_t wdg_timeout_cnt:8;               // [7:0]
        uint32_t wdg_cpurst_cnt:8;                // [15:8]
        uint32_t wdg_fullrst_cnt:8;               // [23:16]
        uint32_t reserved:8;                      // [31:24]
    } b;
};

union wdg_int_rst_cmp_union {
    uint32_t data;
    struct {
        uint32_t wdg_timeout_cmp:8;               // [7:0]
        uint32_t wdg_cpurst_cmp:8;                // [15:8]
        uint32_t wdg_fullrst_cmp:8;               // [23:16]
        uint32_t reserved:8;                      // [31:24]
    } b;
};

union wdg_cpurst_width_union {
    uint32_t data;
    struct {
        /* peri_clk period * XX */
        uint32_t wdg_cpurst_width:8;              // [7:0]
        uint32_t reserved:24;                     // [31:8]
    } b;
};

union wdg_protect_reg_union {
    uint32_t data;
    struct {
        /* 32'h57444750 */
        uint32_t wdg_protect_code:32;             // [31:0]
    } b;
};

typedef struct wdg_reg {
    union wdg_rver_union          reg0;
    union wdg_ctl0_union          reg1;
    union wdg_ctl1_union          reg2;
    union wdg_ctl2_union          reg3;
    union wdg_cnt_union           reg4;
    union wdg_cmp_union           reg5;
    union wdg_int_rst_cnt_union   reg6;
    union wdg_int_rst_cmp_union   reg7;
    union wdg_cpurst_width_union  reg8;
    union wdg_protect_reg_union   reg9;
} wdg_reg_t;

#endif
