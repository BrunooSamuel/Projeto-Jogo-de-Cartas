#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"


void lerDuplaSequencia (wchar_t array[], int quantidade) {
    //so para n aparecer warnings
    printf("Numero de cartas: %d\n", quantidade);
    for (int i = 0; i < quantidade; i++)
    {
        wprintf(L"%C\t",array[i]);
    }
}

void verificarCombinacao (wchar_t array[], int quantidade) {
    printf("Numero de cartas: %d\n", quantidade);
    for (int i = 0; i < quantidade; i++)
    {
        wprintf(L"%C\t",array[i]);
    }
    
}
