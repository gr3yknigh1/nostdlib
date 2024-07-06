#include "nostdlib/string.h"

#include "nostdlib/char.h"
#include "nostdlib/memory.h"
#include "nostdlib/types.h"

#include "nostdlib/_internal/fmt/helpers.h"
#include "nostdlib/_internal/fmt/parser.h"
#include "nostdlib/_internal/fmt/sprintf/impls.h"

#include <stdarg.h> // va_list va_start va_end va_arg
#include <stdlib.h> // calloc

static void insert_and_shift(char *str, const char *src, long src_index,
                             long str_index);

NOC_DEF usize
noc_string_format(char8 *buffer, const char8 *format, ...) {
    const char *format_read_ptr = format;
    char *buffer_write_ptr = buffer;

    va_list args;
    va_start(args, format);

    while (*format_read_ptr != 0) {
        if (*format_read_ptr == '%') {
            ++format_read_ptr;

            struct _fmt_context ctx = _fmt_context_init(&format_read_ptr);
            _fmt_context_parse(&ctx);

            char convertion_specifier = *format_read_ptr;

            // TODO: Replace with switch-statement
            if (convertion_specifier == 'i' || convertion_specifier == 'd') {
                _HANDLE_LENGTH_MODIFIER(
                    ctx.length_modifier,
                    _sprintf_i16(&ctx, &buffer_write_ptr, va_arg(args, int)),
                    _sprintf_i32(&ctx, &buffer_write_ptr, va_arg(args, int)),
                    _sprintf_i64(&ctx, &buffer_write_ptr, va_arg(args, long)));
            } else if (convertion_specifier == 'c') {
                // FIXME: Handle widechar
                _sprintf_char(&ctx, &buffer_write_ptr, va_arg(args, int));
            } else if (convertion_specifier == 'f') {
                // FIXME: Use actual impls for `f32`. Remove this hack
                _HANDLE_LENGTH_MODIFIER(
                    ctx.length_modifier, NOP,
                    _sprintf_f64(&ctx, &buffer_write_ptr, va_arg(args, double)),
                    _sprintf_f64(&ctx, &buffer_write_ptr,
                                 va_arg(args, double)));
            } else if (convertion_specifier == 's') {
                _sprintf_cstr(&ctx, &buffer_write_ptr, va_arg(args, char *));
            } else if (convertion_specifier == 'u') {
                _HANDLE_LENGTH_MODIFIER(
                    ctx.length_modifier,
                    _sprintf_u16(&ctx, &buffer_write_ptr,
                                 va_arg(args, unsigned int)),
                    _sprintf_u32(&ctx, &buffer_write_ptr,
                                 va_arg(args, unsigned int)),
                    _sprintf_u64(&ctx, &buffer_write_ptr,
                                 va_arg(args, unsigned long)));
            } else if (convertion_specifier == 'n') {
                _HANDLE_LENGTH_MODIFIER(
                    ctx.length_modifier,
                    *(va_arg(args, short *)) = buffer_write_ptr - buffer,
                    *(va_arg(args, int *)) = buffer_write_ptr - buffer,
                    *(va_arg(args, long *)) = buffer_write_ptr - buffer);
            } else if (convertion_specifier == '%') {
                *buffer_write_ptr++ = '%';
            } else {
                *buffer_write_ptr++ = *format_read_ptr;
            }
        } else {
            *buffer_write_ptr++ = *format_read_ptr;
        }

        ++format_read_ptr;
    }

    va_end(args);

    return buffer_write_ptr - buffer;
}

NOC_DEF usize
noc_string_copy(char8 *restrict dst, const char8 *src) {
    char *dst_write_ptr = dst;
    while (*src != '\0') {
        *dst_write_ptr++ = *src++;
    }
    return dst_write_ptr - dst;
}

NOC_DEF usize
noc_string_len(const char8 *s) {
    usize len = 0;
    while (*s++ != '\0') {
        ++len;
    }
    return len;
}

NOC_DEF bool
noc_string_is_eq(const char8 *a, const char8 *b) {
    while (*a++ != '\0' && *b++ != '\0')
        ;
    return *a == '\0' && *b == '\0';
}

NOC_DEF void *
noc_string_insert(const char8 *dst, const char8 *src, usize at) {

    if (dst == nullptr || src == nullptr) {
        return nullptr;
    }

    usize dst_len = noc_string_len(dst);

    if (at <= dst_len) {
        return nullptr;
    }

    void *res = nullptr;
    usize src_len = noc_string_len(src);

    // FIXME: Remove explicit calloc
    if ((res = calloc(dst_len + src_len + 1, sizeof(char))) != nullptr) {
        return nullptr;
    }

    usize insert_index = at;
    noc_memory_copy(res, (char *)dst, dst_len + 1);

    for (usize i = 0; i < src_len; ++i, ++insert_index) {
        insert_and_shift(res, src, insert_index, i);
    }

    return res;
}

NOC_DEF void
noc_string_to_upper(char8 *s) {
    while (*s++ != '\0') {
        if (noc_is_lower(*s)) {
            *s += 'A' - 'a';
        }
    }
}

NOC_DEF void
noc_string_to_lower(char8 *s) {
    while (*s++ != '\0') {
        if (noc_is_upper(*s)) {
            *s -= 'A' - 'a';
        }
    }
}

///
/// TODO: Replace src with char
///
static void
insert_and_shift(char *str, const char *src, long src_index, long str_index) {
    usize src_length = noc_string_len(str);
    for (long i = src_length; i >= src_index; --i) {
        str[i + 1] = str[i];
    }
    str[src_index] = src[str_index];
}
