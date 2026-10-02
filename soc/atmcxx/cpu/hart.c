/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <cpu/hart.h>
#include <string.h>
#include <errno.h>

/*
 * Initialize per-hart registers
 *
 * @regs:  Register set to initialize
 */
static void
hart_init_regs(struct cpu_regs *regs)
{
    if (regs == NULL) {
        return;
    }

    memset(regs, 0, sizeof(*regs));
}

int
cpu_init_hart(struct cpu_hart *hart)
{
    struct cpu_regs *regs;

    if (hart == NULL) {
        errno = EINVAL;
        return -1;
    }

    regs = &hart->regs;
    hart_init_regs(regs);
    return 0;
}
