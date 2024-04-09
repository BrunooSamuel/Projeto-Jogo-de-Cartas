// Garante que, se o arquivo já foi incluído em algum lugar anteriormente, ele não será incluído novamente
#ifndef FUNCOES_H
#define FUNCOES_H
#include <wchar.h>
#include "cartas.h"
#include <stdbool.h>

// FUNCOES.C

//Funcao teste para imprimir
void imprimir (int t, carta baralho[]);

//Funcao de limpeza da entrada
void limpar();

//Funcao que lê a mao que recebe
int lerMao(carta baralho[], int *arrayComb, wchar_t *todasMaos, int posMaos, int arrayTamanhos[]);

//Funcao que ordena um array de Ints
void ordena(int mao[], int tamanho);

// COMBINACOES.C

//Funcao para ler que combinação é
void verificarCombinacao (wchar_t mao[], int quantidade,carta baralho[], int *arrayComb);

//Funcao para verificar se é conjunto
void verificaConjunto(int quantidade, int maoNum[], bool *combinacao);

//Funcao para verificar se é sequencia
void verificaSequencia(int quantidade, int maoNum[], bool *combinacao);

//Funcao para verificar se é dupla sequencia
void verificaDSequencia(int quantidade, int maoNum[], bool *combinacao);

//Funcao para ler Conjuntos
void lerConjunto (wchar_t mao[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);

//Funcao para ler Sequencias
void lerSequencia (wchar_t mao[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);

//Funcao para Dupla Sequencias
void lerDuplaSequencia (wchar_t mao[], int quantidade, carta baralho[],wchar_t ordenadoNum[]);

// COMPARACOES.C

//Funcao para verificar se todas as linhas têm o mesmo tamanho
bool compararTamanhos(int array[], int total);

//Funcao para verificar se todas as linhas são a mesma combinacao
bool compararCombinacoes(int array[]);

//Funcao que envia para a comparação da determinada combinação
void escolherCombinacao(int array[], wchar_t *todasMaos, carta baralho[], int comprimento);

//Função que ordena as maos por ordem
void ordenarConjunto(wchar_t *todasMaos, carta baralho[], int comprimento);

//Função que ordena as maos por ordem
void ordenarSeq(wchar_t *todasMaos, carta baralho[], int comprimento);

//Função que ordena as maos por ordem
void ordenarDupSeq(wchar_t *todasMaos, carta baralho[], int comprimento);

// Esta linha fecha a diretiva #ifndef
#endif