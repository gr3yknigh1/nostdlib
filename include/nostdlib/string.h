#ifndef NOSTDLIB_STRING_H_
#define NOSTDLIB_STRING_H_

#include "nostdlib/macros.h"
#include "nostdlib/types.h"

NOC_DEF usize noc_string_format(char *buffer, const char *format, ...);

/*
 * Copies string from `src` to `dst` until '\0' in `src`.
 *
 * :returns: Bytes written in `dst`
 * */
NOC_DEF usize noc_string_copy(char *restrict dst, const char *src);

NOC_DEF usize noc_string_len(const char *s);

NOC_DEF bool noc_string_is_eq(const char *a, const char *b);

/*
 * TODO: Insert allocator
 * */
NOC_DEF void *noc_string_insert(const char *src, const char *str,
                                usize start_index);

NOC_DEF void noc_string_to_upper(char *s);
NOC_DEF void noc_string_to_lower(char *s);

#endif // NOSTDLIB_STRING_H_
