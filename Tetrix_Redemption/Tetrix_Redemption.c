#include<stdio.h>
#include"tetrisfunctions.h"
#include<time.h>
#include<stdlib.h>


int main()
{
    int matestado[10][20],matscreen[10][20];//matestado guarda los bloques ya colocados y matscrren se usará para componer los bloques ya colocados y la posición de la pieza
    pieza pos;
    int empty=' ',rotdir,movdir,exit=0;
    char movr,movl,rotr,rotl,pres;
    int replay=1;

    srand(time(NULL));

    printf("Type in order movement keys left to right and later rotation keys in same order \n");
    scanf("%c %c %c %c \n",&movl,&movr,&rotl,&rotr); //configuración inicial de controles
    do{
     vacia(matestado,10,20,empty); // configuración antes de la partida
     vacia(matscreen,10,20,empty);
     pos=newpiece(pos);
     newframe(matestado,matscreen,10,20,empty,pos);

     while(exit==0)//bucle principal del juego
     {
         scanf("%c",&pres); //deteccion de la proxima accion
         if(pres==movl)//movimientio izqda si es posible
         {
             movdir='l';
             if(canmove(matestado,10,20,pos,movdir,empty)==1)
             {
                 pos = mov(pos,movdir);
             }
         }
         if(pres==movr)//movimientio dcha si es posible
         {
             movdir='r';
             if(canmove(matestado,10,20,pos,movdir,empty)==1)
             {
                 pos=mov(pos,movdir);
             }
         }
         if(pres==rotl)//rotación izqda si es posible
         {
             rotdir='l';
             if(canrotate(matestado,10,20,pos,rotdir,empty)==1)
             {
                 pos=rot(pos,rotdir);
             }
         }
         if(pres==rotr)//rotación dcha si es posible
         {
             rotdir='r';
             if(canrotate(matestado,10,20,pos,rotdir,empty)==1)
             {
                 pos=rot(pos,rotdir);
             }
         }


         if(canfall(matestado,10,20,pos,empty)==1) // hacer la pieza caer si puede
         {
             pos=fall(pos);
         }
         else if (canfall(matestado,10,20,pos,empty)==0) // si no puede caer la pieza
         {
             piece2mat(matestado,pos);  //la pieza pasa a la matriz de estado
             pos=newpiece(pos);  //se genera una nueva pieza
             linea(matestado,10,20,empty);  //se quitan las lineas que haya podido crear la nueva pieza
             exit=endgame(matestado,10,empty);//se comprueba que la pieza no ha podido acabar la partida
         }
         newframe(matestado,matscreen,10,20,empty,pos); //se pinta el estado del juego
     }
     printf("replay? 1 (for yes 0 for no)\n");
     scanf("%i",&replay);
     if(replay==1)
        exit=0;
    }while(replay==1);

    return 0;
}
