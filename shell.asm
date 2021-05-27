global _start
section .text

_start:
    mov     rsi, 0x0                 ; arg[1] = NULL
    push    rsi                      ; push arg2
    mov     rdi, 0x68732f2f6e69622f  ; arg[0] = /bin/bash => 2f 62 69 6e 2f 62 61 73 68, so we set it in reverse order
    push    rdi                      ; push arg[0]
    mov     rdi, rsp                 ; arg[0] = STACK_BUFFER
    mov     eax, 59                  ; 59 is execve syscall (0x3b)
    cdq                              ; double size of EAX
    syscall                          ; perform the syscall
