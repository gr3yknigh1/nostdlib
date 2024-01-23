#ifndef NOSTDLIB__INTERNAL_FMT_HELPERS_H_
#define NOSTDLIB__INTERNAL_FMT_HELPERS_H_

#include "nostdlib/_internal/fmt/parser.h"
#include "nostdlib/types.h"

#define _HANDLE_LENGTH_MODIFIER(__LENGTH_MOD, __16HANDLE_EXPR,                 \
                                __32HANDLE_EXPR, __64HANDLE_EXPR)              \
    do {                                                                       \
        switch ((__LENGTH_MOD)) {                                              \
        case LENGTH_MODIFIER_16:                                               \
            __16HANDLE_EXPR;                                                   \
            break;                                                             \
        case LENGTH_MODIFIER_32:                                               \
            __32HANDLE_EXPR;                                                   \
            break;                                                             \
        case LENGTH_MODIFIER_64:                                               \
            __64HANDLE_EXPR;                                                   \
            break;                                                             \
        case LENGTH_MODIFIER_128:                                              \
            break;                                                             \
        }                                                                      \
    } while (0)

u8 _fmt_sign_precede_charcount(const struct _fmt_context *ctx,
                               bool is_positive);

bool _fmt_is_justification_or_sign_char(char c);
bool _fmt_is_length_modifier_char(char c);
bool _fmt_is_precision_char(char c);

u32 _fmt_handle_sign_precede(struct _fmt_context *ctx, char *buffer,
                             bool is_positive);

u32 _fmt_parse_i32_while_digit(const char *s, i32 *out_num);
u32 _fmt_count_while_digit(const char *s);
u32 _fmt_emmit_char_in_buffer(char *write_buffer, u32 count, char c);

#endif // NOSTDLIB__INTERNAL_FMT_HELPERS_H_
