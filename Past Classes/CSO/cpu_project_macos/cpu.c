//
//  cpu.c
//  
//
//  Created by shrina parikh on 12/8/19.

#include <stdio.h>
#include "cpu.h"
#include "r_instructions.h"
#include "i_instructions.h"
#include "j_instructions.h"

//macro for extracting the opcode field of an instruction
#define opcode(x) ((x >> 26) & 0x3F)
#define funct(x) (x & (0x3F))

#define ADDI_OPCODE (0x08)
#define ADDIU_OPCODE (0x09)
#define LW_OPCODE (0x23)
#define LH_OPCODE (0x21)
#define LHU_OPCODE (0x25)
#define LB_OPCODE (0x20)
#define LBU_OPCODE (0x24)
#define SW_OPCODE (0x2b)
#define SH_OPCODE (0x29)
#define SB_OPCODE (0x28)
#define LUI_OPCODE (0x0f)
#define ORI_OPCODE (0x0d)
#define ANDI_OPCODE (0x0c)
#define XORI_OPCODE (0x0e)
#define SLTI_OPCODE (0x0a)
#define SLTIU_OPCODE (0x0b)
#define BEQ_OPCODE (0x04)
#define BNE_OPCODE (0x05)

#define J_OPCODE (0x02)
#define JAL_OPCODE (0x03)

#define ADD_FUNCT (0x20)
#define ADDU_FUNCT (0x21)
#define SUB_FUNCT (0x22)
#define SUBU_FUNCT (0x23)
#define MULT_FUNCT (0x18)
#define MULTU_FUNCT (0x19)
#define DIV_FUNCT (0x1a)
#define DIVU_FUNCT (0x1b)
#define MFHI_FUNCT (0x10)
#define MFLO_FUNCT (0x12)
#define AND_FUNCT (0x24)
#define OR_FUNCT (0x25)
#define XOR_FUNCT (0x26)
#define NOR_FUNCT (0x27)
#define SLT_FUNCT (0x2a)
#define SLTU_FUNCT (0x2b)
#define SLL_FUNCT (0x00)
#define SLLV_FUNCT (0x04)
#define SRL_FUNCT (0x02)
#define SRLV_FUNCT (0x06)
#define SRA_FUNCT (0x03)
#define SRAV_FUNCT (0x07)
#define JR_FUNCT (0x08)
#define JALR_FUNCT (0x09)
#define SYSCALL_FUNCT (0x0c)

unsigned int registers[NUM_REGISTERS];

//pc holds the current value of the PC (program counter).
//IMPORTANT: pc may be read by an instruction, but should not
//be modified by an instruction.
unsigned int pc;

//npc is the value that the PC will be assigned to once the current
//instruction is completed. A jump or branch instruction should modify
//the value of npc if the jump or branch is taken.  If an instruction
//does not assign a value to npc, it will be given the value of
//pc+4.  IMPORTANT: npc may be modified by an instruction (but only
//by jump or branch), but it should not be read by an instruction.
unsigned int npc;

//HI and LO are the registers assigned by the MULT and DIV instructions
//and read by the MFHI and MFLO instructions.
unsigned int HI;
unsigned int LO;

//Memory is an array of bytes (not words).
unsigned char memory[MEMORY_SIZE_IN_BYTES];


//for condition for cpu_execute
unsigned int test = 1;

//This is the procedure for initializing (or reinitializing) the CPU.
void cpu_initialize() {
    pc = CODE_STARTING_ADDRESS;
    npc = CODE_STARTING_ADDRESS;
    registers[29] = STACK_STARTING_ADDRESS;
    registers[0] = 0;
}

//This procedure will cause the CPU to stop executing the current program.
//If errorcode is 0, a message indicating normal termination will be printed.
//Otherwise, a message indicating abnormal termination, along with the
//errorcode, will be printed.
void cpu_exit(errorcode) {
    if(errorcode == 0) {
        printf("Program terminated normally");
    }
    else {
        printf("Program terminated with an error\n");
        printf("Errorcode: %d", errorcode);
    }
    test = 0;
}


void handle_r_instructions(instruction) {
    
    switch(funct(instruction)) {
        case(ADD_FUNCT): add(instruction);
            break;
        case(ADDU_FUNCT): addu(instruction);
            break;
        case(SUB_FUNCT): sub(instruction);
            break;
        case(SUBU_FUNCT): subu(instruction);
            break;
        case(MULT_FUNCT): mult(instruction);
            break;
        case(MULTU_FUNCT):multu(instruction);
            break;
        case(DIV_FUNCT): div(instruction);
            break;
        case(DIVU_FUNCT): divu(instruction);
            break;
        case(MFHI_FUNCT): mfhi(instruction);
            break;
        case(MFLO_FUNCT): mflo(instruction);
            break;
        case(AND_FUNCT): and(instruction);
            break;
        case(OR_FUNCT): or(instruction);
            break;
        case(XOR_FUNCT): xor(instruction);
            break;
        case(NOR_FUNCT): nor(instruction);
            break;
        case(SLT_FUNCT): slt(instruction);
            break;
        case(SLTU_FUNCT): sltu(instruction);
            break;
        case(SLL_FUNCT): sll(instruction);
            break;
        case(SLLV_FUNCT): sllv(instruction);
            break;
        case(SRL_FUNCT): srl(instruction);
            break;
        case(SRLV_FUNCT): srlv(instruction);
            break;
        case(SRA_FUNCT): sra(instruction);
            break;
        case(SRAV_FUNCT): srav(instruction);
            break;
        case(JR_FUNCT): jr(instruction);
            break;
        case(JALR_FUNCT): jalr(instruction);
            break;
        case(SYSCALL_FUNCT): syscall(instruction);
            break;
    }
    
}

//This is the procedure for causing the CPU to execute. It should
//start by executing the instruction at address CODE_STARTING_ADDRESS
void  cpu_execute() {
    test = 1;
    while(test != 0) {
        pc = npc;
        npc += 4;
        unsigned int instruction = *(unsigned int *) &memory[pc];
        
        switch(opcode(instruction)) {
            case(0): handle_r_instructions(instruction);
                break;
            case(ADDI_OPCODE): addi(instruction);
                break;
            case(ADDIU_OPCODE): addiu(instruction);
                break;
            case(LW_OPCODE): lw(instruction);
                break;
            case(LH_OPCODE): lh(instruction);
                break;
            case(LHU_OPCODE): lhu(instruction);
                break;
            case(LB_OPCODE): lb(instruction);
                break;
            case(LBU_OPCODE): lbu(instruction);
                break;
            case(SW_OPCODE): sw(instruction);
                break;
            case(SH_OPCODE): sh(instruction);
                break;
            case(SB_OPCODE): sb(instruction);
                break;
            case(LUI_OPCODE): lui(instruction);
                break;
            case(ORI_OPCODE): ori(instruction);
                break;
            case(ANDI_OPCODE): andi(instruction);
                break;
            case(XORI_OPCODE): xori(instruction);
                break;
            case(SLTI_OPCODE): slti(instruction);
                break;
            case(SLTIU_OPCODE): sltiu(instruction);
                break;
            case(BEQ_OPCODE): beq(instruction);
                break;
            case(BNE_OPCODE): bne(instruction);
                break;
                
            case(J_OPCODE): j(instruction);
                break;
            case(JAL_OPCODE): jal(instruction);
                break;
        }
    }
}


