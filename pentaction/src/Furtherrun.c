#include "maxcorp_SDL.h"
#include "Pentaction.h"

/* Idées :
- Un carré qu'on doit faire aller le plus loin possible. ( En sautant sur des rampes ou ce genre de choses ... )
- Controle trois bonshommes en meme temps : ZE+IO+VN
- Trois couleurs, les bonshommes traversent ce qui n'est pas leur couleurs et meurt en cas de chute.
- Les trois en vie : +9, les 2 : +4, 1 : 1.
*/

int Further_Run(SDL_Surface *ecran)
{
    int score=0, nb_en_jeu=1, wait=0;
    int v[4]={0,0,0,0}; // vitesse verticale des bonshommes
    int py[4]={0,300,400,500}; // Conditions initiale à régler
    int sup1[960], sup2[960],sup3[960];

    int i=0;
    while(i<=960)
    {
        sup1[i]=300; sup2[i]=400; sup3[i]=500;
        i++;
    }




    while(!Situation.exit && Bouge_bonshommes(ecran, v, py, sup1, sup2, sup3))
    {
        SDL_Flip(ecran);
        Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
        Changer_situation();
        Saut_bonshommes(v);
        Gestion_support(ecran,sup1,sup2,sup3,nb_en_jeu);
        score++;
        if(nb_en_jeu==1 && score>=5000) nb_en_jeu=2;
        else if(nb_en_jeu==2 && score>=15000) nb_en_jeu=3;
        Affichage_score2(ecran,score,TAILLE_X-67,TAILLE_Y-15);
        wait = (2*nb_en_jeu-1)*20-(score*wait)/200 +10*(nb_en_jeu-1)*(nb_en_jeu-2);
        if(wait<1) wait=1;
        if(nb_en_jeu==1 && score>4824) wait=45-1250+score/4;
        if(nb_en_jeu==2 && score>14824) wait=45-3750+score/4;
        SDL_Delay(wait);///REGLER CORRECTEMENT ( COPTER AUSSI )
    }

    return score;
}




int Bouge_bonshommes(SDL_Surface *ecran, int *v, int *py, int *sup1, int *sup2, int *sup3)
{

    if(py[1]<=sup1[100] || sup1[100]==-1)
    {
        if(py[1]!=sup1[100] && v[1]==0) v[1]=-1;
        py[1] += v[1];
        if(py[1]>sup1[100] && sup1[100]!=-1)
        {
            v[1]=0;
            py[1]=sup1[100];
        }
    }
    else return 0;

    if(py[2]<=sup2[860] || sup2[860]==-1)
    {
        if(py[2]!=sup2[860] && v[2]==0) v[2]=-1;
        py[2] += v[2];
        if(py[2]>sup2[860] && sup2[860]!=-1)
        {
            v[2]=0;
            py[2]=sup2[860];
        }
    }
    else return 0;

    if(py[3]<=sup3[480] || sup3[480]==-1)
    {
        if(py[3]!=sup3[480] && v[3]==0) v[3]=-1;
        py[3] += v[3];
        if(py[3]>sup3[480] && sup3[480]!=-1)
        {
            v[3]=0;
            py[3]=sup3[480];
        }
    }
    else return 0;

    /// Faudra voir commment afficher les bonshommes (carré ou autre et position exacte)
    Blit(ecran,100-TAILLE_CARRE,py[1]-TAILLE_CARRE,TAILLE_CARRE,TAILLE_CARRE,255,0,0);
    Blit(ecran,860-TAILLE_CARRE,py[2]-TAILLE_CARRE,TAILLE_CARRE,TAILLE_CARRE,255,255,0);
    Blit(ecran,480-TAILLE_CARRE,py[3]-TAILLE_CARRE,TAILLE_CARRE,TAILLE_CARRE,0,0,255);


    return 1;
}

void Saut_bonshommes(int *v)
{
    // On prendra VBN comme touches de saut et mettant la possibilité d'un double saut
    if(Situation.v && v[1]==0) v[1]=-20;
    if(Situation.n && v[2]==0) v[2]=-20;
    if(Situation.b && v[3]==0) v[3]=-20;
    // On inclut le changement de vitesse progressif. En passant de -1 à 1 sans passer par 0.
    int i=1;
    while(i<4)
    {
        if(v[i]==-1) v[i]=1;
        else if(v[i]!=0) v[i]++;
        i++;
    }
}

void Gestion_support(SDL_Surface *ecran, int *sup1, int *sup2, int *sup3, int nb_en_jeu) /// METTRE VITESSE = 1 en cas de changement de support
{
//SUP1
    int i=0;
    int j=0;
    int k=0; // Vitesse d'avancée
    while(k<5)
    {
        i=0;
        while(i<959)
        {
            sup1[i]=sup1[i+1];
            i++;
        }
        if(sup1[958]!=sup1[858]) sup1[959]=sup1[958];
        else if(sup1[958]!=sup1[758] && sup1[958]!=-1) sup1[959]=sup1[958];
        else if(rand()%3 && sup1[958]!=-1) sup1[959]=sup1[958]-98+rand()%200;
        else if(sup1[958]!=-1) sup1[959]=-1;
        else sup1[959]=sup1[758]-100+rand()%200;
        if(sup1[959]<-1 || sup1[959]>=TAILLE_Y) sup1[959]=600;

        k++;
    }

    i=0;
    while(i<960)
    {
        j=i;
        while(i<960 && sup1[i]==sup1[j]) i++;
        if(sup1[j]!=-1 && i-j-1>0) Blit(ecran, j, sup1[j],i-j-1,3,255,0,0);
    }

//SUP2
    k=0;
    j=0;

    if(nb_en_jeu>1)
    {
        while(k<5)
        {
            i=959;
            while(i>0)
            {
                sup2[i]=sup2[i-1];
                i--;
            }
            if(sup2[1]!=sup2[101]) sup2[0]=sup2[1];
            else if(sup2[1]!=sup2[201] && sup2[1]!=-1) sup2[0]=sup2[1];
            else if(rand()%3 && sup2[1]!=-1) sup2[0]=sup2[1]-98+rand()%200;
            else if(sup2[1]!=-1) sup2[0]=-1;
            else sup2[0]=sup2[201]-100+rand()%200;
            if(sup2[0]<-1 || sup2[0]>=TAILLE_Y) sup2[0]=600;

            k++;
        }
        i=0;
        while(i<960)
        {
            j=i;
            while(i<960 && sup2[i]==sup2[j]) i++;
            if(sup2[j]!=-1 && i-j-1>0) Blit(ecran, j, sup2[j],i-j-1,3,255,255,0);
        }
    }
//SUP3
    if(nb_en_jeu>2)
    {

        k=0;
        j=0;

        while(k<5)
        {
            i=0;
            while(i<959)
            {
                sup3[i]=sup3[i+1];
                i++;
            }
            if(sup3[958]!=sup3[858]) sup3[959]=sup3[958];
            else if(sup3[958]!=sup3[758] && sup3[958]!=-1) sup3[959]=sup3[958];
            else if(rand()%3 && sup3[958]!=-1) sup3[959]=sup3[958]-98+rand()%200;
            else if(sup3[958]!=-1) sup3[959]=-1;
            else sup3[959]=sup3[758]-100+rand()%200;
            if(sup3[959]<-1 || sup3[959]>=TAILLE_Y) sup3[959]=600;

            k++;
        }

        i=0;
        while(i<960)
        {
            j=i;
            while(i<960 && sup3[i]==sup3[j]) i++;
            if(sup3[j]!=-1 && i-j-1>0) Blit(ecran, j, sup3[j],i-j-1,3,0,0,255);
        }
    }
}
