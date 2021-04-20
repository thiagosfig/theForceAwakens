#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "paradigmsUtil.h"

//Funcao que compara dois valores e retorna o maior entre eles.
//Entrada: int a -> Primeiro dos valores a serem comparados;
//         int b -> Segundo dos valores a serem comparados;
//Saida:   int   -> Maior entre a e b;
int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

//Funcao que compara dois valores e retorna o menor entre eles.
//Entrada: int a -> Primeiro dos valores a serem comparados;
//         int b -> Segundo dos valores a serem comparados;
//Saida:   int   -> Menor entre a e b;
int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

//Programacao Dinamica a partir da recorrencia de custo (Forca Bruta).
//Entrada: int    atual -> Planeta atual da rota;
//         int     size -> Numero de rotas;
//         int        n -> Próximo planeta da rota;
//         int        k -> Numero de planetas a serem conquistados;
//         int **matriz -> Matriz quadrada que representa a distancia dos planetas da rota;
//Saida:   int       mn -> Valor minimo dos custos maximos de conquista dos planetas;
int recorrenciaPD(int atual, int size, int n, int k, int **matriz)
{
    //mx1 e mx2 recebem o máximo de uma dada recorrência
    //mn recebe o minimo entre mx1 e mx2, ou seja, menor máxima
    int mx1, mx2, mn;

    //Máximo de planetas já conquistado
    //caso base em que já se conquistou os k planetas necessários
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
    //caso base em que não há mais planetas
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

//Funcao que libera a memoria alocada para a matriz quadrada.
//Entrada: int **matriz -> Matriz quadrada que sera liberada;
//         int     size -> Tamanho da matriz quadrada a ser liberada;
//Saida:   -
void liberaMatriz(int **matriz, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(matriz[i]);
    }
    free(matriz);
}

//Funcao para criar matriz com distancia entre planetas.
//Entrada: int        n -> Numero de planetas da rota;
//         int        k -> Numero de planetas a serem reconquistados;
//         int       *a -> Distancias da rota;
//Saida:   int **matriz -> Matriz quadrada que representa a distancia entre os planetas da rota;
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

//Algoritmo Guloso com estratégia gulosa de média do caminho.
//Entrada: int        n -> Numero de planetas da rota;
//         int        k -> Numero de planetas a serem reconquistados;
//         int       *a -> Distancias da rota;
//Saida:   int maxLocal -> Valor que representa o maior custo de conquistar k planetas da rota;
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
    cMax = sum / (k + 1) * 1.4; // acrescenta 40% à média como fator de correção

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
