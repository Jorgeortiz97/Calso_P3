#include <stdio.h>

int main(int argc, char *argv[]) {
    int a, b, i;

    printf ("First integer: ");
    scanf ("%d", &a);
    fflush(stdin);
    printf ("Second integer: ");
    scanf ("%d", &b);
    fflush(stdin);
    printf ("The multiplication is %d\n", a * b);
    printf ("End.");
    scanf("%d", &i);
    return 0;
}

