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
int lerMao(carta baralho[], int *arrayComb, wchar_t *jogadasAnteriores, int *posMaos, int *arrayTamanhos);

//Função que lê uma mão
int lerUmaMao(wchar_t *mao, carta baralho[]);

//Funcao que ordena um array de Ints
void ordena(int mao[], int tamanho);

//Função que dá free
void libertar (carta *baralho,wchar_t *mao, wchar_t *conjuntoTotal);

//Função que aloca memoria para arrays de Int
int* alocarArrayInt (int linhas);

//Função que aloca memoria para array de Wchar
wchar_t* alocarArrayWchar (int *arrayTamanhos,int *arrayComb, int linhas);

//Função que aloca array de cartas
carta* alocarArrayCartas ();

//Função que dá scan a um int
int scanInt ();

//Função que aloca memoria para a mao
wchar_t* alocarMao ();

//função para verificar se as cartas da jogada atual estão na mão do jogador
void verificarCartasMao(wchar_t *maoJogador, wchar_t *jogadaJogador, int *tamanho);

//Funcão usada para imprimir apenas uma mão
void imprimirUmaMao (wchar_t *mao);

//FUnção que conta os reis
int contadorReis (carta baralho[], wchar_t *jogadas, int ultimo);

//Auxiliar a função a cima
int contadorAuxiliar (carta baralho[], wchar_t *jogada);

//Processa a parte de dentro do loop, para a main não ficar demasiado grande
void processarCodigo(int esteTeste, carta *baralhoDef);

//Apenas devolve o numero da combinacao
int devolveCombinacao (wchar_t mao[], int quantidade, carta baralho[]);

//Devolve o valor da carta mais alta
int valorDaCartaMaisAlta (carta baralho[], wchar_t mao[], int tamanho);

//Devolve o valor de uma carta especifica
int valorDaCarta(carta baralho[], wchar_t mao[], int posicao);

//Devolve o numero da carta
int numeroCarta (carta baralho[], wchar_t carta);

//Esta função verifica a quantidade de cartas do mesmo numero
int analisarMao (carta baralho[], wchar_t mao[], int numero, int tamanho);


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

//Auxiliar
bool verificarAux (carta baralho[], wchar_t *jogadaJogador, wchar_t *jogadasAnte, int arrayTamanhos[], int tamJogadaJogador, int i, int *comb);

//Funçao que da o valor da maior carta
int maiorCartaValor(carta baralho[], wchar_t *mao,int tamanho);

//Caso tenha reis
bool verificarJogadacomReis(carta baralho[], wchar_t *jogadaJogador, int numReis, int tamJogadaJogador);


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



//GERARCONJ.C

//Gera os conjuntos
void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao);

//Continuacao (parte 2 da funcao a cima)
int ContinuacaoGerarConjunto (carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao, int valorCartaMaisAlta);

//Quando o conjunto é apenas de 1 carta
void conjuntosTamanho1 (wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int tamAnterior);

//Quando o conjunto é de tamanho 2 e existem 3 ou 4 cartas
void conjuntosTamanho2 (carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int valorCartaMaisAlta);

//Quando o conjunto é de tamanho 3 e existem 4 cartas
void conjuntosTamanho3(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int valorCartaMaisAlta);

//Caso de quando sao varios conjuntos
int variosConjuntos(carta baralho[], wchar_t mao[], int numero, int quantidade, int tamAnterior, int tamMao, int valorCartaMaisAlta);

//Imprime os conjuntos
void imprimirConjuntos (wchar_t mao[], int tamAnterior);


//GERARSEQ.C

// Função para verificar todas as cartas da combinacao na mão do jogador
bool verificarExisteNaMao(wchar_t *mao, wchar_t *comb, int tamanhoMao, int tamanhoComb); 

//Aumenta a figura de um array inteiro e muda o naipe para espadas
void aumentarFigura (carta baralho[], wchar_t jogada[], int tamanho);

//Coloca uma carta no naipe espadas
void colocarNaipeEspadas (carta baralho[],wchar_t *carta);

//Aumenta o naipe de uma carta
void aumentarNaipeCarta (carta baralho[],wchar_t *carta);

//Quantas cartam tem em comum entre a jogada e a mao
int numeroCartasEmComum ( wchar_t jogada[], wchar_t mao[] ,int tamAnterior, int tamMao);

//Verifica se a carta está na mao
bool cartaExiste (wchar_t mao[], wchar_t carta);

//Verifica se a sequencia existe na mao, sendo de naipe espadas
void colocarSequenciaNaipeEspadas (carta baralho[], wchar_t *jogada, int tamAnterior);

//Verifica se a sequencia na mao existe, passando ao proximo naipe
int verificarSequenciaProximoNaipe (carta baralho[], wchar_t *jogada, wchar_t mao[] ,int tamAnterior, int tamMao, int valorMaisAlto);


void gerar_permutacoes(carta baralho[], wchar_t *jogada, int numero, int posicao, int tamanho);

//Gera as diferentes sequencias com as mesmas figuras
void gerarComMesmasFiguras (carta baralho[], wchar_t *jogada, wchar_t mao[], int tamAnterior);

//Gera as sequencias
void gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao);

//Imprime as sequencias
void imprimirSequencias (wchar_t mao[], int tamAnterior);


//GERARDUPSEQ.C

//Cria os pares possiveis dos naipes
int* criarPares ();

//Devolve o numero da posicao do par no array criarPares
int qualPar (carta baralho[], wchar_t primeiro, wchar_t segundo);

//Gera as duplas sequencias
void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao);


// Esta linha fecha a diretiva #ifndef
#endif