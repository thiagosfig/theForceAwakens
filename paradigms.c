#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combination.h"
#include "paradigms.h"

void dynamicProg(int n, int k, int *a)
{

    printf("\nn = %d, k=%d", n, k);

    for (int i = 0; i < n + 1; i++)
    {
        printf("\n%d", a[i]);
    }
    printf("\n\n");

    return;
}

void greedyAlg(int n, int k, int *a)
{

    int i = 0;
    int sum = 0;
    int max = -1;
    int maxLocal = 0;

    for (i; i < n + 1; i++)
    {
        sum = sum + a[i];
        if (a[i] > max)
        {
            max = a[i];
        }
    }

    if (sum / k > max)
    {
        max = sum / k;
    }

    //comb eh um vetor de 1 a n planetas
    int *comb = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    int posDestino;
    int posAtual = 0;
    int custoViagem = 0;
    int conquistado = 0;
    for (int j = 0; j < n; j++)
    {
        posDestino = comb[j];
        for (int y = posAtual; y < posDestino; y++)
        {

            custoViagem = custoViagem + a[y];
            if ((custoViagem < max) & (posDestino < n) & ((custoViagem + a[y + 1]) <= max) & ((n - y) > (k - conquistado)))
            {
                posDestino++;
                j++;
            }
        }
        if (posDestino != n + 1)
            conquistado++;
        // printf("Saindo de %d para %d -> ", posAtual, posDestino);
        // printf("Custo: %d - Conquistado = %d\n", custoViagem, conquistado);
        if (custoViagem > maxLocal)
            maxLocal = custoViagem;
        custoViagem = 0;
        posAtual = comb[j];

        if (conquistado == k)
            break;
    }
    posDestino++;
    for (int y = posAtual; y <= n + 1; y++)
    {
        custoViagem = custoViagem + a[y];
    }
    // printf("Saindo de %d para %d -> ", posAtual, posDestino);
    // printf("Custo: %d\n", custoViagem);
    if (custoViagem > maxLocal)
        maxLocal = custoViagem;

    printf("%d\n", maxLocal);

    return;
}

// Estrategia de foca bruta
void bruteForce(int n, int k, int *rota)
{

    //comb eh um vetor de 1 a n planetas
    int *comb = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    Combination(rota, comb, n, k);

    free(comb);

    return;
}