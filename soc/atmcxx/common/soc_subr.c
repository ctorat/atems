/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <cul/soc.h>
#include <cul/chipcom.h>
#include <cpu/hart.h>
#include <chip/soc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

static int
soc_init_harts(struct chip_soc_info *chip_soc, const struct soc_init_param *param)
{
    size_t hart_list_sz, i;
    int error;

    if (chip_soc == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* Allocate a hart list */
    hart_list_sz = sizeof(struct cpu_hart) * param->nr_hart;
    chip_soc->harts = malloc(hart_list_sz);
    if (chip_soc->harts == NULL) {
        errno = ENOMEM;
        return -1;
    }

    /* Initialize each hart */
    for (i = 0; i < param->nr_hart; ++i) {
        error = cpu_init_hart(&chip_soc->harts[i]);
        if (error < 0) {
            free(chip_soc->harts);
            return -1;
        }
    }

    chip_soc->nr_hart = param->nr_hart;
    return 0;
}

int
soc_init(struct soc_info *soc, const struct soc_init_param *param)
{
    struct chip_soc_info *chip_soc;
    int error;

    if (soc == NULL || param == NULL) {
        errno = EINVAL;
        return -1;
    }

    chip_soc = malloc(sizeof(struct chip_soc_info));
    if (chip_soc == NULL) {
        errno = ENOMEM;
        return -1;
    }

    error = lazybuf_init(&chip_soc->ram, param->ram_cap);
    if (error < 0) {
        perror("lazybuf_init");
        free(chip_soc);
        return -1;
    }

    error = soc_init_harts(chip_soc, param);
    if (error < 0) {
        perror("soc_init_harts");
        free(chip_soc);
        return -1;
    }

    soc->data = chip_soc;
    error = chip_init_io(soc);
    if (error < 0) {
        perror("chip_init_io");
        free(chip_soc);
        soc->data = NULL;
        return -1;
    }

    return 0;
}

int
soc_emul_run(struct soc_info *soc)
{
    struct chip_soc_info *chip_soc;

    if (soc == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* TODO: Support multi-hart processing */
    chip_soc = soc->data;
    return cpu_run_hart(&chip_soc->harts[0]);
}

void
soc_destroy(struct soc_info *soc)
{
    struct chip_soc_info *chip_soc;

    if (soc == NULL) {
        return;
    }

    if ((chip_soc = soc->data) == NULL) {
        return;
    }

    lazybuf_destroy(&chip_soc->ram);
    free(soc->data);
    soc->data = NULL;
}
