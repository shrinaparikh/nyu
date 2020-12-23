//
//  j_instructions.c
//  
//
//  Created by shrina parikh on 12/2/19.
//

#include <stdio.h>

#include "cpu.h"

#include "utilities.h"

//These are the J-instructions implemented by the simulted MIPS processor

//J instruction:  opcode (6 bits)      address (26 bits)

//macros
#define opcode(x) ((x << 26) & 0x3F);

#define address(x) ((x) & 0x3FFFFFF)

void j(unsigned int instruction) {
    npc = (unsigned int)( ( (pc + 4) & (0xf0000000) ) | (address(instruction) << 2)  );
}


void jal(unsigned int instruction) {
    registers[31] = (unsigned int)(pc + 4);
    npc = (unsigned int)( ( (pc + 4) & (0xf0000000) ) | (address(instruction) << 2)  );
}
