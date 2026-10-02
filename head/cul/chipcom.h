/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef CUL_CHIPCOM_H
#define CUL_CHIPCOM_H 1

#include <cul/soc.h>

/* XXX: This should be made per-chip and lowered */
#define CHIP_ROM_CAP 0x40000000

/* Maximum number of processors */
#define CHIP_MAX_HART 16

/*
 * Initialize I/O devices that are alongside the chip
 *
 * Returns zero on success
 */
int chip_init_io(struct soc_info *soc);

#endif  /* !CUL_CHIPCOM_H */
