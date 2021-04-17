#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "combination.h"
#include "paradigms.h"
#include "paradigmsUtil.h"

//Algoritmo que imprime a solucao otima do problema da reconquista a partir da Programacao Dinamica
//com memoization.
//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -
//int[]     -> Solucao otima do problema da reconquista para os parametros dados?;
void dynamicProg(int n, int k, int *rota)
{
    int atual = n + 1;
    int **matriz = matrizCaminhos(n, k, rota);
    int ***mat;

    //Variaveis para iteracao loop for
    int i, j, l;

    //Dimensoes da matriz mat
    int a = atual + 1;
    int b = n + 1;
    int c = k + 1;

    //Alocacao dinâmica da matriz mat
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
    //Fim alocacao matriz

    //Preenchimento da matriz
    //caso base onde n = 0
    for (i = 0; i <= atual; i++)
    {
        for (j = 0; j <= k; j++)
        {
            mat[i][0][j] = 0;
        }
    }

    //caso base para k = 0
    for (i = 0; i <= atual; i++)
    {
        for (j = 0; j <= n; j++)
        {
            mat[i][j][0] = matriz[0][i];
        }
    }

    //utilização da recorrência de subproblemas
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
    //Fim preenchimento matriz

    //Impressao do resultado
    printf("%d\n", mat[atual][n][k]);

    //Libera matriz de caminhos
    liberaMatriz(matriz, n + 2);

    //Inicio liberacao da matriz mat
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
    //Fim liberacao da matriz mat

    return;
}

//Algoritmo Guloso que imprime uma solucao aproximada para o problema da reconquista.
//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -
//int[]     -> Solucao aproximada da reconquista para os parametros dados?;
void greedyAlg(int n, int k, int *rota)
{
    int maxLocal = 0;

    //Verificacao se e necessário conquistar algum planeta
    if (k > 0)
    {
        int max = greedyAlgMax(n, k, rota);   // Estrategia gulosa 01
        int mean = greedyAlgMean(n, k, rota); // Estrategia gulosa 02

        maxLocal = min(max, mean); // Escolhe resultado da melhor estrategia
    }
    else
    {
        int i;
        for (i = 0; i <= n; i++)
        {
            maxLocal += rota[i];
        }
    }

    //Impressao do resultado
    printf("%d\n", maxLocal);

    return;
}

//Algoritmo de Forca Bruta que chama uma funcao para gerar e testar todas as combinacoes de
//caminhos possiveis, alem de imprimir as solucoes encontradas.
//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -
//int[]     -> Solucao otima da reconquista para os parametros dados?;
void bruteForce(int n, int k, int *rota)
{

    //Gerando matriz de caminhos entre planetas
    int **matriz = matrizCaminhos(n, k, rota);

    //Comb e um vetor de 1 a n planetas
    int *comb = (int *)calloc(n, sizeof(int));
    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    //Gerar e testar todas as combinações
    combination(matriz, comb, n, k);

    //Liberar matriz de caminhos
    liberaMatriz(matriz, n + 2);

    //Liberar arranjo de planetas
    free(comb);

    return;
}
