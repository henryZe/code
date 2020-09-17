#define __REG_N_FIELD__(...) __REG_N_FIELD_(__VA_ARGS__, __FIELD_RSEQ_N())
#define __REG_N_FIELD_(...)  __REG_FIELD_N(__VA_ARGS__)
#define __REG_FIELD_N(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12,   \
                        _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, \
                        _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, \
                        _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, \
                        _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, \
                        _57, _58, _59, _60, _61, _62, _63, _64, N, ...)        \
                        N
#define __FIELD_RSEQ_N()                                                 \
        32, 0, 31, 0, 30, 0, 29, 0, 28, 0, 27, 0, 26, 0, 25, 0, 24, 0,   \
        23, 0, 22, 0, 21, 0, 20, 0, 19, 0, 18, 0, 17, 0, 16, 0, 15, 0,   \
        14, 0, 13, 0, 12, 0, 11, 0, 10, 0, 9, 0, 8, 0, 7, 0, 6, 0, 5, 0, \
        4, 0, 3, 0, 2, 0, 1, 0, 0, 0

#define CONCATENATE(arg1, arg2) arg1##arg2

#define WR_FIELD_1(bitfield, val) (__x.b.bitfield = val)
#define WR_FIELD_2(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_1(__VA_ARGS__); \
    }
#define WR_FIELD_3(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_2(__VA_ARGS__); \
    }
#define WR_FIELD_4(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_3(__VA_ARGS__); \
    }
#define WR_FIELD_5(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_4(__VA_ARGS__); \
    }
#define WR_FIELD_6(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_5(__VA_ARGS__); \
    }
#define WR_FIELD_7(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_6(__VA_ARGS__); \
    }
#define WR_FIELD_8(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_7(__VA_ARGS__); \
    }
#define WR_FIELD_9(f, val, ...)  \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_8(__VA_ARGS__); \
    }
#define WR_FIELD_10(f, val, ...) \
    {                            \
        WR_FIELD_1(f, val);      \
        WR_FIELD_9(__VA_ARGS__); \
    }
#define WR_FIELD_11(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_10(__VA_ARGS__); \
    }
#define WR_FIELD_12(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_11(__VA_ARGS__); \
    }
#define WR_FIELD_13(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_12(__VA_ARGS__); \
    }
#define WR_FIELD_14(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_13(__VA_ARGS__); \
    }
#define WR_FIELD_15(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_14(__VA_ARGS__); \
    }
#define WR_FIELD_16(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_15(__VA_ARGS__); \
    }
#define WR_FIELD_17(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_16(__VA_ARGS__); \
    }
#define WR_FIELD_18(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_17(__VA_ARGS__); \
    }
#define WR_FIELD_19(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_18(__VA_ARGS__); \
    }
#define WR_FIELD_20(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_19(__VA_ARGS__); \
    }
#define WR_FIELD_21(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_20(__VA_ARGS__); \
    }
#define WR_FIELD_22(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_21(__VA_ARGS__); \
    }
#define WR_FIELD_23(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_22(__VA_ARGS__); \
    }
#define WR_FIELD_24(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_23(__VA_ARGS__); \
    }
#define WR_FIELD_25(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_24(__VA_ARGS__); \
    }
#define WR_FIELD_26(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_25(__VA_ARGS__); \
    }
#define WR_FIELD_27(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_26(__VA_ARGS__); \
    }
#define WR_FIELD_28(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_27(__VA_ARGS__); \
    }
#define WR_FIELD_29(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_28(__VA_ARGS__); \
    }
#define WR_FIELD_30(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_29(__VA_ARGS__); \
    }
#define WR_FIELD_31(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_30(__VA_ARGS__); \
    }
#define WR_FIELD_32(f, val, ...)  \
    {                             \
        WR_FIELD_1(f, val);       \
        WR_FIELD_31(__VA_ARGS__); \
    }

#define WR_REG_FIELD_(N, reg, ...)              \
    ({                                          \
        typeof(reg) __x = reg;                  \
        CONCATENATE(WR_FIELD_, N)(__VA_ARGS__); \
        reg = __x;                              \
    })

/**
 * WR_REG_FIELD(reg, field1, val1, field2, val2, field3, val3, ...)
 */
#define WR_REG_FIELD(reg, ...) \
    WR_REG_FIELD_(__REG_N_FIELD__(reg, __VA_ARGS__), reg, __VA_ARGS__)

#define RD_REG_FIELD(reg, bitfield) \
    ({                              \
        typeof(reg) __x = reg;      \
        __x.b.bitfield;            \
    })
