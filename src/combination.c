#include "combination.h"
#include <stdio.h>

void Combination(int **path, int comb[], int n, int k)
{
    //data eh um arranjo com k elementos
    int data[k];
    int inf = 9999;

    int minMax = combinationUtil(path, comb, data, 0, n - 1, 0, k, n, inf);

    printf("%d\n", minMax);

    return;
}

int combinationUtil(int **path, int comb[], int data[], int start, int end, int index, int k, int n, int minMax)
{
    int pathSize = n;
    int i, j;
    int posAtual = 0;
    int posDestino = 0;
    int custoViagem = 0;
    int maxLocal = 0;

    //Percorrer combinação
    if (index == k)
    {
        for (j = 0; j < k; j++)
        {
            posDestino = data[j];
            custoViagem = path[posAtual][posDestino];
            if (custoViagem > maxLocal)
                maxLocal = custoViagem;
            custoViagem = 0;
            posAtual = data[j];
        }

        custoViagem = path[posAtual][pathSize + 1];

        if (custoViagem > maxLocal)
            maxLocal = custoViagem;

        if (minMax > maxLocal)
            minMax = maxLocal;

        return minMax;
    }

    //Gerar combinações possiveis
    for (i = start; i <= end && end - i + 1 >= k - index; i++)
    {
        data[index] = comb[i];
        minMax = combinationUtil(path, comb, data, i + 1, end, index + 1, k, n, minMax);
    }

    return minMax;
}
