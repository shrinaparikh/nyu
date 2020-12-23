//
//  r_instructions.c
//  
//
//  Created by shrina parikh on 11/29/19.
//

#include <stdio.h>

#include "cpu.h"

#include "utilities.h"



//for debugging purposes
//print_bits(registers[RS(instruction)]);
//print_bits(registers[RT(instruction)]);
//print_bits(registers[RD(instruction)]);

//defining the macros for extracting the fields
#define opcode(x) ((x >> 26) & 0x3F)

#define RS(x) ((x >> 21) & 0x1F)

#define RT(x) ((x >> 16) & 0x1F)

#define RD(x) ((x >> 11) & 0x1F)

#define shamt(x) ((x >> 6) & 0x1F)

#define funct(x) (x & (0x3F))


//These are the R-instructions implemented by the simulted MIPS processor

void add(unsigned int instruction) {
    registers[RD(instruction)] = (unsigned int)((int)registers[RS(instruction)] + (int)registers[RT(instruction)]);
}

void addu(unsigned int instruction) {
    registers[RD(instruction)] = (registers[RS(instruction)] + registers[RT(instruction)]);
}

void sub(unsigned int instruction) {
    registers[RD(instruction)] = (unsigned int)((int)registers[RS(instruction)] - (int)registers[RT(instruction)]);
}

void subu(unsigned int instruction) {
    registers[RD(instruction)] = (registers[RS(instruction)] - registers[RT(instruction)]);
}

void mult(unsigned int instruction) {
    long res = ((long)registers[RS(instruction)]) * ((long)registers[RT(instruction)]);
    HI = (unsigned int)((res >> 32) & (0xFFFFFFFF));
    LO = (unsigned int)(res & 0xFFFFFFFF);
}

void multu(unsigned int instruction) {
    unsigned long res = ((unsigned long)registers[RS(instruction)]) * ((unsigned long)registers[RT(instruction)]);
    HI = (unsigned int)((res >> 32) & (0xFFFFFFFF));
    LO = (unsigned int)(res & 0xFFFFFFFF);
}

void div(unsigned int instruction) {
    LO = (unsigned int)( (int)(registers[RS(instruction)]) / ((int)(registers[RT(instruction)])) );
    HI = (unsigned int)( (int)(registers[RS(instruction)]) % ((int)(registers[RT(instruction)])) );
}

void divu(unsigned int instruction) {
    LO = ( (registers[RS(instruction)]) / ((registers[RT(instruction)])) );
    HI = ( (registers[RS(instruction)]) % ((registers[RT(instruction)])) );
}

void and(unsigned int instruction) {
    registers[RD(instruction)] = (registers[RS(instruction)] & registers[RT(instruction)]);
}

void nor(unsigned int instruction) {
    registers[RD(instruction)] = ~(registers[RS(instruction)] | registers[RT(instruction)]);
}

void or(unsigned int instruction) {
    registers[RD(instruction)] = (registers[RS(instruction)] | registers[RT(instruction)]);
}

void xor(unsigned int instruction){
    registers[RD(instruction)] = (registers[RS(instruction)] ^ registers[RT(instruction)]);
}

void sll(unsigned int instruction) {
    registers[RD(instruction)] = ( registers[RT(instruction)] << shamt(instruction) );
}

void sllv(unsigned int instruction) {
    registers[RD(instruction)] = ( registers[RS(instruction)] << registers[RT(instruction)] );
}

void srl(unsigned int instruction) {
    registers[RD(instruction)] = ( registers[RT(instruction)] >> shamt(instruction) );
}



void sra(unsigned int instruction) {
    int n = shamt(instruction);
    if(1 & (registers[RT(instruction)] >> 31)) {
        unsigned int temp = ((1 << n) - 1);
        temp = temp << (32 - n);
        registers[RD(instruction)] = (unsigned int)( (temp) | (registers[RT(instruction)] >> n) );
    }
    else {
        registers[RD(instruction)] = ( (registers[RT(instruction)]) >> n );
    }

}

void srlv(unsigned int instruction) {
    registers[RD(instruction)] = ( registers[RS(instruction)] >> registers[RT(instruction)] );
}

void srav(unsigned int instruction) {
    int n = registers[RT(instruction)];
    if(1 & (registers[RS(instruction)] >> 31)) {
        unsigned int temp = ((1 << n) - 1);
        registers[RD(instruction)] = (unsigned int)( (temp << (32 - n)) | (registers[RS(instruction)] >> n) ); //check logic!
    }
    else {
        registers[RD(instruction)] = ( (registers[RS(instruction)]) >> n );
    }
}

void slt(unsigned int instruction) {///////////////////
    if( ((int)registers[RS(instruction)]) < ((int)registers[RT(instruction)]) ) {
        registers[RD(instruction)] = (unsigned int)1;
    }
    else {
        registers[RD(instruction)] = (unsigned int)0;
    }
}

void sltu(unsigned int instruction) {///////////
    if( (registers[RS(instruction)]) < (registers[RT(instruction)]) ) {
        registers[RD(instruction)] = (unsigned int)1;
    }
    else {
        registers[RD(instruction)] = (unsigned int)0;
    }
}

void jr(unsigned int instruction) {
    npc = registers[RS(instruction)];
}

void jalr(unsigned int instruction) {
    registers[31] = (pc + 4);
    npc = registers[RS(instruction)];
}

void mfhi(unsigned int instruction) {
    registers[RD(instruction)] = HI;
}

void mflo(unsigned int instruction) {
    registers[RD(instruction)] = LO;
}

//void syscall(unsigned int instruction) {
//}  //This is actually defined in syscall.c
