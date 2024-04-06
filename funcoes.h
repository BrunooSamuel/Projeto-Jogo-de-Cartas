// Garante que, se o arquivo já foi incluído em algum lugar anteriormente, ele não será incluído novamente
#ifndef FUNCOES_H
#define FUNCOES_H
#include <wchar.h>
#include "cartas.h"
#include <stdbool.h>

// FUNÇÕES.C

//Funcao teste para imprimir
void imprimir (int t, carta baralho[]);

//Funcao de limpeza da entrada
void limpar();

//Funcao que lê a mao que recebe
int lerMao(carta baralho[],int arrayCombinacoes[], int arrayTamanhos[], wchar_t todasMaos[], int posTodasMaos);

//Funcao que ordena um array de Ints
void ordena(int mao[], int tamanho);


// COMBINCACOES.C

//Funcao para ler que combinação é
void verificarCombinacao (wchar_t mao[], int quantidade,carta baralho[],int arrayCombinacoes[]);

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

//Função que coloca os vários tamanhos das mãos num array, para depois serem comparados
void GuardarTamanhos(int arrayTamanhos[], int tamanho);

//Função que compara os tamanhos das mãos
void CompararTamanhos(int arrayTamanhos[], bool *tamiguais);

//Função que guarda as combinações para serem comparadas
void GuardarCombinacao(int arrayCombinacoes[],bool conjunto,bool sequencia,bool duplasequencia);

//Função que compara as combinações guardadas na função anterior
void CompararCombinacao(int arrayCombinacoes[], int linhas, bool *combiguais);

//Função que compara as mãos
void compararMaos(carta baralho[], bool combiguais, bool tamiguais, wchar_t todasMaos[], int arrayCombinacoes[]);

//Função que ordena as maos por ordem
void ordenarConjunto(carta baralho[],wchar_t todasMaos[]);

//Função que ordena as maos por ordem
void ordenarSeq(carta baralho[],wchar_t todasMaos[]);

//Função que ordena as maos por ordem
void ordenarDupSeq(carta baralho[], wchar_t todasMaos[]);

// Esta linha fecha a diretiva #ifndef
#endif