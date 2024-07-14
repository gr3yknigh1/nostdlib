#include "nostdlib/_internal/fmt/helpers.h"

#include "nostdlib/char.h"
#include "nostdlib/memory.h"
#include "nostdlib/numeric/from_str.h"

u8
_fmt_sign_precede_charcount(const struct _fmt_context *ctx, bool is_positive) {
    u8 charcount = 0;

    if ((ctx->sign_precede == SIGN_PRECEDE_FORCE && is_positive) ||
        (ctx->sign_precede == SIGN_PRECEDE_SPACE)) {
        charcount = 1;
    }

    return charcount;
}

bool
_fmt_is_justification_or_sign_char(char c) {
    return c == '-' || c == ' ' || c == '+';
}

bool
_fmt_is_length_modifier_char(char c) {
    return c == 'l' || c == 'h';
}

bool
_fmt_is_precision_char(char c) {
    return c == '.';
}

u32
_fmt_handle_sign_precede(struct _fmt_context *ctx, char *buffer,
                         bool is_positive) {
    char *buffer_write_ptr = buffer;

    if (ctx->sign_precede == SIGN_PRECEDE_FORCE && is_positive) {
        *buffer_write_ptr++ = '+';
        ctx->justification_value--;
    }

    if (ctx->sign_precede == SIGN_PRECEDE_SPACE && is_positive) {
        *buffer_write_ptr++ = ' ';
        ctx->justification_value--;
    }

    return buffer_write_ptr - buffer;
}

u32
_fmt_count_while_digit(const char *s) {
    u32 count = 0;
    while (noc_is_digit(*s)) {
        ++count;
        ++s;
    }
    return count;
}

u32
_fmt_parse_i32_while_digit(const char *s, i32 *out_num) {
    u32 numlen = _fmt_count_while_digit(s);

    char numstr[numlen + 1];
    numstr[numlen] = '\0';

    NOC_MemoryCopy(numstr, s, numlen);

    if (out_num != nullptr) {
        // TODO: Replace in the future with generic version.
        // TODO: Handle error from convertion.
        noc_i32_from_str(numstr, out_num);
    }
    return numlen;
}

u32
_fmt_emmit_char_in_buffer(char *write_buffer, u32 count, char c) {
    for (u32 i = 0; i < count; ++i) {
        *write_buffer++ = c;
    }
    return count;
}
