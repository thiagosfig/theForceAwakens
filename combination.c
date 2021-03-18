#include "combination.h"
#include <stdio.h>

void Combination(int *path, int comb[], int n, int k)
{
    //data eh um arranjo com k elementos
    int data[k];
    int inf = 9999;

    int minMax = combinationUtil(path, comb, data, 0, n - 1, 0, k, n, inf);

    printf("%d\n", minMax);

    return;
}

int combinationUtil(int *path, int comb[], int data[], int start, int end, int index, int k, int n, int minMax)
{
    int pathSize = n;
    int i, j;
    int posAtual = 0;
    int posDestino = 0;
    int custoViagem = 0;
    int maxLocal = 0;

    if (index == k)
    {
        for (j = 0; j < k; j++)
        {
            posDestino = data[j];
            // printf("\nSaindo de %d para %d -> ", posAtual, posDestino);
            for (int y = posAtual; y < posDestino; y++)
            {
                custoViagem = custoViagem + path[y];
            }
            // printf("Custo: %d", custoViagem);
            if (custoViagem > maxLocal)
                maxLocal = custoViagem;
            custoViagem = 0;
            posAtual = data[j];
        }
        // printf("\nSaindo de %d para F -> ", posAtual);
        for (int y = posAtual; y <= pathSize + 1; y++)
        {
            custoViagem = custoViagem + path[y];
        }
        // printf("Custo: %d\n", custoViagem);
        if (custoViagem > maxLocal)
            maxLocal = custoViagem;
        // printf("Max local = %d\n", maxLocal);

        if (minMax > maxLocal)
            minMax = maxLocal;

        return minMax;
    }

    for (i = start; i <= end && end - i + 1 >= k - index; i++)
    {
        data[index] = comb[i];
        minMax = combinationUtil(path, comb, data, i + 1, end, index + 1, k, n, minMax);
    }

    return minMax;
}
