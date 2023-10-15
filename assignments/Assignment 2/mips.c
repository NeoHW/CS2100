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
#define SELECT_INPUT() return (ctrl) ? (in1) : (in0)

#ifndef ASSIGNMENT2_QUESTION1A

uint8_t mux_u8(bool ctrl, uint8_t in0, uint8_t in1) {
    SELECT_INPUT();
}

uint32_t mux_u32(bool ctrl, uint32_t in0, uint32_t in1) {
    SELECT_INPUT();
}

int32_t mux_i32(bool ctrl, int32_t in0, int32_t in1) {
    SELECT_INPUT();
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

    insn->opcode = in >> 26;
    insn->rs = (in & 0x03E00000) >> 21;
    insn->rt = (in & 0x001F0000) >> 16;
    insn->rd = (in & 0x0000F800) >> 11;
    insn->shamt = (in & 0x000007C0) >> 6;
    insn->funct = in & 0x0000003F;
    insn->immed = in & 0x0000FFFF;
    insn->address = in & 0x03FFFFFF;   

    printf("\nopcode %d", insn->opcode);
    printf("\nrs %d", insn->rs);
    printf("\nrt %d", insn->rt);
    printf("\nrd %d", insn->rd);
    printf("\nshamt %d", insn->shamt);
    printf("\nfunct %d", insn->funct);
    printf("\nimmed %d", insn->immed);
    printf("\naddress %d", insn->address);
    printf("\n");
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
    if (ALUOp == 2) { // R-type instruction
		switch (funct) {
			case 0x20:      // add
                return 2;
			case 0x22:      // sub
                return 6;
			case 0x24:      // and
                return 0;
			case 0x25:      // or
                return 1;
			case 0x27:      // nor
                return 0xC;
			case 0x2a:      // slt
                return 7;
			default:
                error("Invalid funct code in R-type instruction\n");
        }
	} else { // Non R-type
		if (ALUOp == 0)
		   return 2; // Ask ALU to add (lw/sw)
		if (ALUOp == 1)
		   return 6; // Ask ALU to sub (beq)
        return -1;  // to solve warning
	}
}

#endif  // End of Assignment 2, Question 2b

#ifndef ASSIGNMENT2_QUESTION2C

int32_t ALU(int32_t in0, int32_t in1, uint8_t ALUControl, bool* ALUiszero) {
    int32_t result;
	switch (ALUControl) {
		case 0: // and
			result = in0 & in1;
			break;
		case 1: // or
			result = in0 | in1;
			break;
		case 2: // add
			result = in0 + in1;
			break;
		case 6: // sub
			result = in0 - in1;
			break;
		case 7: // slt
			result = (int32_t)(in0 < in1);
			break;
		case 12: // nor
			result = ~(in0 | in1);
			break;
	}
	*ALUiszero = (result == 0);
	return(result);
}

#endif  // End of Assignment 2, Question 2c

#ifndef ASSIGNMENT2_QUESTION3

void execute(uint32_t insn) {
    // pointers to the control signals    
    bool *RegDst = &_RegDst;
    bool *ALUSrc = &_ALUSrc;
    bool *MemtoReg = &_MemtoReg;
    bool *RegWrite = &_RegWrite;
    bool *MemRead = &_MemRead;
    bool *MemWrite = &_MemWrite;
    bool *Branch = &_Branch;
    uint8_t *ALUOp = &_ALUOp;
    uint8_t *ALUCtrl = &_ALUCtrl;
    bool *ALUiszero = malloc(1);
    
    // decode stage
    struct instr *i = malloc(sizeof(struct instr));
    decode(insn, i);

    // Generate the control Signals
    Control(i->opcode, RegDst, ALUSrc, MemtoReg, RegWrite, MemRead, MemWrite, Branch, ALUOp);
    *ALUCtrl = ALUControl(*ALUOp, i->funct);
    
    // registers
    uint8_t RR1 = i->rs;
    uint8_t RR2 = i->rt;
    uint8_t WR = mux_u8(*RegDst,i->rt,i->rd);
    // int32_t WD; // to be computed later from MemToReg
    int32_t *RD1 = &_RF[RR1];
    int32_t *RD2 = &_RF[RR2];

    // operands 1 & 2 for ALU
    int32_t ALUop1 = *RD1;
    int32_t ALUop2 = mux_i32(*ALUSrc, *RD2, i->immed);

    // ALU stage
    uint32_t result = ALU(ALUop1,ALUop2, *ALUCtrl, ALUiszero);

    // PCSrc control signal
    bool PCSrc = *Branch & *ALUiszero;
    // calculating branch target address / Updating PC
    uint32_t PCSrcInputOne = _PC + 4;
    uint32_t PCSrcInputTwo = (_PC + 4) + (i->immed << 2);
    uint32_t PCaddress = mux_u32(PCSrc, PCSrcInputOne, PCSrcInputTwo);

    // Memory stage
    uint32_t memStageAddress = result;
    uint32_t WriteData = *RD2;
    uint32_t memReadData = Memory(memStageAddress, WriteData, *MemRead, *MemWrite);

    // Writeback
    uint32_t WD = mux_u32(*MemtoReg, result, memReadData);

    // update regfile
    RegFile(RR1, RR2, WR, WD, RD1, RD2, *RegWrite);

    // Set PC address to target PC address
    _PC = PCaddress;

}

#endif  // End of Assignment 2, Question 3
