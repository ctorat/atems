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
 * @data:   Chip specific data
 *
 * XXX: Must not fall out of scope for the entire operation
 *      of the VM.
 */
struct soc_info {
    struct romdev rom;
    void *data;
};

/*
 * SoC initialization parameters
 *
 * @ram_cap:  RAM capacity
 * @nr_hart:  Number of harts
 */
struct soc_init_param {
    size_t ram_cap;
    size_t nr_hart;
};

/*
 * Initialize the SoC descriptor
 *
 * @soc:    SoC to initialize
 * @param:  Initialization parameters
 *
 * XXX: This function is chip specific
 *
 * Returns zero on success
 */
int soc_init(struct soc_info *soc, const struct soc_init_param *param);

/*
 * Begin SoC emulation
 *
 * @soc:   SoC descriptor to begin emulating
 *
 * Returns zero on success
 */
int soc_emul_run(struct soc_info *soc);

/*
 * Destroy a SoC descriptor
 *
 * @soc:  SoC descriptor to destroy
 */
void soc_destroy(struct soc_info *soc);

#endif  /* !CUL_SOC_H */
