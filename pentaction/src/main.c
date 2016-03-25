#include "maxcorp_SDL.h"
#include "Pentaction.h"
#include <fmod.h>

/*-------------------------------------------------
                    Pentaction

                 Maxime Niankouri

                       2011
-------------------------------------------------*/



int main ( int argc, char** argv )
{

    srand(time(NULL));
    int score=0, score1=0, score2=0, score3=0, score4=0, score5=0;
    int t=0,t1,t2,t3,t4,t5;
    Situation=Definir_situation();
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Surface *ecran=SDL_SetVideoMode(TAILLE_X,TAILLE_Y, 32,SDL_HWSURFACE | SDL_DOUBLEBUF);    // SDL_RESIZABLE à prévoir
    SDL_WM_SetCaption("Pentaction by MaxCorp v0.0.7b", NULL);

    FMOD_SYSTEM *system;
   	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

    TTF_Init();

    t=SDL_GetTicks();

    Gestion_musique(system, "Arcade2.mp3");
    if(!Situation.exit) score1 = Affichage_score(ecran,Copter(ecran),0);
    t1=SDL_GetTicks()-t;
    t=SDL_GetTicks();

    //Gestion_musique(system, "Arcade3.mp3");
    //if(!Situation.exit) score2 = Affichage_score(ecran,Fastclic(ecran),0);
    t2=SDL_GetTicks()-t;
    t=SDL_GetTicks();

    //Gestion_musique(system, "Arcade3.mp3");
    //if(!Situation.exit) score3 = Affichage_score(ecran,Longer_Higher(ecran),0);
    t3=SDL_GetTicks()-t;
    t=SDL_GetTicks();

    Gestion_musique(system, "Arcade5.mp3");
    if(!Situation.exit) score4 = Affichage_score(ecran,Further_Run(ecran),0);
    t4=SDL_GetTicks()-t;
    t=SDL_GetTicks();

    Gestion_musique(system, "Arcade3.mp3");
    if(!Situation.exit) score5 = Affichage_score(ecran,Dodgeall(ecran),0);
    t5=SDL_GetTicks()-t;

    score=score1+score2+score3+score4+score5;
    if(!Situation.exit) Affichage_score(ecran,score,1);


    TTF_Quit();



    FMOD_System_Close(system);
    SDL_FreeSurface(ecran);
    SDL_VideoQuit();

    Envoie_donnee(score,score1,score2,score3,score4,score5,t1,t2,t3,t4,t5);

    return score;
}

int Affichage_score(SDL_Surface *ecran, int score, int TYPE)
{
    if(Situation.exit) return score;

    char string[] = "Score : ..........................";
    if(TYPE==0) sprintf(string, "Score : %d", score);
    else sprintf(string, "Score total : %d\n", score);
    Blit(ecran,0,0,TAILLE_X,TAILLE_Y,0,0,0);
    SDL_Rect pos; pos.x=100; pos.y=280;
    TTF_Font *police=TTF_OpenFont("ARCENA.ttf",85);
    SDL_Color color={255,255,255}, color2={0,0,0};
    SDL_BlitSurface(TTF_RenderText_Shaded(police, string, color, color2),NULL,ecran,&pos);
    SDL_Flip(ecran);
    TTF_CloseFont(police);

    SDL_Delay(2000);

    return score;
}

void Affichage_score2(SDL_Surface *ecran, int score, int x, int y)
{
    int s[8] = {0};
    s[0]=score/10000000;
    s[1]=(score/1000000)%10;
    s[2]=(score/100000)%10;
    s[3]=(score/10000)%10;
    s[4]=(score/1000)%10;
    s[5]=(score/100)%10;
    s[6]=(score/10)%10;
    s[7]=score%10;

    char string[]="00000000";
    sprintf(string,"%d%d%d%d%d%d%d%d",s[0],s[1],s[2],s[3],s[4],s[5],s[6],s[7]);
    SDL_Rect pos; pos.x = x; pos.y = y;
    TTF_Font *police=TTF_OpenFont("ARCENA.ttf",15);
    SDL_Color color={255,255,255}, color2={0,0,0};
    SDL_BlitSurface(TTF_RenderText_Shaded(police, string, color, color2),NULL,ecran,&pos);
    TTF_CloseFont(police);
}

void Gestion_musique(FMOD_SYSTEM *system, char *nom)
{
	static FMOD_SOUND *musique;
	FMOD_System_CreateSound(system, nom, FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
	FMOD_Sound_SetLoopCount(musique, -1);
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
}
