#include <stdbool.h>
#ifndef juego_2048_h
#define juego_2048_h
#define TAM_TAB 4

typedef struct tablero {
    unsigned int t[TAM_TAB][TAM_TAB];
} tablero;

typedef enum direc{
    arriba,
    izquierda,
    abajo,
    derecha
} direccion;


void inicializar_tablero(tablero*);
bool tablero_lleno(tablero);
void insertar_casilla(tablero*);
direccion pedir_movimiento();
void mover_tablero(tablero*, direccion);


#endif


