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
    
    for (int e1=1; e1<=numtestes;e1++) 
    {
        wprintf(L"Teste %d\n", e1);

        // lê o numero de jogadas anteriores que recebe
        int NumJogAnteriores=scanInt();
        
        limpar();

        int *arrayTamanhos=alocarArrayInt(NumJogAnteriores);

        int *arrayComb=alocarArrayInt(NumJogAnteriores);
    
        wchar_t *jogadasAnteriores=alocarArrayWchar (arrayTamanhos, arrayComb, NumJogAnteriores);
        
        wchar_t *maoJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamMaoJogador = lerUmaMao(maoJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);
<<<<<<< Updated upstream
        
        wprintf(L"Mao Inicial:\n%ls", maoJogador); //teste
        
=======
        // wprintf(L"Mao Inicial:\n%ls", maoJogador); //teste

>>>>>>> Stashed changes
        int e2=0;
        while (e2<NumJogAnteriores)   
        {
            arrayTamanhos[e2]=lerMao(baralhoDef, arrayComb, jogadasAnteriores, e2, arrayTamanhos);
            e2++;
        }
<<<<<<< Updated upstream
        wchar_t *jogadaJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamJogadaJogador = lerUmaMao(jogadaJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);

        //bool tamIguais= compararTamanhos(arrayTamanhos,linhas);
        //bool comIguais= compararCombinacoes(arrayComb);

        // if (!tamIguais||!comIguais) wprintf(L"Combinações não iguais!\n");

        //Este print todo é teste
        if (e2==0) wprintf(L"Não tem Jogadas Anteriores\n");
        else {
            wprintf(L"Jogadas Anteriores:\n");
            for (int i = 0; i < e2; i++) {
                wprintf(L"%ls\n", &jogadasAnteriores[i * 32]);
            }
        }

        wprintf(L"Jogada do Jogador:\n%ls", jogadaJogador);
        //para cima é teste

        // else {
            // ordenarTudo (baralhoDef, jogadasAnteriores, arrayTamanhos[e2-1], linhas);
            // maosCrescente (baralhoDef, jogadasAnteriores, arrayTamanhos[e2-1], linhas, arrayTamanhos);
            ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
=======
        

        wchar_t *jogadaJogador = alocarMao (arrayTamanhos,arrayComb, jogadasAnteriores);
        int tamJogadaJogador = lerUmaMao(jogadaJogador, baralhoDef, arrayComb, jogadasAnteriores, arrayTamanhos);
        
        int numReis=0;
        if (e2!=0) numReis = contadorReis (baralhoDef, jogadasAnteriores, (e2-1), arrayTamanhos[e2-1]);
        
        bool valida=false;
        valida = verificarJogada(baralhoDef, jogadaJogador, jogadasAnteriores, arrayTamanhos, tamJogadaJogador, NumJogAnteriores);
        if (e2!=0 && numReis>0 && numReis<4) valida = verificarJogadacomReis(baralhoDef, jogadaJogador, jogadasAnteriores, arrayTamanhos, tamJogadaJogador, NumJogAnteriores);
        
        
        ordenarMao (baralhoDef,maoJogador,tamMaoJogador);
        
        if(valida) verificarCartasMao(maoJogador, jogadaJogador, &tamMaoJogador);
        else tamMaoJogador--; //porque quando nao é alterada, imprime com um \n a mais
        
        
        imprimirUmaMao (maoJogador);
>>>>>>> Stashed changes
        


        libertarTodas (arrayTamanhos,arrayComb,jogadasAnteriores);
        free(jogadaJogador);
        free(maoJogador);
    }
    
    // Liberta o espaço na memória alocada para o baralho
    free(baralho);

    return 0;
}