/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <cul/soc.h>
#include <cul/chipcom.h>
#include <chip/soc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

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

/*
 * TODO: Destroy the RAM lazy buffer
 */
void
soc_destroy(struct soc_info *soc)
{
    if (soc == NULL) {
        return;
    }

    free(soc->data);
    soc->data = NULL;
}
