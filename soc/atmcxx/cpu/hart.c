/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#include <common/trace.h>
#include <common/comdef.h>
#include <bus/mainbus.h>
#include <cpu/hart.h>
#include <string.h>
#include <errno.h>

/* Safe regtab indexing macro */
#define REG_STR(ID)             \
    ((ID) >= NELEM(regtab))     \
        ? "bad"                 \
        : regtab[(ID)]

/*
 * Lookup table used to convert register IDs into
 * strings.
 *
 * XXX: Do not index directly, instead use REG_STR()
 */
static const char *regtab[] = {
    [REG_G0]  = "G0",
    [REG_G1]  = "G1",
    [REG_G2]  = "G2",
    [REG_G3]  = "G3",
    [REG_G4]  = "G4",
    [REG_G5]  = "G5",
    [REG_G6]  = "G6",
    [REG_SP]  = "SP",
    [REG_FP]  = "FP",
    [REG_RA]  = "RA",
    [REG_A0]  = "A0",
    [REG_A1]  = "A1",
    [REG_A2]  = "A2",
    [REG_A3]  = "A3",
    [REG_A4]  = "A4",
    [REG_A5]  = "A5",
    [REG_A6]  = "A6",
    [REG_A7]  = "A7",
    [REG_LST] = "LST",
    [REG_TLS] = "TLS"
};

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

/*
 * Read a register by ID
 *
 * @regs:  Register set to read
 * @id:    ID of register to read
 */
static uint64_t
hart_read_reg(struct cpu_regs *regs, reg_t id)
{
    if (regs == NULL || id >= REG_MAX) {
        return 0;
    }

    /* Obtain global or argument registers */
    if (id >= REG_G0 && id <= REG_G6)
        return regs->gpreg[id];
    if (id >= REG_A0 && id <= REG_A7)
        return regs->argreg[id - REG_A0];

    /* Obtain other registers */
    switch (id) {
    case REG_SP:
        return regs->sp;
    case REG_RA:
        return regs->ra;
    case REG_LST:
        return regs->lst;
    case REG_TLS:
        return regs->tls;
    default:
        return 0;
    }

    return 0;
}

/*
 * Dump the processor registers
 *
 * @regs: Registers to dump
 */
static void
hart_dump_regs(struct cpu_regs *regs)
{
    reg_t i;

    if (regs == NULL) {
        return;
    }

    for (i = 0; i < REG_MAX; ++i) {
        if ((i % 3) == 0 && i > 0) {
            printf("\n");
        }

        printf("%s=%016lX ", REG_STR(i), hart_read_reg(regs, i));
    }

    printf("\n");
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

        /* Don't cause log spam if we are waiting */
        if (opcode != OPCODE_WFI) {
            hart_dump_regs(regs);
        }
    }

    return retval;
}
