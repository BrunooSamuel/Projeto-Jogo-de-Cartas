#include <stdio.h>
#include "funcoes.h"
#include "cartas.c"
#include <locale.h>
#include <wchar.h>

int main () {
    int n;
    printf("Escolhe um numero:\n");
    scanf("%d", &n);
    dobro(n);

    return 0;
}