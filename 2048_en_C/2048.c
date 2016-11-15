#include "2048.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void inicializar_tablero(tablero* tab){

    int i,j;
    for(i=0; i<TAM_TAB;i++){
        for(j=0; j<TAM_TAB;j++){
        tab->t[i][j]=0;
        }
    }
}
/*
void imprimir_tablero(tablero tab){
    int i=0,j=0;
    fprintf(stdout,"\n      %d       %d       %d       %d",j,j+1,j+2,j+3);
    fprintf(stdout,"\n  \u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u252c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524");
    for(i=0 ; i<TAM_TAB ; i++){
        fprintf(stdout,"\n%d \u2502",i);
        for(j=0 ; j<TAM_TAB ; j++){
            imprimir_celda(tab.t[i][j]);
        }
        fprintf(stdout,"\n  \u251c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u253c\u2500\u2500\u2500\u2500\u2500\u2500\u2500\u2524");
    }
    fprintf(stdout,"\n\n\n");
}
*/

void imprimir_tablero(tablero tab){
    int i=0,j=0;
    fprintf(stdout,"\n      %d       %d       %d       %d",j,j+1,j+2,j+3);
    fprintf(stdout,"\n  +-------+-------+-------+-------+");
    for(i=0 ; i<TAM_TAB ; i++){
        fprintf(stdout,"\n%d |",i);
        for(j=0 ; j<TAM_TAB ; j++){
            imprimir_celda(tab.t[i][j]);
        }
        fprintf(stdout,"\n  |-------+-------+-------+-------|");
    }
    fprintf(stdout,"\n\n\n");
}


void imprimir_celda(int valor){
    if(valor == 0 ){
        fprintf(stdout, "       |");
    }
    else if(valor < 10)
    {
        fprintf(stdout, "   %d   |", valor);
    }else if(valor < 100)
    {
        fprintf(stdout, "  %d   |", valor);
    }
    else if(valor < 1000)
    {
        fprintf(stdout, "  %d  |", valor);
    }
    else
    {
        fprintf(stdout, " %d  |", valor);
    }
}

bool tablero_lleno(tablero tab){

    bool esta_lleno = true;
    int i, j;
    for(i=0; i<TAM_TAB;i++){
        for(j=0; j<TAM_TAB;j++){
            if( tab.t[i][j] == 0 ){
                esta_lleno = false;
            }
        }
    }
    return esta_lleno;
}

void insertar_casilla(tablero* tab){
    int i=rand()%4;
    int j=rand()%4;
    while(tab->t[i][j]!=0){
        i=rand()%4;
        j=rand()%4;
    }
    tab->t[i][j]=2;
}

direccion pedir_movimiento(){

    direccion dir;
    char c='q';
    while( c != 'w' && c != 'a' && c != 's' && c != 'd')
    {
        fprintf(stdout,"Escribe un caracter y pulsa enter");
        scanf(" %c",&c);
        switch (c)
        {

            case 'w':
                dir=arriba;
                fprintf(stderr,"Estableciendo direccion: %d",dir);
                break;
            case 'a':
                dir=izquierda;
                break;

            case 'd':
                dir=derecha;
                break;

            case 's':

                dir=abajo;
                break;

            default:
                break;
        }
    }
    return dir;
}

void mover_tablero(tablero* tab, direccion dir){
    printf("Moviendo tablero\n");
    switch (dir){

        case arriba:
            mover_tablero_arriba(tab);
            break;
        case abajo:
            mover_tablero_abajo(tab);
            break;
        case izquierda:
            mover_tablero_izquierda(tab);
            break;
        case derecha:
            mover_tablero_derecha(tab);
            break;
    }
}

void mover_tablero_arriba(tablero* tab)
{
     int i,j;   //Recorremos el tablero empezando por la esquina superior derecha
     for(i=0; i<TAM_TAB;i++)
     {
        for(j=0;j<TAM_TAB;j++)
        {
            if(!casilla_vacia(tab->t[i][j])){
                mover_casilla_arriba(tab, i, j);
            }
        }
     }
}

void mover_tablero_abajo(tablero* tab)
{
    int i,j; //Recorremos el tablero de abajo a arriba.
     for( i=TAM_TAB-1; i >= 0; i--)
     {
        for(j=0; j<TAM_TAB;j++) //Las columnas de izda a dcha.
        {
            if( tab->t[i][j] != 0 )
            {
                mover_casilla_abajo(tab,i,j);
            }
        }
    }
}

void mover_tablero_izquierda(tablero* tab)
{
    int i,j;
     for(j=0; j<TAM_TAB;i++)
     {
        for(i=0; i<TAM_TAB;i++)
        {
            if( tab->t[i][j] != 0 )
            {
                mover_casilla_izquierda(tab,i,j);
            }
        }
    }
}

void mover_tablero_derecha(tablero* tab)
{
    int i,j;
    for(j=TAM_TAB-1; j>=0;j++)
    {
        for(i=0; i<TAM_TAB;i++)
        {
            if( tab->t[i][j] != 0 )
            {
                mover_casilla_derecha(tab,i,j);
            }
        }
    }
}


bool casilla_vacia(int valor){
    bool retorno;
    if (valor == 0){
        retorno = true;
    }
    else{
        retorno = false;
    }
    return retorno;
}



void mover_casilla_arriba(tablero* tab, int f, int c){
    int i = f;
    int j = c;
    f--;
    while(tab->t[f][c]==0 && f>0)
    {
        f--;
    }
    if(tab->t[f][c]==0)
    {
        tab->t[f][c]=tab->t[i][j];
        tab->t[i][j]=0;
    }
    else if(tab->t[f][c]==tab->t[i][j])
    {
        tab->t[f][c]+=tab->t[i][j];
        tab->t[i][j]=0;
    }
}

void mover_casilla_derecha(tablero* tab, int f, int c){
    int i = f;
    int j = c;
    c++;
    while(tab->t[f][c]==0 && c<TAM_TAB-2)
    {
        c++;
    }
    if(tab->t[f][c]==0)
    {
        tab->t[f][c]=tab->t[i][j];
        tab->t[i][j]=0;
    }
    else if(tab->t[f][c]==tab->t[i][j])
    {
        tab->t[f][c]+=tab->t[i][j];
        tab->t[i][j]=0;
    }
}


void mover_casilla_izquierda(tablero* tab, int f, int c){
    int i = f;
    int j = c;
    c--;
    while(tab->t[f][c]==0 && c>0)
    {
        c--;
    }
    if(tab->t[f][c]==0)
    {
        tab->t[f][c]=tab->t[i][j];
        tab->t[i][j]=0;
    }
    else if(tab->t[f][c]==tab->t[i][j])
    {
        tab->t[f][c]+=tab->t[i][j];
        tab->t[i][j]=0;
    }
}

void mover_casilla_abajo(tablero* tab, int f, int c){
    int i = f;
    int j = c;

    f++;
    if ( f < (TAM_TAB-1) ){
        while(tab->t[f][c] == 0){
            f++;
        }
    }









}

