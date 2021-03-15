#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "combination.h"

int minMax;

void Combination(int *path, int comb[], int n, int k)
{
    //data eh um arranjo com k elementos
    int data[k];
    minMax = 9999;

    combinationUtil(path, comb, data, 0, n - 1, 0, k, n);

    printf("\n%d", minMax);

    return;
}

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

    printf("\nn = %d, k=%d", n, k);

    for (int i = 0; i < n + 1; i++)
    {
        printf("\n%d", a[i]);
    }
    printf("\n\n");

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

//Funcao para ler o tipo de estrategia
int readType(char **argv)
{

    char type[3];
    char PD[] = "PD";
    char AG[] = "AG";
    char FB[] = "FB";

    sscanf(argv[1], "%s", type);

    if (strcmp(type, PD) == 0)
    {
        printf("Você optou por PROGRAMAÇÃO DINÂMICA\n");
        return 1;
    }
    if (strcmp(type, AG) == 0)
    {
        printf("Você optou por ALGORITMO GULOSO\n");
        return 2;
    }
    if (strcmp(type, FB) == 0)
    {
        printf("Você optou por FORÇA BRUTA\n");
        return 3;
    }
}

//Ler entrada do usuario (t n k a1 a2 ... an)
//t - quantiade de instancias do problema
//n - quantidade de planetas de uma instancia
//k - quatidade de planetas a ser conquistado
//a1, a2, ..., an - custo da viagem entre planetas -> I p/ P1 = a1 .... an p/ F = an
void readEntry(int type)
{

    int t, n, k, a;
    int *rota;
    printf("Digite sua entrada: ");
    scanf("%d", &t);

    for (int j = 0; j < t; j++)
    {
        scanf("%d %d", &n, &k);

        rota = (int *)calloc(n + 1, sizeof(int));

        if (rota == NULL)
        {
            printf("Memory not allocated.\n");
            exit(0);
        }
        else
        {
            //Read
            for (int i = 0; i < n + 1; ++i)
            {
                scanf("%d", &a);
                rota[i] = a;
            }
        }

        switch (type)
        {
        case 1:
            dynamicProg(n, k, rota);
            break;
        case 2:
            greedyAlg(n, k, rota);
            break;
        case 3:
            bruteForce(n, k, rota);
            break;
        default:
            printf("\nDEU BIZIU!!!\n");
            break;
        }

        free(rota);
    }
}

int main(int argc, char **argv)
{

    //Ler o tipo de estrategia a ser adotada
    int type = readType(argv);

    //Ler entradas do usuario
    readEntry(type);

    return 0;
}