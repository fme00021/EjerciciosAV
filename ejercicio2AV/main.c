#include <stdio.h>
#include <stdlib.h>
#include "ivector.h"

/*************************PROBLEMA 1: REORDENACIÓN DE VECTOR CON SUMA MÁXIMA***************************/
/*
Sean los vectores A y B de n números naturales cada uno, el primero de
los cuales, A, está ordenado crecientemente. Implementa un algoritmo voraz que
obtenga una reordenación del vector B tal que maximice la suma de los
elementos de A que no superan al elemento correspondiente de B.

S = ∑ A(i), para i=1 hasta n, donde A(i) ≤ B(i)

Ejemplo: A= {1, 4, 6, 7, 9}, B = {3, 2, 4, 6, 5}
Una posible reordenación de B (no la óptima) podría ser: B = {2, 4, 5, 3, 6}
Obtendremos un valor de S = 1 + 4 = 5
¿Cuál sería la solución óptima para este ejemplo?
*/
/*************************************************************/

int compare(const void *_a, const void *_b){
    int* a, *b;
    a=(int*)_a;
    b=(int*)_b;
    return *b - *a;
}

void AV(ivector vectorA, ivector vectorB, int tam){
    qsort(vectorB, tam, sizeof (int), compare);

    ivector solucion = icreavector(tam);
    int pos=0;
    int posF=tam-1;

    int maxA=vectorA[tam-1];
    int maxB=vectorB[tam-1];
    int minB=vectorB[pos];

    int i=tam-1;
    int j=tam-1;

    while(i>=0 && j>=0){
        if(maxB>=maxA){
            solucion[posF--] = maxB;
            maxB = vectorB[--j];
            maxA = vectorA[--i];
        }else{
            solucion[posF--] = minB;
            minB = vectorB[++pos];
            maxA = vectorA[--i];
        }
    }

    for(int x=0; x<tam; x++){
        vectorB[x] = solucion[x];
    }

    ifreevector(solucion);


}

int main() {
    int tam = 5;
    ivector vectorA = icreavector(tam);
    ivector vectorB = icreavector(tam);
    vectorA[0] = 1;
    vectorA[1] = 4;
    vectorA[2] = 6;
    vectorA[3] = 7;
    vectorA[4] = 9;

    vectorB[0] = 3;
    vectorB[1] = 2;
    vectorB[2] = 4;
    vectorB[3] = 6;
    vectorB[4] = 5;

    AV(vectorA, vectorB, tam);
    for(int i=0; i<tam; i++){
        printf("Vector A: %d; Vector B: %d \n", vectorA[i], vectorB[i]);
    }
    return 0;
}
