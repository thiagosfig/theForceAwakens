#ifndef __COMBINATION_H__
#define __COMBINATION_H__

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
int combinationUtil(int **path, int comb[], int data[], int start, int end, int index, int k, int n, int minMax);

//Entrada: int **path -> Matriz de caminhos com as distancias dos planetas da rota;
//         int comb[] -> Vetor com [1..n] planetas da rota;
//         int      n -> Numero de planetas da rota;
//         int      k -> Numero de planetas a serem conquistados
//Saída:   Será retornado o menor dentre todos os maiores sub-caminho da solução ótima;
int combination(int **path, int comb[], int n, int k);

#endif
