#ifndef NOSTDLIB__INTERNAL_FMT_PARSER_H_
#define NOSTDLIB__INTERNAL_FMT_PARSER_H_

#include "nostdlib/types.h"

enum _justification_type {
    JUSTIFICATION_LEFT,
    JUSTIFICATION_RIGHT,
};

enum _sign_precede {
    SIGN_PRECEDE_NONE,
    SIGN_PRECEDE_SPACE,
    SIGN_PRECEDE_FORCE,
};

enum _length_modifier {
    LENGTH_MODIFIER_16,
    LENGTH_MODIFIER_32,
    LENGTH_MODIFIER_64,
    LENGTH_MODIFIER_128,
};

struct _fmt_context {
    enum _justification_type justification_type;
    i64 justification_value;
    enum _sign_precede sign_precede;
    enum _length_modifier length_modifier;
    u32 precision;

    const char **format_read_ptr;
    char curchar;
};

/*
 * Sets defaults for formatter contexts
 *
 * :param `format_read_ptr`: Pointer after `%` char
 * */
struct _fmt_context _fmt_context_init(const char **format_read_ptr);

void _fmt_context_advance(struct _fmt_context *ctx);
void _fmt_context_advance_for(struct _fmt_context *ctx, u64 count);

/*
 * Parsing formatting context. Should set `format_read_ptr` to conversion
 * specifier.
 * */
void _fmt_context_parse(struct _fmt_context *ctx);

#endif // NOSTDLIB__INTERNAL_FMT_PARSER_H_
