#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include "funcoes.h"
#include "cartas.h"

void imprimir () {
    setlocale(LC_CTYPE, "C.UTF-8");
    wprintf(L"%lc\n", AsEspadas.codigo);
}


