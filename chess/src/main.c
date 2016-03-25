#include "C:\Users\MaxCorp\Downloads\Chess\fonctions.h"



int main ( int argc, char** argv )
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran=SDL_SetVideoMode(8*TAILLE,8*TAILLE, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);    // SDL_RESIZABLE à prévoir
    SDL_WM_SetCaption("Chess by MaxCorp", NULL);

    TTF_Init();

    while(jouer(ecran, menu(ecran)));            // Retour 1 si retour au menu. Retour 0 si fin du jeu.


    TTF_Quit();
    SDL_FreeSurface(ecran);
    SDL_VideoQuit();
    return 0;
}






jeu menu(SDL_Surface *ecran)      // Ecran menu
{
    SDL_Surface *menu_img=SDL_LoadBMP("main.bmp");
    SDL_Rect origine;   origine.x=0;  origine.y=0;
    SDL_BlitSurface(menu_img, NULL, ecran, &origine);
    SDL_Flip(ecran);

    int t=15;
    char titre[100]="partie_000.sav";
    while(t<100)
    {
        titre[t]='\0';
        t++;
    }
    t=0;


    jeu plan=Definir_Jeu();

    SDL_Event event;


    while(fopen(titre,"r")!=NULL)
    {
        t++;
        sprintf(titre, "partie_%d%d%d.sav", t/100, (t/10)%10, t%10);
    }
    strcpy(plan.nom, titre);


    while(plan.menu==-1)
    {
        SDL_WaitEvent(&event);

        if(event.type==SDL_KEYUP)
        {
            if(event.key.keysym.sym==SDLK_KP1 || event.key.keysym.sym==SDLK_1) plan.menu=1;
            else if(event.key.keysym.sym==SDLK_KP2 || event.key.keysym.sym==SDLK_2) plan.menu=2;
            else if(event.key.keysym.sym==SDLK_KP3 || event.key.keysym.sym==SDLK_3)
            {
                strcpy(plan.nom, Ecrire(ecran,Definir_ecrire()));;

                SDL_BlitSurface(menu_img, NULL, ecran, &origine);
                SDL_Flip(ecran);

                if(!strcmp(plan.nom,"QUIT0000"))
                {
                    plan.menu=0;
                }
                else if(!strcmp(plan.nom,"ECHAP000"))
                {
                    strcpy(plan.nom, titre);
                    plan.menu=-1;
                }
                else if(fopen(plan.nom,"r")==NULL)
                {
                    strcpy(plan.nom, titre);
                    plan.menu=-1;
                }
                else plan.menu=3;
            }
            else if(event.key.keysym.sym==SDLK_F4) plan.menu=0;
        }
        else if(event.type==SDL_QUIT) plan.menu=0;
        /// MANQUE une image ainsi que le possibilité de choisir au clic
    }

    SDL_FreeSurface(menu_img);

    return plan;
}


char jouer(SDL_Surface *ecran, jeu plan)    // Hors du menu, l'échiquier étant affiché.
{
    if(plan.menu==0) return 0;

    char echec_mat=0;

    Blit_Jeu(ecran, plan);
    SDL_Flip(ecran);

    if(plan.menu==1)
    {
        while(plan.exit && !echec_mat)
        {
            plan=Deplacement(ecran,plan);
            Save(plan);
            plan.tour++;
            echec_mat=Echec_mat(plan);
        }
    }
    else if(plan.menu==2)
    {
        while(plan.exit && !echec_mat)
        {
            plan=Deplacement(ecran,plan);
            Save(plan);
            plan.tour++;
            echec_mat=Echec_mat(plan);
            if(!echec_mat && plan.exit)
            {
                plan=IA(plan);
                Save(plan);
                Blit_Jeu(ecran, plan);
                SDL_Flip(ecran);
                plan.tour++;
                echec_mat=Echec_mat(plan);
            }
        }
    }
    else if(plan.menu==3)
    {
        SDL_Event event0;
        while(plan.exit && !echec_mat)
        {
            SDL_WaitEvent(&event0);
            while(event0.key.keysym.sym!=SDLK_RETURN || event0.type!=SDL_KEYUP)
            {
                SDL_WaitEvent(&event0);
                if(event0.type==SDL_QUIT || (event0.type==SDL_KEYUP && event0.key.keysym.sym==SDLK_F4)) return 0;
            }
            plan=Load(plan);
            Blit_Jeu(ecran, plan);
            SDL_Flip(ecran);
            plan.tour++;
            echec_mat=Echec_mat(plan);
        }
    }

    if(echec_mat) // Si on est dans le cas d'un echec et mat : fin de partie
    {
        SDL_Event event;
        SDL_Rect origine;    origine.x=0;   origine.y=0;
        SDL_Surface *fog=SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE*8, TAILLE*8, 32, 0, 0, 0, 0);
        SDL_FillRect(fog, NULL, SDL_MapRGB(ecran->format, 230, 90, 70));
        SDL_SetAlpha(fog, SDL_SRCALPHA, 90);   // transparence de l'ecran masque   ( 0 - 255 )
        SDL_BlitSurface(fog,NULL,ecran,&origine);
        SDL_Flip(ecran);

        SDL_WaitEvent(&event);
        while(event.type!=SDL_KEYUP)
        {
            SDL_WaitEvent(&event);
        }
    }

    return plan.shut;
}



jeu IA(jeu plan)               // INTELLIGENCE ARTIFICIELLE
{
    jeu faux_plan=plan;
    // Jeu Noir

    faux_plan.lieu[4][3]=PION_N;
    if(plan.tour==1 && !Verification_echec(faux_plan,4,3))     // Au premier tour : e5
    {
        plan.lieu[4][1]=VIDE;
        plan.lieu[4][3]=PION_N;
        plan.avant_x=4;
        plan.avant_y=1;
        plan.apres_x=4;
        plan.apres_y=3;
        return plan;
    }


/* TECHNIQUE RECURSIVE*/

return Meilleur_coup(plan, 1);



/* TECHNIQUE A L'ANCIENNE






    jeu faux_plan1, faux_plan2;
    char i=0, j=0, a=0, b=0, i1=0, j1=0, a1=0, b1=0;
    int MAX1=-100000, max_i1=0, max_j1=0, max_a1=0, max_b1=0, MAX2=-100000, max_i2=0, max_j2=0, max_a2=0, max_b2=0, c=-100000;

    // max2 retient le nombre total de coup possible au dernier tour.
    // maxi2 et maxj2 désigneront le "plus grand actuel"

    while(i<8)
    {
        while(j<8)
        {
            if(plan.lieu[i][j]>NOIR)
            {
                while(a<8)
                {
                    while(b<8)
                    {
                        if(Verification_mouvement(plan,i,j,a,b))
                        {
                            // On effectue un premier coup.
                            faux_plan=plan;
                            faux_plan.lieu[a][b]=faux_plan.lieu[i][j];
                            faux_plan.lieu[i][j]=VIDE;
                            c=Valeur_Attaque(faux_plan,NOIR);
                            if(c==10000)
                            {
                                plan.lieu[a][b]=plan.lieu[i][j];
                                plan.lieu[i][j]=VIDE;
                                plan.avant_x=i;
                                plan.avant_y=j;
                                plan.apres_x=a;
                                plan.apres_y=b;
                                return plan;

                            }

                            // On effectue le meilleur coup adverse.
                            i1=0;
                            j1=0;
                            while(i1<8)
                            {
                                while(j1<8)
                                {
                                    if(faux_plan.lieu[i1][j1]<BLANC && faux_plan.lieu[i1][j1]!=VIDE)
                                    {
                                        while(a1<8)
                                        {
                                            while(b1<8)
                                            {
                                                if(Verification_mouvement(faux_plan,i1,j1,a1,b1))
                                                {
                                                    faux_plan1=faux_plan;
                                                    faux_plan1.lieu[a1][b1]=faux_plan1.lieu[i1][j1];
                                                    faux_plan1.lieu[i1][j1]=VIDE;
                                                    c=Valeur_Attaque(faux_plan1,BLANC);
                                                    if(c>MAX1)
                                                    {
                                                        MAX1=c;
                                                        max_i1=i1;
                                                        max_j1=j1;
                                                        max_a1=a1;
                                                        max_b1=b1;
                                                    }
                                                }
                                                b1++;
                                            }
                                            a1++;
                                            b1=0;
                                        }
                                        a1=0;
                                    }
                                    j1++;
                                }
                                i1++;
                                j1=0;
                            }
                            // Le meilleur coup de l'adverse étant dans max_X1, on va retester tous les coups noirs
                            faux_plan1=faux_plan;
                            faux_plan1.lieu[max_a1][max_b1]=faux_plan1.lieu[max_i1][max_j1];
                            faux_plan1.lieu[max_i1][max_j1]=VIDE;

                            MAX1=-1000;

                            i1=0;
                            j1=0;
                            while(i1<8)
                            {
                                while(j1<8)
                                {
                                    if(faux_plan1.lieu[i1][j1]>NOIR)
                                    {
                                        while(a1<8)
                                        {
                                            while(b1<8)
                                            {
                                                if(Verification_mouvement(faux_plan1,i1,j1,a1,b1))
                                                {
                                                    faux_plan2=faux_plan1;
                                                    faux_plan2.lieu[a1][b1]=faux_plan2.lieu[i1][j1];
                                                    faux_plan2.lieu[i1][j1]=VIDE;
                                                    c=Valeur_Attaque(faux_plan2,NOIR);
                                                    if(c>MAX2)
                                                    {
                                                        MAX2=c;
                                                        max_i2=i;
                                                        max_j2=j;
                                                        max_a2=a;
                                                        max_b2=b;
                                                    }
                                                }
                                                b1++;
                                            }
                                            a1++;
                                            b1=0;
                                        }
                                        a1=0;
                                    }
                                    j1++;
                                }
                                i1++;
                                j1=0;
                            }

                        }
                        b++;
                    }
                    a++;
                    b=0;
                }
                a=0;
            }
            j++;
        }
        i++;
        j=0;
    }
    plan.lieu[max_a2][max_b2]=plan.lieu[max_i2][max_j2];
    plan.lieu[max_i2][max_j2]=VIDE;
    plan.avant_x=max_i2;
    plan.avant_y=max_j2;
    plan.apres_x=max_a2;
    plan.apres_y=max_b2;


    return plan;*/
}


