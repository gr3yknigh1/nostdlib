#ifndef NOSTDLIB_STRING_H_
#define NOSTDLIB_STRING_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_DEF usize noc_string_format(char8 *buffer, const char8 *format, ...);

/*
 * Copies string from `src` to `dst` until '\0' in `src`.
 *
 * :returns: Bytes written in `dst`
 * */
NOC_DEF usize noc_string_copy(char8 *restrict dst, const char8 *src);

NOC_DEF usize noc_string_len(const char8 *s);

NOC_DEF bool noc_string_is_eq(const char8 *a, const char8 *b);

/*
 * TODO: Insert allocator
 * */
NOC_DEF void *noc_string_insert(const char8 *src, const char8 *str,
                                usize start_index);

NOC_DEF void noc_string_to_upper(char8 *s);
NOC_DEF void noc_string_to_lower(char8 *s);

#endif // NOSTDLIB_STRING_H_
