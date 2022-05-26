#include<stdio.h>
#include"tetrisfunctions.h"
#include<time.h>
#include<stdlib.h>
#include<SDL2/SDL.h>


int main(int argv, char** args)
{
    int matestado[10][20],matscreen[10][20];//matestado guarda los bloques ya colocados y matscrren se usará para componer los bloques ya colocados y la posición de la pieza
    pieza pos,old,cola[4];
    int empty=' ',rotdir,movdir,exit=0,i;
    int replay=1;
    time_t past, now;
    SDL_Event evento;
    SDL_Window *ventana;
    SDL_Renderer *render;
    SDL_Texture *textura=NULL;

	exit=menu();

    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    ventana = SDL_CreateWindow( "Tetrix.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN );
    render= SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED );


    scene(render,ventana,textura,"sprites/Tetrix_Background.bmp");

    do{
     vacia(matestado,10,20,empty); // configuración antes de la partida
     vacia(matscreen,10,20,empty);
     for(i=0;i<4;i+=1)
     {
         cola[i]=newpiece();
     }
     pos=nextpiece(cola,4,render,textura);
     newframe(matestado,matscreen,10,20,empty,pos,render);
     past=time(NULL);

     while(exit==0)//bucle principal del juego
     {
         now=time(NULL);


         while(SDL_PollEvent(&evento))
         {
             if (evento.type==SDL_KEYDOWN)
            {
                old=pos;
                 now=time(NULL);
                 if(evento.key.keysym.sym==SDLK_a || evento.key.keysym.sym==SDLK_LEFT)//movimientio izqda si es posible
                 {
                     movdir='l';
                     if(canmove(matestado,10,20,pos,movdir,empty)==1)
                     {
                         pos=mov(pos,movdir);
                     }
                 }
                 if(evento.key.keysym.sym==SDLK_d || evento.key.keysym.sym==SDLK_RIGHT)//movimientio dcha si es posible
                 {
                     movdir='r';
                     if(canmove(matestado,10,20,pos,movdir,empty)==1)
                     {
                         pos=mov(pos,movdir);
                     }
                 }
                 if(evento.key.keysym.sym==SDLK_f)//rotación izqda si es posible
                 {
                     rotdir='l';
                     if(canrotate(matestado,10,20,pos,rotdir,empty)==1)
                     {
                         pos=rot(pos,rotdir);
                     }
                 }
                 if(evento.key.keysym.sym==SDLK_g || evento.key.keysym.sym==SDLK_UP || evento.key.keysym.sym==SDLK_w)//rotación dcha si es posible
                 {
                     rotdir='r';
                     if(canrotate(matestado,10,20,pos,rotdir,empty)==1)
                     {
                         pos=rot(pos,rotdir);
                     }
                 }
                 if(evento.key.keysym.sym==SDLK_s || evento.key.keysym.sym==SDLK_DOWN) // Caida rápida si es posible
                 {
                     truefall(matestado,matscreen,empty,&exit,
                              &old,&pos,cola,render,textura);
                 }
                 pintapiece(pos,old,render);
            }


        }

         if(difftime(now,past)>=1)
         {
             old=pos;
             truefall(matestado,matscreen,empty,&exit,&old,&pos,cola,render,textura);
             past=now;

              pintapiece(pos,old,render);
         }
     }
     printf("replay? 1 (for yes 0 for no)\n");
     scanf("%i",&replay);
     if (replay!=0)
     {
         exit=0;
     }

    }while(replay!=0);

    return 0;
}
