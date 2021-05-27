#include <stdio.h>

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
    *ret += 4;
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
