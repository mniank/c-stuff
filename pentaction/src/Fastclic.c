#include "maxcorp_SDL.h"
#include "Pentaction.h"

/* Idées :
- Carré rouge tendant vers le noir -> Cliquer dessus rapporte R point ( avec R€[0;255] )
- Faux carré ( style orange ( qu'on croit que ca soit du rouge)) qui diminuent les points et stop le combo.
- Combo : A chaque clic qur un carré rouge : combo++; le score est R*combo
- A parti d'un certain N, carrés mobiles.
- En upgrade : Affichage d'un carré bleu signalant la présence d'un futur carré coloré à cet endroit.
*/


int N=1;

int Fastclic(SDL_Surface *ecran)
{
    int score=0;
    int combo=0;
    int temps=SDL_GetTicks();
    int carre_x[20]={-1}, carre_y[20]={-1}, carre_t[20]={-1}, carre_c[20]={255};

    while(Genere_carre(ecran,carre_x,carre_y,carre_t,carre_c) && !Situation.exit)
    {
        SDL_Flip(ecran);
        Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Changer_situation();
        switch(Gerer_clic(carre_x, carre_y, carre_t))
        {
            case 1: combo+=N; score += combo; break;
            case -1: combo=0; break;
            case 0: break;
        }
        if(combo >= 5*N*(N+2)) N++;

        Affichage_score2(ecran,score*100,TAILLE_X-67,TAILLE_Y-15);

        temps=SDL_GetTicks()-temps;
        if(temps<15) SDL_Delay(15- temps);
        temps=SDL_GetTicks();
    }

    return score*100;
}

int Genere_carre(SDL_Surface *ecran, int *carre_x, int *carre_y, int *carre_t, int *carre_c)
{
    int i=0;
    int k=0;
    while(carre_t[i]!=-1 && i<20)
    {
        if(carre_c[i]<=0) carre_c[i]=255;
        carre_c[i]-=N;
        if(carre_c[i] <= 0) return 0;
        if(carre_t[i]==0) // Type 0 lorsqu'on a cliqué dessus (ou fin d'un carre fake )
        {
            k=i;
            while(k<20-1 && carre_t[k]!=-1)
            {
                carre_x[k]=carre_x[k+1];
                carre_y[k]=carre_y[k+1];
                carre_t[k]=carre_t[k+1];
                carre_c[k]=carre_c[k+1];
                k++;
            }
            carre_t[k]=-1;
            carre_c[k]=-1;
            i--;
        }
        if(carre_t[i]==1) Blit(ecran,carre_x[i],carre_y[i],50,50,carre_c[i],0,0);
        i++;
    }
    if(i<20 && rand()%150==0)
    {
        carre_x[i]=rand()%(TAILLE_X-50-1);
        carre_y[i]=rand()%(TAILLE_Y-50-1);
        carre_t[i]=1;
        carre_c[i]=255;
    }
    return 1;
}

int Gerer_clic(int *carre_x, int *carre_y, int *carre_t)
{
        int i=0;
    if(Situation.clicx!=-1)
    {
        while(carre_t[i]!=-1)
        {
            if(Situation.clicx >= carre_x[i] && Situation.clicx < carre_x[i]+50 && Situation.clicy >= carre_y[i] && Situation.clicy < carre_y[i]+50)
            {
                carre_t[i]=0;
                Situation.clicx=-1;
                Situation.clicy=-1;
                return 1;
            }
            i++;
        }
        Situation.clicx=-1;
        Situation.clicy=-1;
        return -1;
    }

    return 0;
}
