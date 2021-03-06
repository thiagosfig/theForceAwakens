#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void combinationUtil(int *path, int arr[], int data[], int start, int end, int index, int r, int n)
{
    int pathSize = n;
    int i, j;
    int posAtual = 0;
    int posDestino = 0;
    int custoViagem = 0;

    if (index == r)
    {
        for (j = 0; j < r; j++)
        {
            posDestino = data[j];
            printf("\nSaindo de %d para %d -> ", posAtual, posDestino);
            for (int y = posAtual; y < posDestino; y++)
            {
                custoViagem = custoViagem + path[y];
            }
            printf("Custo: %d", custoViagem);
            custoViagem = 0;
            posAtual = data[j];
        }
        printf("\nSaindo de %d para F -> ", posAtual);
        for (int y = posAtual; y <= pathSize + 1; y++)
        {
            custoViagem = custoViagem + path[y];
        }
        printf("Custo: %d\n\n", custoViagem);
    }

    for (i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(path, arr, data, i + 1, end, index + 1, r, n);
    }
}

void printCombination(int *path, int arr[], int n, int r)
{
    int data[r];

    combinationUtil(path, arr, data, 0, n - 1, 0, r, n);
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

void bruteForce(int n, int k, int *a)
{

    int *comb = (int *)calloc(n, sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    printCombination(a, comb, n, k);

    free(comb);

    return;
}

int readType(char **argv)
{

    char x[3];
    char PD[] = "PD";
    char AG[] = "AG";
    char FB[] = "FB";

    sscanf(argv[1], "%s", x);

    if (strcmp(x, PD) == 0)
    {
        printf("Você optou por PROGRAMAÇÃO DINÂMICA\n");
        return 1;
    }
    if (strcmp(x, AG) == 0)
    {
        printf("Você optou por ALGORITMO GULOSO\n");
        return 2;
    }
    if (strcmp(x, FB) == 0)
    {
        printf("Você optou por FORÇA BRUTA\n");
        return 3;
    }
}

void readEntry(int type)
{

    int t, n, k, a;
    int *ptr;
    printf("Digite sua entrada: ");
    scanf("%d\n", &t);

    for (int j = 0; j < t; j++)
    {
        scanf("%d %d", &n, &k);

        ptr = (int *)calloc(n + 1, sizeof(int));

        if (ptr == NULL)
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
                ptr[i] = a;
            }
        }

        switch (type)
        {
        case 1:
            dynamicProg(n, k, ptr);
            break;
        case 2:
            greedyAlg(n, k, ptr);
            break;
        case 3:
            bruteForce(n, k, ptr);
            break;
        default:
            printf("\nDEU BIZIU!!!\n");
            break;
        }

        free(ptr);
    }
}

int main(int argc, char **argv)
{

    int type = readType(argv);

    readEntry(type);

    return 0;
}