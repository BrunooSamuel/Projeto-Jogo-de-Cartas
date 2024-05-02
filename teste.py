def comb(cartas, N):
    res=[]
    if N==0:
        return [[]]
    
    for I, C in enumerate (cartas):
        if len(cartas)<N:
            break
        resto = cartas[I+1:]
        for R in comb(resto,N-1):
            res.append([C]+R)
    return res

def _comb (cartas, comb_so_far, N):
    if N==0:
        print(*comb_so_Far, sep="")
        return
    
    for I,C in enumerate(cartas):
        if len(cartas)<N:
            break
        resto=cartas[I+1:]
        _comb(resto,comb_so_far + [C], N-1)

#include <stdio.h>
#include <stdlib.h>

void comb(int cartas[], int tamCartas, int N, int **result, int *tamResult, int *numResults) {
    if (N == 0) {
        result[*numResults] = (int *)malloc(tamCartas * sizeof(int));
        (*tamResult) = 0;
        (*numResults)++;
        return;
    }

    for (int i = 0; i < tamCartas; i++) {
        if (tamCartas - i < N) break;
        
        int *resto = (int *)malloc((tamCartas - i - 1) * sizeof(int));
        for (int j = i + 1; j < tamCartas; j++) {
            resto[j - i - 1] = cartas[j];
        }

        comb(resto, tamCartas - i - 1, N - 1, result, tamResult, numResults);

        free(resto);
    }
}

void _comb(int cartas[], int tamCartas, int comb_so_far[], int tamComb, int N) {
    if (N == 0) {
        for (int i = 0; i < tamComb; i++) {
            printf("%d", comb_so_far[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < tamCartas; i++) {
        if (tamCartas - i < N) break;
        
        int *resto = (int *)malloc((tamCartas - i - 1) * sizeof(int));
        for (int j = i + 1; j < tamCartas; j++) {
            resto[j - i - 1] = cartas[j];
        }

        comb(resto, tamCartas - i - 1, comb_so_far, tamComb + 1, N - 1);

        free(resto);
    }
}

int main() {
    int cartas[] = {1, 2, 3, 4, 5};
    int tamCartas = sizeof(cartas) / sizeof(cartas[0]);
    int N = 3;

    // Usando a função comb()
    int **result = (int **)malloc(100 * sizeof(int *));
    int tamResult = 0;
    int numResults = 0;
    comb(cartas, tamCartas, N, result, &tamResult, &numResults);

    printf("Combinações usando comb():\n");
    for (int i = 0; i < numResults; i++) {
        for (int j = 0; j < tamCartas - N; j++) {
            printf("%d", result[i][j]);
        }
        printf("\n");
        free(result[i]);
    }
    free(result);

    // Usando a função _comb()
    printf("\nCombinações usando _comb():\n");
    int comb_so_far[N];
    _comb(cartas, tamCartas, comb_so_far, 0, N);

    return 0;
}
