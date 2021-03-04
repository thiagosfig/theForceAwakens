#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    printf("\nn = %d, k=%d", n, k);

    for (int i = 0; i < n + 1; i++)
    {
        printf("\n%d", a[i]);
    }
    printf("\n\n");

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