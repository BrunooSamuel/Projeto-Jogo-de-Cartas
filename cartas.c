#include "cartas.h"
#include <wchar.h>
#include <locale.h>

/*
A ordem ascendente dos valores é: A 2 3 4 5 6 7 8 9 10 J C Q K
A ordem dos naipes é: ♠ ♥ ♦ ♣ (Espadas -> Copas -> Ouros -> Paus)
O naipe das cartas é definido por um numero: Espadas-1, Copas-2, Ouros-3, Paus-4
*/

void definirCartas(carta baralho[]) { //funcao para definir todas as cartas

    setlocale(LC_CTYPE, "C.UTF-8");

    //Espadas-1, Copas-2, Ouros-3, Paus-4
    // A 2 3 4 5 6 7 8 9 10 J C Q K
    wchar_t codigosEspadas[14] = {0x1F0A1,0x1F0A2,0x1F0A3,0x1F0A4,0x1F0A5,0x1F0A6,0x1F0A7,0x1F0A8,0x1F0A9,0x1F0AA,0x1F0AB,0x1F0AC,0x1F0AD,0x1F0AE};
    wchar_t codigosCopas[14] = {0x1F0B1,0x1F0B2,0x1F0B3,0x1F0B4,0x1F0B5,0x1F0B6,0x1F0B7,0x1F0B8,0x1F0B9,0x1F0BA,0x1F0BB,0x1F0BC,0x1F0BD,0x1F0BE};
    wchar_t codigosOuros[14] = {0x1F0C1,0x1F0C2,0x1F0C3,0x1F0C4,0x1F0C5,0x1F0C6,0x1F0C7,0x1F0C8,0x1F0C9,0x1F0CA,0x1F0CB,0x1F0CC,0x1F0CD,0x1F0CE};
    wchar_t codigosPaus[14] = {0x1F0D1,0x1F0D2,0x1F0D3,0x1F0D4,0x1F0D5,0x1F0D6,0x1F0D7,0x1F0D8,0x1F0D9,0x1F0DA,0x1FDB,0x1F0DC,0x1F0DD,0x1F0DE};

    int pos=0; //numero da carta no baralho

    for (int i = 0; i < 14; i++) // selecionar o numero da carta
    {
        for (int j = 1; j <= 4; j++) // selecionar o naipe
        {
            baralho[pos].naipe=j;
            baralho[pos].numero=(i+1);

            if(j==1) baralho[pos].codigo=codigosEspadas[i];
            else if(j==2) baralho[pos].codigo=codigosCopas[i];
            else if(j==3) baralho[pos].codigo=codigosOuros[i];
            else if(j==4) baralho[pos].codigo=codigosPaus[i];

            pos++;
        }
    }
    wprintf(L"%lc\n", 0x2648); // SO SERVE PARA TESTAR, NAO CONSIGO IMPRIMIR ESTA LINHA :(
    printf("Definiu Cartas Com Sucesso!\n");
} 