/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <cul/chipcom.h>
#include <bus/mainbus.h>

#define ROM_BASE  0x00000000

static int
chip_rom_init(struct soc_info *soc)
{
    struct mainbus_endpoint *ep;
    int error;

    error = mainbus_resolve(ROM_BASE, &ep);
    if (error < 0) {
        return error;
    }

    ep->data = &soc->rom;
    return 0;
}

int
chip_init_io(struct soc_info *soc)
{
    int error;

    if ((error = chip_rom_init(soc)) < 0) {
        return error;
    }

    return 0;
}
