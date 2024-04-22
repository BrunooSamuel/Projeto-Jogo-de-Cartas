#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoes.h"
#include "cartas.h"

int main () {

    //Baralho de cartas, usado malloc para alocar a memória necessária para o baralho
    carta *baralho = alocarArrayCartas();

    // define o baralho
    carta *baralhoDef = definirCartas();

    if (baralhoDef == NULL) {
        free(baralho);
        return 1;
    }

    setlocale(LC_CTYPE, "C.UTF-8");

    int numtestes=scanInt();
    int totalTestes = numtestes;
    
    for (int e1=1; e1<=numtestes;e1++) 
    {
        processarCodigo(e1, baralhoDef);
        if (e1 != totalTestes) { // Verifica se não é o último teste
            wprintf(L"\n"); // Adiciona uma nova linha após cada teste, exceto o último
        }
    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}

void processarCodigo(int esteTeste, carta *baralhoDef) {

    wprintf(L"Teste %d\n", esteTeste);

        // lê o numero de jogadas anteriores que recebe
        int NumJogAnteriores=scanInt();
        
        limpar();

        int *arrayTamanhos=alocarArrayInt(NumJogAnteriores);

        int *arrayComb=alocarArrayInt(NumJogAnteriores);
    
        wchar_t *jogadasAnteriores=alocarArrayWchar (arrayTamanhos, arrayComb, NumJogAnteriores);
        
        wchar_t *maoJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);
        //wprintf(L"Mao Inicial:\n%ls", maoJogador); //teste
        
        int e2=0;
        while (e2<NumJogAnteriores)   
        {
            arrayTamanhos[e2]=lerMao(baralhoDef, arrayComb, jogadasAnteriores, &e2, arrayTamanhos);
        }
        
        wchar_t *jogadaJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamJogadaJogador = lerUmaMao(jogadaJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);
    
        // se e2 for diferente de 0, vai realizar a contadorReis, caso contrario, fica 0
        int numReis = e2 != 0 ? contadorReis(baralhoDef, jogadasAnteriores, e2 - 1) : 0;
        // se numReis for maior que 0, vai realizar a verificarJogadaComReis, se não, verificarJogada
        bool valida = numReis > 0 ? verificarJogadacomReis(baralhoDef, jogadaJogador, numReis, tamJogadaJogador) : verificarJogada(baralhoDef, jogadaJogador, jogadasAnteriores, arrayTamanhos, tamJogadaJogador, NumJogAnteriores);
        
        ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
        
        if(valida) verificarCartasMao(maoJogador, jogadaJogador, &tamMaoJogador);
        else tamMaoJogador--; //porque quando nao é alterada, imprime com um \n a mais

        if (tamMaoJogador>=0) imprimirUmaMao (maoJogador);
    
        libertarTodas (arrayTamanhos,arrayComb,jogadasAnteriores,maoJogador,jogadaJogador);
}