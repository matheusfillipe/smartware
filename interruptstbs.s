.set IRQ_BASE, 0x20

.section .text

.extern _ZN15InterrupManager15HandleInterruptEhj
.global _ZN15InterrupManager22IgnoreInterruptRequestEv
.macro HandleException num
.global  _ZN15InterrupManager16HandleException\num\()Ev
_ZN15InterrupManager16HandleException\num\()Ev:
    movb $\num, (interruptnumber)
    jmp int_bottom
.endm

.macro HandleInterruptRequest num
.global  _ZN15InterrupManager26HandleInterruptRequest\num\()Ev
_ZN15InterrupManager26HandleInterruptRequest\num\()Ev:
    movb $\num + IRQ_BASE, (interruptnumber)
    jmp int_bottom
.endm

HandleInterruptRequest 0x00
HandleInterruptRequest 0x01



int_bottom:
    
    pusha
    pushl %ds
    pushl %es
    pushl %fs
    pushl %gs
    
    pushl %esp
    push (interruptnumber)
    call _ZN15InterrupManager15HandleInterruptEhj
    #addl $5, %esp
    add %esp, 6
    mov %eax, %esp
    
    
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa


_ZN15InterrupManager22IgnoreInterruptRequestEv:   
    iret
    
.data
    interruptnumber: .byte 0
