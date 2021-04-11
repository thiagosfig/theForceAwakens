#ifndef __PARADIGMSUTIL_H__
#define __PARADIGMSUTIL_H__

int max(int a, int b);
int min(int a, int b);
int recorrenciaPD(int atual, int size, int n, int k, int **matriz);
void liberaMatriz(int **matriz, int size);
int **matrizCaminhos(int n, int k, int *a);
int greedyAlgMax(int n, int k, int *a);
int greedyAlgMean(int n, int k, int *a);

#endif
