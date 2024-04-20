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
int lerMao(carta baralho[], int *arrayComb, wchar_t *jogadasAnteriores, int posMaos, int *arrayTamanhos);

//Função que lê uma mão
int lerUmaMao(wchar_t *maoJogador, carta baralho[], int *arrayComb, wchar_t *jogadasAnteriores, int *arrayTamanhos);

//Funcao que ordena um array de Ints
void ordena(int mao[], int tamanho);

//Função que dá free
void libertarTodas (int *arrayTamanhos, int *arrayComb,wchar_t *jogadasAnteriores);

//Função que aloca memoria para arrays de Int
int* alocarArrayInt (int linhas);

//Função que aloca memoria para array de Wchar
wchar_t* alocarArrayWchar (int *arrayTamanhos,int *arrayComb, int linhas);

//Função que aloca array de cartas
carta* alocarArrayCartas ();

//Função que dá scan a um int
int scanInt ();

//Função que aloca memoria para a mao
wchar_t* alocarMao (int *arrayTamanhos,int *arrayComb, wchar_t *jogadas);

//função para verificar se as cartas da jogada atual estão na mão do jogador
void verificarCartasMao(wchar_t *maoJogador, wchar_t *jogadaJogador, int *tamanho);

//Funcão usada para imprimir apenas uma mão
void imprimirUmaMao (wchar_t *mao);

//FUnção que conta os reis
int contadorReis (carta baralho[], wchar_t *jogadas, int ultimo, int comp);

//Auxiliar a função a cima
int contadorAuxiliar (carta baralho[], wchar_t *jogada, int comp);

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

//Função que verifica se a jogada é válida

bool verificarJogada(carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int numAnte);

//Funçao que da o valor da maior carta
int maiorCartaValor(carta baralho[], wchar_t *mao,int tamanho);


//Caso tenha reis
bool verificarJogadacomReis(carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int numAnte);
// PARES.C

//Função que ordena todas as maos
void ordenarTudo (carta baralho[], wchar_t *jogadasAnteriores, int comprimento, int linhas);

//Função que ordena uma mao
void ordenarMao (carta baralho[], wchar_t *jogadasAnteriores, int comprimento);

//Função que transforma as cartas que recebe em pares numero naipe
void arranjaPar (carta baralho[], wchar_t mao[], int comprimento, int *numeros, int *naipes);

//Função que ordena os pares
void ordenaPares (int comprimento, int *numeros, int *naipes);

//Função que transforma os pares em carta
void parParaCarta (carta baralho[], wchar_t *mao, int comprimento, int *numeros, int *naipes);

//Função que troca dois ints num array
void trocarPosicoes(int *x, int *y);

//Função que coloca as maos por ordem crescente
void maosCrescente (carta baralho[], wchar_t *jogadasAnteriores,int comprimento, int linhas, int array[]);

//Função que transforma a ultima carta num valor (numero*4+(naipe-4))
void ultimoValor(carta baralho[], wchar_t *mao,int tamanho, int *valores, int posicao);

//Funçao final que imprime as maos
void imprimeMaosOrdenadas (int linhas, int arrayTamanhos[], wchar_t *jogadasAnteriores);

// Esta linha fecha a diretiva #ifndef
#endif