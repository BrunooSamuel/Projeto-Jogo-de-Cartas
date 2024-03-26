#include "funcoes.h"

void dobro (int x) {
    int y= 2*x;
    printf("O dobro de %d -> %d\n", x, y);
}


#include <stdio.h>
#include <locale.h>
#include <wchar.h>

/*
        Mudar para UTF8
        setlocale(LC_CTYPE, "C.UTF-8");

        if(scanf("%d%d", &dia, &mes) == 2) {
            wchar_t c = 0x2648;
            wprintf(L"%C\n", c);
        }
*/