#include "nostdlib/_internal/fmt/sprintf/impls.h"

#include "nostdlib/_internal/fmt/helpers.h"
#include "nostdlib/macros.h"
#include "nostdlib/numeric/countdigits.h"
#include "nostdlib/numeric/flt_charcount.h"
#include "nostdlib/numeric/to_str.h"
#include "nostdlib/string.h"

#define _SPRINTF_INT(__TYPE)                                                   \
    void _sprintf_##__TYPE(struct _fmt_context *ctx, char **buffer_write_ptr,  \
                           __TYPE value) {                                     \
        if (ctx->justification_value != 0) {                                   \
            i32 sign_charcount = _fmt_sign_precede_charcount(ctx, value > 0);  \
            i32 value_charcount = NOC_COUNTDIGITS(value);                      \
            ctx->justification_value = MAX(                                    \
                ctx->justification_value - value_charcount - sign_charcount,   \
                0);                                                            \
                                                                               \
            switch (ctx->justification_type) {                                 \
            case JUSTIFICATION_LEFT:                                           \
                *buffer_write_ptr += _fmt_handle_sign_precede(                 \
                    ctx, *buffer_write_ptr, value > 0);                        \
                *buffer_write_ptr += NOC_TO_STR(value, *buffer_write_ptr);     \
                *buffer_write_ptr += _fmt_emmit_char_in_buffer(                \
                    *buffer_write_ptr, ctx->justification_value, ' ');         \
                break;                                                         \
            case JUSTIFICATION_RIGHT:                                          \
                *buffer_write_ptr += _fmt_emmit_char_in_buffer(                \
                    *buffer_write_ptr, ctx->justification_value, ' ');         \
                *buffer_write_ptr += _fmt_handle_sign_precede(                 \
                    ctx, *buffer_write_ptr, value > 0);                        \
                *buffer_write_ptr += NOC_TO_STR(value, *buffer_write_ptr);     \
                break;                                                         \
            }                                                                  \
        } else {                                                               \
            *buffer_write_ptr +=                                               \
                _fmt_handle_sign_precede(ctx, *buffer_write_ptr, value > 0);   \
            *buffer_write_ptr += NOC_TO_STR(value, *buffer_write_ptr);         \
        }                                                                      \
    }

// FIXME: Checkout values: 1232.3 and replace f64 with f32 version
#define _SPRINTF_FLT(__TYPE)                                                   \
    void _sprintf_##__TYPE(struct _fmt_context *ctx, char **buffer_write_ptr,  \
                           __TYPE value) {                                     \
        if (ctx->justification_value != 0) {                                   \
            i32 sign_charcount = _fmt_sign_precede_charcount(ctx, value > 0);  \
            i32 value_charcount = NOC_FLT_CHARCOUNT(value, ctx->precision);    \
            ctx->justification_value = MAX(                                    \
                ctx->justification_value - value_charcount - sign_charcount,   \
                0);                                                            \
                                                                               \
            switch (ctx->justification_type) {                                 \
            case JUSTIFICATION_LEFT:                                           \
                *buffer_write_ptr += _fmt_handle_sign_precede(                 \
                    ctx, *buffer_write_ptr, value > 0);                        \
                *buffer_write_ptr +=                                           \
                    NOC_TO_STR(value, *buffer_write_ptr, ctx->precision);      \
                *buffer_write_ptr += _fmt_emmit_char_in_buffer(                \
                    *buffer_write_ptr, ctx->justification_value, ' ');         \
                break;                                                         \
            case JUSTIFICATION_RIGHT:                                          \
                *buffer_write_ptr += _fmt_emmit_char_in_buffer(                \
                    *buffer_write_ptr, ctx->justification_value, ' ');         \
                *buffer_write_ptr += _fmt_handle_sign_precede(                 \
                    ctx, *buffer_write_ptr, value > 0);                        \
                *buffer_write_ptr +=                                           \
                    NOC_TO_STR(value, *buffer_write_ptr, ctx->precision);      \
                break;                                                         \
            }                                                                  \
        } else {                                                               \
            *buffer_write_ptr +=                                               \
                _fmt_handle_sign_precede(ctx, *buffer_write_ptr, value > 0);   \
            *buffer_write_ptr +=                                               \
                NOC_TO_STR(value, *buffer_write_ptr, ctx->precision);          \
        }                                                                      \
    }

_SPRINTF_INT(i16)
_SPRINTF_INT(i32)
_SPRINTF_INT(i64)

_SPRINTF_INT(u16)
_SPRINTF_INT(u32)
_SPRINTF_INT(u64)

// FIXME: Replace `f64` on `float` usage in sprintf with this
// _SPRINTF_FLT(f32)
_SPRINTF_FLT(f64)

void
_sprintf_char(struct _fmt_context *ctx, char **buffer_write_ptr, char value) {
    if (ctx->justification_value != 0) {
        i32 sign_charcount = _fmt_sign_precede_charcount(ctx, value > 0);
        i32 value_charcount = 1;
        ctx->justification_value =
            MAX(ctx->justification_value - value_charcount - sign_charcount, 0);

        switch (ctx->justification_type) {
        case JUSTIFICATION_LEFT:
            *buffer_write_ptr +=
                _fmt_handle_sign_precede(ctx, *buffer_write_ptr, value > 0);
            *(*buffer_write_ptr)++ += value;
            *buffer_write_ptr += _fmt_emmit_char_in_buffer(
                *buffer_write_ptr, ctx->justification_value, ' ');
            break;
        case JUSTIFICATION_RIGHT:
            *buffer_write_ptr += _fmt_emmit_char_in_buffer(
                *buffer_write_ptr, ctx->justification_value, ' ');
            *buffer_write_ptr +=
                _fmt_handle_sign_precede(ctx, *buffer_write_ptr, value > 0);
            *(*buffer_write_ptr)++ += value;
            break;
        }
    } else {
        *(*buffer_write_ptr)++ += value;
    }
}

void
_sprintf_cstr(struct _fmt_context *ctx, char **buffer_write_ptr,
              const char *value) {
    u32 value_charcount = noc_string_len(value);

    if (ctx->justification_value != 0) {
        ctx->justification_value =
            MAX(ctx->justification_value - value_charcount, 0);

        switch (ctx->justification_type) {
        case JUSTIFICATION_LEFT:
            *buffer_write_ptr += noc_string_copy(*buffer_write_ptr, value);
            *buffer_write_ptr += _fmt_emmit_char_in_buffer(
                *buffer_write_ptr, ctx->justification_value, ' ');
            break;
        case JUSTIFICATION_RIGHT:
            *buffer_write_ptr += _fmt_emmit_char_in_buffer(
                *buffer_write_ptr, ctx->justification_value, ' ');
            *buffer_write_ptr += noc_string_copy(*buffer_write_ptr, value);
            break;
        }
    } else {
        *buffer_write_ptr += noc_string_copy(*buffer_write_ptr, value);
    }
}
