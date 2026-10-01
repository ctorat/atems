/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef CUL_SOC_H
#define CUL_SOC_H 1

#include <io/rom.h>

/*
 * Represents a System-on-Chip
 *
 * @rom:    On-chip ROM
 *
 * XXX: Must not fall out of scope for the entire operation
 *      of the VM.
 */
struct soc_info {
    struct romdev rom;
};

#endif  /* !CUL_SOC_H */
