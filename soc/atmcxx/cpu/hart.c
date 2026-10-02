/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <common/trace.h>
#include <bus/mainbus.h>
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

int
cpu_run_hart(struct cpu_hart *hart)
{
    struct cpu_regs *regs;
    uint8_t opcode;
    int error, retval = 0;
    inst_t inst;

    if (hart == NULL) {
        errno = EINVAL;
        return -1;
    }

    regs = &hart->regs;
    for (;;) {
        /*
         * Instructions must be fetched on a 4-byte boundary, otherwise we are to
         * throw an instruction fetch fault.
         *
         * TODO: Actually throw an exception rather than terminating VM execution.
         */
        if ((regs->pc & (4 - 1)) != 0) {
            trace_fatal("misaligned instruction fetch @ %016lX\n", regs->pc);
            retval = -1;
            break;
        }

        error = mainbus_read(regs->pc, &inst, 0, sizeof(inst));
        if (error < 0) {
            trace_fatal("mainbus error during instruction fetch\n");
            retval = -1;
            break;
        }

        opcode = inst & 0xFF;
        switch (opcode) {
        case OPCODE_NOP:
            regs->pc += sizeof(inst);
            break;
        case OPCODE_WFI:
            /* TODO: This needs to be handled more correctly */
            break;
        case OPCODE_SPW:
            /* Unused in the emulator (for now at least) */
            regs->pc += sizeof(inst);
            break;
        default:
            trace_fatal("undefined opcode %02X\n", opcode);
            return -1;
        }
    }

    return retval;
}
