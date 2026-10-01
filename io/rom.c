/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <io/rom.h>
#include <io/romvar.h>
#include <errno.h>

int
rom_init_dev(struct romdev *romdev, size_t capacity)
{
    int error;

    if (romdev == NULL || capacity == 0) {
        errno = EINVAL;
        return -1;
    }

    error = lazybuf_init(&romdev->data, capacity);
    if (error < 0) {
        return error;
    }

    return 0;
}

int
rom_flash_dev(struct romdev *romdev, void *src, size_t len, size_t off)
{
    if (romdev == NULL || src == NULL ) {
        errno = EINVAL;
        return -1;
    }

    if (len == 0) {
        errno = EINVAL;
        return -1;
    }

    return lazybuf_write(&romdev->data, off, len, src);
}

int
rom_bus_read(void *romdev, void *dest, size_t off, size_t len)
{
    struct romdev *rdp;

    if (romdev == NULL || dest == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (len == 0) {
        errno = EINVAL;
        return -1;
    }

    rdp = (struct romdev *)romdev;
    return lazybuf_read(&rdp->data, off, len, dest);
}
