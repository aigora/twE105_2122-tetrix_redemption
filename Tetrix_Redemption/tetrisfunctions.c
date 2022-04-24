#include<stdio.h>
#include"tetrisfunctions.h"
#include<time.h>
#include<stdlib.h>

void pintamatr(int matriz[][20],int tamfil,int tamcol) //pintar una matriz, usando dos bucles uno anidado en el otro, yo uso while, lo normal serían for
{
    int i=0, j=0;

    i=0;
    while(i<tamcol)
    {
        printf("%i \t( ",i);
        j=0;
        while(j<tamfil)
        {
            printf(" %c ", matriz[j][i]);
            j+=1;
        }
        i+=1;
        printf(") \n");
    }
    printf("\n \n");
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

pieza newpiece(pieza pise) //genera una nueva pieza
{
    int seed;

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

void linea(int mat[][20],int fil,int col,int vasio) //detecta y elimina lineas completas
{
    int i,j,comp;

    for(i=0;i<col;i++) // mira lineas de arriba hacia abajo
    {
        comp=1;
        for(j=0;j<fil;j++)
            {
                if(mat[j][i]==vasio) //si hay una linea que no tiene ningun hueco el comprobador no cambia
                    comp=0;
            }
        if(comp==1) //si el comprobador no cambia la linea actual y las que tenga arriba serán sustituidas por la linea directamente superior
        {
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

void newframe(int mat[][20],int mats[][20],int fil,int col,int vasio,pieza pis) //ejecuta en orden las funciones necesarias para actualizar la pantalla al estado del momento del juego
{
    vacia(mats,fil,col,vasio); //primero se vacia la matriz que se usara para imprimir por pantalla
    mat2mat(mat,mats,fil,col); //segundo se asigna la matriz de estado a la matriz "pantalla"
    piece2mat(mats,pis);       //tercero se coloca la pieza en su posición actual, es importante hacer esto despues de asignar la matriz de estado ya que si se hiciera antes sería sobreescrita por los huecos de la matriz de estado
    pintamatr(mats,fil,col);   //Por último se imprime la matriz "pantalla"
}
