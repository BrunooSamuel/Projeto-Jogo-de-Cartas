#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir (int t, carta baralho[]) {

    setlocale(LC_CTYPE, "C.UTF-8");

    for (int i = 0; i < 56; i++)
    {
        if (baralho[i].numero==t) 
        {
            wprintf(L"%lc ", baralho[i].codigo);  
        }
    } 
    printf("\n");  
}


