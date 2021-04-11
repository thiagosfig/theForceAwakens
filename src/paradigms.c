#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "combination.h"
#include "paradigms.h"
#include "paradigmsUtil.h"


//programacao dinamica com recorrencia forca bruta
int dynamic_algorithm(int atual, int size, int n, int k, int **matriz)
{
    int maxL, maxL1, minL;

    //Máximo de planetas já conquistado
    if (k == 0)
    {
        return matriz[atual][size];
    }

    // k igual a quantidade de planetas a frente
    // Será necssário conquistar os próximos planetas
    if (k == (size - n))
    {
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
        return maxL;
    }

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

//criar matriz para ser utilizada na pd
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

    PDmemo(n, k, matriz);

    LiberaMatriz(matriz, n + 2);

    return;
}


//base para algoritmo guloso
void greedyAlg(int n, int k, int *a)
{
    int maxLocal = 0;

    if (k > 0)
    {
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
    }
    else
    {
        int i = 0;
        for (i = 0; i <= n; i++)
        {
            maxLocal += a[i];
        }
    }
    printf("%d\n", maxLocal);

    return;
}

//algoritmo de força bruta
void bruteForce(int n, int k, int *a)
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

    //comb eh um vetor de 1 a n planetas
    int *comb = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    Combination(matriz, comb, n, k);

    LiberaMatriz(matriz, n + 2);

    free(comb);

    return;
}
