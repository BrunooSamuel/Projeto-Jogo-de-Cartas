#include "cartas.h"
#include <wchar.h>


//variáveis globais para serem usadas em todos os arquivos
carta AsEspadas;

int definirCartas() {

    AsEspadas.codigo=0x1F0A1; AsEspadas.naipe=1; AsEspadas.numero=1; AsEspadas.valor=1;

    return 0;
}