// Garante que, se o arquivo já foi incluído em algum lugar anteriormente, ele não será incluído novamente
#ifndef FUNCOES_H
#define FUNCOES_H
#include <wchar.h>
#include "cartas.h"


//Funcao teste para imprimir
void imprimir (int t, carta baralho[]);

//Funcao de limpeza da entrada
void limpar();

//Funcao que lê a mao que recebe
void lerMao(carta baralho[]);

//Funcao que ordena um array de Ints
void ordena(int array[], int tamanho);

//Funcao para ler que combinação é
void verificarCombinacao (wchar_t array[], int quantidade,carta baralho[]);

//Funcao para ler Conjuntos
void lerConjunto (wchar_t array[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);

//Funcao para ler Sequencias
void lerSequencia (wchar_t array[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);

//Funcao para Dupla Sequencias
void lerDuplaSequencia (wchar_t array[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);



// Esta linha fecha a diretiva #ifndef
#endif