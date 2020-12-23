//
//  R9.s
//  
//
//  Created by shrina parikh on 10/31/19.
//

_allocate_node:
    pushq   %rbp //rbp has base of stack pointers, rsp has top
    movq    %rsp,%rbp //need to take care of stack

    movq    %16,%rdi //need to pass 16 to malloc to allocate space
    call    _malloc //calling malloc
# the address of the cell is already in %rax so we just leave it there
    popq    %rbp
    retq

_insert:
    pushq   %rbp
    movq    %rsp,%rbp

    $0,%rdx //temp node will be in rdx, initialized to NULL

    pushl   %esi
    pushq   %rdi

    call    _allocate_cell //returns the address of the new celll

    movq    %rax,%rdx //mov the address into p, in %rdx
    popq    %rdi
    popq    %rsi

    movl    %esi,0(%rdx) //move i into p->val (offset of 0 from p)
    movq    %rdi, 8(%rdx) //move head into temp->next (offset of 8)
    movq    %rdx,(%rdi)

    popq    %rbp
    ret



