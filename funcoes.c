#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"
#include "cartas.h"

int lerMao(carta baralho[], int *arrayComb, wchar_t *jogadasAnteriores, int *posMaos, int *arrayTamanhos) {

    //32 porque houve testes de dupla sequencia onde o input foi de 28 cartas, +4 de margem
    wchar_t maoTemp[32]={0};

    //funcao que coloca as cartas recebidas no array mao
    if (fgetws(maoTemp, 32, stdin)==NULL) {
        wprintf(L"O Scan da mão é inválido.\n");
        free(arrayTamanhos);
        free(arrayComb);
        free(baralho);
        return -1;
    }

    int tamanho = 0;

    // Percorre a sequência até encontrar '\n' ou '\0'
    while (maoTemp[tamanho] != L'\n' && maoTemp[tamanho] != L'\0') {
        tamanho++;
    }

    //copia o mao para o array jogadasAnteriores
    wcsncpy(&jogadasAnteriores[*posMaos * 32], maoTemp, tamanho);
    
    /*
    wprintf(L"tamanho %d\n", tamanho);
    int pos;
    wprintf(L"Está na mao: %ls\n", maoTemp);

    for (pos = 0; maoTemp[pos+1]!='\0'; pos++)
    {
        wprintf(L"Os símbolos são: %lc\t", maoTemp[pos]);
    }
    wprintf(L"\n");
    */
    (*posMaos)++;

    verificarCombinacao (maoTemp, tamanho, baralho, arrayComb);
    
    return tamanho;
}

int lerUmaMao(wchar_t *mao, carta baralho[]) {

    //funcao que coloca as cartas recebidas no array mao
    if (fgetws(mao, 60, stdin)==NULL) {
        wprintf(L"O Scan da mão é inválido.\n");
        free(mao);
        free(baralho);
        return -1;
    }
    
    int comprimento = 0;
    //wprintf(L"Está na mao: %ls\n", mao);
    // Percorre a sequência até encontrar '\n' ou '\0'
    while (mao[comprimento] != L'\n' && mao[comprimento] != L'\0') {
        comprimento++;
    }
    return comprimento;

    /*
    int pos;
    wprintf(L"Está na mao: %ls\n", mao);

    for (pos = 0; mao[pos+1]!='\0'; pos++)
    {
        wprintf(L"Os símbolos são: %x\t", mao[pos]);
    }
    wprintf(L"\n");
    */

    //verificarCombinacao (mao, tamanho, baralho, arrayComb);
}


// FUNCAO DE LIMPEZA
void limpar() {
    wchar_t limpeza;
    wscanf(L"%lc", &limpeza);
}

// Funcao que ordena um array
void ordena(int mao[], int tamanho) {
    int aux[tamanho];
    // O array tem como valor minimo 1 e máximo 32
    int n=1; //numero para ordenar
    int pos=0; //posiçao no array original
    int posA=0; //posicao no array auxiliar

    //ordenaçao no array auxiliar
    for (n=1; n<=32; n++)
    {   
        for (pos=0; pos<tamanho; pos++)
        {
            if (mao[pos]==n) 
            {
            aux[posA++]=n;
            }
        }
    }
    
    //passar do auxiliar para o array
    for (int i = 0; i < tamanho; i++)
    {
        mao[i]=aux[i];
    }


    /*
    FUNÇÃO TESTE QUE IMPRIME OS NUMEROS PARA VERIFICAR SE ESTÁ ORGANIZADO
    for (int i = 0; i < tamanho; i++)
    {
        wprintf(L"%d\t",aux[i]);
    }
    wprintf(L"\n");
    */
    
}   


void libertar (carta *baralho,wchar_t *mao, wchar_t *conjuntoTotal) {
    free (conjuntoTotal);
    free (baralho);
    free (mao);
}


int* alocarArrayInt (int linhas) {
    int *array=malloc((linhas)*sizeof(int)); //aloca memoria para o array
    if (array == NULL) {
        return NULL;
    }
    else {
        memset(array, 0, sizeof(array[0])*linhas); //coloca tudo a 0 no array
        return array;
    }
}

wchar_t* alocarArrayWchar (int *arrayTamanhos,int *arrayComb, int linhas) {
    wchar_t *array=malloc(sizeof(wchar_t)*32*linhas); //array para colocar todas as maos
    if (array == NULL) {
        free(array);
        free(arrayTamanhos);
        free(arrayComb);
        return NULL;
    }
    else return array; 
}

wchar_t* alocarMao () {
    wchar_t *array=malloc(sizeof(wchar_t)*60);
    if (array == NULL) {
        free(array);
        return NULL;
    }
    else return array; 
}


carta* alocarArrayCartas () {
    carta *array = malloc(56 * sizeof(carta));
    if (array == NULL) {
        return NULL;
    }
    else return array;
}

int scanInt () {
    int numero;
    if (wscanf(L"%d", &numero)==EOF) {
        return 1;
    }
    else return numero;
}

// Função para verificar e remover cartas da mão do jogador
void verificarCartasMao(wchar_t *maoJogador, wchar_t *jogadaJogador, int *tamanho) {
    if (wcscmp(jogadaJogador, L"PASSO\n") != 0) 
    {
        while (*jogadaJogador != L'\0' && *tamanho>0) {
        bool encontrou=false;
        wchar_t *posicao = NULL; // Buscar a carta na mão do jogador

        for (wchar_t *ptr = maoJogador; *ptr != L'\0' && !encontrou; ++ptr) 
        {
            if (*ptr == *jogadaJogador) 
            {
                posicao = ptr;
                encontrou=true;
            }
        }
        // Se a carta estiver na mão, removê-la
        if (encontrou) 
        {
            while (*posicao != L'\0') 
            {
                *posicao = *(posicao + 1);
                posicao++;
            }
            (*tamanho)--;
        } 
        // Avançar para a próxima carta da jogada
        jogadaJogador++;
        }
    }

    int comprimento = 0;
    // Percorre a sequência até encontrar '\n' ou '\0'
    while (maoJogador[comprimento] != L'\n' && maoJogador[comprimento] != L'\0') {
        comprimento++;
    }
    (*tamanho)=comprimento;
}


void imprimirUmaMao (wchar_t *mao) {
    int comp = 0;
    while (mao[comp] != L'\n' && mao[comp] != L'\0') 
    {
        comp++;
    }
    if (comp==0) wprintf(L"\n");
    else 
    {
        int i;
        for (i = 0; i < (comp-1); i++) 
        {
            wprintf(L"%lc ", mao[i]);
        }
        wprintf(L"%lc", mao[i]);
    }
}

int contadorReis (carta baralho[], wchar_t *jogadas, int ultimo) {
    int passos=0;
    int pos;
    bool encontrouCartas=false;
    for(pos = ultimo; pos > (ultimo-3) && passos < 3 && pos>=0 && !encontrouCartas; pos--) {
        //wprintf(L"Jogada atual: %ls\n", &jogadas[pos * 32]);
        if (jogadas[pos * 32] == L'P') {
            passos++;
        }
        else encontrouCartas=true;
    }
    pos++;
    
    //wprintf(L"Deu %d passos na funcao contadorReis\n", passos);
    if (passos==3) return 0;
    else return contadorAuxiliar(baralho, &jogadas[pos*32]);

}

int contadorAuxiliar (carta baralho[], wchar_t *jogadas) {
    int comp = 0;
    int i=0;
    bool naoCarta = false;
    for (int k = 0; k<=56 && !naoCarta; k++) {
        if (k==56) naoCarta=true;
        else if (jogadas[i] == baralho[k].codigo) 
        {
            comp++;
            i++;
            k=0;
        }
        else if (jogadas[i] == L'\n' && jogadas[i] == L'\0') naoCarta=true;
    }
    int comb[4]={0};
    verificarCombinacao(jogadas, comp, baralho, comb);
    if (comb[0]==0) return 0;
    else {
            int r=0;
        for (int i = 0; i < comp; i++) 
        {
            for (int k = 52; k < 56; k++) 
            {
                //wprintf(L"%lc e %lc\n", jogadas[i], baralho[k].codigo);
                if (jogadas[i] == baralho[k].codigo) 
                {
                r++;  
                }
            }
        }
        return r;
    }
}

int devolveCombinacao (wchar_t mao[], int quantidade, carta baralho[]) {
    int comb[4]={0};

    verificarCombinacao (mao, quantidade, baralho, comb);

    if (comb[0]==1) return 0;
    else if (comb[1]==1) return 1; 
    else if (comb[2]==1) return 2; 
    else return 3; 
}

int valorDaCartaMaisAlta (carta baralho[], wchar_t mao[], int tamanho) {
    int r=0;
    int posicao=tamanho-1;
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(mao[posicao]==baralho[k].codigo)  
        {
            //wprintf(L"%d + %d\n", baralho[k].numero*4, (baralho[k].naipe-4));
            r=baralho[k].numero*4+(baralho[k].naipe-4);
            encontrado=true;
        }
    } 
    return r;
}

int valorDaCarta(carta baralho[], wchar_t carta) {
    int r=0;
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(carta==baralho[k].codigo)  
        {
            //wprintf(L"%d + %d\n", baralho[k].numero*4, (baralho[k].naipe-4));
            r=baralho[k].numero*4+(baralho[k].naipe-4);
            encontrado=true;
        }
    } 
    return r;
}

int numeroCarta (carta baralho[], wchar_t carta) {
    int r=0;
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(carta==baralho[k].codigo)  
        {
            r=baralho[k].numero;
            encontrado=true;
            //wprintf(L"O numero é %d\n", r);
        }
    } 
    return r;
}

int naipeCarta (carta baralho[], wchar_t carta) {
    int r=0;
    bool encontrado=false;
    for (int k = 0; k < 56 && !encontrado; k++)
    {
        if(carta==baralho[k].codigo)  
        {
            r=baralho[k].naipe;
            encontrado=true;
            //wprintf(L"O numero é %d\n", r);
        }
    } 
    return r;
}

//Esta função verifica a quantidade de cartas do mesmo numero
int analisarMao (carta baralho[], wchar_t mao[], int numero, int tamanho) {
    bool passou=false;
    int pos=0;
    int t;
    int contagem=0;

    while ((pos < tamanho) && !passou)
    {
        t=numeroCarta(baralho, mao[pos]);
        if (t<numero) pos++;
        else if (t==numero) 
        {
            contagem++; 
            pos++;
        }
        else if(t>numero) {passou=true;}
    }
    //wprintf(L"A mão tem %d cartas de número %d\n", contagem, numero);
    return contagem;
}

//Esta função verifica a quantidade de cartas da mesma figura, apenas nos proximos naipes
int analisarProximosNaipes (carta baralho[], wchar_t mao[], int numero, int valor, int tamanho) {
    bool passou=false;
    int pos=0;
    int t;
    int contagem=0;

    while ((pos < tamanho) && !passou)
    {
        t=numeroCarta(baralho, mao[pos]);
        if (t<numero) pos++;
        else if (t==numero) 
        {
            if (valorDaCarta(baralho, mao[pos])>valor) {contagem++;} pos++;
        }
        else if(t>numero) {passou=true;}
    }
    //wprintf(L"A mão tem %d cartas de número %d\n", contagem, numero);
    return contagem;
}

void funcaoImprimir (wchar_t mao[], int tamAnterior) {
    int i;
    for (i = 0; i < tamAnterior-1; i++)
    {
        wprintf(L"%lc ", mao[i]);
    }
    wprintf(L"%lc\n", mao[i]);
}