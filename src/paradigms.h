#ifndef __PARADIGMS_H__
#define __PARADIGMS_H__

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   Será impresso o maior caminho da solução ótima;
void dynamicProg(int n, int k, int *rota);

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   Será impresso o maior caminho da solução aproximada;
void greedyAlg(int n, int k, int *rota);

//Entrada: int     n -> Numero de planetas da rota;
//         int     k -> Numero de planetas a serem reconquistados;
//         int *rota -> Distancias da rota;
//Saída:   Será impresso o maior caminho da solução ótima;
void bruteForce(int n, int k, int *rota);

#endif
