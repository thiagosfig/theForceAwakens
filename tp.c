#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//CONTADOR PARA QUANTIDADE DE COMBINAÇÕES(n, k)
int counter;

void combinationUtil(int *path, int arr[], int data[], int start, int end, int index, int r)
{
    int pathSize = sizeof(path) / sizeof(path[0]);
    int i, j;
    int posAtual = 0;
    int posDestino = 0;

    if (index == r)
    {
        for (j = 0; j < r; j++)
        {
            posDestino = data[j];
            printf("Saindo de %d para %d\n", posAtual, posDestino);
            posAtual = data[j];
        }
        printf("Saindo de %d para F\n\n", posAtual);

        // for (int x = 0; x <= pathSize + 1; x++)
        // {
        //     printf("%d ", path[x]);
        // }
        // printf(" -> ");
        // for (j = 0; j < r; j++)
        //     printf("%d ", data[j]);
        // counter++;
        // printf("\n");
        return;
    }

    for (i = start; i <= end && end - i + 1 >= r - index; i++)
    {
        data[index] = arr[i];
        combinationUtil(path, arr, data, i + 1, end, index + 1, r);
    }
}

void printCombination(int *path, int arr[], int n, int r)
{
    int data[r];

    combinationUtil(path, arr, data, 0, n - 1, 0, r);
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

    int *comb = (int *)malloc(n * sizeof(int));

    for (int i = 1; i < n + 1; i++)
    {
        comb[i - 1] = i;
    }

    //printf("\nn = %d, k=%d", n, k);

    // for (int i = 0; i < n + 1; i++)
    // {
    //     printf("\n%d", a[i]);
    // }
    // printf("\n\n");

    printf("\nCOMB(%d, %d)\n", n, k);
    printCombination(a, comb, n, k);
    printf("\n %d \n", counter);
    counter = 0;

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

        ptr = (int *)malloc(n + 1 * sizeof(int));

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

void exampleComb()
{

    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int r = 3;
    int n = sizeof(arr) / sizeof(arr[0]);

    // NECESSÁRIO TIRAR PARAMETRO PATH DA FUNÇÃO ORIGINAL
    // printCombination(arr, n, r);

    printf("%d", counter);
    return;
}