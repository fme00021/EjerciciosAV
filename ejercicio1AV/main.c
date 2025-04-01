#include <stdio.h>
#include <stdlib.h>
#include "Pedido.h"
#include "ivector.h"

/*************************PROBLEMA 1: PLANIFICACIÓN DE TAREAS CON TIEMPO LÍMITE ***************************/
/*
El repartidor de Uber tiene que entregar N pedidos de diferente valor
teniendo que hacerlo antes de lo indicado en la tabla. En un instante
determinado solamente puede entregar un pedido.

Pedido        | 1  | 2  | 3  | 4  | 5  | 6  | 7  | 8  | 9
Tiempo límite | 1  | 5  | 5  | 6  | 6  | 4  | 4  | 2  | 2
A cobrar      | 60 | 70 | 80 | 20 | 20 | 30 | 50 | 50 | 90

Si entrega tarde un pedido, al cliente le sale gratis. Construye una heurística de
tu invención y un algoritmo Voraz basado en lo explicado en el libro de G.
Brassard, P. Bratley en la sección de “Planificación con plazo fijo” (página 233 y
siguientes, en la edición de 1997), que le indique el orden que debe seguir en el
reparto para obtener el máximo beneficio. Aplícalo al ejemplo detallando TODOS
los pasos.
*/
/*************************************************************/


//Función de comparación para ordenar los pedidos por valor/tiempo límite (será usada luego por qsort)
int compararPedidos(const void *_a, const void *_b){
    Pedido *a, *b;
    a=(Pedido*)_a; //Convertimos _a en Pedido* ya que es un const void (necesidades para el qsort)
    b=(Pedido*)_b; //Convertimos _b en Pedido* ya que es un const void (necesidades para el qsort)

    //Calcula la relación valor/tiempo límite de cada pedido
    double relacionA = (double)a->a_cobrar / a->tiempo_limite;
    double relacionB = (double)b->a_cobrar / b->tiempo_limite;

    //Compara las relaciones y devuelve un valor para indicar el orden
    if(relacionA < relacionB){
        return 1; //B va antes que A
    }else if(relacionA > relacionB){
        return -1; //A va antes que B
    } else{
        return 0; //A y B son iguales
    }
}

//Función que implementa el algoritmo voraz para seleccionar los pedidos
ivector AV(ivector pedidos, int numPedidos, int *numPedidosSolucionReal){
    //Ordena los pedidos usando la función de coparación personalizada
    qsort(pedidos, numPedidos, sizeof(Pedido), compararPedidos);

    //Crea un vector dinámica para almacenar la solución
    ivector solucion = icreavector(numPedidos);
    int numPedidosSolucion = 0;

    //Itera sobre los pedidos ordenados
    for(int i=0; i<numPedidos; i++){
        //Verifica si el pedido se puede entregar dentro de su tiempo límite
        if(pedidos[i].tiempo_limite>=numPedidosSolucion+1){
            //Agrega el pedido a la solución
            solucion[numPedidosSolucion] = pedidos[i];
            numPedidosSolucion++;
        }
    }

    //Actualiza el número real de pedidos en la solución
    *numPedidosSolucionReal = numPedidosSolucion;

    //Devuelve la solución
    return solucion;

}


int main() {
    int numPedidos = 9;
    ivector pedidos = icreavector(numPedidos);
    pedidos[0].tiempo_limite = 1;
    pedidos[0].a_cobrar = 60;
    pedidos[1].tiempo_limite = 5;
    pedidos[1].a_cobrar = 70;
    pedidos[2].tiempo_limite = 5;
    pedidos[2].a_cobrar = 80;
    pedidos[3].tiempo_limite = 6;
    pedidos[3].a_cobrar = 20;
    pedidos[4].tiempo_limite = 6;
    pedidos[4].a_cobrar = 20;
    pedidos[5].tiempo_limite = 4;
    pedidos[5].a_cobrar = 30;
    pedidos[6].tiempo_limite = 4;
    pedidos[6].a_cobrar = 50;
    pedidos[7].tiempo_limite = 2;
    pedidos[7].a_cobrar = 50;
    pedidos[8].tiempo_limite = 2;
    pedidos[8].a_cobrar = 90;

    int numPedidosSolucion;
    ivector solucion = AV(pedidos, numPedidos, &numPedidosSolucion);
    for(int i=0; i<numPedidosSolucion; i++){
        printf("Instante %d: Pedido {%d tiempo limite, %d a cobrar} \n", i+1, solucion[i].tiempo_limite, solucion[i].a_cobrar);
    }
    return 0;
}
