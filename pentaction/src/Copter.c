#include "maxcorp_SDL.h"
#include "Pentaction.h"

/* Idées :
- Modifier gestion des obstacle en ajoutant obstacle_t[] contenant son type ( enlver lvlup )
- Obstacle rouge = bonus de score (+1000*L ?)
- Obstacle jaune = Capacité de tirer un missile avec le clic droit ou shift( détruisant ainsi l'obstacle bleu en face )
*/

int L=1;

int Copter(SDL_Surface *ecran)
{
    SDL_ShowCursor(0);
    int score=0;
    int py=TAILLE_Y/2;
    int temps=SDL_GetTicks();
    int couloir_b[TAILLE_X/L], couloir_h[TAILLE_X/L];
    int obstacle_x[MAX_OBSTACLE]={-1}, obstacle_y[MAX_OBSTACLE]={-1}, obstacle_t[MAX_OBSTACLE]={-1};
    Definir_couloir(couloir_b, couloir_h);

    while(collide(py, obstacle_x, obstacle_y, obstacle_t, couloir_b, couloir_h) && !Situation.exit)
    {
        score+=L*L;
        Changer_situation();
        Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Genere_couloir(ecran, couloir_b, couloir_h);
        Genere_obstacle(ecran, couloir_b[TAILLE_X/L-1], couloir_h[TAILLE_X/L-1], obstacle_x, obstacle_y, obstacle_t);
        py = Move(ecran,py);
        Trainee_carre(ecran,py);

        Affichage_score2(ecran,score/10,TAILLE_X-67,TAILLE_Y-15);

        SDL_Flip(ecran);


        temps=SDL_GetTicks()-temps;
        if(temps<3) SDL_Delay(3- temps);
        temps=SDL_GetTicks();
    }
    SDL_ShowCursor(1);
    return score/10;
}


void Definir_couloir(int *couloir_b, int *couloir_h)
{
    int i=0;
    while (i<TAILLE_X/L)
    {
        couloir_h[i]=0;
        couloir_b[i]=TAILLE_Y-1;
        i++;
    }
}

void Genere_couloir(SDL_Surface *ecran, int *couloir_b, int *couloir_h)
{
    int i=1;
    while(i<TAILLE_X/L)
    {
        couloir_h[i-1]=couloir_h[i];
        couloir_b[i-1]=couloir_b[i];
        Blit(ecran,(i-1)*L,couloir_h[i-1],L,1,255,255,255);
        Blit(ecran,(i-1)*L,couloir_b[i-1],L,1,255,255,255);
        i++;
    }
    couloir_h[i-1]= couloir_h[i-1]+rand()%5-2 + (rand()%30)/29;
    couloir_b[i-1]= couloir_b[i-1]+rand()%5-2 - (rand()%30)/29;
    if(couloir_b[i-1]-couloir_h[i-1]< ECART_MIN)       // en cas de chemin trop mince
    {
        if(couloir_h[i-1]<=0)                           couloir_b[i-1]=couloir_h[i-1]+ECART_MIN;
        else if(couloir_b[i-1]>=TAILLE_Y-1 || rand()%2) couloir_h[i-1]=couloir_b[i-1]-ECART_MIN;
        else                                            couloir_b[i-1]=couloir_h[i-1]+ECART_MIN;
    }
    if(couloir_h[i-1]<0) couloir_h[i-1]=0;
    if(couloir_b[i-1]>TAILLE_Y-1) couloir_b[i-1]=TAILLE_Y-1;
    Blit(ecran,(i-1)*L,couloir_h[i-1],L,1,255,255,255);
    Blit(ecran,(i-1)*L,couloir_b[i-1],L,1,255,255,255);
}

void Genere_obstacle(SDL_Surface *ecran, int fin_couloir_b, int fin_couloir_h, int *obstacle_x, int *obstacle_y, int *obstacle_t)
{
    int i = 0;
    int k = 0;
    // Partie affichage
    while(i<MAX_OBSTACLE && obstacle_y[i]!=-1)
    {
        obstacle_x[i]-=L;
        if(obstacle_x[i]<-1)
        {
            k=i;
            while(k<MAX_OBSTACLE-1 && obstacle_y[k]!=-1)
            {
                obstacle_x[k]=obstacle_x[k+1];
                obstacle_y[k]=obstacle_y[k+1];
                obstacle_t[k]=obstacle_t[k+1];
                k++;
            }
            obstacle_x[k]=-1;
            obstacle_y[k]=-1;
            obstacle_t[k]=-1;
            i--;
        }
        if(obstacle_t[i]==2) Blit(ecran, obstacle_x[i], obstacle_y[i], 2, HAUTEUR_OBSTACLE, 0, 255, 0);
        else  Blit(ecran, obstacle_x[i], obstacle_y[i], 2, HAUTEUR_OBSTACLE, 0, 0, 255);
        i++;
    }
    //Partie nouveaux obstacles
    if(i<MAX_OBSTACLE && rand()%(100-5*L)==0 && fin_couloir_b-fin_couloir_h > ECART_MIN)
    {
        obstacle_x[i] = TAILLE_X;
        obstacle_y[i] = fin_couloir_h + 1 + (rand()%(fin_couloir_b - fin_couloir_h - HAUTEUR_OBSTACLE));
        obstacle_t[i] = 1;
        if(L==1 || rand()%(L*5)==0)
        {
            obstacle_t[i]=2;
            Blit(ecran, obstacle_x[i], obstacle_y[i], 2, HAUTEUR_OBSTACLE, 0, 255, 0);
        }
        else Blit(ecran, obstacle_x[i], obstacle_y[i], 2, HAUTEUR_OBSTACLE, 0, 0, 255);
    }
}

int Move(SDL_Surface *ecran, int py)
{
    static int vy=0;
    static int compteur=4;
    compteur++;
    if(compteur==5)
    {
        if(Situation.enfoncees>0 || Situation.clic_g==1) vy = vy - 2;
        else        vy = vy + 3;
        compteur=0;
        py = py + vy/2;
    }
    Blit(ecran, POSITION_X, py, TAILLE_CARRE,TAILLE_CARRE,255,0,0);
    return py;
}

void Trainee_carre(SDL_Surface *ecran, int py)
{
    static int trainee[POSITION_X/5+1]={-1};
    static int compteur=2;
    compteur++;
    int i = 0;
    while(i<POSITION_X/5/L)
    {
        if(compteur==5)trainee[i]=trainee[i+1];
        Blit(ecran, 5*i*L, trainee[i], 1, 1, 4*i*L+50, 0, 0);
        i++;
    }
    if(compteur==5)
    {
        trainee[i]=py+TAILLE_CARRE/2 -1;
        Blit(ecran, 5*i*L, trainee[i], 1, 1, 255, 0, 0);
        compteur=0;
    }
}

int collide(int py, int *obstacle_x, int *obstacle_y, int *obstacle_t, int *couloir_b, int *couloir_h)
{
    int g=0;
    int k=0;
    int i = POSITION_X/L;
    while(i<=(POSITION_X+TAILLE_CARRE)/L)
    {
        if(couloir_h[i]>=py || couloir_b[i]<py+TAILLE_CARRE) return 0;
        else
        {
            k=0;
            while(k<MAX_OBSTACLE || obstacle_x[k]==-1)
            {
                if(obstacle_x[k]>=POSITION_X && obstacle_x[k]<POSITION_X+TAILLE_CARRE && obstacle_y[k]>py-HAUTEUR_OBSTACLE && obstacle_y[k]<py+TAILLE_CARRE)
                {
                    if(obstacle_t[k]==2)
                     {
                         L++;
                         obstacle_t[k]=-1;
                         g=k;
                         while(g<MAX_OBSTACLE-1 && obstacle_y[g]!=-1)
                        {
                            obstacle_x[g]=obstacle_x[g+1];
                            obstacle_y[g]=obstacle_y[g+1];
                            obstacle_t[g]=obstacle_t[g+1];
                            g++;
                        }
                        obstacle_x[g]=-1;
                        obstacle_y[g]=-1;
                        obstacle_t[g]=-1;
                    }
                    else return 0;
                }
                k++;
            }
        }
        i++;
    }
    return 1;
}


