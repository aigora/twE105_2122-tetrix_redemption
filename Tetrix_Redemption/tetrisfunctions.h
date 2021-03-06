#include<stdio.h>
#include<SDL2/SDL.h>

typedef struct //entiendo la pieza como una pieza formada por cuatro bloques
{
    int rposx[3], rposy[3]; //posiciones relativas al bloque central o eje, uso esta forma para rotar las piezas de forma sencilla, manteniendo la forma que definen.
    int posx, posy; //posición total o real del bloque central o eje.
    int type; // tipo de pieza, para el color o letra que saldrá por pantalla.

} pieza;

typedef struct
{
    int puntuacion;
    char name1,name2,name3;
}jugador;

void appendscore(int punt);
void ordenahighscore();

//para obtener las coordenadas de los bloques no centrales se suman las coordenadas relativas a las totales

int menu(int *cargar,int *replay);

void pintamatr(int matriz[][20],int tamfil,int tamcol,SDL_Renderer *render); //sacará una matriz por pantalla
void vacia(int matriz [][20],int fil, int col,int vasio); // vacia una matriz
void mat2mat(int mat[][20],int screenmat[][20], int fil, int col); // asigna el contenido de una matriz a otra
void piece2mat(int mat[][20],pieza pis); //asigna una pieza a la matriz, metiendo sus posiciones en la matriz
void newframe(int mat[][20],int mats[][20],int fil,int col,int vasio,pieza pis,SDL_Renderer *render); //composicion de funciones para actualizar y pintar el nuevo estado del juego
void scene(SDL_Renderer *Render,SDL_Window *Ventana,SDL_Texture *Textura,char path[]); //Para pintar fondos y escenarios
void pintapiece(pieza curr,pieza old,int mat[][20],int vasio,SDL_Renderer *render);//Saca la pieza con la que se está jugando por pantalla

pieza newpiece(); // generación de una nueva pieza
int canfall(int matriz[][20],int fil,int col,pieza pise,int vasio); //comprueba que la pieza puede caer
pieza fall(pieza pis); //hace caer la pieza
int canmove(int mat[][20],int fil,int col,pieza pis,int dir,int vasio);//comprueba que puede moverse la pieza a la direccion elegida
pieza mov(pieza pis,char dir);//mueve la pieza a la direccion elegida
int canrotate(int mat[][20],int fil,int col,pieza pis,char dir,int vasio);//comprueba que puede rotar la pieza a la dirección elegida
pieza rot(pieza pis,char dir); // rota la pieza según la dirección elegida
pieza hardfall(pieza pis,int mat [][20],int vasio);
pieza giro(pieza pos, int matestado[][20], int fil, int col, char rotdir, int vasio);

void linea(int mat[][20],int fil,int col,int vasio,int *p); //si hay una linea completa baja todo lo que haya arriba borrando la linea completa en el proceso
int endgame(int mat[][20],int fil, int vasio); //si hay algún bloque en la última linea acaba la partida

void truefall(int matestado[][20],int matscreen[][20],int vasio,int *exit,pieza *old,pieza *pos,pieza cola[],SDL_Renderer *render,SDL_Texture *textura,int *canhold,int *p);
pieza nextpiece(pieza cola[],int tam,SDL_Renderer *render,SDL_Texture *textura);
void rendercola(pieza cola[], int tam, SDL_Renderer *render,SDL_Texture *textura);
pieza hold(pieza *hold,pieza curr,int *canhold,pieza cola[],SDL_Renderer *render, SDL_Texture *textura);
void piecepreview(pieza pis,int mat[][20],int vasio,int alfa,int old,SDL_Renderer *render);

int pausa(int mat[][20],pieza pos,pieza hold,pieza cola[],int pts);
void iniciarpartida(int matestado [][20],int matscreen[][20],int vasio,pieza cola[],pieza *pos,pieza *holdedpiece,SDL_Renderer *render,SDL_Texture *textura);
