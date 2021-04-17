#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "combination.h"
#include "paradigms.h"

//Entrada:
//t - quantiade de instancias do problema
//n - quantidade de planetas de uma instancia
//k - quantidade de planetas a ser conquistado
//d1, d2, ..., dn - custo da viagem entre planetas -> I p/ P1 = d1 .... an p/ F = dn
//Saida: menor maximo dos sub-caminhos entre os planetas conquistados

//Funcao para ler o tipo de estrategia e retornar um inteiro que representa essa estrategia.
//Entrada: char **argv -> Qual paradigma foi passado na entrada do programa;
//Saida:   int         -> Inteiro que representa o paradigma a ser utilizado;
//                        1: Programacao Dinamica;
//                        2: Algoritmo Guloso;
//                        3: Forca Bruta;
int readType(char **argv)
{

    char type[3];
    char PD[] = "PD";
    char AG[] = "AG";
    char FB[] = "FB";

    sscanf(argv[1], "%s", type);

    //Programacao Dinamica
    if (strcmp(type, PD) == 0)
    {
        return 1;
    }

    //Algoritmo Guloso
    if (strcmp(type, AG) == 0)
    {
        return 2;
    }

    //Forca Bruta
    if (strcmp(type, FB) == 0)
    {
        return 3;
    }

    return 0;
}

//Funcao para direcionar qual estrategia sera utilizada a partir de um inteiro.
//Entrada: int type -> Valor indicando qual paradigma sera utilizado;
//Saida:   -
void readEntry(int type)
{

    int t, n, k, d;
    int *rota;

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
                scanf("%d", &d);
                rota[i] = d;
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
            printf("\nEntrada inválida\n");
            break;
        }

        free(rota);
    }

    return;
}

//Funcao main que recebe o paradigma que sera executado e as instancias do problema.
//Entrada: int    argc -> Valor que representa o numero de argumentos passados na execucao do programa;
//         char **argv -> Valor que representa os argumentos passados para a execucao do programa 
//                        (paradigma e instancias);
//Saida:   -
int main(int argc, char **argv)
{
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    if (argc < 2)
    {
        printf("A chamada do programa deve ser do tipo: $ ./tp [AG | FB | PD] < input.txt\n");
        return 1;
    }

    //Ler o tipo de estrategia a ser adotada
    int type = readType(argv);

    //Ler entradas do usuario e direcionar para uma estratégia
    readEntry(type);

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execucao: %f seg\n", cpu_time_used);

    return 0;
}
