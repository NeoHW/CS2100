#include "mips.h"

/******************************************************************************
 *      DO NOT MODIFY THE CODE BELOW
 ******************************************************************************/
#ifndef CS2100_ROUTINE_MASK_OUT
uint32_t _PC;
int32_t _RF[32]                   = {0};
int32_t _DataMemory[MAX_MEM >> 2] = {0};

// All the control signals needed
bool _RegDst;
bool _ALUSrc;
bool _MemtoReg;
bool _RegWrite;
bool _MemRead;
bool _MemWrite;
bool _Branch;
uint8_t _ALUOp;
uint8_t _ALUCtrl;

void RegFile(uint8_t RR1, uint8_t RR2, uint8_t WR, int32_t WD, int32_t* RD1,
             int32_t* RD2, bool RegWrite) {
    // Because we need to send out multiple outputs,
    // we will use passing by pointers.
    *RD1 = (RR1 > 0) ? _RF[RR1] : 0;
    *RD2 = (RR2 > 0) ? _RF[RR2] : 0;

    if (RegWrite && WR) _RF[WR] = WD;
}

int32_t Memory(uint32_t Address, int32_t WrData, bool MemRead, bool MemWrite) {
    // We can do a sanity check here.
    // You can at most do one memory operation.
    // Will assume that "error" raises hell.
    if (MemRead && MemWrite) {
        error("Cannot do both read and write at the same time.");
    }

    if (!(MemRead || MemWrite)) {
        return 0;
    }

    if ((Address > MAX_MEM) || (Address > MAX_MEM)) {
        error("Address %u is out of range. Simulator exiting...\n", Address);
    }

    if (MemRead) {
        return _DataMemory[Address >> 2];
    }

    if (MemWrite) {
        _DataMemory[Address >> 2] = WrData;
    }

    return 0;
}
#endif
/******************************************************************************
 *      DO NOT MIDIFY THE CODE ABOVE
 ******************************************************************************/

// Here starts your code for Assignment 2 Part A
// If you need to define some macros, you can do so below this comment.

#ifndef ASSIGNMENT2_QUESTION1A

uint8_t mux_u8(bool ctrl, uint8_t in0, uint8_t in1) {
    if(ctrl) {
        return in1;
    } else {
        return in0;
    }
}

uint32_t mux_u32(bool ctrl, uint32_t in0, uint32_t in1) {
    if(ctrl) {
        return in1;
    } else {
        return in0;
    }
}

int32_t mux_i32(bool ctrl, int32_t in0, int32_t in1) {
    if(ctrl) {
        return in1;
    } else {
        return in0;
    }
}

#endif  // End of Assignment 2, Question 1a

#ifndef ASSIGNMENT2_QUESTION1B

void decode(uint32_t in, struct instr* insn) {
    // TODO: Implement decode
}

#endif  // End of Assignment 2, Question 1b

#ifndef ASSIGNMENT2_QUESTION2A

void Control(uint8_t opcode, bool* _RegDst, bool* _ALUSrc, bool* _MemtoReg,
             bool* _RegWrite, bool* _MemRead, bool* _MemWrite, bool* _Branch,
             uint8_t* _ALUOp) {
    // TODO: Implement Control
}

#endif  // End of Assignment 2, Question 2a

#ifndef ASSIGNMENT2_QUESTION2B

uint8_t ALUControl(uint8_t ALUOp, uint8_t funct) {
    // TODO: Implement ALUControl
    return -1;
}

#endif  // End of Assignment 2, Question 2b

#ifndef ASSIGNMENT2_QUESTION2C

int32_t ALU(int32_t in0, int32_t in1, uint8_t ALUControl, bool* ALUiszero) {
    // TODO: Implement ALU
    return -1;
}

#endif  // End of Assignment 2, Question 2c

#ifndef ASSIGNMENT2_QUESTION3

void execute(uint32_t insn) {
    // TODO: Implement execute
}

#endif  // End of Assignment 2, Question 3
