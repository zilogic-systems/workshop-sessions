#define __ASSEMBLY__

#define ENTRY(x) \
        .text; .globl x; .type x,@function; x:

ENTRY(mcount)
    /* Save */
    subq $0x38, %rsp
    movq %rax, (%rsp)
    movq %rcx, 8(%rsp)
    movq %rdx, 16(%rsp)
    movq %rsi, 24(%rsp)
    movq %rdi, 32(%rsp)

    /*
     * write(1, ".", 1)
     */
    push $0x2E
    movq $1, %rax
    movq $1, %rdi
    movq %rsp, %rsi
    movq $1, %rdx
    syscall
    pop %rdi

    /* Restore */
    movq 32(%rsp), %rdi
    movq 24(%rsp), %rsi
    movq 16(%rsp), %rdx
    movq 8(%rsp), %rcx
    movq (%rsp), %rax
    addq $0x38, %rsp
    retq
