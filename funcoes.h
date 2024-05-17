// Garante que, se o arquivo já foi incluído em algum lugar anteriormente, ele não será incluído novamente
#ifndef FUNCOES_H
#define FUNCOES_H
#include <wchar.h>
#include "cartas.h"
#include <stdbool.h>

//MAIN.C

//Processa a parte de dentro do loop, para a main não ficar demasiado grande
void processarCodigo(carta *baralhoDef, int NumJogAnteriores);

//Continua o processamento
void continuarCodigo(carta *baralhoDef, wchar_t *ultimaJogadaValida, int tamJogadaAnterior, wchar_t *maoJogador, int tamMaoJogador, int numReisAnterior);


// FUNCOES.C

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

//Usada no fim para libertar os restantes
void libertarFim (wchar_t *ultimaJogadaValida, wchar_t *maoJogador, int *arrayTamanhos, int *arrayComb, wchar_t *jogadasAnteriores);

//Função que aloca memoria para arrays de Int
int* alocarArrayInt (int linhas);

//Função que aloca memoria para array de Wchar
wchar_t* alocarArrayWchar (int *arrayTamanhos,int *arrayComb, int linhas);

//Função que aloca array de cartas
carta* alocarArrayCartas ();

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

//Apenas devolve o numero da combinacao
int devolveCombinacao (wchar_t mao[], int quantidade, carta baralho[]);

//Devolve o valor da carta mais alta
int valorDaCartaMaisAlta (carta baralho[], wchar_t mao[], int tamanho);

//Devolve o valor de uma carta especifica
int valorDaCarta(carta baralho[], wchar_t carta);

//Devolve o numero da carta
int numeroCarta (carta baralho[], wchar_t carta);

//Devolve o naipe da carta
int naipeCarta (carta baralho[], wchar_t carta);

//Esta função verifica a quantidade de cartas do mesmo numero
int analisarMao (carta baralho[], wchar_t mao[], int numero, int tamanho);

//Esta função verifica a quantidade de cartas da mesma figura, apenas nos proximos naipes
int analisarProximosNaipes (carta baralho[], wchar_t mao[], int numero, int valor, int tamanho); 

//Usada para saltar os passos, caso sejam 3, vai para o caso especial para jogar livremente
bool colocarUltimaJogadaValida(wchar_t *ultimaJogadaValida, wchar_t *jogadasAnteriores, int ultimo, int arrayTamanhos[], int *tamanho);

//Imprime a mao final
void funcaoImprimir (wchar_t mao[], int tamAnterior);




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

//Gera cartas isoladas
int cartaIsolada (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int tamMao, int numReis, bool *jaImprimiu);

//Gera os conjuntos
void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int numeroMaisAlta, int tamAnterior, int tamMao, int numReis, bool *jaImprimiu);

//Continuacao (parte 2 da funcao a cima)
int ContinuacaoGerarConjunto (carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao, int valorCartaMaisAlta, bool *jaImprimiu);

//Quando o conjunto é de tamanho 2 e existem 3 ou 4 cartas
void conjuntosTamanho2 (carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int valorCartaMaisAlta, bool *jaImprimiu);

//Quando o conjunto é de tamanho 3 e existem 4 cartas
void conjuntosTamanho3(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int valorCartaMaisAlta, bool *jaImprimiu);

//Caso de quando sao varios conjuntos
int variosConjuntos(carta baralho[], wchar_t mao[], int numero, int quantidade, int tamAnterior, int tamMao, int valorCartaMaisAlta, bool *jaImprimiu);


//GERARSEQ.C

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

//Continuacao das permutacoes
void gerarPermutacoes(carta baralho[], wchar_t mao[], wchar_t *jogada, int numero, int posicao, int tamanho, int tamanhoMao, int valorMaisAlto, bool *jaImprimiu);

//Gera as sequencias
void gerarSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta, int tamAnterior, int tamMao, int numReis);


//GERARDUPSEQ.C

//Coloca a figura com o naipe copas
void colocarNaipeCopas (carta baralho[],wchar_t *carta);

//Coloca numa dupla sequencia a primeira figura a espadas e a proxima a copas
void colocarDupSeqEspadasCopas (carta baralho[], wchar_t *jogada, int tamAnterior);

//Cria as varias duplas sequencias
void gerarPermutacoesDupSeq(carta baralho[], wchar_t mao[], wchar_t *jogada, int numero, int posicao, int tamanho, int tamanhoMao, int valorMaisAlto,  bool *jaImprimiu);

//Funcao principal
void gerarDuplaSequencia (carta baralho[], wchar_t mao[], wchar_t jogadaAnterior[], int valorCartaMaisAlta, int tamAnterior, int tamMaom, int numReis, bool *jaImprimiu);

//Gera um array so de ases
void gerarAses (wchar_t array[], int tamAnterior); 

//Para os casos especiais
int gerarDuplaSeqEspeciaisReis (carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, bool *jaImprimiu);

//Continuacao
int continuacaogerarDupSeq(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao);


//GERARESPECIALSEMANTERIOR.C

//Gerar dupla sequência quando não tem jogadas anteriores ou 3 passos
int gerarDSeqSemAnterior (carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, bool *jaImprimiu);

//Gerar sequência quando não tem jogadas anteriores ou 3 passos
int gerarSeqSemAnterior (carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, bool *jaImprimiu);


// Esta linha fecha a diretiva #ifndef
#endif