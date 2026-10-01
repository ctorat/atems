/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef CHIP_SOC_H
#define CHIP_SOC_H 1

#include <stdint.h>
#include <stddef.h>
#include <common/lazybuf.h>

/*
 * Chip specific SoC information
 *
 * @ram: Random access memory
 */
struct chip_soc_info {
    struct lazybuf ram;
};

#endif  /* !CHIP_SOC_H */
