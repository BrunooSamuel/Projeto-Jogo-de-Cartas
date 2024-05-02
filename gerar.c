#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void gerarConjunto (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);
    for (int i = numeroMaisAlta; i <= 14; i++)
    {
        int contagem=analisarMao (baralho, mao, i, tamMao);
        // wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

        if (contagem==tamAnterior) 
        {
            //wprintf(L"Pode haver conjunto no numero %d, pq tem %d cartas\n", i, contagem);
            ContinuacaoGerarConjunto (baralho, mao, i, tamAnterior, tamMao, valorCartaMaisAlta);
        }
        else if (contagem>tamAnterior) variosConjuntos(baralho, mao, i, contagem, tamAnterior, tamMao, valorCartaMaisAlta);
    }
}

//Caso so haja uma hipotese de impressao
int ContinuacaoGerarConjunto (carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao, int valorCartaMaisAlta) {
    bool encontrou=false;
    int posicao=0;

    wchar_t* conjuntoAtual = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
    if (conjuntoAtual == NULL) {
        free (conjuntoAtual);
        free (baralho);
        free (mao);
        return -1;
    }

    for (int i = 0; i < tamMao && posicao<tamAnterior; i++)
    {
        for (int k = (numero*4)-4; k <= (numero*4)-1 && !encontrou; k++)
        {
            //wprintf(L"Comparando %lc e %lc\n", mao[i],baralho[k].codigo);
            if (mao[i]==baralho[k].codigo) 
            {
                conjuntoAtual[posicao]=mao[i];
                posicao++;
                encontrou=true;
            }
        }
        encontrou=false;
    }

    int valorConjuntoAtual=valorDaCartaMaisAlta (baralho, conjuntoAtual, tamAnterior);
    //wprintf(L"Conjunto atual -> %ls\nvalores %d e %d\n", conjuntoAtual, valorConjuntoAtual,valorCartaMaisAlta);
    if (posicao == tamAnterior && valorConjuntoAtual > valorCartaMaisAlta)
    {
        imprimirConjuntos (conjuntoAtual, tamAnterior);
    }

    free (conjuntoAtual);
    return 0;
}

int variosConjuntos(carta baralho[], wchar_t mao[], int numero, int quantidade, int tamAnterior, int tamMao, int valorCartaMaisAlta) {
    wchar_t* conjuntoTotal = (wchar_t*)malloc (sizeof(wchar_t)*quantidade);
    if (conjuntoTotal == NULL) {
        free (conjuntoTotal);
        free (baralho);
        free (mao);
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
        free (conjuntoTotal);
        free (baralho);
        free (mao);
        return -1;
    }
        
    if (tamAnterior==1) {
        for (int i = 0; i < quantidade; i++)
        {
            conjunto[0]=conjuntoTotal[i];
            imprimirConjuntos (conjunto, tamAnterior);
        }
        
    }
    else if (tamAnterior==2) conjuntosTamanho2 (baralho, conjuntoTotal, conjunto, posicao, valorCartaMaisAlta);
    else conjuntosTamanho3 (baralho, conjuntoTotal, conjunto, valorCartaMaisAlta);

    free(conjunto);

    free(conjuntoTotal);
    return 0;
}

void conjuntosTamanho2 (carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int quantidade, int valorCartaMaisAlta) {
    //quantidade de cartas pode ser 3 ou 4
    int p; //primeira carta
    int s; // segunda carta
    int posicaoPfinal=quantidade-2; //ultima posicao da primeira carta
    for (p=0; p <= posicaoPfinal;p++) 
    {            
        int posicaoSfinal=quantidade-1;
        conjunto[0]=conjuntoTotal[p];         
        for (s = p + 1; s <= posicaoSfinal; s++) 
        {
            conjunto[1]=conjuntoTotal[s];
            if (valorDaCartaMaisAlta(baralho,conjunto,2)>valorCartaMaisAlta) {imprimirConjuntos (conjunto, 2);}
        }
    }
}

void conjuntosTamanho3(carta baralho[], wchar_t conjuntoTotal[], wchar_t conjunto[], int valorCartaMaisAlta) {
    //quantidade de cartas é sempre 4
    int p; //primeira carta
    int s; // segunda carta
    int t; //terceira carta
    int posicaoPfinal=1; //ultima posicao da primeira carta
    for (p=0;p <= posicaoPfinal;p++) 
    {            
        int posicaoSfinal=2;
        int posicaoTfinal=3;
        conjunto[0]=conjuntoTotal[p];            
        for (s = p + 1; s <= posicaoSfinal; s++) 
        {
            conjunto[1]=conjuntoTotal[s];
            for (t = s + 1; t <= posicaoTfinal; t++)
            {
                conjunto[2]=conjuntoTotal[t];
                if (valorDaCartaMaisAlta(baralho,conjunto,3)>valorCartaMaisAlta) {imprimirConjuntos (conjunto, 3);}
            }
        }
    }
}
// Criei essa função para usar como teste na gerarSequencia
void imprimirSequencia(wchar_t* sequencia, int tamanho) {
    wprintf(L"Sequência maior encontrada: ");
    for (int i = 0; i < tamanho; i++) {
        wprintf(L"%lc ", sequencia[i]);
    }
    wprintf(L"\n");
}
void gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta, wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Sequencia\n"); 

void imprimirConjuntos (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int gerarSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta);  
    for (int i = tamAnterior-1; i < tamMao; i++)
    {
        int numero=numeroCarta (baralho, mao[i]);
        
        //i passa para a posicao na mao da ultima carta igual (por exemplo, se tem varios 5, vai parar no ultimo)
        for (int k = i+1; k<tamMao && numeroCarta (baralho, mao[k])==numero; k++) {i=k;}
        
        bool existeSequencia=verificarSequencia(baralho, mao, numero, tamAnterior, tamMao);
        
        if (numero>=numeroMaisAlta && existeSequencia) 
        {
            bool encontradoj=false;
            int posicaoComeco;
            //posicaoComeco é a posicao da menor carta que vai pertencer á sequencia
            for (int j = 0; j < i && !encontradoj; j++)
            {
                if (numeroCarta (baralho, mao[j])==(numero-tamAnterior+1)) {encontradoj=true;posicaoComeco=j;}
            }
            
            int quantidade=i-posicaoComeco;
            
            wchar_t* sequenciaTotal = (wchar_t*)malloc (sizeof(wchar_t)*quantidade);
            if (sequenciaTotal == NULL) {
                free (sequenciaTotal);
                free (baralho);
                free (mao);
                return -1;
            }
            
            //vai colocar no array sequenciaTotal, todas as cartas desse intervalo
            int pos=0;
            for (int j = posicaoComeco; j <= i; j++)
            {
                sequenciaTotal[pos]=mao[j];
                pos++;
            }
            continuacaoGerarSequencias(baralho, sequenciaTotal, tamAnterior, pos, valorCartaMaisAlta);

            free(sequenciaTotal);        
        }
    }
    return 0;
}

//verifica se pode existir sequencia nesse numero
bool verificarSequencia(carta baralho[], wchar_t mao[], int numero, int tamAnterior, int tamMao) {
    bool r=true;
    int limiteNumero = numero-tamAnterior+1;

    while (r && numero>=limiteNumero) {
        if (analisarMao (baralho, mao, numero, tamMao)==0) r=false;
        numero--;
    }
    return r;
}

//Recebe já apenas as cartas para serem geradas as sequencias
int continuacaoGerarSequencias(carta baralho[], wchar_t sequenciaTotal[], int tamAnterior, int tamanho, int valorCartaMaisAlta) {
    if (tamanho==tamAnterior) imprimirSequencias (sequenciaTotal, tamAnterior);
    
    else 
    {
        imprimirSequencias(sequenciaTotal,tamanho);
        for (int i = 0; i < tamanho; i++)
        {
            
            /*
            wchar_t* sequencia = (wchar_t*)malloc (sizeof(wchar_t)*tamAnterior);
            if (sequencia == NULL) {
                free (sequencia);
                free (sequenciaTotal);
                free (baralho);
                return -1;
            }
            
            int pos=0;
            for (int j = 0; j < tamanho; j++)
            {
                if (numeroCarta(baralho, sequenciaTotal[j]) != numeroCarta(baralho, sequenciaTotal[j + 1])) {
                    sequencia[pos] = sequenciaTotal[j];
                    pos++;
                }
            }
            
            if (valorDaCartaMaisAlta(baralho,sequencia,tamAnterior)>valorCartaMaisAlta) imprimirSequencias(sequencia,tamAnterior);
            
            free (sequencia);
            */
        }
        
    }
    
    return 0;
}

void imprimirSequencias (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void gerarDuplaSequencia (carta baralho[], wchar_t mao[], int valorCartaMaisAlta,wchar_t codigoCartaMaisAlta, int tamAnterior, int tamMao) {
    wprintf(L"Veio para gerar Dupla Sequencia\n");

    int numeroMaisAlta=numeroCarta(baralho, codigoCartaMaisAlta); 

    //encontrar a carta maior que a carta mais alta da jogada anterior
    for (int i = 0; i < tamMao; i++){ 

        int numeroMaior = numeroCarta (baralho, mao[i]);

        //verificar se tem dupla
        if(numeroMaior > numeroMaisAlta) {
            
            int contagem = analisarMao (baralho, mao, i, tamMao);
            // wprintf(L"A mão tem %d cartas de número %d\n", contagem, i);

            //se tiver, prosseguir para formar dupla sequência
            if (contagem >= 2) {
            continuacaogerarDupSeq (baralho, mao, tamAnterior, tamMao, i);
            }
        }        
    }  
}


int continuacaogerarDupSeq(carta baralho[], wchar_t mao[], int tamAnterior, int tamMao, int posicao) {
    wchar_t* duplasSeqPossiveis = (wchar_t*)malloc(sizeof(wchar_t) * tamAnterior);
    if (duplasSeqPossiveis == NULL) {
        free(duplasSeqPossiveis);
        return -1;
    }

    bool existe = false;
    int tamanho = tamAnterior; // Correção aqui
    int posSequencia = 1;
    int posAnt = posicao;
    duplasSeqPossiveis[0] = mao[posicao]; //o primeiro elemento do array recebe o caracter da posicao da mao
    wprintf(L"Tamanho antes %d\n", tamanho);
    for (int j = posicao; j < tamMao - 1 && tamanho > 0; j++) // Correção aqui
    {
        wprintf(L"%lc e %lc\n", mao[posAnt], mao[j+1]);
        if (numeroCarta(baralho, mao[posAnt]) == (numeroCarta(baralho, mao[j + 1])))
        {
            duplasSeqPossiveis[posSequencia] = mao[j + 1];
            posSequencia++;
            tamanho--;

            if (j + 2 < tamMao && numeroCarta(baralho, mao[posAnt]) == (numeroCarta(baralho, mao[j + 2])) - 1) // Correção aqui
            {
                posAnt = j + 1;
                duplasSeqPossiveis[posSequencia] = mao[j + 2]; // Correção aqui
                posSequencia++;
                tamanho--;
            }
        }
    }
    wprintf(L"Tamanho %d\n", tamanho);
    if (tamanho == 0) existe = true;

    if (existe)
    {
        wprintf(L"Ola\n");
        for (int i = 0; i < tamAnterior; i++)
        {
            if (i == tamAnterior - 1) wprintf(L"%lc\n", duplasSeqPossiveis[i]);
            else wprintf(L"%lc ", duplasSeqPossiveis[i]);
        }
    }

    free(duplasSeqPossiveis);

    return 0;
}


