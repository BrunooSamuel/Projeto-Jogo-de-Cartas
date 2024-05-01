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
    limpar();
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

        wchar_t *jogadaAnterior = alocarMao ();
        int tamJogadaAnterior = lerUmaMao(jogadaAnterior, baralhoDef);
        //wprintf(L"Jogada Anterior: %lsTamanho:%d\n", jogadaAnterior,tamJogadaAnterior);

        ordenarMao (baralhoDef, jogadaAnterior, tamJogadaAnterior);
        wchar_t codigoMaisAltaAnterior=jogadaAnterior[tamJogadaAnterior-1];
        int valorMaisAltaAnterior=valorDaCartaMaisAlta (baralhoDef, jogadaAnterior, tamJogadaAnterior);
        int numReisAnterior=contadorAuxiliar (baralhoDef, jogadaAnterior);
        //wprintf(L"Carta mais alta da jogada anterior : %lc\tO valor dela é %d\nO Numero de reis é %d\n", codigoMaisAltaAnterior,valorMaisAltaAnterior,numReisAnterior);


        int combAnterior=devolveCombinacao (jogadaAnterior, tamJogadaAnterior, baralhoDef);
        //wprintf(L"A jogada anterior era de combinação: %d\n", combAnterior);

        wchar_t *maoJogador = alocarMao ();
        int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef);
        ordenarMao (baralhoDef, maoJogador, tamMaoJogador);
        //wprintf(L"Mao Inicial: %lsTamanho:%d\n", maoJogador,tamMaoJogador);


        if (numReisAnterior>0) 
        {
            wprintf(L"Casos Especiais Reis!!!!!!\n");
            // resto do codigo
        }
        else 
        {   
            if (combAnterior==0) gerarConjunto(baralhoDef, maoJogador, valorMaisAltaAnterior, codigoMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador);
            else if (combAnterior==1) gerarSequencia(baralhoDef, maoJogador, valorMaisAltaAnterior, codigoMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador);
            else if (combAnterior==2) gerarDuplaSequencia(baralhoDef, maoJogador, valorMaisAltaAnterior, codigoMaisAltaAnterior, tamJogadaAnterior, tamMaoJogador);
        }

        free(jogadaAnterior);
        free(maoJogador);
}


/* COISAS DO GUIAO ANTERIOR

// se e2 for diferente de 0, vai realizar a contadorReis, caso contrario, fica 0
        int numReis = e2 != 0 ? contadorReis(baralhoDef, jogadasAnteriores, e2 - 1) : 0;
        //wprintf(L"Numero de reis %d\n", numReis);
        // se numReis for maior que 0, vai realizar a verificarJogadaComReis, se não, verificarJogada
        bool valida = numReis > 0 ? verificarJogadacomReis(baralhoDef, jogadaJogador, numReis, tamJogadaJogador) : verificarJogada(baralhoDef, jogadaJogador, jogadasAnteriores, arrayTamanhos, tamJogadaJogador, NumJogAnteriores);
        
        ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
        
        if(valida) verificarCartasMao(maoJogador, jogadaJogador, &tamMaoJogador);
        else tamMaoJogador--; //porque quando nao é alterada, imprime com um \n a mais

        if (tamMaoJogador>=0) imprimirUmaMao (maoJogador);

*/