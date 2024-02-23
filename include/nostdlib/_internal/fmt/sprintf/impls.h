#ifndef NOSTDLIB__INTERNAL_FMT_SPRINTF_IMPLS_H_
#define NOSTDLIB__INTERNAL_FMT_SPRINTF_IMPLS_H_

#include "nostdlib/_internal/fmt/parser.h"
#include "nostdlib/types.h"

void _sprintf_i16(struct _fmt_context *ctx, char **buffer_write_ptr, i16 value);
void _sprintf_i32(struct _fmt_context *ctx, char **buffer_write_ptr, i32 value);
void _sprintf_i64(struct _fmt_context *ctx, char **buffer_write_ptr, i64 value);

void _sprintf_u16(struct _fmt_context *ctx, char **buffer_write_ptr, u16 value);
void _sprintf_u32(struct _fmt_context *ctx, char **buffer_write_ptr, u32 value);
void _sprintf_u64(struct _fmt_context *ctx, char **buffer_write_ptr, u64 value);

void _sprintf_f32(struct _fmt_context *ctx, char **buffer_write_ptr, f32 value);
void _sprintf_f64(struct _fmt_context *ctx, char **buffer_write_ptr, f64 value);

void _sprintf_char(struct _fmt_context *ctx, char **buffer_write_ptr,
                   char value);
void _sprintf_cstr(struct _fmt_context *ctx, char **buffer_write_ptr,
                   const char *value);

#endif // NOSTDLIB__INTERNAL_FMT_SPRINTF_IMPLS_H_
