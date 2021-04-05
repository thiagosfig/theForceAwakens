#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combination.h"
#include "paradigms.h"

void LiberaMatriz(int **matriz, int l)
{
    int i;
    for (i = 0; i < l; i++)
    {
        //Liberamos primeiro as linhas
        free(matriz[i]);
    }
    free(matriz);
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int dynamic_algorithm(int atual, int size, int n, int k, int **matriz)
{

    int maxL, maxL1, minL;

    //Máximo de planetas já conquistado
    if (k == 0)
    {
        // printf("Maximo conquistado, indo pro fim\n");
        // printf("Saindo de %d para %d -> custo = %d\n", atual, size, matriz[atual][size]);
        return matriz[atual][size];
    }

    // k igual a quantidade de planetas a frente
    // Será necssário conquistar os próximos planetas
    if (k == (size - n))
    {
        // printf("Será necssário conquistar os próximos planetas.\n");
        k--;
        maxL = max(
            matriz[atual][n],
            dynamic_algorithm(n, size, n + 1, k, matriz));
        return maxL;
    }

    //Chegou ao último planeta
    if (n == size - 1)
    {
        maxL = max(
            matriz[atual][n],
            matriz[n][size]);
        // printf("Ultimo passo -> %d\n", maxL);
        return maxL;
    }

    // printf("Saindo de %d para %d -> custo = %d\n", atual, n, matriz[atual][n]);

    //conquistar planeta
    maxL =
        max(
            matriz[atual][n],
            dynamic_algorithm(n, size, n + 1, k - 1, matriz));

    //pular planeta
    maxL1 =
        max(
            matriz[atual][n + 1],
            dynamic_algorithm(atual, size, n + 1, k, matriz));

    minL = min(
        maxL,
        maxL1);

    return minL;
}

void dynamicProg(int n, int k, int *a)
{
    int aux;
    int aux2 = k;
    int **matriz;
    int sum;

    matriz = (int **)malloc((n + 2) * sizeof(int *));

    for (int i = 0; i < n + 2; i++)
    {
        matriz[i] = (int *)malloc((n + 2) * sizeof(int));
    }

    for (int i = 0; i < n + 2; i++)
    {
        aux = aux2;
        sum = 0;
        for (int j = 0; j < n + 2; j++)
        {
            if (i >= j)
            {
                matriz[i][j] = 0;
            }
            else
            {
                if ((aux > 0) & (j - 1 == n - aux + 1))
                {
                    matriz[i][j] = -999;
                    aux--;
                }
                else
                {
                    sum += a[j - 1];
                    matriz[i][j] = sum;
                }
            }
            // printf("\t%d ", matriz[i][j]);
        }
        aux2--;
        // printf("\n");
    }

    printf("%d\n", dynamic_algorithm(0, n + 1, 1, k, matriz));

    LiberaMatriz(matriz, n + 2);

    return;
}

int greedyAlgMax(int n, int k, int *a)
{

    int i = 0;
    int max = -1;
    int maxLocal = 0;

    for (i = 0; i < n + 1; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
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

        if (custoViagem > maxLocal)
            maxLocal = custoViagem;

        custoViagem = 0;
        posAtual = comb[j];

        if (conquistado == k)
            break;
    }

    posDestino++;

    for (int y = posAtual; y <= n; y++)
    {
        custoViagem = custoViagem + a[y];
    }

    if (custoViagem > maxLocal)
        maxLocal = custoViagem;

    return maxLocal;
}

int greedyAlgMean(int n, int k, int *a)
{

    int i = 0;
    int sum = 0;
    int max = -1;
    int maxLocal = 0;

    for (i = 0; i < n + 1; i++)
    {
        sum = sum + a[i];
    }

    max = ((sum - (sum % k)) / (k + 1)) + 2;

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

        if (custoViagem > maxLocal)
            maxLocal = custoViagem;

        custoViagem = 0;
        posAtual = comb[j];

        if (conquistado == k)
            break;
    }

    posDestino++;

    for (int y = posAtual; y <= n; y++)
    {
        custoViagem = custoViagem + a[y];
    }

    if (custoViagem > maxLocal)
        maxLocal = custoViagem;

    return maxLocal;
}

void greedyAlg(int n, int k, int *a)
{
    int maxLocal = 0;

    int max = greedyAlgMax(n, k, a);
    int mean = greedyAlgMean(n, k, a);

    if (max <= mean)
    {
        maxLocal = max;
    }
    else
    {
        maxLocal = mean;
    }

    printf("%d\n", maxLocal);

    return;
}

// Estrategia de forca bruta
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