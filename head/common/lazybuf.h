/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef COMMON_LAZYBUF_H
#define COMMON_LAZYBUF_H 1

#include <stdint.h>
#include <stddef.h>

/* Initial size of a lazy buffer */
#define LAZYBUF_INITIAL_SIZE 8

/*
 * For optimization purposes, we require LAZYBUF_INITIAL_SIZE to
 * be a power-of-two value that is greater than two and (less strictly)
 * a value that is less than 64 unless we choose to support the use of
 * SIMD in the future... Otherwise you can tweak at your will.
 */
_Static_assert(
    (LAZYBUF_INITIAL_SIZE & (LAZYBUF_INITIAL_SIZE - 1)) == 0 &&
        LAZYBUF_INITIAL_SIZE > 2,
    "initial size must be greater than two and a power of two"
);

/*
 * Represents a lazy buffer that can be set to be capped at a
 * specific maximum while sized at a smaller value.
 *
 * @data: Data this buffer backs
 * @cap:  Maximum size data can grow
 * @size: Current size of data
 */
struct lazybuf {
    void *data;
    size_t cap;
    size_t size;
};

/*
 * Initialize a lazy buffer
 *
 * @lp:  Pointer to lazy buffer to initialize
 * @cap: Maximum size of lazy buffer
 */
int lazybuf_init(struct lazybuf *lp, size_t cap);

/*
 * Write to a given number of bytes at a specific offset within
 * a lazy buffer.
 *
 * @lp:     Lazy buffer pointer
 * @off:    Offset to write to in lazybuffer
 * @count:  Number of bytes to write
 * @source: Source buffer to write from
 */
int lazybuf_write(
    struct lazybuf *lp, size_t off,
    size_t count, const void *source
);

/*
 * Read from a lazybuffer into a specified buffer
 *
 * @lp:     Lazy buffer pointer
 * @off:    Offset to read from
 * @count:  Number of bytes to read
 * @dest:   Destination buffer to read into
 */
int lazybuf_read(
    struct lazybuf *lp, size_t off,
    size_t count, void *dest
);

#endif  /* !COMMON_LAZYBUF_H */
