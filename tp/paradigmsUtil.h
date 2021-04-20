#ifndef __PARADIGMSUTIL_H__
#define __PARADIGMSUTIL_H__

//Entrada: int a -> Primeiro dos valores a serem comparados;
//         int b -> Segundo dos valores a serem comparados;
//Saida:   int   -> Maior entre a e b;
int max(int a, int b);

//Entrada: int a -> Primeiro dos valores a serem comparados;
//         int b -> Segundo dos valores a serem comparados;
//Saida:   int   -> Menor entre a e b;
int min(int a, int b);

//Entrada: int    atual -> Planeta atual da rota;
//         int     size -> Numero de rotas;
//         int        n -> Próximo planeta da rota;
//         int        k -> Numero de planetas a serem conquistados;
//         int **matriz -> Matriz quadrada que representa a distancia dos planetas da rota;
//Saida:   int       mn -> Valor minimo dos custos maximos de conquista dos planetas;
int recorrenciaPD(int atual, int size, int n, int k, int **matriz);

//Entrada: int **matriz -> Matriz quadrada que sera liberada;
//         int     size -> Tamanho da matriz quadrada a ser liberada;
//Saida:   -
void liberaMatriz(int **matriz, int size);

//Entrada: int        n -> Numero de planetas da rota;
//         int        k -> Numero de planetas a serem reconquistados;
//         int       *a -> Distancias da rota;
//Saida:   int **matriz -> Matriz quadrada que representa a distancia entre os planetas da rota;
int **matrizCaminhos(int n, int k, int *a);

//Entrada: int        n -> Numero de planetas da rota;
//         int        k -> Numero de planetas a serem reconquistados;
//         int       *a -> Distancias da rota;
//Saida:   int maxLocal -> Valor que representa o maior custo de conquistar k planetas da rota;
int greedyAlgMean(int n, int k, int *a);

#endif
