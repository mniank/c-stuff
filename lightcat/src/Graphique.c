#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
/*
struct Coord
{
    long x;
    long y;
};
*/
    char e = 1, e1 = 1;
    int tempsPrec=0, tempsActuel=0, intervalle = 0;
    SDL_Surface *ecran = NULL, *imageDeFond = NULL, *perso = NULL;
    SDL_Rect positionFond, perso1[3], perso2[3], perso3[3], persox, skinPartie;
    SDL_Event event;

void IntialGraphique(void)
{
    positionFond.x=0;
    positionFond.y=0;
    persox.x=160;
    persox.y=100;


    perso1[0].x=72;
    perso1[0].y=0;
    perso1[0].w=24;
    perso1[0].h=32;

    perso1[1].x=72;
    perso1[1].y=33;
    perso1[1].w=24;
    perso1[1].h=32;

    perso1[2].x=72;
    perso1[2].y=66;
    perso1[2].w=24;
    perso1[2].h=32;

    perso1[3].x=72;
    perso1[3].y=99;
    perso1[3].w=24;
    perso1[3].h=32;

    perso2[0].x=96;
    perso2[0].y=0;
    perso2[0].w=24;
    perso2[0].h=32;

    perso2[1].x=96;
    perso2[1].y=33;
    perso2[1].w=24;
    perso2[1].h=32;

    perso2[2].x=96;
    perso2[2].y=66;
    perso2[2].w=24;
    perso2[2].h=32;

    perso2[3].x=96;
    perso2[3].y=99;
    perso2[3].w=24;
    perso2[3].h=32;

    perso3[0].x=120;
    perso3[0].y=0;
    perso3[0].w=24;
    perso3[0].h=32;

    perso3[1].x=120;
    perso3[1].y=33;
    perso3[1].w=24;
    perso3[1].h=32;

    perso3[2].x=120;
    perso3[2].y=66;
    perso3[2].w=24;
    perso3[2].h=32;

    perso3[3].x=120;
    perso3[3].y=99;
    perso3[3].w=24;
    perso3[3].h=32;
}/*

    SDL_Init(SDL_INIT_VIDEO);

    ecran = SDL_SetVideoMode(320, 200, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Test de perso", NULL);


    imageDeFond = IMG_Load("Titre.png");
    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);

    perso = IMG_Load("cat.png");
    SDL_SetColorKey(perso, SDL_SRCCOLORKEY, SDL_MapRGB(perso->format, 32, 156, 0));
    skinPartie = perso2[2];

    SDL_Flip(ecran);

    SDL_EnableKeyRepeat(1, 300); // Répétition en touche enfoncée.

    while(e)
    {
        SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
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
                        case SDLK_UP:
                            if(intervalle >= 1000)
                            if(persox.y >= 4)
                                {
                                    persox.y = persox.y - 4;
                                    skinPartie = perso2[0];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y - 4;
                                    skinPartie = perso3[0];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y - 4;
                                    skinPartie = perso1[0];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y - 4;
                                    skinPartie = perso2[0];
                                    e1=0;
                                }
                            break;
                        case SDLK_RIGHT:
                            if(intervalle >= 1000)
                            if(persox.x < 280)
                                {
                                    persox.x = persox.x + 4;
                                    skinPartie = perso2[1];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x + 4;
                                    skinPartie = perso3[1];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x + 4;
                                    skinPartie = perso1[1];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x + 4;
                                    skinPartie = perso2[1];
                                    e1=0;
                                }
                            break;
                        case SDLK_DOWN:
                            if(intervalle >= 1000)
                            if(persox.y < 160)
                                {
                                    persox.y = persox.y + 4;
                                    skinPartie = perso2[2];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y + 4;
                                    skinPartie = perso3[2];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y + 4;
                                    skinPartie = perso1[2];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.y = persox.y + 4;
                                    skinPartie = perso2[2];
                                    e1=0;
                                }
                            break;
                        case SDLK_LEFT:
                            if(intervalle >= 1000)
                            if(persox.x >= 4)
                                {
                                    persox.x = persox.x - 4;
                                    skinPartie = perso2[3];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x - 4;
                                    skinPartie = perso3[3];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x - 4;
                                    skinPartie = perso1[3];
                                    SDL_BlitSurface(imageDeFond, NULL, ecran, &positionFond);
                                    SDL_BlitSurface(perso, &skinPartie, ecran, &persox);
                                    SDL_Flip(ecran);
                                    SDL_Delay(150);
                                    persox.x = persox.x - 4;
                                    skinPartie = perso2[3];
                                    e1=0;
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
return 0;
}*/
