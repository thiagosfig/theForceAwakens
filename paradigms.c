#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combination.h"
#include "paradigms.h"
#include <math.h>

//funcao para liberar matriz de 2 dimensões
void LiberaMatriz(int **matriz, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

//funcao que retorna maior valor
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

//valor que retorna menor valor
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

//programacao dinamica com memoization
int PDmemo(int n, int k, int **matriz)
{
    int atual = n + 1;
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

    ////////////// inicio impressão matriz
    // for (int i = 0; i <= n; i++)
    // {
    //     for (int j = 0; j <= k; j++)
    //     {
    //         printf("[");
    //         for (int l = 1; l <= atual; l++)
    //         {
    //             printf(" %d ", mat[l][i][j]);
    //         }
    //         printf("], ");
    //     }
    //     printf("\n");
    // }
    ///////////// fim impressão a matriz

    printf("%d\n", mat[atual][n][k]);

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

//algoritmo guloso que utiliza o maior caminho entre planetas como estratégia gulosa
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

//algoritmo guloso que utiliza uma média como estratégia gulosa
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