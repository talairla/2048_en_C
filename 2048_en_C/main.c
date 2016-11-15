#include <stdio.h>
#include <stdlib.h>
#include "2048.h"
#include <stdbool.h>

int main()
{
    tablero t;
    direccion dir;
    inicializar_tablero(&t);
    insertar_casilla(&t);
    insertar_casilla(&t);
    insertar_casilla(&t);
    insertar_casilla(&t);
    insertar_casilla(&t);
    while(!tablero_lleno(t)){
        imprimir_tablero(t);
        dir = pedir_movimiento();
        fprintf(stderr,"Direccion: %d",dir);
        mover_tablero(&t,dir);
    }
}
