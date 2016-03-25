#include "maxcorp_SDL.h"
#include "Pentaction.h"

/* Idées :
- On joue avec la souris ( éventuellement les fleches pour les plus sado )
- On déplace un carré faisant office de curseur, et on évite toutes les merdes qui arrivent de partout.
- On peut envisager deux carrés à déplacer, un souris et un clavier. Soit les deux de la même couleur d'obstacle, soit distincte.
*/

int Dodgeall (SDL_Surface *ecran)
{
    SDL_ShowCursor(0);
    //SDL_WarpMouse(480,320);
    int score=0;
    int aff=10, affichage=1;
    int p[2]={480,320};
    int y[50], xdeb[50], xfin[50];
    int sens=1; // 1 : bas, -1 : haut, 2 : gauche, -2 : droite
    int ecart=100, trou=200; // ecart +-1/4 et trou +-1/2


    sens=rand()%4;
    if(sens==0) sens=-2;
    else if (sens==3) sens=-1;

    int i=0;
    while(i<50)
    {
        y[i]=-1;
        xdeb[i]=-1;
        xfin[i]=-1;
        i++;
    }
    y[0]=0; xdeb[0]=50; xfin[0]= TAILLE_X-50; ///Au cas ou le decor ne démarre pas


    while(!Situation.exit && Collision(p[0], p[1], y, xdeb, xfin, sens))
    {
        if(affichage)SDL_Flip(ecran);
        if(affichage)Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Changer_situation();
        Genere_mobile(ecran, sens, y, xdeb, xfin, ecart, trou, affichage);
        if(affichage)Bouge_souris(ecran, p);
        score++;
        if( aff>1 && score%500==0) aff--;
        if(aff<2)
        {
            if(score%((3-aff)*1000)==0) aff--;
            affichage=score%(4-aff);
            if(affichage) affichage=0;
            else affichage=1;
        }
        else affichage=score%aff;
        if(affichage)Affichage_score2(ecran,score,TAILLE_X-67,TAILLE_Y-15);
        //SDL_Delay(5);

    }

    SDL_ShowCursor(1);
    return score;
}


int Collision(int px, int py, int *y, int *xdeb, int *xfin, int sens)
{
    int i=0;
    if(sens==1)
    {
        while(y[i]!=-1)
        {
            if(!(py<y[i]-TAILLE_CARRE || py>= y[i]+2) && (px<xdeb[i] || px>= xfin[i]+TAILLE_CARRE)) return 0;
            i++;
        }
    }
    else if(sens==-1)
    {
        while(y[i]!=-1)
        {
            if(!(py<TAILLE_Y-y[i]-TAILLE_CARRE || py>= TAILLE_Y-y[i]+2) && (px<xdeb[i] || px>= xfin[i]+TAILLE_CARRE)) return 0;
            i++;
        }
    }
    else if(sens==-2)
    {
        while(y[i]!=-1)
        {
            if((py<xdeb[i] || py>= xfin[i]+TAILLE_CARRE)  && !(px<y[i]-TAILLE_CARRE || px>= y[i]+2)) return 0;
            i++;
        }
    }
    else if(sens==2)
    {
        while(y[i]!=-1)
        {
            if((py<xdeb[i] || py>= xfin[i]+TAILLE_CARRE)  && !(px<TAILLE_X-y[i]-TAILLE_CARRE || px>= TAILLE_X-y[i]+2)) return 0;
            i++;
        }
    }
    return 1;
}

void Genere_mobile(SDL_Surface *ecran, int sens, int *y, int *xdeb, int *xfin, int ecart, int trou, int affichage)
{
    int i=0;
    int k=0;
    int t=0;
    while(i<50 && y[i]>-1)
    {
        y[i]++;
        if((y[i]==TAILLE_Y && (sens==1 || sens== -1)) || (y[i]==TAILLE_X && (sens==2 || sens== -2)))
        {
            k=i;
            while(k<49 && y[k]!=-1)
            {
                y[k]=y[k+1];
                xdeb[k]=xdeb[k+1];
                xfin[k]=xfin[k+1];
                k++;
            }
        }
        else if(sens==1)
        {
            if(affichage)Blit(ecran,0,y[i],xdeb[i],2,255,0,0);
            if(affichage)Blit(ecran,xfin[i],y[i],TAILLE_X-xfin[i],2,255,0,0);
            i++;
        }
        else if(sens==-1)
        {
            if(affichage)Blit(ecran,0,TAILLE_Y-y[i],xdeb[i],2,255,0,0);
            if(affichage)Blit(ecran,xfin[i],TAILLE_Y-y[i],TAILLE_X-xfin[i],2,255,0,0);
            i++;
        }
        else if(sens==2)
        {
            if(affichage)Blit(ecran,TAILLE_X-y[i],0,2,xdeb[i],255,0,0);
            if(affichage)Blit(ecran,TAILLE_X-y[i],xfin[i],2,TAILLE_X-xfin[i],255,0,0);
            i++;
        }
        else if(sens==-2)
        {
            if(affichage)Blit(ecran,y[i],0,2,xdeb[i],255,0,0);
            if(affichage)Blit(ecran,y[i],xfin[i],2,TAILLE_X-xfin[i],255,0,0);
            i++;
        }
    }

    if(y[i]==-1) y[i]= rand()%(ecart/2) - 5*ecart/4;

    else if(y[i]>-y[i-1])
    {
        y[i]=0;
        t=rand()%(trou)+trou/2;
        if(sens==1 || sens ==-1) xdeb[i]=rand()%(TAILLE_X-t);
        else                     xdeb[i]=rand()%(TAILLE_Y-t);
        xfin[i]=xdeb[i]+t;
    }
}

void Bouge_souris(SDL_Surface *ecran, int *p)
{
    p[0]=Situation.mousex;
    p[1]=Situation.mousey;
    Blit(ecran,p[0]-TAILLE_CARRE/2,p[1]-TAILLE_CARRE/2,TAILLE_CARRE,TAILLE_CARRE,255,0,0);
}
