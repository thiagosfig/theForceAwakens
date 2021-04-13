#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "paradigmsUtil.h"

//Funcao que compara dois valores e retorna o maior
//Entrada:
//Saída:
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

//Funcao que compara dois valores e retorna o menor
//Entrada:
//Saída:
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

//Programação Dinâmica por recorrência Força Bruta
//Entrada:
//Saída:
int recorrenciaPD(int atual, int size, int n, int k, int **matriz)
{
    //mx1 e mx2 recebem o máximo de uma dada recorrência
    //mn recebe o minímo entre mx1 e mx2, ou seja, menor máxima
    int mx1, mx2, mn;

    //Máximo de planetas já conquistado
    if (k == 0)
    {
        return matriz[atual][size];
    }

    //k igual a quantidade de planetas a frente
    //será necssário conquistar os todos planetas a frente
    if (k == (size - n))
    {
        mx1 = max(
            matriz[atual][n],
            recorrenciaPD(n, size, n + 1, k - 1, matriz));
        return mx1;
    }

    //chegou ao último planeta
    //será necessário ir direto para o final
    if (n == size - 1)
    {
        mx1 = max(
            matriz[atual][n],
            matriz[n][size]);
        return mx1;
    }

    //conquistar planeta
    mx1 =
        max(
            matriz[atual][n],
            recorrenciaPD(n, size, n + 1, k - 1, matriz));

    //pular planeta
    mx2 =
        max(
            matriz[atual][n + 1],
            recorrenciaPD(atual, size, n + 1, k, matriz));

    //o menor máximo
    mn = min(
        mx1,
        mx2);

    return mn;
}

//Funcao que para libera a alocação dinâmica de uma matriz quadrada
//Entrada:
//Saída:
void liberaMatriz(int **matriz, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

//Funcao para criar matriz com distancia entre planetas
//Entrada:
//Saída:
int **matrizCaminhos(int n, int k, int *a)
{
    int aux;
    int aux2 = k;
    int sum;

    //Alocação dinamica da matriz de duas dimensões
    int **matriz = (int **)malloc((n + 2) * sizeof(int *));
    for (int i = 0; i < n + 2; i++)
    {
        matriz[i] = (int *)malloc((n + 2) * sizeof(int));
    }
    //Fim da alocação dinâmica

    //Preenchimento da matriz
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
        }
        aux2--;
    }

    return matriz;
}

//Algoritmo Guloso com estratégia gulosa de maior sub-caminho entre pares de planetas
//Entrada:
//Saída:
int greedyAlgMax(int n, int k, int *a)
{

    //Variaveis para iteraçao de loop
    int i, j, y;

    //caminho Maximo
    int cMax = -1;
    int maxLocal = 0;

    //Encontrar o maior caminho entre um par de planetas adjacentes
    for (i = 0; i <= n; i++)
    {
        cMax = max(a[i], cMax);
    }

    int posDestino = 1;
    int posAtual = 0;
    int custoViagem = 0;

    //Conquistar k planetas e somar o custo da viagem
    for (j = 0; j < k; j++)
    {
        for (y = posAtual; y < posDestino; y++)
        {
            custoViagem = custoViagem + a[y];
            if ((custoViagem < cMax) & (posDestino < n) & ((custoViagem + a[y + 1]) <= cMax) & ((n - y) > (k - j)))
            {
                posDestino++;
            }
        }

        maxLocal = max(custoViagem, maxLocal);
        custoViagem = 0;
        posAtual = posDestino;
        posDestino++;
    }

    //Finalizar viagem após a conquisa de k planetas
    for (y = posAtual; y <= n; y++)
    {
        custoViagem = custoViagem + a[y];
    }

    maxLocal = max(custoViagem, maxLocal);

    return maxLocal;
}

//Algoritmo Guloso com estratégia gulosa de média do caminho
//Entrada:
//Saída:
int greedyAlgMean(int n, int k, int *a)
{

    //Variaveis para iteraçao de loop
    int i, j, y;

    //caminho Maximo
    int cMax = -1;
    int maxLocal = 0;

    //Computar valpr 'médio' para maior viagem
    int sum = 0;
    for (i = 0; i < n + 1; i++)
    {
        sum = sum + a[i];
    }
    cMax = ((sum - (sum % k)) / (k + 1)) + 2;

    int posDestino = 1;
    int posAtual = 0;
    int custoViagem = 0;

    //Conquistar k planetas e somar o custo da viagem
    for (j = 0; j < k; j++)
    {
        for (y = posAtual; y < posDestino; y++)
        {
            custoViagem = custoViagem + a[y];
            if ((custoViagem < cMax) & (posDestino < n) & ((custoViagem + a[y + 1]) <= cMax) & ((n - y) > (k - j)))
            {
                posDestino++;
            }
        }

        maxLocal = max(custoViagem, maxLocal);
        custoViagem = 0;
        posAtual = posDestino;
        posDestino++;
    }

    //Finalizar viagem após a conquisa de k planetas
    for (y = posAtual; y <= n; y++)
    {
        custoViagem = custoViagem + a[y];
    }

    maxLocal = max(custoViagem, maxLocal);

    return maxLocal;
}
