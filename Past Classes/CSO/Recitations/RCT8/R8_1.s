movq $0x4, %rcx
leaq 4(, %rcx, $2), %rax
leaq (%rcx, %rcx, $2), %rbx
movq $2, %rdx

cmpq %rax, %rbx
jne L1
cmpq %rax, %rcx
jge L1
addq $1, %rdx
jmp L2

L1:
cmpq %rcx, %rbx
jne L2
subq $1, %rdx

L2:
movq $1, %r4
bne %rdx, %r4, L3
jmp L5
L3:
addq $1, %r4
bne %rdx, %r4, L4
jmp L6
L4:
addq $1, %r4
bne %rdx, %r4, L8
jmp L7
L5:
addq $1, %rdx
L6:
addq $2, %rdx
jmp L8
L7:
addq $3, %rdx
L8:
movq %rdx, %rax
ret

//return value
//what is BNE --> branch if not equal

//c=4
//a = 4+c*2 = 12
//b=c+c*2=12
//d=2
//if a == b
//  if a>c
//      d=d+1 (d=3)
//if c== b
//  d = d-1

//switch(i) {
//  case(1): d=d+1
//  case(2): d=d+2 //L6
//  case(3): d=d+3

//res= 6
//return res
