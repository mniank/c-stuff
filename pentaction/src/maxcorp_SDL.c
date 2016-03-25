#include "maxcorp_SDL.h"


situation Situation;

void Blit(SDL_Surface *ecran, int x, int y, int w, int h, int R, int V, int B)
{
    SDL_Rect pos;
    pos.x=x;
    pos.y=y;
    SDL_Surface *surface=SDL_CreateRGBSurface(SDL_HWSURFACE, w, h, 32, 0, 0, 0, 0);
    SDL_FillRect(surface, NULL, SDL_MapRGB(ecran->format, R, V, B));
    SDL_BlitSurface(surface,NULL,ecran,&pos);
    SDL_FreeSurface(surface);
}

/*void BlitLine_aux(int *tab, int x, int k, int n)
{
    if(2*k>x-2*n)
    {
        k -= 2;
        tab[n]++;
        tab[x-1-n]++;
        n++;
    }
    else if(2*k<x-2*n)
    {
        n++;
    }
    else if(2*k==x-2*n)
    {
        int i=n;
        while(i<x-1-n)
        {
            tab[i]++;
            i += 2;
            k--;
        }
        k=0; // si pas deja le cas, y a une couille
    }
    if(k!=0 && n<x/2) BlitLine_aux(tab,x,k,n);
}

void BlitLine(SDL_Surface *ecran, int x1, int y1, int x2, int y2, int R, int V, int B) // Ligne du point (x1,y1) au point (x2,y2)
{

    int x = x1-x2, y=y1-y2;
    if(x<0) x=-x;
    if(y<0) y=-y;
    x++;
    y++;
    if(x<=y)
    {
        int tab[641]={y/x}; // Normalement , mettre x à la place de 960, mais ce con ne vuet pas
        int i=0;
        while(i<x)
        {
            tab[i]=y/x;
            i++;
        }
        int k=0;
        BlitLine_aux(tab,x,y%x,0);

        int kx=x1, ky=y1;
        if(y1>y2) ky-= tab[0];

        while(k<x)
        {
            Blit(ecran,kx,ky,1,tab[k],R,V,B);
            if(x1<=x2) kx++;
            else kx--;
            if(y1<=y2) ky+=tab[k];
            else ky-=tab[k];
            k++;
        }
    }
    else if(y<=x)
    {
        int tab[641]={x/y}; // Normalement , mettre y à la place de 640, mais ce con ne vuet pas
        int i=0;
        while(i<y)
        {
            tab[i]=x/y;
            i++;
        }
        int k=0;
        BlitLine_aux(tab,y,x%y,0);

        int kx=x1, ky=y1;
        if(x1>x2) kx-= tab[0];
        while(k<y)
        {
            Blit(ecran,kx,ky,tab[k],1,R,V,B);
            if(y1<=y2) ky++;
            else ky--;
            if(x1<=x2) kx+=tab[k];
            else kx-=tab[k];
            k++;
        }
    }
}*/

/// PLANTAGE ASSURE
void BlitLine(SDL_Surface *ecran, int x1, int y1, int x2, int y2, int R, int V, int B) // Ligne du point (x1,y1) au point (x2,y2)
{
    if(x1==x2 && y1==y2) Blit(ecran,x1,y1,1,1,R,V,B);
    else if(x1!=x2 && y1!=y2)                               /// Cas de droite horizontale/verticale à traiter
    {
        int a=x1,b=y1,c=x2,d=y2;
        if(x1>x2) {a=x2;c=x1;b=y2;d=y1;}


        int j=0;
        int t=0;
        double coef=(double)((d-b)/(c-a));

        if(coef>1) // cas où la pente est inférieure à 1, on passe chaque x en revue et on lui attribue y
        {
            Blit(ecran,a,b,1,1,R,V,B);
            coef=(double)((d-b)/(c-a));
            j=a+1;
            while(j<=c)
            {
                t=coef*(j-a)+b;
                Blit(ecran,j,t,1,1,R,V,B);
                j++;
            }
        }
        else if(coef>0) // cas où la pente est strictement supérieure à 1, on passe chaque y en revue et on lui attribue x
        {
            Blit(ecran,a,b,1,1,R,V,B);
            coef=(double)((c-a)/(d-b));
            j=b+1;
            while(j<=d)
            {
                t=coef*(j-b)+a;
                Blit(ecran,t,j,1,1,R,V,B);
                j++;
            }
        }
        else if(coef>-1)
        {
            Blit(ecran,a,b,1,1,R,V,B);
            coef=(double)((c-a)/(d-b));
            j=b+1;
            while(j<=d)
            {
                t=coef*(j-b)+a;
                Blit(ecran,t,j,1,1,R,V,B);
                j--;
            }
        }
        else
        {
            Blit(ecran,a,b,1,1,R,V,B);
            coef=(double)((c-a)/(d-b));
            j=b+1;
            while(j<=d)
            {
                t=coef*(j-b)+a;
                Blit(ecran,t,j,1,1,R,V,B);
                j--;
            }
        }
    }
}

void BlitBall(SDL_Surface *ecran, int x, int y, int r, int R, int V, int B)  // Cercle de centre (x,y) et de rayon r
{
    if(r==0) // 38 pixels de diametre
    {
        Blit(ecran,x-5,y-19,10,1,R,V,B);
        Blit(ecran,x-8,y-18,16,1,R,V,B);
        Blit(ecran,x-10,y-17,20,1,R,V,B);
        Blit(ecran,x-11,y-16,22,1,R,V,B);
        Blit(ecran,x-13,y-15,26,1,R,V,B);
        Blit(ecran,x-14,y-14,28,1,R,V,B);
        Blit(ecran,x-15,y-13,30,2,R,V,B);
        Blit(ecran,x-16,y-11,32,1,R,V,B);
        Blit(ecran,x-17,y-10,34,2,R,V,B);
        Blit(ecran,x-18,y-8,36,3,R,V,B);
        Blit(ecran,x-19,y-5,38,11,R,V,B);

        Blit(ecran,x-5,y+19,10,1,R,V,B);
        Blit(ecran,x-8,y+18,16,1,R,V,B);
        Blit(ecran,x-10,y+17,20,1,R,V,B);
        Blit(ecran,x-11,y+16,22,1,R,V,B);
        Blit(ecran,x-13,y+15,26,1,R,V,B);
        Blit(ecran,x-14,y+14,28,1,R,V,B);
        Blit(ecran,x-15,y+12,30,2,R,V,B);
        Blit(ecran,x-16,y+11,32,1,R,V,B);
        Blit(ecran,x-17,y+9,34,2,R,V,B);
        Blit(ecran,x-18,y+6,36,3,R,V,B);
    }
    else
    {
        int t= r/6;
        Blit(ecran,x-2*t,y-6*t,4*t,1*t,R,V,B);
        Blit(ecran,x-4*t,y-5*t,8*t,1*t,R,V,B);
        Blit(ecran,x-5*t,y-4*t,10*t,2*t,R,V,B);
        Blit(ecran,x-6*t,y-2*t,12*t,4*t,R,V,B);
        Blit(ecran,x-5*t,y+2*t,10*t,2*t,R,V,B);
        Blit(ecran,x-4*t,y+4*t,8*t,1*t,R,V,B);
        Blit(ecran,x-2*t,y+5*t,4*t,1*t,R,V,B);
    }
}



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


situation Definir_situation()
{
    situation S;
    S.enfoncees=0;
    S.a=0;
    S.b=0;
    S.c=0;
    S.d=0;
    S.e=0;
    S.f=0;
    S.g=0;
    S.h=0;
    S.i=0;
    S.j=0;
    S.k=0;
    S.l=0;
    S.m=0;
    S.n=0;
    S.o=0;
    S.p=0;
    S.q=0;
    S.r=0;
    S.s=0;
    S.t=0;
    S.u=0;
    S.v=0;
    S.w=0;
    S.x=0;
    S.y=0;
    S.z=0;
    S.k0=0;
    S.k1=0;
    S.k2=0;
    S.k3=0;
    S.k4=0;
    S.k5=0;
    S.k6=0;
    S.k7=0;
    S.k8=0;
    S.k9=0;
    S.kp0=0;
    S.kp1=0;
    S.kp2=0;
    S.kp3=0;
    S.kp4=0;
    S.kp5=0;
    S.kp6=0;
    S.kp7=0;
    S.kp8=0;
    S.kp9=0;
    S.enter=0;
    S.backspace=0;
    S.space=0;
    S.capslock=0;
    S.maj=0;
    S.tab=0;
    S.f1=0;
    S.f2=0;
    S.f3=0;
    S.f4=0;
    S.f5=0;
    S.f6=0;
    S.f7=0;
    S.f8=0;
    S.f9=0;
    S.f10=0;
    S.f11=0;
    S.f12=0;
    S.escape=0;
    S.clic_d=0;
    S.clic_g=0;
    S.clic_m=0;
    S.mousex=0;
    S.mousey=0;
    S.kp_point=0;
    S.kp_plus=0;
    S.kp_moins=0;
    S.kp_etoile=0;
    S.kp_slash=0;
    S.k_point=0;
    S.k_ask=0;
    S.k_slash=0;
    S.k_exclam=0;
    S.k_plus=0;
    S.k_degre=0;
    S.k_circonflexe=0;
    S.k_dollar=0;
    S.k_pourcentage=0;
    S.k_micro=0;
    S.haut=0;
    S.bas=0;
    S.gauche=0;
    S.droite=0;
    S.exit=0;
    S.kp_enter=0;
    S.clicx=0;
    S.clicy=0;
    return S;
}

void Changer_situation()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT) Situation.exit=1;
        else if(event.type==SDL_MOUSEMOTION)
        {
            Situation.mousex=event.motion.x;
            Situation.mousey=event.motion.y;
        }
        else if(event.type==SDL_MOUSEBUTTONDOWN)
        {
            if(event.button.button==SDL_BUTTON_LEFT)
            {
                Situation.clic_g=1;
                // Enregistre la position du dernier clic gauche.
                Situation.clicx=event.button.x;
                Situation.clicy=event.button.y;
            }
            else if(event.button.button==SDL_BUTTON_RIGHT) Situation.clic_d=1;
            else if(event.button.button==SDL_BUTTON_MIDDLE) Situation.clic_m=1;
        }else if(event.type==SDL_MOUSEBUTTONUP)
        {
            if(event.button.button==SDL_BUTTON_LEFT) Situation.clic_g=0;
            else if(event.button.button==SDL_BUTTON_RIGHT) Situation.clic_d=0;
            else if(event.button.button==SDL_BUTTON_MIDDLE) Situation.clic_m=0;
        }
        else if(event.type==SDL_KEYDOWN)
        {
            Situation.enfoncees++;
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT:    Situation.gauche=1; break;
                case SDLK_RIGHT:    Situation.droite=1; break;
                case SDLK_UP:    Situation.haut=1; break;
                case SDLK_DOWN:    Situation.bas=1; break;
                case SDLK_ESCAPE: Situation.escape=1; break;
                case SDLK_F1:     Situation.f1=1; break;
                case SDLK_F2:     Situation.f2=1; break;
                case SDLK_F3:     Situation.f3=1; break;
                case SDLK_F4:     Situation.f4=1; Situation.exit=1; break;
                case SDLK_F5:     Situation.f5=1; break;
                case SDLK_F6:     Situation.f6=1; break;
                case SDLK_F7:     Situation.f7=1; break;
                case SDLK_F8:     Situation.f8=1; break;
                case SDLK_F9:     Situation.f9=1; break;
                case SDLK_F10:     Situation.f10=1; break;
                case SDLK_F11:     Situation.f11=1; break;
                case SDLK_F12:     Situation.f12=1; break;
                case SDLK_RETURN: Situation.enter=1;  break;
                case SDLK_KP_ENTER: Situation.kp_enter=1; break;
                case SDLK_BACKSPACE: Situation.backspace=1;  break;
                case SDLK_q: Situation.a=1;  break;
                case SDLK_b: Situation.b=1; break;
                case SDLK_c: Situation.c=1; break;
                case SDLK_d: Situation.d=1; break;
                case SDLK_e: Situation.e=1; break;
                case SDLK_f: Situation.f=1; break;
                case SDLK_g: Situation.g=1; break;
                case SDLK_h: Situation.h=1; break;
                case SDLK_i: Situation.i=1; break;
                case SDLK_j: Situation.j=1; break;
                case SDLK_k:  Situation.k=1; break;
                case SDLK_l:  Situation.l=1; break;
                case SDLK_SEMICOLON:  Situation.m=1; break;
                case SDLK_n:  Situation.n=1; break;
                case SDLK_o:  Situation.o=1; break;
                case SDLK_p:  Situation.p=1; break;
                case SDLK_a:  Situation.q=1; break;
                case SDLK_r:  Situation.r=1; break;
                case SDLK_s:  Situation.s=1; break;
                case SDLK_t:  Situation.t=1; break;
                case SDLK_u:  Situation.u=1; break;
                case SDLK_v:  Situation.v=1; break;
                case SDLK_z:  Situation.w=1; break;
                case SDLK_x:  Situation.x=1; break;
                case SDLK_y:  Situation.y=1; break;
                case SDLK_w:  Situation.z=1; break;
                case SDLK_0:  Situation.k0=1; break;
                case SDLK_1:  Situation.k1=1; break;
                case SDLK_2:  Situation.k2=1; break;
                case SDLK_3:  Situation.k3=1; break;
                case SDLK_4:  Situation.k4=1; break;
                case SDLK_5:  Situation.k5=1; break;
                case SDLK_6:  Situation.k6=1; break;
                case SDLK_7:  Situation.k7=1; break;
                case SDLK_8:  Situation.k8=1; break;
                case SDLK_9:  Situation.k9=1; break;
                case SDLK_KP0:  Situation.kp0=1; break;
                case SDLK_KP1:  Situation.kp1=1; break;
                case SDLK_KP2:  Situation.kp2=1; break;
                case SDLK_KP3:  Situation.kp3=1; break;
                case SDLK_KP4:  Situation.kp4=1; break;
                case SDLK_KP5:  Situation.kp5=1; break;
                case SDLK_KP6:  Situation.kp6=1; break;
                case SDLK_KP7:  Situation.kp7=1; break;
                case SDLK_KP8:  Situation.kp8=1; break;
                case SDLK_KP9:  Situation.kp9=1; break;
                case SDLK_KP_MINUS: Situation.kp_moins=1; break;
                case SDLK_KP_PERIOD: Situation.kp_point=1; break;
                case SDLK_COMMA: Situation.k_point=1; break;
                case SDLK_SLASH: Situation.k_exclam=1; break;
                case SDLK_SPACE: Situation.space=1; break;
                case SDLK_m: Situation.k_ask=1; break;
            }
        }else if(event.type==SDL_KEYUP)
        {
            Situation.enfoncees--;
            switch(event.key.keysym.sym)
            {
                case SDLK_LEFT:    Situation.gauche=0; break;
                case SDLK_RIGHT:    Situation.droite=0; break;
                case SDLK_UP:    Situation.haut=0; break;
                case SDLK_DOWN:    Situation.bas=0; break;
                case SDLK_ESCAPE: Situation.escape=0; break;
                case SDLK_F1:     Situation.f1=0; break;
                case SDLK_F2:     Situation.f2=0; break;
                case SDLK_F3:     Situation.f3=0; break;
                case SDLK_F4:     Situation.f4=0; break;
                case SDLK_F5:     Situation.f5=0; break;
                case SDLK_F6:     Situation.f6=0; break;
                case SDLK_F7:     Situation.f7=0; break;
                case SDLK_F8:     Situation.f8=0; break;
                case SDLK_F9:     Situation.f9=0; break;
                case SDLK_F10:     Situation.f10=0; break;
                case SDLK_F11:     Situation.f11=0; break;
                case SDLK_F12:     Situation.f12=0; break;
                case SDLK_RETURN: Situation.enter=0;  break;
                case SDLK_KP_ENTER: Situation.kp_enter=0; break;
                case SDLK_BACKSPACE: Situation.backspace=0;  break;
                case SDLK_q: Situation.a=0;  break;
                case SDLK_b: Situation.b=0; break;
                case SDLK_c: Situation.c=0; break;
                case SDLK_d: Situation.d=0; break;
                case SDLK_e: Situation.e=0; break;
                case SDLK_f: Situation.f=0; break;
                case SDLK_g: Situation.g=0; break;
                case SDLK_h: Situation.h=0; break;
                case SDLK_i: Situation.i=0; break;
                case SDLK_j: Situation.j=0; break;
                case SDLK_k:  Situation.k=0; break;
                case SDLK_l:  Situation.l=0; break;
                case SDLK_SEMICOLON:  Situation.m=0; break;
                case SDLK_n:  Situation.n=0; break;
                case SDLK_o:  Situation.o=0; break;
                case SDLK_p:  Situation.p=0; break;
                case SDLK_a:  Situation.q=0; break;
                case SDLK_r:  Situation.r=0; break;
                case SDLK_s:  Situation.s=0; break;
                case SDLK_t:  Situation.t=0; break;
                case SDLK_u:  Situation.u=0; break;
                case SDLK_v:  Situation.v=0; break;
                case SDLK_z:  Situation.w=0; break;
                case SDLK_x:  Situation.x=0; break;
                case SDLK_y:  Situation.y=0; break;
                case SDLK_w:  Situation.z=0; break;
                case SDLK_0:  Situation.k0=0; break;
                case SDLK_1:  Situation.k1=0; break;
                case SDLK_2:  Situation.k2=0; break;
                case SDLK_3:  Situation.k3=0; break;
                case SDLK_4:  Situation.k4=0; break;
                case SDLK_5:  Situation.k5=0; break;
                case SDLK_6:  Situation.k6=0; break;
                case SDLK_7:  Situation.k7=0; break;
                case SDLK_8:  Situation.k8=0; break;
                case SDLK_9:  Situation.k9=0; break;
                case SDLK_KP0:  Situation.kp0=0; break;
                case SDLK_KP1:  Situation.kp1=0; break;
                case SDLK_KP2:  Situation.kp2=0; break;
                case SDLK_KP3:  Situation.kp3=0; break;
                case SDLK_KP4:  Situation.kp4=0; break;
                case SDLK_KP5:  Situation.kp5=0; break;
                case SDLK_KP6:  Situation.kp6=0; break;
                case SDLK_KP7:  Situation.kp7=0; break;
                case SDLK_KP8:  Situation.kp8=0; break;
                case SDLK_KP9:  Situation.kp9=0; break;
                case SDLK_KP_MINUS: Situation.kp_moins=0; break;
                case SDLK_KP_PERIOD: Situation.kp_point=0; break;
                case SDLK_COMMA: Situation.k_point=0; break;
                case SDLK_SLASH: Situation.k_exclam=0; break;
                case SDLK_SPACE: Situation.space=0; break;
                case SDLK_m: Situation.k_ask=0; break;
            }
        }
    }
}
