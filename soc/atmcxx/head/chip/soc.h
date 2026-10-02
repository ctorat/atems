/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef CHIP_SOC_H
#define CHIP_SOC_H 1

#include <stdint.h>
#include <stddef.h>
#include <common/lazybuf.h>
#include <cpu/hart.h>

/*
 * Chip specific SoC information
 *
 * @ram:        Random access memory
 * @harts:      Processor execution units
 * @nr_hart:    Number of harts in use
 */
struct chip_soc_info {
    struct lazybuf ram;
    struct cpu_hart *harts;
    size_t nr_hart;
};

#endif  /* !CHIP_SOC_H */
