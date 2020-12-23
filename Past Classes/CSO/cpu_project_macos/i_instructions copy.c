//
//  i_instructions.c
//  
//
//  Created by shrina parikh on 12/2/19.
//

#include <stdio.h>

#include "cpu.h"

#include "utilities.h"

//for debugging purposes
//print_bits(registers[RS(instruction)]);

//macros
#define opcode(x) ((x >> 26) & 0x3F)

#define RS(x) ((x >> 21) & 0x1F)

#define RT(x) ((x >> 16) & 0x1F)

#define imm(x) (x & (0xFFFF))


//These are the i-instructions implemented by the simulted MIPS processor

//16 to 32 bit
unsigned int sign_extend_Imm(unsigned short s) { //sign_extend_Imm(imm(instruction))
    unsigned int signExImm;
    if(1 & (s >> 15)) {
        signExImm = (0xFFFF0000 | s);
        
    }
    else {
        signExImm = (s);
        //print_bits(signExImm);
    }
    return signExImm;
}

//8 to 32 bit
unsigned int sign_extend_byte(unsigned char c) {
    unsigned int signEx;
    if(1 & (c >> 7)) {
        signEx = (0xFFFFFF00 | c);
    }
    else {
        signEx = (c);
        //print_bits(signExImm);
    }
    return signEx;
}

void addi(unsigned int instruction) {
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    registers[RT(instruction)] = (unsigned int)( ((int)registers[RS(instruction)]) + (int)(signExImm) );
}

void addiu(unsigned int instruction) {
    printf("addiu \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    registers[RT(instruction)] = (unsigned int)( ((unsigned int)registers[RS(instruction)]) + (signExImm) );

}

void andi(unsigned int instruction) {
    printf("andi \n");
    unsigned int signExImm = (0x00000000 | imm(instruction));
    registers[RT(instruction)] = (unsigned int)( (registers[RS(instruction)]) & (signExImm) );
}

void ori(unsigned int instruction) {
    printf("ori \n");
    unsigned int signExImm = (0x00000000 | imm(instruction));
    registers[RT(instruction)] = (unsigned int)( (registers[RS(instruction)]) | (signExImm) );
}

void xori(unsigned int instruction) {
    printf("xori \n");
    unsigned int signExImm = (0x00000000 | imm(instruction));
    registers[RT(instruction)] = (unsigned int)( (registers[RS(instruction)]) ^ (signExImm) );
}

void slti(unsigned int instruction) {
    printf("slti \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    
    if((int)registers[RS(instruction)] < (int)signExImm) {
        registers[RT(instruction)] = (unsigned int)1;
    }
    else {
        registers[RT(instruction)] = (unsigned int)0;
    }
}

void sltiu(unsigned int instruction) {
    printf("sltiu \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    if( (registers[RS(instruction)]) < (signExImm) ) {
        registers[RT(instruction)] = (unsigned int)1;
    }
    else {
        registers[RT(instruction)] = (unsigned int)0;
    }
}

void beq(unsigned int instruction){
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    if(registers[RS(instruction)] == registers[RT(instruction)]) {
        npc = pc + 4 + (signExImm << 2);
    }
}

void bne(unsigned int instruction) {
    printf("bne \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    
    if( (registers[RS(instruction)]) != (registers[RT(instruction)]) ) {
        npc = (unsigned int) (pc + 4 + (signExImm << 2));
    }
}

void lb(unsigned int instruction) {
    printf("lb \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    registers[RT(instruction)] = sign_extend_byte( memory[(registers[RS(instruction)]) + (signExImm) ]);
}

void lbu(unsigned int instruction) {
    printf("lbu \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    registers[RT(instruction)] = (0x00000000 | memory[(registers[RS(instruction)]) + (signExImm) ]);
}

void lh(unsigned int instruction) {
    printf("lh \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    
    registers[RT(instruction)] = sign_extend_Imm( *(unsigned short *) &(memory[(registers[RS(instruction)]) + signExImm]) );
}

void lhu(unsigned int instruction) {
    printf("lhu \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    
    registers[RT(instruction)] = (0x00000000 | *(unsigned short *) &(memory[registers[RS(instruction)] + (unsigned int)signExImm]));
}

void lw(unsigned int instruction) {
    printf("lw \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    registers[RT(instruction)] = *(unsigned int*) &memory[(int)(registers[RS(instruction)]) + (signExImm)];
}

void lui(unsigned int instruction) {
    printf("lui \n");
    registers[RT(instruction)] = ((imm(instruction)) << 16);

}

void sb(unsigned int instruction) {
    printf("sb \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));

    memory[registers[RS(instruction)] + signExImm] = (unsigned char)(0xFF & registers[RT(instruction)]);
}

void sh(unsigned int instruction) {
    printf("sh \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    
    *(unsigned short *) &memory[registers[RS(instruction)] + signExImm] = registers[RT(instruction) & (0xFFFF)];
    
}
void sw(unsigned int instruction) {
    printf("sw \n");
    unsigned int signExImm = sign_extend_Imm(imm(instruction));
    *(unsigned int *) (&memory[0] + registers[RS(instruction)] + signExImm) = registers[RT(instruction)];
}

