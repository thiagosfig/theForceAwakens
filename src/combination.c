#include "combination.h"
#include "paradigmsUtil.h"
#include <stdio.h>

//Função que inicia a construcao das combinacoes, alem de retornar o valor da solucão
//gerada a partir das combinacoes.
//Entrada: int **path -> Matriz de caminhos com as distancias dos planetas da rota;
//         int comb[] -> Vetor com [1..n] planetas da rota;
//         int      n -> Numero de planetas da rota;
//         int      k -> Numero de planetas a serem conquistados
//Saída:   Será impresso o maior caminho da solução aproximada;
int combination(int **path, int comb[], int n, int k)
{
    //Data é um arranjo com k elementos
    int data[k];

    //Valor 'alto' para 'simular infinito'
    int inf = 9999;

    int minMax = combinationUtil(path, comb, data, 0, n - 1, 0, k, n, inf);

    return minMax;
}

//Algoritmo para gerar as combinações e encontrar o menor sub-caminho máximo.
//Entrada: int **path -> Matriz de caminhos com as distancias dos planetas da rota;
//         int comb[] -> Vetor com [1...n] planetas da rota;
//         int data[] -> Vetor auxiliar com [1...k] elementos;
//         int  start -> Indice que indica o inicio das combinacoes que serao geradas;
//         int    end -> Limite superior das combinacoes que serao geradas;
//         int  index -> Indice que serve como marcador de qual combinacao esta sendo gerada;
//         int      k -> Numero de planetas a serem reconquistados;
//         int      n -> Numero de planetas da rota;
//         int minMax -> Valor minimo dos custos maximos dos sub-caminhos gerados pelas combinacoes feitas;
//Saída:   int minMax -> Valor minimo dos custos maximos dos sub-caminhos gerados por todas as combinacoes;
int combinationUtil(int **path, int comb[], int data[], int start, int end, int index, int k, int n, int minMax)
{
    //variáveis para iteração do loop
    int i, j;

    //variáveis para controle da viagem
    int posAtual = 0;
    int posDestino = 0;

    //variáveis para custo da viagem
    int custoViagem = 0;
    int maxLocal = 0;

    //Percorrer cada combinação gerada e encontra o maior sub-caminho
    if (index == k)
    {
        for (j = 0; j < k; j++)
        {
            posDestino = data[j];
            custoViagem = path[posAtual][posDestino];
            maxLocal = max(custoViagem, maxLocal);
            custoViagem = 0;
            posAtual = data[j];
        }

        custoViagem = path[posAtual][n + 1];

        maxLocal = max(custoViagem, maxLocal);
        minMax = min(minMax, maxLocal);

        return minMax;
    }

    //Gerar combinações possiveis por meio de recursividade
    for (i = start; i <= end && end - i + 1 >= k - index; i++)
    {
        data[index] = comb[i];
        minMax = combinationUtil(path, comb, data, i + 1, end, index + 1, k, n, minMax);
    }

    return minMax;
}
