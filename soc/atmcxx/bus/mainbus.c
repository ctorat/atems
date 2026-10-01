/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <bus/mainbus.h>
#include <common/comdef.h>
#include <errno.h>

static struct mainbus_endpoint memory_map[] = {
    /* Boot ROM */
    {
        0x000000000000,
        0x000000002000,
        NULL
    },

    /* System-level cache */
    {
        0x000000005000,
        0x000000105000,
        NULL
    }
};

int
mainbus_resolve(uintptr_t addr, struct mainbus_endpoint *ep_res)
{
    struct mainbus_endpoint *ep;
    size_t i;

    if (ep_res == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (i = 0; i < NELEM(memory_map); ++i) {
        ep = &memory_map[i];
        if (addr >= ep->start && addr < ep->end) {
            *ep_res = *ep;
            return 0;
        }
    }

    errno = ENODEV;
    return -1;
}
