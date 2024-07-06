/*
 * Dynamic array.
 * */
#if !defined(NOSTDLIB_DYNAMIC_ARRAY_H_)
#define NOSTDLIB_DYNAMIC_ARRAY_H_

#include "nostdlib/types.h"

typedef struct {
    void *items;
    usize item_size;
    u64 item_count;
    u64 item_capacity;
} noc_darray_t;

#define NOC_DARRAY_FREE_SPACE_BEGIN(__DARRAY_PTR)                              \
    ((__DARRAY_PTR)->item_count * (__DARRAY_PTR)->item_size)
#define NOC_DARRAY_BUFFER_CAPACITY_BYTES(__DARRAY_PTR)                         \
    ((__DARRAY_PTR)->item_capacity * (__DARRAY_PTR)->item_size)
#define NOC_DARRAY_FOREACH(__DARRAY_PTR, __TYPE, __IT)                         \
    for (__TYPE *__IT = (__DARRAY_PTR)->items;                                 \
         __IT !=                                                               \
         ((__TYPE *)(__DARRAY_PTR)->items) + (__DARRAY_PTR)->item_count;       \
         __IT++)

/*
 * Dynamic array initalization function
 */
NOC_DEF void noc_darray_init(noc_darray_t *out_s, u64 item_capacity,
                             usize item_size);

/*
 * Copies item and pushes it at the and of buffer
 */
NOC_DEF void noc_darray_push(noc_darray_t *s, void *item);

/*
 * Just moving pointer of buffer end to the left by `item_size`. And copies to
 * the `out_item` ptr last item value
 */
NOC_DEF void noc_darray_pop(noc_darray_t *s, void *out_item);

/*
 * Assigning `out_ptr_item` to value of last item address
 */
NOC_DEF void noc_darray_peek(const noc_darray_t *s,
                             void const **const out_ptr_item);

/*
 * Deallocates inner buffer and setting all stats except `item_size` to zero
 */
NOC_DEF void noc_darray_free(noc_darray_t *s);

#endif // NOSTDLIB_DYNAMIC_ARRAY_H_
