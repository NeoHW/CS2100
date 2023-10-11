#include <stdio.h>
#include <stdlib.h>

#include "mips.h"

const char *regName[] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2",
                         "$a3",   "$t0", "$t1", "$t2", "$t3", "$t4", "$t5",
                         "$t6",   "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
                         "$s5",   "$s6", "$s7", "$t8", "$t9", "$k0", "$k1",
                         "$gp",   "$sp", "$fp", "$ra", 0};

// Do not modify the dumping routines. They will be used for grading as it is.
void dumpControl() {
    printf("RegDst   = %x\n", _RegDst);
    printf("RegWrite = %x\n", _RegWrite);
    printf("ALUSrc   = %x\n", _ALUSrc);
    printf("MemRead  = %x\n", _MemRead);
    printf("MemWrite = %x\n", _MemWrite);
    printf("MemtoReg = %x\n", _MemtoReg);
    printf("Branch   = %x\n", _Branch);
    printf("ALUOp    = %x\n", _ALUOp);
    printf("ALUCtrl  = %x\n", _ALUCtrl);
}

void dumpPC() {
    printf("PC = 0x%08x\n", _PC);
}

void initRegs() {
    uint32_t addr;
    FILE *fp = NULL;
    char buf[128], type;

    // Initial _PC
    _PC = rand() & 0x3FFFF0;

    // Initialize
    _RF[0] = 0;
    for (addr = 1; addr < 32; addr++) {
        _RF[addr] = rand();
    }
}

void dumpRF() {
    int i;

    for (i = 0; i < 32; i++) {
        printf("%s (r%d) \t= 0x%08x (%d)\n", regName[i], i, _RF[i], _RF[i]);
    }
}

int main(int argc, char *argv[]) {
    uint32_t insn;
    int stat;
    const char *init_regs = NULL;

    /* Read the input found in argv[1] which must be of the form "0x...". */
    if (argc < 2) {
        error("Usage: %s <instruction>\n", argv[0]);
    }

    stat = sscanf(argv[1], "0x%x", &insn);
    if (stat != 1) {  // Argument read failure. Exit...
        error("Attempt to read in arg[1] and convert failed. Exiting...\n");
    }

    if (argc > 2) {
        srand(insn);
    }
    initRegs();

    dumpRF();
    dumpPC();
    printf("=======================================================\n");

    execute(insn);

    dumpControl();
    dumpRF();
    dumpPC();
}
