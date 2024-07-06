#include "nostdlib/dynamic_array.h"

#include "nostdlib/memory.h"

#include <stdlib.h>

void
noc_darray_init(noc_darray_t *out_s, u64 item_capacity, usize item_size) {
    *out_s = (noc_darray_t){
        .items = malloc(item_size * item_capacity),
        .item_size = item_size,
        .item_count = 0,
        .item_capacity = item_capacity,
    };
}

void
noc_darray_push(noc_darray_t *s, void *item) {
    if (s->item_count + 1 >= s->item_capacity) {
        usize new_capacity = NOC_DARRAY_BUFFER_CAPACITY_BYTES(s) * 2;
        s->items = realloc(s->items, new_capacity);
        s->item_capacity *= 2;
    }

    usize offset = NOC_DARRAY_FREE_SPACE_BEGIN(s);
    noc_memory_copy(((byte *)s->items) + offset, item, s->item_size);
    s->item_count += 1;
}

void
noc_darray_pop(noc_darray_t *s, void *out_item) {
    if (s->item_count == 0) {
        return;
    }
    s->item_count -= 1;

    if (out_item != NULL) {
        noc_memory_copy(out_item,
                        ((char *)s->items) + s->item_count * s->item_size,
                        s->item_size);
    }
}

void
noc_darray_peek(const noc_darray_t *s, void const **const out_ptr_item) {
    if (s->item_count == 0) {
        return;
    }
    usize offset = NOC_DARRAY_FREE_SPACE_BEGIN(s);
    *out_ptr_item = s->items + offset - s->item_size;
    //                                  ^^^^^^^^^^^^^^^^^ - Substract size of
    //                                  last item
}

void
noc_darray_free(noc_darray_t *s) {
    free(s->items);
    s->items = NULL;
    s->item_count = 0;
    s->item_capacity = 0;
}
