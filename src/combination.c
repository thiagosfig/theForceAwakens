#include "combination.h"
#include "paradigmsUtil.h"
#include <stdio.h>

//Função para chamada inicial da construção das combinações
//Entrada:
//Saída:
void combination(int **path, int comb[], int n, int k)
{
    //data eh um arranjo com k elementos
    int data[k];

    //Valor 'alto' para 'simular infinito'
    int inf = 9999;

    int minMax = combinationUtil(path, comb, data, 0, n - 1, 0, k, n, inf);

    printf("%d\n", minMax);

    return;
}

//Algoritmo para gerar as combinações e encontrar o menor sub-caminho máximo
//Entrada:
//Saída:
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
