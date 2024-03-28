#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir(int t, carta baralho[]) { // AINDA NAO FUNCIONA

    printf("Começa a imprimir as cartas com numero %d\n", t);


    for (int i = 0; i < 56; i++) {
        if (baralho[i].numero == t) {
            setlocale(LC_CTYPE, "C.UTF-8");
            wchar_t c = baralho[i].codigo;
    	    wprintf(L"%C\n", c);
        }
    } 

    printf("Acabou de Imprimir\n");  
}


void lerDuplaSequencia (wchar_t array[], int quantidade) {

}

void verificarCombinacao (wchar_t array[], int quantidade) {
    printf("Numero de cartas: %d\n", quantidade);
    for (int i = 0; i < quantidade; i++)
    {
        wprintf(L"%C\t",array[i]);
    }
    
}
