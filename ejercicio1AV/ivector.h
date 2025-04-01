/*************************ivector.h***************************/
/*         Módulo de cabeceras para uso de objetos           */
/*                   VECTORES DE ENTEROS                     */
/*************************************************************/

#ifndef IVECTOR

#define IVECTOR

#include "Pedido.h"

typedef Pedido *ivector;

ivector icreavector(int tam);
void ifreevector(ivector *v);

#endif
