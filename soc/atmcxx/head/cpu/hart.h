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
#define OPCODE_ADDI  0x06

/* Instruction type */
typedef uint32_t inst_t;

/*
 * Represents the format of an A-type instruction.
 *
 * @opcode:   Operation code
 * @rd:       Destination register
 * @imm:      Immediate value
 */
union inst_a_type {
    struct {
        uint32_t opcode : 8;
        uint32_t rd     : 5;
        uint32_t rs1    : 5;
        uint32_t imm    : 14;
    };
    uint32_t inst;
};

/*
 * Represents valid register IDs
 */
typedef enum {
    REG_G0  = 0x00,
    REG_G1  = 0x01,
    REG_G2  = 0x02,
    REG_G3  = 0x03,
    REG_G4  = 0x04,
    REG_G5  = 0x05,
    REG_G6  = 0x06,
    REG_SP  = 0x07,
    REG_FP  = 0x08,
    REG_RA  = 0x09,
    REG_A0  = 0x0A,
    REG_A1  = 0x0B,
    REG_A2  = 0x0C,
    REG_A3  = 0x0D,
    REG_A4  = 0x0E,
    REG_A5  = 0x0F,
    REG_A6  = 0x10,
    REG_A7  = 0x11,
    REG_LST = 0x12,
    REG_TLS = 0x13,
    REG_PC  = 0x14,
    REG_MAX
} reg_t;

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
