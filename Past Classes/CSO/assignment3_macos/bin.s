
 	 .section	__TEXT,__text,regular,pure_instructions
 	 .globl	_insert_node
 	 .p2align	4, 0x90

_insert_node: //insert_node(NODE *new_n) --> first parameter stored in %rdi
    pushq   %rbp
    movq    %rsp, %rbp

    cmpq    $0, _root(%rip) //if (root == NULL)
    je      NULLROOT
    movq    _root(%rip), %rsi //%rsi holds p for traversal

TOP:                                     //simply marks start of loop
    movq    0(%rsi), %r9 //r9 has p
    cmpq    0(%rdi), %r9
    je      DONE
    pushq   %rdi
    pushq   %rsi
    leaq    116(%rdi), %rdi //new_n->person.last
    leaq    116(%rsi), %rsi //p->person.last
    call    _strcmp //strcmp(new_n->person.last, p->person.last)
    popq    %rsi
    popq    %rdi
    movq    %rax, %rcx
    cmpq    $0, %rcx
    je      FIRSTNAMES     //if last names same, compare first names
REST:
    cmpq    $0, %rcx
    jl      LEFT   //go to left subtree
    jge     RIGHT     //else, go to right subtree
FIRSTNAMES:  //comparing first names
    pushq   %rdi
    pushq   %rsi
    leaq    16(%rdi), %rdi //new_n->person.first
    leaq    16(%rsi), %rsi //p->person.first
    call    _strcmp //strcmp(new_n->person.first, p->person.first)
    popq    %rsi
    popq    %rdi
    movq    %rax, %rcx
    jmp     REST
NULLROOT:
    movq    %rdi,_root(%rip)    //root = new_n
    jmp     DONE                                        //return
LEFT:
    cmpq    $0, 216(%rsi)        //if (p->left == NULL)
    je      LEQUAL
    movq    216(%rsi),%rsi //else, p = p->left;
    jmp     TOP
LEQUAL:
    movq    %rdi, 216(%rsi) //p->left = new_n;
    jmp     DONE
RIGHT:                                    // Otherwise
    cmpq    $0, 224(%rsi)    //if (p->right == NULL)
    je      REQUAL
    movq    224(%rsi),%rsi //else, p = p->right;
    jmp     TOP
REQUAL:
    movq    %rdi, 224(%rsi) //p->right = new_n;
    jmp     DONE //break;
DONE:
    popq    %rbp
    ret

.section    __TEXT,__text,regular,pure_instructions
.globl    _remove_smallest
.p2align    4, 0x90


_remove_smallest: // NODE *remove_smallest()
    pushq   %rbp
    movq    %rsp, %rbp

    movq    _root(%rip), %r8 //%r8 hold root now
    cmpq    $0, _root(%rip) //if (root == NULL)
    je      NULLROOT2
    cmpq    $0,216(%r8) //if (root->left == NULL)
    je      LEFTNULL
    movq    _root(%rip), %rcx   //NODE *parent = root //parent is in %rcx
    movq    216(%rcx), %rbx //%rbx holds parent.left
TOP2: //while loop
    cmpq    $0, 216(%rbx) //parent->left->left != NULL //initial condition while loop
    je      FIN
    movq    216(%rcx), %rcx
    movq    216(%rcx), %rbx
    jmp     TOP2
FIN:
    movq    216(%rcx),%rsi //p in %rsi

    movq    216(%rcx), %r9
    movq    224(%r9), %rdx
    movq    %rdx,216(%rcx)

    movq    %rsi,%rax //return p
    jmp     DONE2
NULLROOT2:
    movq    $0, %rax
    jmp     DONE2
LEFTNULL:
    movq    _root(%rip),%rdx //NODE *p = root
    movq    224(%rdx),%r9
    movq    %r9, _root(%rip) //root = root->right
    movq    %rdx,%rax //return p
    jmp     DONE2
DONE2:
    popq    %rbp
    ret








