#include "maxcorp_SDL.h"



_ecrire Definir_ecrire()
{

    _ecrire retour;
    SDL_Color blanc = {255,255,255};
    SDL_Color noir = {0,0,0};

    retour.fond = noir;
    retour.couleur = blanc;
    retour.police = TTF_OpenFont("ARCENA.ttf",65);
    retour.pos.x = 40;
    retour.pos.y = 530;
    retour.pos.w = 800;
    retour.pos.h = 80;

    int i=0;
    while(i<100)
    {
        retour.txt[i]='\0';
        i++;
    }

    return retour;
}


char* Ecrire(SDL_Surface *ecran, _ecrire recu)   // Renvoi ce qui a été tapé
{
    SDL_Surface *print, *cache=SDL_CreateRGBSurface(SDL_HWSURFACE, recu.pos.w, recu.pos.h, 32, 0, 0, 0, 0);
    SDL_FillRect(cache, NULL, SDL_MapRGB(ecran->format, recu.fond.r, recu.fond.g, recu.fond.b));
    SDL_Event event;
    int i=0, j=99;
    int maj=0;
    while(recu.txt[i]!='\0') i++;

    while(1)
    {
        SDL_WaitEvent(&event);

        if(event.type==SDL_QUIT)
        {
            return "QUIT0000";
        }
        else if(event.key.keysym.sym==SDLK_LSHIFT)
        {
            if(maj) maj=0;
            else maj=1;
        }
        else if(event.type==SDL_KEYUP)
        {
            if(!maj)
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: return "ECHAP000"; break;      // Quitte le mode ecriture
                case SDLK_F4:     return "QUIT0000"; break;     // Exit total
                case SDLK_RETURN: return recu.txt;   break;
                case SDLK_KP_ENTER: return recu.txt; break;
                case SDLK_BACKSPACE: if(i>0)i--; recu.txt[i]='\0'; break;
                case SDLK_q: recu.txt[i]='a'; i++; break;
                case SDLK_b: recu.txt[i]='b'; i++; break;
                case SDLK_c: recu.txt[i]='c'; i++; break;
                case SDLK_d: recu.txt[i]='d'; i++; break;
                case SDLK_e: recu.txt[i]='e'; i++; break;
                case SDLK_f: recu.txt[i]='f'; i++; break;
                case SDLK_g: recu.txt[i]='g'; i++; break;
                case SDLK_h: recu.txt[i]='h'; i++; break;
                case SDLK_i: recu.txt[i]='i'; i++; break;
                case SDLK_j: recu.txt[i]='j'; i++; break;
                case SDLK_k: recu.txt[i]='k'; i++; break;
                case SDLK_l: recu.txt[i]='l'; i++; break;
                case SDLK_SEMICOLON: recu.txt[i]='m'; i++; break;
                case SDLK_n: recu.txt[i]='n'; i++; break;
                case SDLK_o: recu.txt[i]='o'; i++; break;
                case SDLK_p: recu.txt[i]='p'; i++; break;
                case SDLK_a: recu.txt[i]='q'; i++; break;
                case SDLK_r: recu.txt[i]='r'; i++; break;
                case SDLK_s: recu.txt[i]='s'; i++; break;
                case SDLK_t: recu.txt[i]='t'; i++; break;
                case SDLK_u: recu.txt[i]='u'; i++; break;
                case SDLK_v: recu.txt[i]='v'; i++; break;
                case SDLK_z: recu.txt[i]='w'; i++; break;
                case SDLK_x: recu.txt[i]='x'; i++; break;
                case SDLK_y: recu.txt[i]='y'; i++; break;
                case SDLK_w: recu.txt[i]='z'; i++; break;
                case SDLK_0: recu.txt[i]='à'; i++; break;
                case SDLK_1: recu.txt[i]='&'; i++; break;
                case SDLK_2: recu.txt[i]='é'; i++; break;
                case SDLK_3: recu.txt[i]='\"'; i++; break;
                case SDLK_4: recu.txt[i]='\''; i++; break;
                case SDLK_5: recu.txt[i]='('; i++; break;
                case SDLK_6: recu.txt[i]='-'; i++; break;
                case SDLK_7: recu.txt[i]='è'; i++; break;
                case SDLK_8: recu.txt[i]='_'; i++; break;
                case SDLK_9: recu.txt[i]='ç'; i++; break;
                case SDLK_KP0: recu.txt[i]='0'; i++; break;
                case SDLK_KP1: recu.txt[i]='1'; i++; break;
                case SDLK_KP2: recu.txt[i]='2'; i++; break;
                case SDLK_KP3: recu.txt[i]='3'; i++; break;
                case SDLK_KP4: recu.txt[i]='4'; i++; break;
                case SDLK_KP5: recu.txt[i]='5'; i++; break;
                case SDLK_KP6: recu.txt[i]='6'; i++; break;
                case SDLK_KP7: recu.txt[i]='7'; i++; break;
                case SDLK_KP8: recu.txt[i]='8'; i++; break;
                case SDLK_KP9: recu.txt[i]='9'; i++; break;
                case SDLK_MINUS: recu.txt[i]='-'; i++; break;
                case SDLK_UNDERSCORE: recu.txt[i]='_'; i++; break;
                case SDLK_KP_MINUS: recu.txt[i]='-'; i++; break;
                case SDLK_KP_PERIOD: recu.txt[i]='.'; i++; break;
                case SDLK_COMMA: recu.txt[i]=';'; i++; break;;
                case SDLK_SLASH: recu.txt[i]='!'; i++; break;
                case SDLK_SPACE: recu.txt[i]=' '; i++; break;
                case SDLK_m: recu.txt[i]=','; i++; break;

            }
            else
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE: return "ECHAP000"; break;      // Quitte le mode ecriture
                case SDLK_F4:     return "QUIT0000"; break;     // Exit total
                case SDLK_RETURN: return recu.txt;   break;
                case SDLK_KP_ENTER: return recu.txt; break;
                case SDLK_BACKSPACE: if(i>0)i--; recu.txt[i]='\0'; break;
                case SDLK_q: recu.txt[i]='A'; i++; break;
                case SDLK_b: recu.txt[i]='B'; i++; break;
                case SDLK_c: recu.txt[i]='C'; i++; break;
                case SDLK_d: recu.txt[i]='D'; i++; break;
                case SDLK_e: recu.txt[i]='E'; i++; break;
                case SDLK_f: recu.txt[i]='F'; i++; break;
                case SDLK_g: recu.txt[i]='G'; i++; break;
                case SDLK_h: recu.txt[i]='H'; i++; break;
                case SDLK_i: recu.txt[i]='I'; i++; break;
                case SDLK_j: recu.txt[i]='J'; i++; break;
                case SDLK_k: recu.txt[i]='K'; i++; break;
                case SDLK_l: recu.txt[i]='L'; i++; break;
                case SDLK_SEMICOLON: recu.txt[i]='M'; i++; break;
                case SDLK_n: recu.txt[i]='N'; i++; break;
                case SDLK_o: recu.txt[i]='O'; i++; break;
                case SDLK_p: recu.txt[i]='P'; i++; break;
                case SDLK_a: recu.txt[i]='Q'; i++; break;
                case SDLK_r: recu.txt[i]='R'; i++; break;
                case SDLK_s: recu.txt[i]='S'; i++; break;
                case SDLK_t: recu.txt[i]='T'; i++; break;
                case SDLK_u: recu.txt[i]='U'; i++; break;
                case SDLK_v: recu.txt[i]='V'; i++; break;
                case SDLK_z: recu.txt[i]='W'; i++; break;
                case SDLK_x: recu.txt[i]='X'; i++; break;
                case SDLK_y: recu.txt[i]='Y'; i++; break;
                case SDLK_w: recu.txt[i]='Z'; i++; break;
                case SDLK_0: recu.txt[i]='0'; i++; break;
                case SDLK_1: recu.txt[i]='1'; i++; break;
                case SDLK_2: recu.txt[i]='2'; i++; break;
                case SDLK_3: recu.txt[i]='3'; i++; break;
                case SDLK_4: recu.txt[i]='4'; i++; break;
                case SDLK_5: recu.txt[i]='5'; i++; break;
                case SDLK_6: recu.txt[i]='6'; i++; break;
                case SDLK_7: recu.txt[i]='7'; i++; break;
                case SDLK_8: recu.txt[i]='8'; i++; break;
                case SDLK_9: recu.txt[i]='9'; i++; break;
                case SDLK_KP0: recu.txt[i]='0'; i++; break;
                case SDLK_KP1: recu.txt[i]='1'; i++; break;
                case SDLK_KP2: recu.txt[i]='2'; i++; break;
                case SDLK_KP3: recu.txt[i]='3'; i++; break;
                case SDLK_KP4: recu.txt[i]='4'; i++; break;
                case SDLK_KP5: recu.txt[i]='5'; i++; break;
                case SDLK_KP6: recu.txt[i]='6'; i++; break;
                case SDLK_KP7: recu.txt[i]='7'; i++; break;
                case SDLK_KP8: recu.txt[i]='8'; i++; break;
                case SDLK_KP9: recu.txt[i]='9'; i++; break;
                case SDLK_MINUS: recu.txt[i]='-'; i++; break;
                case SDLK_UNDERSCORE: recu.txt[i]='_'; i++; break;
                case SDLK_KP_MINUS: recu.txt[i]='-'; i++; break;
                case SDLK_KP_PERIOD: recu.txt[i]='.'; i++; break;
                case SDLK_COMMA: recu.txt[i]='.'; i++; break;;
                case SDLK_SLASH: recu.txt[i]='§'; i++; break;
                case SDLK_SPACE: recu.txt[i]=' '; i++; break;
                case SDLK_m: recu.txt[i]='?'; i++; break;

            }

            print=TTF_RenderText_Shaded(recu.police, recu.txt, recu.couleur, recu.fond);
            SDL_BlitSurface(cache,NULL,ecran,&recu.pos);
            SDL_BlitSurface(print,NULL,ecran,&recu.pos);
            SDL_Flip(ecran);
            SDL_FreeSurface(print);
        }

    }
}
