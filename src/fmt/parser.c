#include "nostdlib/_internal/fmt/parser.h"

#include "nostdlib/_internal/fmt/helpers.h"
#include "nostdlib/char.h"

struct _fmt_context
_fmt_context_init(const char **format_read_ptr) {
    return (struct _fmt_context){
        .justification_type = JUSTIFICATION_RIGHT,
        .justification_value = 0,
        .sign_precede = SIGN_PRECEDE_NONE,
        .length_modifier = LENGTH_MODIFIER_32,
        .precision = 6,
        .format_read_ptr = format_read_ptr,
        .curchar = **format_read_ptr,
    };
}

void
_fmt_context_parse(struct _fmt_context *ctx) {
    while (_fmt_is_justification_or_sign_char(ctx->curchar)) {
        switch (ctx->curchar) {
        case '-':
            ctx->justification_type = JUSTIFICATION_LEFT;
            break;
        case '+':
            ctx->sign_precede = SIGN_PRECEDE_FORCE;
            break;
        case ' ':
            if (ctx->sign_precede != SIGN_PRECEDE_FORCE) {
                ctx->sign_precede = SIGN_PRECEDE_SPACE;
            }
            break;
        }
        _fmt_context_advance(ctx);
    }

    if (NOC_IsDigit(ctx->curchar)) {
        _fmt_context_advance_for(ctx, _fmt_parse_i32_while_digit(
                                          *ctx->format_read_ptr,
                                          (i32 *)(&ctx->justification_value)));
        //                                  ^^^^^^^
        // FIXME: Remove this pointer conversion. Replace i32 version with u32
    }

    if (_fmt_is_precision_char(ctx->curchar)) {
        _fmt_context_advance(ctx);
        _fmt_context_advance_for(
            ctx, _fmt_parse_i32_while_digit(*ctx->format_read_ptr,
                                            (i32 *)(&ctx->precision)));
        //                                  ^^^^^^^
        // FIXME: Remove this pointer conversion. Replace i32 version with u32
    }

    if (_fmt_is_length_modifier_char(ctx->curchar)) {
        // FIXME: We currently only supporting `h` and `l` length modifiers
        switch (ctx->curchar) {
        case 'l':
            ctx->length_modifier = LENGTH_MODIFIER_64;
            break;
        case 'h':
            ctx->length_modifier = LENGTH_MODIFIER_16;
            break;
        }
        _fmt_context_advance(ctx);
    }
}

void
_fmt_context_advance(struct _fmt_context *ctx) {
    if (**ctx->format_read_ptr != '\0') {
        (*ctx->format_read_ptr)++;
        ctx->curchar = **ctx->format_read_ptr;
    }
}

void
_fmt_context_advance_for(struct _fmt_context *ctx, u64 count) {
    while (count-- > 0) {
        _fmt_context_advance(ctx);
    }
}
