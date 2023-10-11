#ifndef __CS2100_MIPS_H__
#define __CS2100_MIPS_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_MEM 4096

// error(...) is just a variadic macro wrapper to printf to stderr and then exit. 
// Use it for errors you do not want to recover from.
#define error(...)                    \
    {                                 \
        fprintf(stderr, __VA_ARGS__); \
        exit(-1);                     \
    }

// Multiplexers (Question 1a)
uint8_t mux_u8(bool ctrl, uint8_t in0, uint8_t in1);
uint32_t mux_u32(bool ctrl, uint32_t in0, uint32_t in1);
int32_t mux_i32(bool ctrl, int32_t in0, int32_t in1);

// Registers File
extern int32_t _RF[];
void RegFile(uint8_t RR1, uint8_t RR2, uint8_t WR, int32_t WD, int32_t* RD1,
             int32_t* RD2, bool RegWrite);

// Instruction Decoding (Question 1b)
// You are to use this struct. Do not modify this.
struct instr {
    uint8_t opcode, rs, rt, rd, shamt, funct;
    uint16_t immed;
    uint32_t address;
};
void decode(uint32_t in, struct instr* insn);

// Control Unit (Question 2a)
extern bool _RegDst;
extern bool _ALUSrc;
extern bool _MemtoReg;
extern bool _RegWrite;
extern bool _MemRead;
extern bool _MemWrite;
extern bool _Branch;
extern uint8_t _ALUOp;
void Control(uint8_t opcode, bool* _RegDst, bool* _ALUSrc, bool* _MemtoReg,
             bool* _RegWrite, bool* _MemRead, bool* _MemWrite, bool* _Branch,
             uint8_t* _ALUOp);

// ALU Control (Question 2b)
extern uint8_t _ALUCtrl;
uint8_t ALUControl(uint8_t ALUOp, uint8_t funct);

// ALU (Question 2c)
int32_t ALU(int32_t in0, int32_t in1, uint8_t ALUControl, bool* ALUiszero);

// Data Memory
extern int32_t _DataMemory[];
int32_t Memory(uint32_t Address, int32_t WrData, bool MemRead, bool MemWrite);

// Program Counter
extern uint32_t _PC;

// Assignment 2, Question 3
void execute(uint32_t insn);

#endif
