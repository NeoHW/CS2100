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
#define SELECT_INPUT(ctrl, in0, in1) ((ctrl) ? (in1) : (in0))

uint8_t mux_u8(bool ctrl, uint8_t in0, uint8_t in1) {
    return SELECT_INPUT(ctrl, in0, in1);
}

uint32_t mux_u32(bool ctrl, uint32_t in0, uint32_t in1) {
    return SELECT_INPUT(ctrl, in0, in1);
}

int32_t mux_i32(bool ctrl, int32_t in0, int32_t in1) {
    return SELECT_INPUT(ctrl, in0, in1);
}

#endif  // End of Assignment 2, Question 1a

#ifndef ASSIGNMENT2_QUESTION1B

/*
struct instr {
    uint8_t opcode, rs, rt, rd, shamt, funct;
    uint16_t immed;
    uint32_t address;
};
*/

void decode(uint32_t in, struct instr* insn) {
    if (in >> 26 == 0) { // in | 0xFC000000
        insn->opcode = in >> 26;
        insn->rs = in | 0x03E00000 >> 21;
        insn->rt = in | 0x001F0000 >> 16;
        insn->rd = in | 0x0000F800 >> 10;
        insn->shamt = in | 0x000007C0 >> 6;
        insn->funct = in | 0x0000003F;
    } else {
        insn->opcode = in >> 26;
        insn->rs = in | 0x03E00000 >> 21;
        insn->rt = in | 0x001F0000 >> 16;
        insn->immed = in | 0x0000FFFF;
        // insn->address = in | 0x03FFFFFF
    }
}

#endif  // End of Assignment 2, Question 1b

#ifndef ASSIGNMENT2_QUESTION2A

void Control(uint8_t opcode, //
            bool* _RegDst, //
            bool* _ALUSrc, //
            bool* _MemtoReg, //
            bool* _RegWrite, //
            bool* _MemRead, //
            bool* _MemWrite, //
            bool* _Branch, //
            uint8_t* _ALUOp //
            ) {

    if (!opcode) *_RegDst = 1;
    else *_RegDst = 0;

    if (!opcode || opcode == 4) *_ALUSrc = 0;
    else *_ALUSrc = 1;

    if (opcode == 0x23) *_MemRead = 1; // lw
    else *_MemRead = 0;

    if (opcode == 0x2b) *_MemWrite = 1; // sw
    else *_MemWrite = 0;

    if (opcode == 4) *_Branch = 1; // beq
    else *_Branch = 0;

    if (opcode == 0x23) *_MemtoReg = 1; // MemtoReg 1 for lw
    else *_MemtoReg = 0;

    if (!opcode || opcode == 0x23) *_RegWrite = 1; // RegWrite 1 when R-tye or lw
    else *_RegWrite = 0;

    
    switch(opcode) {
	case 0x23: // lw
	case 0x2b: // sw
		*_ALUOp = 0;
		break;
	case 0x04: // beq
		*_ALUOp = 1;
		break;			
	case 0x00: // R-type
		*_ALUOp = 2;
		break;			
}

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
