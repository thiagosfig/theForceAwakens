#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "combination.h"
#include "paradigms.h"
#include "paradigmsUtil.h"

//programacao dinamica com memoization
int dynamicProg(int n, int k, int *rota)
{
    int atual = n + 1;
    int **matriz = matrizCaminhos(n, k, rota);
    int ***mat;

    // variaveis para iteracao loop for
    int i, j, l;

    //dimensoes da matriz
    int a = atual + 1;
    int b = n + 1;
    int c = k + 1;

    // Alocacao dinâmica da matriz
    mat = (int ***)malloc(a * sizeof(int *));

    for (i = 0; i < a; i++)
    {
        mat[i] = (int **)malloc(b * sizeof(int *));
    }

    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            mat[i][j] = (int *)malloc(c * sizeof(int *));
        }
    }
    ///////////// fim alocacao matriz

    ////////////// inicio utilziar a matriz
    for (i = 0; i <= atual; i++)
    {
        for (j = 0; j <= k; j++)
        {
            mat[i][0][j] = 0;
        }
    }

    for (i = 0; i <= atual; i++)
    {
        for (j = 0; j <= n; j++)
        {
            mat[i][j][0] = matriz[0][i];
        }
    }

    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= k; j++)
        {
            for (l = 1; l <= atual; l++)
            {

                if (i <= j)
                {
                    mat[l][i][j] = max(
                        mat[i][i - 1][j - 1],
                        matriz[i][l]);
                }

                else
                {
                    mat[l][i][j] = min(
                        max(
                            mat[i][i - 1][j - 1],
                            matriz[i][l]),

                        max(
                            mat[l][i - 1][j],
                            matriz[i - 1][l]));
                }
            }
        }
    }
    ///////////// fim utilizar a matriz

    printf("%d\n", mat[atual][n][k]);

    // Libera matriz de caminhos
    liberaMatriz(matriz, n + 2);

    ////////// inicio liberacao da matriz
    for (i = 0; i < a; i++)
    {
        for (j = 0; j < b; j++)
        {
            free(mat[i][j]);
        }
    }
    for (i = 0; i < a; i++)
    {
        free(mat[i]);
    }
    free(mat);
    /////////// fim liberacao da matriz

    return 0;
}

//base para algoritmo guloso
void greedyAlg(int n, int k, int *rota)
{
    int maxLocal = 0;

    if (k > 0)
    {
        int max = greedyAlgMax(n, k, rota);
        int mean = greedyAlgMean(n, k, rota);

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
            maxLocal += rota[i];
        }
    }
    printf("%d\n", maxLocal);

    return;
}

//algoritmo de força bruta
void bruteForce(int n, int k, int *rota)
{

    int **matriz = matrizCaminhos(n, k, rota);

    //comb eh um vetor de 1 a n planetas
    int *comb = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    Combination(matriz, comb, n, k);

    liberaMatriz(matriz, n + 2);

    free(comb);

    return;
}
