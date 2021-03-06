#include<stdio.h>

typedef struct //entiendo la pieza como una pieza formada por cuatro bloques
{
    int rposx[3], rposy[3]; //posiciones relativas al bloque central o eje, uso esta forma para rotar las piezas de forma sencilla, manteniendo la forma que definen.
    int posx, posy; //posición total o real del bloque central o eje.
    int type; // tipo de pieza, para el color o letra que saldrá por pantalla.

} pieza;

//para obtener las coordenadas de los bloques no centrales se suman las coordenadas relativas a las totales

void pintamatr(int matriz[][20],int tamfil,int tamcol); //sacará una matriz por pantalla
void vacia(int matriz [][20],int fil, int col,int vasio); // vacia una matriz
void mat2mat(int mat[][20],int screenmat[][20], int fil, int col); // asigna el contenido de una matriz a otra
void piece2mat(int mat[][20],pieza pis); //asigna una pieza a la matriz, metiendo sus posiciones en la matriz
void newframe(int mat[][20],int mats[][20],int fil,int col,int vasio,pieza pis); //composicion de funciones para actualizar y pintar el nuevo estado del juego

pieza newpiece(pieza pise); // generación de una nueva pieza
int canfall(int matriz[][20],int fil,int col,pieza pise,int vasio); //comprueba que la pieza puede caer
pieza fall(pieza pis); //hace caer la pieza
int canmove(int mat[][20],int fil,int col,pieza pis,int dir,int vasio);//comprueba que puede moverse la pieza a la direccion elegida
pieza mov(pieza pis,char dir);//mueve la pieza a la direccion elegida
int canrotate(int mat[][20],int fil,int col,pieza pis,char dir,int vasio);//comprueba que puede rotar la pieza a la dirección elegida
pieza rot(pieza pis,char dir); // rota la pieza según la dirección elegida

void linea(int mat[][20],int fil,int col,int vasio); //si hay una linea completa baja todo lo que haya arriba borrando la linea completa en el proceso
int endgame(int mat[][20],int fil, int vasio); //si hay algún bloque en la última linea acaba la partida
