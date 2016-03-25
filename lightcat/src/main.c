#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "Graphique.h"
#include <time.h>
#include <fmod.h>

/*SDL_Rect move(int random,SDL_Rect dark, SDL_Surface *ecran, SDL_Surface *perso, SDL_Rect dark0)
{
    if(random==0) {  dark.y=dark.y-4; SDL_BlitSurface(perso, &dark0, ecran, &dark); }
    else if(random==1) {  dark.x=dark.x+4; SDL_BlitSurface(perso, &dark0, ecran, &dark); }
    else if(random==2) {  dark.y=dark.y+4; SDL_BlitSurface(perso, &dark0, ecran, &dark); }
    else if(random==3) {  dark.x=dark.x-4; SDL_BlitSurface(perso, &dark0, ecran, &dark); }
    return dark;
}
SDL_Rect lmove(int random,SDL_Rect dark)
{
    if(random==0)   dark.y=dark.y-4;
    else if(random==1)   dark.x=dark.x+4;
    else if(random==2)   dark.y=dark.y+4;
    else if(random==3)   dark.x=dark.x-4;
    return dark;
}
*/

int main(int argc, char *argv[])
{

    struct GraphMapEdit chipxy[2][2];
    struct Coord coord[2];
    int tempsPrec=0, tempsActuel=0, intervalle = 0;
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *perso = NULL, *ico = NULL, *Case[2][2];
    SDL_Rect positionFond, perso1[3], perso2[3], perso3[3], skinPartie, persox, skinDark[100], dark[100], dark1[3], dark2[3], dark3[3], casexy[2][2], casePartie[2][2];
 //   SDL_Rect skinGold,gold,gold0[3][3];

    SDL_Event event;
    int delai=50, i= 0,j=0, e= 1, e1=1, m = -1, k = 0, random[100],trand=0;

    positionFond.x=0; positionFond.y=0;
    persox.x=524; persox.y=568;

//for( y=0; y>=2 ; y++ ) for( x=0; x>=2 ; x++ )
 //   {   casexy[x][y].x = 16*x+4 ; casexy[x][y].y = 16*y+16 ; }    // Le milieu bas de la case et au milieu des pieds du perso (22.10.10)


perso1[0].x=72; perso1[0].y=0; perso1[0].w=24; perso1[0].h=32;
perso1[1].x=72; perso1[1].y=33; perso1[1].w=24; perso1[1].h=32;
perso1[2].x=72; perso1[2].y=66; perso1[2].w=24; perso1[2].h=32;
perso1[3].x=72; perso1[3].y=99; perso1[3].w=24; perso1[3].h=32;
perso2[0].x=96; perso2[0].y=0; perso2[0].w=24; perso2[0].h=32;
perso2[1].x=96; perso2[1].y=33; perso2[1].w=24; perso2[1].h=32;
perso2[2].x=96; perso2[2].y=66; perso2[2].w=24; perso2[2].h=32;
perso2[3].x=96; perso2[3].y=99; perso2[3].w=24; perso2[3].h=32;
perso3[0].x=120; perso3[0].y=0; perso3[0].w=24; perso3[0].h=32;
perso3[1].x=120; perso3[1].y=33; perso3[1].w=24; perso3[1].h=32;
perso3[2].x=120; perso3[2].y=66; perso3[2].w=24; perso3[2].h=32;
perso3[3].x=120; perso3[3].y=99; perso3[3].w=24; perso3[3].h=32;



dark1[0].x=0; dark1[0].y=0; dark1[0].w=24; dark1[0].h=32;
dark1[1].x=0; dark1[1].y=33; dark1[1].w=24; dark1[1].h=32;
dark1[2].x=0; dark1[2].y=66; dark1[2].w=24;dark1[2].h=32;
dark1[3].x=0; dark1[3].y=99; dark1[3].w=24; dark1[3].h=32;
dark2[0].x=24; dark2[0].y=0; dark2[0].w=24; dark2[0].h=32;
dark2[1].x=24; dark2[1].y=33; dark2[1].w=24; dark2[1].h=32;
dark2[2].x=24; dark2[2].y=66; dark2[2].w=24; dark2[2].h=32;
dark2[3].x=24; dark2[3].y=99; dark2[3].w=24; dark2[3].h=32;
dark3[0].x=48; dark3[0].y=0; dark3[0].w=24; dark3[0].h=32;
dark3[1].x=48; dark3[1].y=33; dark3[1].w=24; dark3[1].h=32;
dark3[2].x=48; dark3[2].y=66; dark3[2].w=24; dark3[2].h=32;
dark3[3].x=48; dark3[3].y=99; dark3[3].w=24; dark3[3].h=32;

/*for(i=1; i<=3; i++) for(j=0; j<=3; j++)
{
    gold0[i][j].x=120+24*i;
    gold0[i][j].y=33*j;
    gold0[i][j].w=24;
    gold0[i][j].h=32;
}*/

/// Son


    FMOD_SYSTEM *system;
	FMOD_SOUND *musique, *chat, *erase;
	FMOD_CHANNELINDEX musique0=FMOD_CHANNEL_FREE, chat0=FMOD_CHANNEL_FREE, erase0=FMOD_CHANNEL_FREE;

    int t=1;

	FMOD_System_Create(&system);
	FMOD_System_Init(system, 3, FMOD_INIT_NORMAL, NULL);

/* On ouvre la musique */
	FMOD_System_CreateSound(system, "hidden\\fond.mp3", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
    FMOD_System_CreateSound(system, "hidden\\chat.mp3",FMOD_CREATESAMPLE, 0, &chat);
    FMOD_System_CreateSound(system, "hidden\\erase.mp3",FMOD_CREATESAMPLE, 0, &erase);

/* On active la répétition de la musique à l'infini */
	FMOD_Sound_SetLoopCount(musique, -1);


/* On joue la musique */
	FMOD_System_PlaySound(system, musique0, musique, 0, NULL);




/// Partie






    SDL_Init(SDL_INIT_VIDEO);

    ico=SDL_LoadBMP("hidden\\ico.bmp");
    SDL_SetColorKey(ico, SDL_SRCCOLORKEY, SDL_MapRGB(ico->format, 255, 255, 255));
    SDL_WM_SetIcon(ico, NULL);

    ecran = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("MaxCorp te propose LightCat et ses ShadowCats", NULL);


    imageDeFond = IMG_Load("hidden\\fond.png");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    perso = IMG_Load("hidden\\cat.png");
    SDL_SetColorKey(perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso->format, 32, 156, 0));
    skinPartie = perso2[2];

    //Case[0][0] = IMG_Load("ICI.png");

    SDL_Flip(ecran);

    SDL_EnableKeyRepeat(1, delai); // Répétition en touche enfoncée.

    while(e)
    {
        for(i=0; i<=m; i++)
            if((persox.x>=dark[i].x-16 && persox.x<=dark[i].x+16 && persox.y<=dark[i].y+16 && persox.y>=dark[i].y-16) && (skinDark[i].x +72 != skinPartie.x || skinDark[i].y != skinPartie.y))
               {

                    skinDark[i]=skinDark[m];
                    dark[i].x=dark[m].x;
                    dark[i].y=dark[m].y;
                    m--;

               }

        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
            for(i=0; i<=m; i++)   SDL_BlitSurface(perso, &skinDark[i], ecran, &dark[i]);
        SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
        SDL_Flip(ecran);
        while(e1)
            {
                SDL_WaitEvent(&event);
                tempsActuel = SDL_GetTicks();
                intervalle = tempsActuel - tempsPrec;
                switch(event.key.keysym.sym) // Touches du clavier !
                    {
                        case SDLK_ESCAPE:
                            e = 0;
                            e1 = 0;
                            break;

                        case SDLK_q:

                            for(i=0; i<=m; i++ )
                            {
                                srand((trand+1)*(i+1)*997*time(NULL));
                                trand=rand() % 4;
                                random[i]=rand() % 4;
                            }

/*                                                  for(i=0; i<=m; i++ ) dark[i]=move(random[i],dark[i],ecran,perso,dark2[random[i]]);
                                                    for(i=0; i<=m; i++ ) dark[i]=move(random[i],dark[i],ecran,perso,dark3[random[i]]);
                                                    for(i=0; i<=m; i++ ) dark[i]=move(random[i],dark[i],ecran,perso,dark1[random[i]]);
                                                    for(i=0; i<=m; i++ ) { dark[i]=lmove(random[i],dark[i]); skinDark[i]=dark2[random[i]]; }
*/
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                            for(i=0; i<=m; i++ )
                            {
                                if(random[i]==0) if(dark[i].y>=8)   dark[i].y=dark[i].y-4;
                                if(random[i]==1) if(dark[i].x<=1000)   dark[i].x=dark[i].x+4;
                                if(random[i]==2) if(dark[i].y<=736)   dark[i].y=dark[i].y+4;
                                if(random[i]==3) if(dark[i].x>=4)   dark[i].x=dark[i].x-4;
                                SDL_BlitSurface(perso, &dark2[random[i]], ecran, &dark[i]);
                            }
                            SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                            SDL_Flip(ecran);
                            SDL_Delay(delai);
              //
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                            for(i=0; i<=m; i++ )
                            {
                                if(random[i]==0) if(dark[i].y>=8)   dark[i].y=dark[i].y-4;
                                if(random[i]==1) if(dark[i].x<=1000)   dark[i].x=dark[i].x+4;
                                if(random[i]==2) if(dark[i].y<=736)   dark[i].y=dark[i].y+4;
                                if(random[i]==3) if(dark[i].x>=4)   dark[i].x=dark[i].x-4;
                                SDL_BlitSurface(perso, &dark3[random[i]], ecran, &dark[i]);
                            }
                            SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                            SDL_Flip(ecran);
                            SDL_Delay(delai);
             //
                            SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                            for(i=0; i<=m; i++ )
                            {
                                if(random[i]==0) if(dark[i].y>=8)   dark[i].y=dark[i].y-4;
                                if(random[i]==1) if(dark[i].x<=1000)   dark[i].x=dark[i].x+4;
                                if(random[i]==2) if(dark[i].y<=736)   dark[i].y=dark[i].y+4;
                                if(random[i]==3) if(dark[i].x>=4)   dark[i].x=dark[i].x-4;
                                SDL_BlitSurface(perso, &dark1[random[i]], ecran, &dark[i]);
                            }
                            SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                            SDL_Flip(ecran);
                            SDL_Delay(delai);
             //
                            for(i=0; i<=m; i++ )
                            {
                                if(random[i]==0) if(dark[i].y>=8)   dark[i].y=dark[i].y-4;
                                if(random[i]==1) if(dark[i].x<=1000)   dark[i].x=dark[i].x+4;
                                if(random[i]==2) if(dark[i].y<=736)   dark[i].y=dark[i].y+4;
                                if(random[i]==3) if(dark[i].x>=4)   dark[i].x=dark[i].x-4;
                                skinDark[i]=dark2[random[i]];
                            }
                            e1=0;
                            break;











                        case SDLK_BACKSPACE:
                            if(t && m!= -1) FMOD_System_PlaySound(system, erase0, erase, 0, NULL);
                            m=-1;
                            e1 = 0;
                            break;










                        case SDLK_SPACE:

                            if(event.type == SDL_KEYUP )
                            if(intervalle>=1000)
                            {
                                if(m<=98)         { m++; k=0; }
                                if(m==99 && k==0)        k=100;
                                if(m==99)                k--;
                                dark[m-k].x=persox.x;  dark[m-k].y=persox.y;
                                skinDark[m-k]=skinPartie;
                                skinDark[m-k].x = skinPartie.x - 72;

                                if(t) FMOD_System_PlaySound(system, chat0, chat, 0, NULL);

                                e1 = 0;
                            }
                            break;










                        case SDLK_UP:
                            if(event.type == SDL_KEYDOWN)
                            if(intervalle >= 1000)
                            if(persox.y >= 8)
                                {
                                    persox.y = persox.y - 4;
                                    for(i=0;i<=m;i++) if(dark[i].y<=736) dark[i].y = dark[i].y + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark2[2], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso2[0], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y - 4;
                                    for(i=0;i<=m;i++) if(dark[i].y<=736) dark[i].y = dark[i].y + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++ )SDL_BlitSurface(perso, &dark3[2], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso3[0], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y - 4;
                                    for(i=0;i<=m;i++) if(dark[i].y<=736) dark[i].y = dark[i].y + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark1[2], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso1[0], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y - 4;
                                    for(i=0;i<=m;i++) if(dark[i].y<=736) dark[i].y = dark[i].y + 4;
                                    skinPartie = perso2[0];
                                    for(i=0;i<=m;i++) skinDark[i] = dark2[2];
                                    e1=0;
                                }
                            break;
                        case SDLK_RIGHT:
                            if(event.type == SDL_KEYDOWN)
                            if(intervalle >= 1000)
                            if(persox.x <= 1000)
                                {
                                    persox.x = persox.x + 4;
                                    for(i=0;i<=m;i++) if(dark[i].x>=4) dark[i].x = dark[i].x - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark2[3], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso2[1], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x + 4;
                                    for(i=0;i<=m;i++) if(dark[i].x>=4) dark[i].x = dark[i].x - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark3[3], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso3[1], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x + 4;
                                    for(i=0;i<=m;i++) if(dark[i].x>=4) dark[i].x = dark[i].x - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark1[3], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso1[1], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x + 4;
                                    for(i=0;i<=m;i++) if(dark[i].x>=4) dark[i].x = dark[i].x - 4;
                                    skinPartie = perso2[1];
                                    for(i=0;i<=m;i++) skinDark[i] = dark2[3];
                                    e1=0;
                                }
                            break;
                        case SDLK_DOWN:
                            if(event.type == SDL_KEYDOWN)
                            if(intervalle >= 1000)
                            if(persox.y <= 736)
                                {
                                    persox.y = persox.y + 4;
                                    for(i=0;i<=m;i++) if(dark[i].y>=8) dark[i].y = dark[i].y - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark2[0], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso2[2], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y + 4;
                                    for(i=0;i<=m;i++) if(dark[i].y>=8) dark[i].y = dark[i].y - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark3[0], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso3[2], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y + 4;
                                    for(i=0;i<=m;i++) if(dark[i].y>=8) dark[i].y = dark[i].y - 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark1[0], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso1[2], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.y = persox.y + 4;
                                    for(i=0;i<=m;i++) if(dark[i].y>=8) dark[i].y = dark[i].y - 4;
                                    skinPartie = perso2[2];
                                    for(i=0;i<=m;i++) skinDark[i] = dark2[0];
                                    e1=0;
                                }
                            break;
                        case SDLK_LEFT:
                            if(event.type == SDL_KEYDOWN)
                            if(intervalle >= 1000)
                            if(persox.x >= 4)
                                {
                                    persox.x = persox.x - 4;
                                    for(i=0;i<=m;i++) if(dark[i].x<=1000) dark[i].x = dark[i].x + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark2[1], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso2[3], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x - 4;
                                    for(i=0;i<=m;i++) if(dark[i].x<=1000) dark[i].x = dark[i].x + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark3[1], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso3[3], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x - 4;
                                    for(i=0;i<=m;i++) if(dark[i].x<=1000) dark[i].x = dark[i].x + 4;
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    for(i=0;i<=m;i++) SDL_BlitSurface(perso, &dark1[1], ecran, &dark[i]);
                                    SDL_BlitSurface(perso, &perso1[3], ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(delai);
                                    persox.x = persox.x - 4;
                                    for(i=0;i<=m;i++) if(dark[i].x<=1000) dark[i].x = dark[i].x + 4;
                                    skinPartie = perso2[3];
                                    for(i=0;i<=m;i++) skinDark[i] = dark2[1];
                                    e1=0;
                                }
                            break;




                            case SDLK_p:
                            if(event.type == SDL_KEYUP)
                            {
                                FMOD_CHANNELGROUP *canal;
                                FMOD_BOOL etat;
                                FMOD_System_GetMasterChannelGroup(system, &canal);
                                FMOD_ChannelGroup_GetPaused(canal, &etat);

                                if (etat)
                                  {  FMOD_ChannelGroup_SetPaused(canal, 0); t=1; }
                                else
                                  {  FMOD_ChannelGroup_SetPaused(canal, 1); t=0; }
                            }
                            break;


                    }
                switch(event.type) // Souris !
                    {
                        case SDL_QUIT:
                            e = 0;
                            e1 = 0;
                            break;
                    }
            }
        tempsActuel = tempsPrec;
        e1 = 1;

    }
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(imageDeFond);
    SDL_FreeSurface(perso);


    FMOD_Sound_Release(musique);
    FMOD_Sound_Release(chat);
    FMOD_Sound_Release(erase);
	FMOD_System_Close(system);
	FMOD_System_Release(system);


return 0;
}
