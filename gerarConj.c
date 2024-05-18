#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

int cartaIsolada (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int tamMao, int numReis, bool *jaImprimiu) {
    for (int i = 0; i < tamMao; i++)
    {
        if (valorDaCarta(baralho,mao[i])>valorCartaMaisAlta && !(*jaImprimiu)) 
        {
            wprintf(L"%lc\n",mao[i]);
            (*jaImprimiu)=true;
        }
    }
    if (!(*jaImprimiu) && (numReis==0 || numReis==4)) { wprintf(L"PASSO\n"); (*jaImprimiu)=true;}

    return 0;
}


void gerarConjunto(carta baralho[], wchar_t mao[], int valorCartaMaisAlta, int numeroMaisAlta, int tamAnterior, int tamMao, int numReis, bool *jaImprimiu) {
    bool existeConjunto = false;

    // Para a figura original
    if ((valorCartaMaisAlta / numeroMaisAlta) != 4) {
        int contagem = analisarMao(baralho, mao, numeroMaisAlta, tamMao);

        if (contagem == tamAnterior) {
            existeConjunto = true;
            ContinuacaoGerarConjunto(baralho, mao, numeroMaisAlta, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);
        } else if (contagem > tamAnterior) {
            existeConjunto = true;
            variosConjuntos(baralho, mao, numeroMaisAlta, contagem, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);
        }
    }

    // Loop para verificar as cartas subsequentes
    int i = numeroMaisAlta + 1;
    while (i <= 14 && !(*jaImprimiu) && !existeConjunto) {
        int contagem = analisarMao(baralho, mao, i, tamMao);

        if (contagem == tamAnterior) {
            existeConjunto = true;
            ContinuacaoGerarConjunto(baralho, mao, i, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);
        } else if (contagem > tamAnterior) {
            existeConjunto = true;
            variosConjuntos(baralho, mao, i, contagem, tamAnterior, tamMao, valorCartaMaisAlta, jaImprimiu);
        }
        
        i++;
    }

    // Se nenhum conjunto válido foi encontrado e o número de Reis é 0 ou 4, imprimir "PASSO"
    if (!(*jaImprimiu) && !existeConjunto && (numReis == 0 || numReis == 4)) {
        wprintf(L"PASSO\n");
    }
}

//Caso so haja uma hipotese de impressao
int ContinuacaoGerarConjunto(carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao, int valorCartaMaisAlta, bool *imprimiu) {
    bool encontrou = false;
    int posicao = 0;

    wchar_t* conjuntoAtual = (wchar_t*)malloc(sizeof(wchar_t) * tamAnterior);
    if (conjuntoAtual == NULL) {
        free(conjuntoAtual);
        return -1;
    }

    for (int i = 0; i < tamMao && posicao < tamAnterior; i++) {
        for (int k = (numero * 4) - 4; k <= (numero * 4) - 1 && !encontrou; k++) {
            if (mao[i] == baralho[k].codigo) {
                *imprimiu = true;
                conjuntoAtual[posicao] = mao[i];
                posicao++;
                encontrou = true;
            }
        }
        encontrou = false;
    }

    int valorConjuntoAtual = valorDaCartaMaisAlta(baralho, conjuntoAtual, tamAnterior);
    if (posicao == tamAnterior && valorConjuntoAtual > valorCartaMaisAlta) {
        funcaoImprimir(conjuntoAtual, tamAnterior);
        free(conjuntoAtual); // Liberar a memória após a impressão do conjunto válido
        return 0; // Retorna 0 indicando sucesso
    }

    free(conjuntoAtual);
    return 0;
}

int variosConjuntos(carta baralho[], wchar_t mao[], int numero, int quantidade, int tamAnterior, int tamMao, int valorCartaMaisAlta, bool *jaImprimiu) {
    wchar_t* conjuntoTotal = (wchar_t*)malloc (sizeof(wchar_t)*quantidade);
    if (conjuntoTotal == NULL) {
        libertar (baralho, mao, conjuntoTotal);
        return -1;
    }
    bool encontrou=false;
    int posicao=0;
   
    //coloca todas as cartas no array para serem usadas nos varios conjuntos
    for (int i = 0; i < tamMao && posicao<quantidade; i++)
    {
        for (int k = (numero*4)-4; k <= (numero*4)-1 && !encontrou; k++)
        {
            if (mao[i]==baralho[k].codigo) 
            {
                conjuntoTotal[posicao]=mao[i];
                posicao++;
                encontrou=true;
            }
        }
        encontrou=false;
    }
    wchar_t* conjunto = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (conjunto == NULL) {
        free (conjunto);
        libertar (baralho, mao, conjuntoTotal);
        return -1;
    }
        
    if (tamAnterior==2) conjuntosTamanho2 (baralho, conjuntoTotal, conjunto, posicao, valorCartaMaisAlta, jaImprimiu);
    else conjuntosTamanho3 (baralho, conjuntoTotal, conjunto, valorCartaMaisAlta, jaImprimiu);

    free(conjunto);
    free(conjuntoTotal);
    return 0;
}

void conjuntosTamanho2(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int valorCartaMaisAlta, bool *jaImprimiu) {
    // quantidade de cartas pode ser 3 ou 4
    int p; // primeira carta
    int s; // segunda carta
    int posicaoPfinal = quantidade - 2; // última posição da primeira carta
    for (p = 0; p <= posicaoPfinal; p++) {
        if (*jaImprimiu) {
            return; // Se já imprimiu, saia do loop externo
        }
        int posicaoSfinal = quantidade - 1;
        conjunto[0] = conjuntoTotal[p];

        for (s = p + 1; s <= posicaoSfinal; s++) {
            if (*jaImprimiu) {
                return; // Se já imprimiu, saia do loop interno
            }
            conjunto[1] = conjuntoTotal[s];
            if (valorDaCartaMaisAlta(baralho, conjunto, 2) > valorCartaMaisAlta) {
                *jaImprimiu = true;
                funcaoImprimir(conjunto, 2);
                return; // Saia imediatamente após imprimir o primeiro conjunto válido
            }
        }
    }
}

void conjuntosTamanho3(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int valorCartaMaisAlta, bool *jaImprimiu) {
    // quantidade de cartas é sempre 4
    int p; // primeira carta
    int s; // segunda carta
    int t; // terceira carta
    int posicaoPfinal = 1; // última posição da primeira carta
    int posicaoSfinal = 2; // última posição da segunda carta
    int posicaoTfinal = 3; // última posição da terceira carta
    for (p = 0; p <= posicaoPfinal; p++) {
        if (*jaImprimiu) {
            return; // Se já imprimiu, saia da função
        }
        conjunto[0] = conjuntoTotal[p];

        for (s = p + 1; s <= posicaoSfinal; s++) {
            if (*jaImprimiu) {
                return; // Se já imprimiu, saia da função
            }
            conjunto[1] = conjuntoTotal[s];

            for (t = s + 1; t <= posicaoTfinal; t++) {
                if (*jaImprimiu) {
                    return; // Se já imprimiu, saia da função
                }
                conjunto[2] = conjuntoTotal[t];
                if (valorDaCartaMaisAlta(baralho, conjunto, 3) > valorCartaMaisAlta) {
                    *jaImprimiu = true;
                    funcaoImprimir(conjunto, 3);
                    return; // Saia da função após imprimir o primeiro conjunto válido
                }
            }
        }
    }
}
