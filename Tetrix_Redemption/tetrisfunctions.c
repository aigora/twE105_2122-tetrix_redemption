#include<stdio.h>
#include"tetrisfunctions.h"
#include<time.h>
#include<stdlib.h>
#include<SDL2/SDL.h>

int menu()
{
    int exit=1;
    char menu;
    printf("Puntuación(p) \nControles(c) \nJugar(j)\n");

    while(exit=!0)
    {
        scanf("%c", &menu);

        switch(menu)
        {
            case 'p':
            case 'P':
                //abre fichero y muestra la puntuación mas alta
                break;

            case 'c':
            case 'C':
                printf("Para mover la pieza en horizontal utilizar las flechas laterales, para rotar utilizar la flecha superior, y para bajar utilizar la inferior\n");
                break;

            case 'j':
            case 'J':
                exit = 0;
                return exit;
                break;

        }
    }
    return exit;
}

void pintapiece(pieza curr,pieza old,int mat[][20],int vasio,SDL_Renderer *render) //Saca la pieza con la que se está jugando por pantalla
{
    int i,x1,y1,x[4],y[4];
    SDL_Rect filrect;
    filrect.w=50;
    filrect.h=50;

    piecepreview(old,mat,vasio,255,1,render);
    piecepreview(curr,mat,vasio,128,0,render);

    SDL_SetRenderDrawColor(render,0,0,0,255);

    x[0]=old.posx;
    y[0]=old.posy;
    for(i=1;i<4;i+=1)
    {
        x[i]=(old.posx+old.rposx[i-1]);
        y[i]=(old.posy+old.rposy[i-1]);
    }


    for(i=0;i<4;i+=1)
    {
        x1=710+50*(x[i]);
        y1=40+50*(y[i]);

        filrect.x=x1;
        filrect.y=y1;
        SDL_RenderFillRect(render,&filrect);
        SDL_RenderPresent(render);

    }

    x[0]=curr.posx;
    y[0]=curr.posy;
    for(i=1;i<4;i+=1)
    {
        x[i]=curr.posx+curr.rposx[i-1];
        y[i]=curr.posy+curr.rposy[i-1];
    }

    if(curr.type=='i')
    {
        SDL_SetRenderDrawColor(render,51,255,255,255);
    }
    if(curr.type=='c')
    {
         SDL_SetRenderDrawColor(render,255,255,0,255);
    }
    if(curr.type=='t')
    {
        SDL_SetRenderDrawColor(render,170,0,255,255);
    }
    if(curr.type=='s')
    {
        SDL_SetRenderDrawColor(render,0,255,0,255);
    }
    if(curr.type=='z')
    {
        SDL_SetRenderDrawColor(render,255,0,0,255);
    }
    if(curr.type=='l')
    {
        SDL_SetRenderDrawColor(render,0,38,230,255);
    }
    if(curr.type=='j')
    {
        SDL_SetRenderDrawColor(render,255,128,0,255);
    }

    for(i=0;i<4;i+=1)
    {
        x1=710+50*(x[i]);
        y1=40+50*(y[i]);

        filrect.x=x1;
        filrect.y=y1;
        SDL_RenderFillRect(render,&filrect);
        SDL_RenderPresent(render);

    }
}

void pintamatr(int matriz[][20],int tamfil,int tamcol,SDL_Renderer *render) //pintar una matriz, usando dos bucles uno anidado en el otro, yo uso while, lo normal serían for
{
    int i=0, j=0,x1,y1;
    SDL_Rect filrect;

    filrect.w=50;
    filrect.h=50;

    for(i=0;i<tamcol;i++)
    {
        for(j=0;j<tamfil;j++)
        {
            x1=710+50*j;
            y1=40+50*i;

            filrect.x=x1;
            filrect.y=y1;

            if( matriz[j][i]==' ')
            {
                SDL_SetRenderDrawColor(render,0,0,0,255);
            }
            if( matriz[j][i]=='i')
            {
                SDL_SetRenderDrawColor(render,51,255,255,255);
            }
            if( matriz[j][i]=='c')
            {
                SDL_SetRenderDrawColor(render,255,255,0,255);
            }
            if( matriz[j][i]=='t')
            {
                SDL_SetRenderDrawColor(render,170,0,255,255);
            }
            if( matriz[j][i]=='s')
            {
                SDL_SetRenderDrawColor(render,0,255,0,255);
            }
            if( matriz[j][i]=='z')
            {
                SDL_SetRenderDrawColor(render,255,0,0,255);
            }
            if( matriz[j][i]=='l')
            {
                SDL_SetRenderDrawColor(render,0,38,230,255);
            }
            if( matriz[j][i]=='j')
            {
                SDL_SetRenderDrawColor(render,255,128,0,255);
            }

            SDL_RenderFillRect(render,&filrect);

            SDL_RenderPresent(render);
        }
    }
}

void vacia(int mat[][20],int fil, int col,int vasio) //vacia una matriz usando un bucle anidado en otro
{
    int i,j;

    for(i=0;i<col;i++)
    {
        for(j=0;j<fil;j++)
            mat[j][i]=vasio;
    }
}

void mat2mat(int mat[][20],int mat2[][20],int fil,int col) //se asigna una matriz a otra haciendo uso de un buclr anidado
{
    int i,j;
    for(i=0;i<col;i++)
    {
        for(j=0;j<fil;j++)
        {
            mat2[j][i]=mat[j][i];
        }
    }
}

void piece2mat(int mat[][20],pieza pis) //se asignan los cuatro bloques de una pieza donde las coordenadas de la pieza indican
{
    int i;
    mat[pis.posx][pis.posy]=pis.type; //asignacion bloque central
    for(i=0;i<3;i++)//asignacion bloques no centrales
    {
        mat[pis.posx+pis.rposx[i]][pis.posy+pis.rposy[i]]=pis.type;
    }
}

int canfall(int matriz[][20],int fil,int col,pieza pise,int vasio) //comprobación de si la pieza puede caer
{
    int x[4],y[4],i;
    int comp=1; //comprobador

//obteniendo la posicion de los cuatro bloques si la pieza cayese
    x[0]=pise.posx;
    y[0]=pise.posy+1; // si la pieza cayese esta sería la nueva coordenada y
    for(i=1;i<4;i++)
    {
        x[i]=pise.posx+pise.rposx[i-1];
        y[i]=pise.posy+pise.rposy[i-1]+1;
    }
    for(i=0;i<4;i++) //se comprueba que en todas las posiciones que tomaría la pieza si cayese hay vacio y no se sale de los limites del juego
    {
        if((matriz[x[i]][y[i]]!=vasio)||(y[i]>19))
            comp=0;
    }
    return comp;

}

pieza newpiece() //genera una nueva pieza
{
    int seed;
    pieza pise;

    seed=rand() % 7 + 1; //genera un numero aleatorio entre 1 y 7, incluidos, ya que hay 7 posibles piezas
    //para cada numero se asignan las posiciones relativas que tendrá la pieza cuando aparezaca por pantalla, estan puestas para que quepa teniendo en cuenta el límite superior
    //tambien se asigna el tipo, en este caso con letras
     if(seed==1) //cuadrado (c)
     {
         pise.type='c';
         pise.rposx[0]=0;
         pise.rposx[1]=1;
         pise.rposx[2]=1;
         pise.rposy[0]=1;
         pise.rposy[1]=0;
         pise.rposy[2]=1;
     }
     if(seed==2) //T tipo(t)
     {
         pise.type='t';
         pise.rposx[0]=0;
         pise.rposx[1]=1;
         pise.rposx[2]=-1;
         pise.rposy[0]=1;
         pise.rposy[1]=0;
         pise.rposy[2]=0;
     }
     if(seed==3) //I/palo tipo(i)
     {
         pise.type='i';
         pise.rposx[0]=1;
         pise.rposx[1]=-1;
         pise.rposx[2]=2;
         pise.rposy[0]=0;
         pise.rposy[1]=0;
         pise.rposy[2]=0;
     }
     if(seed==4) //J tipo(j)
     {
         pise.type='j';
         pise.rposx[0]=-1;
         pise.rposx[1]=1;
         pise.rposx[2]=1;
         pise.rposy[0]=0;
         pise.rposy[1]=0;
         pise.rposy[2]=1;
     }
     if(seed==5) //L tipo(l)
     {
         pise.type='l';
         pise.rposx[0]=-1;
         pise.rposx[1]=1;
         pise.rposx[2]=-1;
         pise.rposy[0]=1;
         pise.rposy[1]=0;
         pise.rposy[2]=0;
     }
     if(seed==6) //Z tipo(z)
     {
         pise.type='z';
         pise.rposx[0]=1;
         pise.rposx[1]=-1;
         pise.rposx[2]=0;
         pise.rposy[0]=1;
         pise.rposy[1]=0;
         pise.rposy[2]=1;
     }
     if(seed==7) //S tipo(s)
     {
         pise.type='s';
         pise.rposx[0]=0;
         pise.rposx[1]=1;
         pise.rposx[2]=-1;
         pise.rposy[0]=1;
         pise.rposy[1]=0;
         pise.rposy[2]=1;
     }

     // asignacion de la posición inicial del bloque central de la pieza en la matriz
     pise.posx=4;
     pise.posy=0;

    return pise;
}

pieza fall(pieza pis) // hace caer la pieza cambiando la coordenada y del bloque central
{
    pis.posy+=1;
    return pis;
}

int canmove(int mat[][20],int fil,int col,pieza pis,int dir,int vasio) //comprueba que se puede mover la pieza hacia la direccion elegida
{
    int x[4],y[4],i;
    int comp=1;

    if(dir=='r') //obtiene las posiciones quegeneraria un movimiento a la derecha
    {
        x[0]=pis.posx+1;
        y[0]=pis.posy;
    for(i=1;i<4;i++)
    {
        x[i]=pis.posx+pis.rposx[i-1]+1;
        y[i]=pis.posy+pis.rposy[i-1];
    }
    }
    else if(dir=='l') //obtiene las posiciones quegeneraria un movimiento a la izquierda
    {
        x[0]=pis.posx-1;
        y[0]=pis.posy;
        for(i=1;i<4;i++)
    {
        x[i]=pis.posx+pis.rposx[i-1]-1;
        y[i]=pis.posy+pis.rposy[i-1];
    }
    }
    else // esto no deberia darse por tanto cambia la comprobacion señalizando un error
    {
        comp=0;
    }
    for(i=0;i<4;i++) //comprueba que las coordenadas que resultarian del movimiento elegido estan vacias y no se salen de los limites de la zona de juego
    {
        if((mat[x[i]][y[i]]!=vasio)||(x[i]>=fil)||(x[i]<0))
            comp=0;
    }
    return comp;

}

pieza mov(pieza pis,char dir) // mueve la pieza en la dirección elegida, solo hace falta cambiar la coordenada x el bloque central
{

    if(dir=='l') //izquierda
        {
            pis.posx-=1;
        }
    else if (dir=='r') //derecha
        {
            pis.posx+=1;
        }
    return pis;
}

int canrotate(int mat[][20],int fil,int col,pieza pis,char dir,int vasio) // comprueba que la pieza puede rotar en la dirección elegida
{
    int x[4],y[4],i;
    int comp=1;

      // las coordenadas del bloque central no varían en una rotacion, solo varían las relativas
        x[0]=pis.posx;
        y[0]=pis.posy;

    if(dir=='r') //calcula las posicionse de los bloques no centrales resultantes de una rotación hacia la derecha
    {
    for(i=1;i<4;i++) // para la derecha el cambio es (x,y)->(-y,x)
    {
        x[i]=pis.posx-pis.rposy[i-1];
        y[i]=pis.posy+pis.rposx[i-1];
    }
    }
    else if(dir=='l') //calcula las posicionse de los bloques no centrales resultantes de una rotación hacia la izquierda
    {
        for(i=1;i<4;i++) //para la izquierda el cambio es (x,y)->(y,-x)
    {
        x[i]=pis.posx+pis.rposy[i-1];
        y[i]=pis.posy-pis.rposx[i-1];
    }
    }
    else //posible error
    {
        comp=0;
    }
    for(i=0;i<4;i++) //comprueba que las coordenadas resultantes de una rotación en la dirección elegida estan vacias y no superan los limites de la zona de juego
    {
        if((mat[x[i]][y[i]]!=vasio)||(x[i]>=fil)||(x[i]<0)||(y[i]>=col))
            comp=0;
    }
    return comp;
}

pieza rot(pieza pis,char dir) //rota la pieza hacia la sireccion elegida
{
    int i, oldx[3], oldy[3]; //en este caso se guardan las coordenadas relativas para que al irlas cambiando no den error

    for (i=0;i<3;i++) // guardado de coordenadas relativas
    {
        oldx[i]=pis.rposx[i];
        oldy[i]=pis.rposy[i];
    }


    if(dir=='l') // giro hacia la izquierda (x,y)->(y,-x)
        {
            for(i=0;i<3;i++)
            {
                pis.rposx[i]=oldy[i];
                pis.rposy[i]=-oldx[i];
            }
        }
    else if (dir=='r') //giro hacia la derecha (x,y)->(-y,x)
    {
            for(i=0;i<3;i++)
            {
                pis.rposx[i]=-oldy[i];
                pis.rposy[i]=oldx[i];
            }
    }
    return pis;

}

int endgame(int mat[][20],int fil,int vasio) //comprueba si ha de terminar el juego
{
    int comp=0,i;
    for(i=0;i<fil;i++) //si la linea mas alta tiene algún bloque el comprobador cambia a que la partida debería terminar
    {
        if(mat[i][0]!=vasio)
            comp=1;
    }
    return comp;
}

void linea(int mat[][20],int fil,int col,int vasio, int *p) //detecta y elimina lineas completas
{
    int i,j,comp;
    int n=0;
    for(i=0;i<col;i++) // mira lineas de arriba hacia abajo
    {
        comp=1;
        for(j=0;j<fil;j++)
            {
                if(mat[j][i]==vasio) //si hay una linea que no tiene ningun hueco el comprobador no cambia
                {
                    comp=0;
                }
        if(comp==1) //si el comprobador no cambia la linea actual y las que tenga arriba serán sustituidas por la linea directamente superior
        {
            n += 1;
            while(i>0)
            {
                for(j=0;j<fil;j++)
                {
                    mat[j][i]=mat[j][i-1];
                }
                i-=1; //como usa la misma variable de avance que el for, al terminar este while el bucle for comenzara desde la linea 1, esto a lo mejor podría ser optimizado
            }
            comp=0; //pasa el comprobador a 0 de nuevo ya que pueden crearse hasta cuatro lineas en una jugada
        }
            }

    }
    while(n<=4 && n>0)
    {
    *p += n*100;
    n-=1 ;
    }
}

void newframe(int mat[][20],int mats[][20],int fil,int col,int vasio,pieza pis,SDL_Renderer *render) //ejecuta en orden las funciones necesarias para actualizar la pantalla al estado del momento del juego
{
    vacia(mats,fil,col,vasio); //primero se vacia la matriz que se usara para imprimir por pantalla
    mat2mat(mat,mats,fil,col); //segundo se asigna la matriz de estado a la matriz "pantalla"
    piece2mat(mats,pis);       //tercero se coloca la pieza en su posición actual, es importante hacer esto despues de asignar la matriz de estado ya que si se hiciera antes sería sobreescrita por los huecos de la matriz de estado
    pintamatr(mats,fil,col,render);   //Por último se imprime la matriz "pantalla"
}

void scene(SDL_Renderer *Render,SDL_Window *Ventana,SDL_Texture *Textura,char path[])//Para pintar fondos y escenarios
{
      SDL_SetRenderDrawColor( Render, 0xFF, 0xFF, 0xFF, 0xFF ); //Se pone el color del render en blanco


        SDL_Surface *SupCarg = SDL_LoadBMP(path); //Se carga el fondo
            if( SupCarg == NULL ) //Se comprueba si se ha guardado bien el fondo
            {
                printf( "No se pudo cargar la imagen: %s SDL Error: %s\n", path, SDL_GetError() );
            }
            else
            {
                Textura = SDL_CreateTextureFromSurface( Render, SupCarg ); //Se aplica el fondo sobre la textura
                if(  Textura == NULL ) //Se compueba si la textura ha cogido el fondo
                {
                    printf( "No se pudo cargar crear la textura SDL Error: %s\n", SDL_GetError() );
                }
                SDL_FreeSurface( SupCarg );


                    SDL_RenderCopy( Render, Textura, NULL, NULL ); //Se coloca la textura sobre el render
                    SDL_RenderPresent( Render ); //Se actualiza el Render
            }
}

void truefall(int matestado[][20],int matscreen[][20],int vasio,int *exit,pieza *old,pieza *pos,pieza cola[],SDL_Renderer *render,SDL_Texture *textura,int *canhold)
{
    if(canfall(matestado,10,20,*pos,vasio)==1) // hacer la pieza caer si puede
                         {
                             *pos=fall(*pos);
                         }
                         else if (canfall(matestado,10,20,*pos,vasio)==0) // si no puede caer la pieza
                         {
                             piece2mat(matestado,*pos);  //la pieza pasa a la matriz de estado
                             *pos=nextpiece(cola,4,render,textura); //se genera una nueva pieza
                             linea(matestado,10,20,vasio);  //se quitan las lineas que haya podido crear la nueva pieza
                             newframe(matestado,matscreen,10,20,vasio,*pos,render);
                             *exit=endgame(matestado,10,vasio);//se comprueba que la pieza no ha podido acabar la partida
                             *old=*pos;
                             *canhold=1;
                         }
}

pieza nextpiece(pieza cola[],int tam,SDL_Renderer *render,SDL_Texture *textura)
{
    pieza pos;
    int i;

    pos=cola[0];

    for(i=0;i<(tam-1);i+=1)
    {
        cola[i]=cola[i+1];
    }
    cola[tam-1]=newpiece();

    rendercola(cola,tam,render,textura);

    return pos;
}

void rendercola(pieza cola[], int tam, SDL_Renderer *render,SDL_Texture *textura)
{
    int i;
    SDL_Rect cl;
    cl.w=80;
    cl.h=80;
    cl.x=1300;


    SDL_SetRenderDrawColor( render, 0xFF, 0xFF, 0xFF, 0xFF );

    for(i=0;i<tam;i++)
    {
        if(cola[i].type=='i')
        {
        char camino[50]=("sprites/i.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(cola[i].type=='c')
        {
        char camino[50]=("sprites/c.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(cola[i].type=='t')
        {
        char camino[50]=("sprites/t.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(cola[i].type=='s')
        {
        char camino[50]=("sprites/s.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(cola[i].type=='z')
        {
        char camino[50]=("sprites/z.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }


        if(cola[i].type=='l')
        {
        char camino[50]=("sprites/l.bmp");
        SDL_Surface *SupCarg = SDL_LoadBMP(camino);

        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }

        if(cola[i].type=='j')
        {
        char camino[50]=("sprites/j.bmp");

        SDL_Surface *SupCarg = SDL_LoadBMP(camino);
        cl.y=200+100*i;
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
    }
}

pieza hold(pieza *hold,pieza curr,int *canhold,pieza cola[],SDL_Renderer *render, SDL_Texture *textura)
{
    pieza aux;
    SDL_Rect cl;
    cl.w=80;
    cl.h=80;
    cl.x=510;
    cl.y=200;

    if(*canhold==1)
    {
        if(hold->type=='f')
        {
            *hold=curr;
            curr=nextpiece(cola,4,render,textura);
        }
        else
        {
            aux=curr;
            curr=*hold;
            *hold=aux;

        }
        *canhold=0;
    }


        if(hold->type=='i')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/i.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='c')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/c.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='t')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/t.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='s')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/s.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='z')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/z.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='l')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/l.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }
        if(hold->type=='j')
        {
        SDL_Surface *SupCarg = SDL_LoadBMP("sprites/j.bmp");
        textura=SDL_CreateTextureFromSurface(render,SupCarg);
        SDL_RenderCopy(render,textura,NULL,&cl);
        SDL_RenderPresent(render);
        }

    return curr;
}

void piecepreview(pieza pis,int mat[][20],int vasio,int alfa,int old,SDL_Renderer *render)
{
    int x[4],y[4],i,j,comp;
    SDL_Rect filrect;
    filrect.w=50;
    filrect.h=50;


    x[0]=pis.posx;
    for(i=1;i<4;i+=1)
    {
        x[i]=x[0]+pis.rposx[i-1];
    }

    comp=1;
    i=0;
    while(comp==1)
    {
        y[0]=pis.posy+i;
        for(j=1;j<4;j+=1)
        {
            y[j]=y[0]+pis.rposy[j-1];
        }
        for(j=0;j<4;j+=1)
        {
            if((mat[x[j]][y[j]]!=vasio)||y[j]>19)
            {
                comp=0;
            }
        }

        i+=1;
    }
    y[0]=pis.posy+(i-2);
    for(i=1;i<4;i+=1)
    {
        y[i]=y[0]+pis.rposy[i-1];
    }



    if(old==1)
    {
        SDL_SetRenderDrawColor(render,0,0,0,255);
        for(i=0;i<4;i+=1)
        {
            filrect.x=710+50*(x[i]);
            filrect.y=40+50*(y[i]);
            SDL_RenderFillRect(render,&filrect);
            SDL_RenderPresent(render);

        }
    }
    else
    {
        if(pis.type=='i')
        {
            SDL_SetRenderDrawColor(render,51,255,255,alfa);
        }
        if(pis.type=='c')
        {
             SDL_SetRenderDrawColor(render,255,255,0,alfa);
        }
        if(pis.type=='t')
        {
            SDL_SetRenderDrawColor(render,170,0,255,alfa);
        }
        if(pis.type=='s')
        {
            SDL_SetRenderDrawColor(render,0,255,0,alfa);
        }
        if(pis.type=='z')
        {
            SDL_SetRenderDrawColor(render,255,0,0,alfa);
        }
        if(pis.type=='l')
        {
            SDL_SetRenderDrawColor(render,0,38,230,alfa);
        }
        if(pis.type=='j')
        {
            SDL_SetRenderDrawColor(render,255,128,0,alfa);
        }

        SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_BLEND);
        for(i=0;i<4;i+=1)
        {
            filrect.x=710+50*(x[i]);
            filrect.y=40+50*(y[i]);
            SDL_RenderFillRect(render,&filrect);
            SDL_RenderPresent(render);

        }
        SDL_SetRenderDrawBlendMode(render,SDL_BLENDMODE_NONE);
    }

}

pieza hardfall(pieza pis,int mat [][20],int vasio)
{
    int x[4],y[4],i,j,comp;


    x[0]=pis.posx;
    for(i=1;i<4;i+=1)
    {
        x[i]=x[0]+pis.rposx[i-1];
    }

    comp=1;
    i=0;
    while(comp==1)
    {
        y[0]=pis.posy+i;
        for(j=1;j<4;j+=1)
        {
            y[j]=y[0]+pis.rposy[j-1];
        }
        for(j=0;j<4;j+=1)
        {
            if((mat[x[j]][y[j]]!=vasio)||y[j]>19)
            {
                comp=0;
            }
        }

        i+=1;
    }
    pis.posy+=(i-2);

        return pis;
}

void highscore(jugador vec[])//ordena puntuación,vector de estructura para definir los jugadores
{
    int i,j;
    jugador aux;
    for(i=0;i<51;i++)//bucle for anidado
    {
        for(j=i;j<51;j++)
        {
            if(vec[i].puntuacion<vec[j].puntuacion)
            {
                aux=vec[i];
                vec[i]=vec[j];
                vec[j]=aux;
            }
        }
    }
}

