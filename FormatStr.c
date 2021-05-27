#include <stdio.h>

int main(int argc, char *argv[]) {
    int i;
    char cad[15];

    printf ("What is your address?: ");
    scanf ("%s", cad);
    fflush(stdin);
    printf ("Your address is: ");
    printf(cad);
    scanf("%d", &i);
    return 0;
}

