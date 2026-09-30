/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <common/lazybuf.h>
#include <common/trace.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int
lazybuf_init(struct lazybuf *lp, size_t cap)
{
    if (lp == NULL || cap < LAZYBUF_INITIAL_SIZE) {
        errno = EINVAL;
        return -1;
    }

    lp->cap = cap;
    lp->size = LAZYBUF_INITIAL_SIZE;
    lp->data = malloc(lp->size);

    if (lp->data == NULL) {
        trace_error("out of memory while allocating lazybuf\n");
        errno = ENOMEM;
        return -1;
    }

    return 0;
}

int
lazybuf_write(struct lazybuf *lp, size_t off, size_t count, const void *source)
{
    uint8_t *dest;
    void *tmp;
    size_t newsize;

    if (lp == NULL || source == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (lp->size == 0) {
        errno = EINVAL;
        return -1;
    }

    /* Do not exceed the maximum capacity */
    if ((off + count) > lp->cap || off > lp->cap) {
        errno = EOVERFLOW;
        return -1;
    }

    /*
     * If the offset plus the count is greater than the current
     * size, resize the buffer to the sum of `off` and `count`.
     */
    if ((off + count) > lp->size) {
        newsize = off + count;
        tmp = realloc(lp->data, newsize);
        if (tmp == NULL) {
            errno = ENOMEM;
            return -1;
        }

        dest = tmp;
        memset(&dest[lp->size], 0, newsize - lp->size);
        lp->size = newsize;
        lp->data = tmp;
    }

    dest = lp->data;
    memcpy(&dest[off], source, count);
    return 0;
}

int
lazybuf_read(struct lazybuf *lp, size_t off, size_t count, void *dest)
{
    size_t real_size, delta;

    if (lp == NULL) {
        errno = EINVAL;
        return -1;
    }

    if ((off + count) > lp->cap || off > lp->cap) {
        errno = EOVERFLOW;
        return -1;
    }

    /*
     * Zero the whole buffer if the offset exceeds
     * the size of the lazy buffer.
     */
    if (off >= lp->size) {
        memset(dest, 0, count);
        return 0;
    }

    /* Compute the real size */
    real_size = count;
    if ((count + off) > lp->size) {
        delta = (count + off) - lp->size;
        real_size = count - delta;
        memset(&((char *)dest)[real_size], 0, delta);
    }

    memcpy(dest, &((char *)lp->data)[off], real_size);
    return 0;
}
