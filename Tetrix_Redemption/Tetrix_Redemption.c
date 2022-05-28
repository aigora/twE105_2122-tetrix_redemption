#include<stdio.h>
#include"tetrisfunctions.h"
#include<time.h>
#include<SDL2/SDL.h>


int main(int argv, char** args)
{
    char guardarpuntuacion,replayc;
    int matestado[10][20],matscreen[10][20];//matestado guarda los bloques ya colocados y matscrren se usará para componer los bloques ya colocados y la posición de la pieza
    pieza pos,old,cola[4],holdedpiece;
    int empty=' ',rotdir,movdir,exit=0,canhold=1,cargar=0,puntuacion,i;
    int replay=1;
    time_t past, now;
    SDL_Event evento;
    SDL_Window *ventana;
    SDL_Renderer *render;
    SDL_Texture *textura=NULL;

	exit=menu(&cargar,&replay);

    srand(time(NULL));


    while(replay!=0){
            SDL_Init(SDL_INIT_EVERYTHING);
            ventana = SDL_CreateWindow( "Tetrix.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN );
            render= SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED );
            scene(render,ventana,textura,"sprites/Tetrix_Background.bmp");

            if (cargar!=1)
            {
                iniciarpartida(matestado,matscreen,empty,cola,&pos,&holdedpiece,render,textura);
                puntuacion=0;
            }
            if(cargar==1)
            {
                cargarpartida(matestado,&pos,&holdedpiece,cola,&puntuacion);
                cargar=0;
            }
            canhold=0;
            pos=hold(&holdedpiece,pos,&canhold,cola,render,textura);
            canhold=1;//se devuelbe la posibilidad de holdear
            newframe(matestado,matscreen,10,20,empty,pos,render);
            rendercola(cola,4,render,textura);


     past=time(NULL);
     while(exit==0)//bucle principal del juego
     {
         now=time(NULL);

         if(difftime(now,past)>=1)
         {
             old=pos;
             truefall(matestado,matscreen,empty,&exit,&old,&pos,cola,render,textura,&canhold,&puntuacion);
             past=now;

              pintapiece(pos,old,matestado,empty,render);
         }


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
                    pos= giro(pos, matestado, 10, 20, 'l', empty);
                 }
                 if(evento.key.keysym.sym==SDLK_g || evento.key.keysym.sym==SDLK_UP || evento.key.keysym.sym==SDLK_w)//rotación dcha si es posible
                 {
                     pos= giro(pos,matestado,10,20,'r',empty);
                 }
                 if(evento.key.keysym.sym==SDLK_s || evento.key.keysym.sym==SDLK_DOWN) // Caida rápida si es posible
                 {
                     truefall(matestado,matscreen,empty,&exit,&old,&pos,cola,render,textura,&canhold,&puntuacion);
                 }
                 if(evento.key.keysym.sym==SDLK_c || evento.key.keysym.sym==SDLK_k)
                 {
                     pos=hold(&holdedpiece,pos,&canhold,cola,render,textura);
                 }
                 if(evento.key.keysym.sym==SDLK_SPACE)
                 {
                     pos=hardfall(pos,matestado,empty);
                     truefall(matestado,matscreen,empty,&exit,&old,&pos,cola,render,textura,&canhold,&puntuacion);
                 }
                 if(evento.key.keysym.sym==SDLK_ESCAPE)
                 {
                    SDL_DestroyWindow(ventana);
                    SDL_DestroyTexture(textura);
                    SDL_DestroyRenderer(render);

                    exit=pausa(matestado,pos,holdedpiece,cola,puntuacion);

                    if(exit==0)
                    {
                        SDL_Init(SDL_INIT_EVERYTHING);
                        ventana = SDL_CreateWindow( "Tetrix.exe", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1920, 1080, SDL_WINDOW_SHOWN );
                        render= SDL_CreateRenderer( ventana, -1, SDL_RENDERER_ACCELERATED );
                        scene(render,ventana,textura,"sprites/Tetrix_Background.bmp");
                        canhold=0;
                        pos=hold(&holdedpiece,pos,&canhold,cola,render,textura);
                        canhold=1;//se devuelve la habilidad
                        newframe(matestado,matscreen,10,20,empty,pos,render);
                        rendercola(cola,4,render,textura);

                        past=now; // para evitar un salto repentino tras la pausa
                    }
                 }


                 pintapiece(pos,old,matestado,empty,render);
            }


        }
     }
     SDL_DestroyWindow(ventana);
     SDL_DestroyTexture(textura);
     SDL_DestroyRenderer(render);
     i=0;
     while(i==0)
     {
         printf("Desea guardar la puntuacion? (y) (n) \n Su puntuacion: %i \n",puntuacion);
         scanf("%c%c",&guardarpuntuacion,&guardarpuntuacion);//al dale al enterdetecta un segudo char y hace dos veces el ciclo
         if(guardarpuntuacion=='y')
         {
             appendscore(puntuacion);
             i=1;
         }
         if(guardarpuntuacion=='n')
         {
             i=1;
         }
     }
     while(exit==1&&i==1)
        {
            printf("Nueva partida? y (si) n (no)\n");
            scanf("%c%c",&replayc,&replayc);
            if(replayc=='y')
            {
                i=0;
            }
            if(replayc=='n')
            {
                replay=0;
                i=0;
            }
     }
     if (replay!=0)
     {
         exit=0;
     }

    }

    return 0;
}
