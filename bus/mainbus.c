/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <bus/mainbus.h>
#include <errno.h>

int
mainbus_read(uintptr_t addr, void *dest, size_t off, size_t len)
{
    struct mainbus_endpoint *ep;
    int error;
    size_t delta;

    if (dest == NULL || len == 0) {
        errno = EINVAL;
        return -1;
    }

    error = mainbus_resolve(addr, &ep);
    if (error < 0) {
        return -1;
    }

    delta = addr - ep->start;
    return ep->read(ep->data, dest, delta, len);
}
