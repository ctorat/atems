/*
 * Copyright (c) 2026, Apollo Telephone Laboratories.
 * Provided under the BSD-3 clause.
 */

#ifndef CPU_HART_H
#define CPU_HART_H 1

#include <stdint.h>
#include <stddef.h>

/* Instruction opcodes */
#define OPCODE_NOP   0x01
#define OPCODE_WFI   0x02
#define OPCODE_SPW   0x03
#define OPCODE_RDMSR 0x04
#define OPCODE_WRMSR 0x05

/* Instruction type */
typedef uint32_t inst_t;

/*
 * Represents the processor registers of the ATMCXX
 *
 * @gpreg:  General purpose 'G' registers
 * @sp:     Stack pointer
 * @ra:     Return address
 * @argreg: Argument registers
 * @lst:    Local state pointer
 * @tls:    Thread local storage pointer
 * @pc:     Program counter
 */
struct cpu_regs {
    uint64_t gpreg[7];
    uint64_t sp;
    uint64_t ra;
    uint64_t argreg[8];
    uint64_t lst;
    uint64_t tls;
    uint64_t pc;
};

/*
 * Represents a hardware thread, a unit of execution
 * within a processor.
 *
 * @regs: Processor registers
 */
struct cpu_hart {
    struct cpu_regs regs;
};

/*
 * Initialize a hardware thread
 *
 * @hart:  HART to initialize
 *
 * Returns zero on success.
 */
int cpu_init_hart(struct cpu_hart *hart);

/*
 * Begin hart execution
 *
 * @hart:  Hart to run
 *
 * Returns non-zero values on fatal errors
 */
int cpu_run_hart(struct cpu_hart *hart);

#endif  /* !CPU_HART_H */
