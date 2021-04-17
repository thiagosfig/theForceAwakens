#ifndef __PARADIGMS_H__
#define __PARADIGMS_H__

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -
//int[]     -> Solucao otima do problema da reconquista para os parametros dados?;
void dynamicProg(int n, int k, int *rota);

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -
//int[]     -> Solucao aproximada da reconquista para os parametros dados?;
void greedyAlg(int n, int k, int *rota);

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   -   
//int[]     -> Solucao otima da reconquista para os parametros dados?;
void bruteForce(int n, int k, int *rota);

#endif
