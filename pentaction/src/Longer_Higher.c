#include "maxcorp_SDL.h"
#include "Pentaction.h"
#include <math.h>

/* Idées :
- Le but : aller le plus loin mais aussi le plus haut possible
- Le score pourrait etre aire en dessous ( integrale de fonction en escalier de pas 10)
- Mettre des obstacles et des boosts ... à voir quand on y sera
*/

int Longer_Higher(SDL_Surface *ecran)
{
    int score=0;
    int past_longueur=0;
    int a[6]={0}; // 0 : px, 1 py, 2 : vx, 3 : vy, 4 : longueur, 5 : hauteur
    int tir[3];


    tir[0]=0; // direction de frappe du marteau ( ou contenant la vitesse algebrique )
    tir[1]=TAILLE_X/2; // marteaux
    tir[2]=TAILLE_Y/10 + TAILLE_Y/2 ; // marteauy
    a[0]=TAILLE_X/8*7-TAILLE_CARRE/2;
    a[1]=TAILLE_Y/2-TAILLE_CARRE/2;
    a[3]=6;

    // Phase de départ
    while(Gestion_lanceur(ecran,a, tir) && !Situation.exit)
    {
        SDL_Flip(ecran);
        Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Changer_situation();
        Mouvement_depart(ecran,a);
        SDL_Delay(3);
    }

    //Test de vitesse initiale
    a[2] = 5;
    a[3] *= -1;
    a[5]= TAILLE_Y - a[1];

    // Phase de jeu
    while(a[5] >= 0 && !Situation.exit)
    {
        SDL_Flip(ecran);
        Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Changer_situation();
        Mouvement_reel(ecran,a);
        score += (a[4]-past_longueur)*a[5];
        past_longueur=a[4];

        Affichage_score2(ecran,score,TAILLE_X-67,TAILLE_Y-15);
    }

    return score;
}


void Mouvement_depart(SDL_Surface *ecran, int *a)
{
    Blit(ecran, TAILLE_X/8*7-TAILLE_CARRE,TAILLE_Y/8-TAILLE_CARRE,TAILLE_CARRE*2,TAILLE_CARRE*2,255,0,255);
    Blit(ecran, TAILLE_X/8*7-TAILLE_CARRE,TAILLE_Y/8*7-TAILLE_CARRE,TAILLE_CARRE*2,TAILLE_CARRE*2,255,0,255);

    if(a[1]<=TAILLE_Y/8+TAILLE_CARRE) a[3]= 6;
    else if(a[1]>=TAILLE_Y/8*7-TAILLE_CARRE*2) a[3]= -6;

    a[1] += a[3];

    Blit(ecran,a[0],a[1],TAILLE_CARRE,TAILLE_CARRE,255,0,0);

}


void Mouvement_reel(SDL_Surface *ecran, int *a)
{
    a[3]--;
    a[0] -= a[2];
    a[4] += a[2];
    a[1] -= a[3];
    a[5] += a[3];

    Blit(ecran,a[0],a[1],TAILLE_CARRE,TAILLE_CARRE,255,0,0);
    SDL_Delay(50);
}

int Gestion_lanceur(SDL_Surface *ecran, int *a, int *tir)
{
    static int captureclic=0;
    static float t=0;
    static int supportx=TAILLE_X/2 , supporty=TAILLE_Y/10 ;
    static int ligne=TAILLE_Y/2;


    if(captureclic==-1) // Démarrer le lancer
    {
        if(Situation.escape) captureclic=0;
        else
        {
                tir[1]=ligne*sin(t)+supportx;
                tir[2]=ligne*cos(t)+supporty;
                if(cos(t)>0) t += 0.001 + cos(t)/40.;
                else t += 0.001 - cos(t)/40.;
        }
        //Ligne
       // BlitLine(ecran,supportx,supporty,tir[1],tir[2],0,0,255);                                /// A GRANDEMENT AMELIORER
        //Support
        Blit(ecran,supportx-SUPPORT_X/2,supporty-SUPPORT_Y/2,SUPPORT_X,SUPPORT_Y,255,255,255);
        //Marteau
        BlitBall(ecran, tir[1], tir[2], 0, 255, 0, 0);

        if(a[0]<=tir[1]+MARTEAU_X/2 && a[0]+TAILLE_CARRE>=tir[1]-MARTEAU_X/2 && a[1]<=tir[2]+MARTEAU_Y/2 && a[1]+TAILLE_CARRE>=tir[2]-MARTEAU_Y/2)
        {
            tir[0]=11;// Un certain potentiel dépendant du cos(t) et des positions relatives des objets
            SDL_ShowCursor(1);
            return 0;
        }
        else return 1;
    }
    else if(Situation.space==1) // Monter propgressivement le marteau
    {
        t=3.14159;
        SDL_ShowCursor(0);
        captureclic=-1;
        //Support
        Blit(ecran,supportx-SUPPORT_X/2,supporty-SUPPORT_Y/2,SUPPORT_X,SUPPORT_Y,255,255,255);
        //Marteau
        BlitBall(ecran, tir[1], tir[2], 0, 255, 0, 0);
        return 1;
    }
    else if(Situation.clic_g==0)
    {
        captureclic=0;
        SDL_ShowCursor(1);
    }
    else if(captureclic==0 && Situation.clic_g==1)
    {
        if(Situation.mousex>=supportx-SUPPORT_X/2 && Situation.mousex<=supportx+SUPPORT_X/2 && Situation.mousey>=supporty-SUPPORT_Y/2 && Situation.mousey<=supporty+SUPPORT_Y/2)
        {
            captureclic=1;
            SDL_ShowCursor(0);
        }
        else if(Situation.mousex>=tir[1]-MARTEAU_X/2 && Situation.mousex<=tir[1]+MARTEAU_X/2 && Situation.mousey>=tir[2]-MARTEAU_Y/2 && Situation.mousey<=tir[2]+MARTEAU_Y/2)
        {
            captureclic=2;
            SDL_ShowCursor(0);
        }
    }
    else if(captureclic==1)
    {
            supportx=Situation.mousex;
            supporty=Situation.mousey;
    }
    else if(captureclic==2)
    {
            ligne=Situation.mousey-supporty;
            if(ligne<MARTEAU_Y/2+SUPPORT_Y/2) ligne=MARTEAU_Y/2+SUPPORT_Y/2;
    }

    tir[1]= supportx ;
    tir[2]= supporty + ligne ;
    //Ligne
    Blit(ecran,supportx,supporty,1,ligne,0,0,255);
    //Support
    Blit(ecran,supportx-SUPPORT_X/2,supporty-SUPPORT_Y/2,SUPPORT_X,SUPPORT_Y,255,255,255);
    //Marteau
    BlitBall(ecran, tir[1], tir[2], 0, 255, 0, 0);


    return 1;
}

