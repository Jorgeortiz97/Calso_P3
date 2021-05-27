#include <stdio.h>
#include <string.h>

void check (char *pas) {
    char passwd[10];
    char *p;

    strcpy(passwd, pas);
    // para que tenga sentido la funci�n
    // p = (char *) strlwr(passwd);
    if (strcmp(p, "mipas") == 0)
        printf ("Correct password . ");
    else
        printf ("Incorrect password . ");
}

int main(int argc, char *argv[]) {
    int i;

    check (argv[1]);
    printf ("End.");
    scanf("%d", &i);
    return 0;
}

