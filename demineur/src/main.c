#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>


int main ( int argc, char** argv )
{

    int x=0,y=0,e=1,i=0,f=0;
    int n=20;                                              // n pair > 5
    int vus=0,mines=0,score[7],partie[9], RESTART=1;

    int casen[26][26], vu[26][26];
    SDL_Surface *cases[14], *ecran, *ico;
    SDL_Rect casep[26][26];

    SDL_Event event;

    // Si mine case[x][y]=-1, sinon = mines alentours


    while(y<26)
    {
        while(x<26)
        {
            vu[x][y]=0;
            casep[x][y].y=32*y;
            casep[x][y].x=32*x;
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;

            partie[7]=2;
            partie[8]=0;


/// VIDEO START

    SDL_Init(SDL_INIT_VIDEO);

    ico=SDL_LoadBMP("hidden\\9.bmp");
    SDL_SetColorKey(ico, SDL_SRCCOLORKEY, SDL_MapRGB(ico->format, 255, 255, 255));
    SDL_WM_SetIcon(ico, NULL);

    ecran = SDL_SetVideoMode(32*n, 32*n, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("MaxCorp vous propose son demineur", NULL);


    cases[0] = SDL_LoadBMP("hidden\\0.bmp");
    cases[1] = SDL_LoadBMP("hidden\\1.bmp");
    cases[2] = SDL_LoadBMP("hidden\\2.bmp");
    cases[3] = SDL_LoadBMP("hidden\\3.bmp");
    cases[4] = SDL_LoadBMP("hidden\\4.bmp");
    cases[5] = SDL_LoadBMP("hidden\\5.bmp");
    cases[6] = SDL_LoadBMP("hidden\\6.bmp");
    cases[7] = SDL_LoadBMP("hidden\\7.bmp");
    cases[8] = SDL_LoadBMP("hidden\\8.bmp");
    cases[9] = SDL_LoadBMP("hidden\\9.bmp");
    cases[10] = SDL_LoadBMP("hidden\\x.bmp");    // covered
    cases[11] = SDL_LoadBMP("hidden\\m.bmp");    // mine
    cases[12] = SDL_LoadBMP("hidden\\00.bmp");   // 0 du score
    cases[13] = SDL_LoadBMP("hidden\\n.bmp");    // mine pensée

while(RESTART)    /// En cas de restart. Réinitialisation des variables.
{
    RESTART=0;
    e=1; i=0; x=0; y=0; f=0; vus=0; mines=0; while(f<7) { score[f]=0; partie[f]=0; f++;} f=0;
    while(y<n)
    {
        while(x<n)
        {
            vu[x][y]=0;
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;







    while(y<n)
    {
        while(x<n)
        {
            SDL_BlitSurface(cases[10],NULL,ecran,&casep[x][y]);
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-3][n/2-1]);
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-2][n/2-1]);
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-1][n/2-1]);
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2][n/2-1]);
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2+1][n/2-1]);
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2+2][n/2-1]);

    SDL_Flip(ecran);

    /// CHOIX DU NUMERO DE LA PARTIE


SDL_WM_SetCaption("Choissisez un numero de partie - le premier chiffre donnant la difficulte", NULL);
    while(f!=-1)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                f = -1;
                e = 0;
            break;
            case SDL_KEYUP:
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                f = -1;
                e = 0;
            break;
            case SDLK_RETURN:
            if(f==6 || f==9)
                f = -1;
            break;
            case SDLK_d:
            if(f==6)
                f++;
            SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-1][n/2]);
            SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2][n/2]);
            SDL_Flip(ecran);
            break;
            case SDLK_KP_ENTER:
            if(f==6 || f==9)
                f = -1;
            break;
            case SDLK_BACKSPACE:
            if(f>0 && f<7)
            {
                SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
                partie[0]=partie[0]-partie[f]*(10^(6-f));
                f--;
            }
            else if(f==8 || f==9) {SDL_BlitSurface(cases[0],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran); partie[f]=0; f--; }
            break;

            case SDLK_0:
            if(f<6)
            {
                f++;
                partie[f]=0;
                SDL_BlitSurface(cases[12],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=0; f++; SDL_BlitSurface(cases[12],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_1:
            if(f<6)
            {
                f++;
                partie[f]=1;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=1; f++; SDL_BlitSurface(cases[1],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_2:
            if(f<6)
            {
                f++;
                partie[f]=2;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=2; f++; SDL_BlitSurface(cases[2],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_3:
            if(f<6)
            {
                f++;
                partie[f]=3;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=3; f++; SDL_BlitSurface(cases[3],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_4:
            if(f<6)
            {
                f++;
                partie[f]=4;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=4; f++; SDL_BlitSurface(cases[4],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_5:
            if(f<6)
            {
                f++;
                partie[f]=5;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=5; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_6:
            if(f<6)
            {
                f++;
                partie[f]=6;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=6; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_7:
            if(f<6)
            {
                f++;
                partie[f]=7;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=7; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_8:
            if(f<6)
            {
                f++;
                partie[f]=8;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=8; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_9:
            if(f<6)
            {
                f++;
                partie[f]=9;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=9; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP0:
            if(f<6)
            {
                f++;
                partie[f]=0;
                SDL_BlitSurface(cases[12],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=0; f++; SDL_BlitSurface(cases[12],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP1:
            if(f<6)
            {
                f++;
                partie[f]=1;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=1; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP2:
            if(f<6)
            {
                f++;
                partie[f]=2;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=2; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP3:
            if(f<6)
            {
                f++;
                partie[f]=3;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=3; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP4:
            if(f<6)
            {
                f++;
                partie[f]=4;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=4; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP5:
            if(f<6)
            {
                f++;
                partie[f]=5;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=5; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP6:
            if(f<6)
            {
                f++;
                partie[f]=6;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=6; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP7:
            if(f<6)
            {
                f++;
                partie[f]=7;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=7; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP8:
            if(f<6)
            {
                f++;
                partie[f]=8;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=8; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
            case SDLK_KP9:
            if(f<6)
            {
                f++;
                partie[f]=9;
                partie[0]=partie[0]+partie[f]*(10^(6-f));
                SDL_BlitSurface(cases[partie[f]],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=9; f++; SDL_BlitSurface(cases[partie[f-1]],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
            break;
        }
        break;
        }
    }


    n=partie[7]*10+partie[8];
    if(n<6 || n%2!=0 || n>26) n=20;

    ecran = SDL_SetVideoMode(32*n, 32*n, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    while(y<n)
    {
        while(x<n)
        {
            SDL_BlitSurface(cases[10],NULL,ecran,&casep[x][y]);
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;

    SDL_Flip(ecran);




    /// INITIALISATION DU JEU

    srand(partie[0]);

SDL_WM_SetCaption("MaxCorp vous propose son demineur", NULL);
    while(y<n)
    {
        while(x<n)
        {
            casen[x][y]=(rand()+x*y)%(partie[1]+2);
                if(casen[x][y]==0) casen[x][y]=-1;
                else               casen[x][y]=0;
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;

    while(y<n)
    {
        while(x<n)
        {
            if(casen[x][y]==-1)
            {
                mines++;
                if(x>0  && y>0  && casen[x-1][y-1]!=-1) casen[x-1][y-1]++;
                if(x>0  &&         casen[x-1][y]!=-1)   casen[x-1][y]++;
                if(x>0  && y<n-1 && casen[x-1][y+1]!=-1) casen[x-1][y+1]++;
                if(        y>0  && casen[x][y-1]!=-1)   casen[x][y-1]++;
                if(        y<n-1 && casen[x][y+1]!=-1)   casen[x][y+1]++;
                if(x<n-1 && y>0  && casen[x+1][y-1]!=-1) casen[x+1][y-1]++;
                if(x<n-1 &&         casen[x+1][y]!=-1)   casen[x+1][y]++;
                if(x<n-1 && y<n-1 && casen[x+1][y+1]!=-1) casen[x+1][y+1]++;
            }
            x++;
        }
        y++;
        x=0;
    }
    x=0;
    y=0;

  /// JEU START

    score[0]=(SDL_GetTicks()-SDL_GetTicks()%1000)/1000;

    while(e)
    {
        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                e = 0;
            break;
            case SDLK_r:
                e = 0;
                RESTART=1;
            break;
        }
        switch(event.type)
        {

            case SDL_QUIT:
                e = 0;
            break;


            case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_RIGHT && e==1)    /// CLIC DROIT MINE PENSEE
            {
                x=(event.button.x - event.button.x%32)/32;
                y=(event.button.y - event.button.y%32)/32;

                if(vu[x][y]==0)
                {
                    vu[x][y]=2;
                    SDL_BlitSurface(cases[13],NULL,ecran,&casep[x][y]);
                }
                else if(vu[x][y]==2)
                {
                    vu[x][y]=0;
                    SDL_BlitSurface(cases[10],NULL,ecran,&casep[x][y]);
                }
                SDL_Flip(ecran);
                x=0; y=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && e==1)
            {
                x=(event.button.x - event.button.x%32)/32;
                y=(event.button.y - event.button.y%32)/32;

                if(vu[x][y]==0) vus++;
                vu[x][y]=1;

                if(casen[x][y]==-1)          /// FIN DU JEU
                {
                    x=0; y=0;
                    while(y<n)
                    {
                        while(x<n)
                        {
                            vu[x][y]=1;
                            x++;
                        }
                        y++;
                        x=0;
                    }
                }
                else if(vus+mines==n*n)       /// WINNER + AFFICHAGE SCORE
                {
                    score[0]=(SDL_GetTicks()-SDL_GetTicks()%1000)/1000 - score[0];

                    i=0;
                    while(i<6)
                    {
                        if(score[0]==0) score[6-i]=0;
                        else
                        {
                            score[6-i]=score[0]%10;
                            score[0]=(score[0]-score[6-i])/10;
                            if(score[6-i]==0) score[6-i]=12;
                        }
                        i++;
                    }
                    x=0;
                    y=0;
                    while(y<n)
                    {
                        while(x<n)
                        {
                            SDL_BlitSurface(cases[10],NULL,ecran,&casep[x][y]);
                            x++;
                        }
                        y++;
                        x=0;
                    }
                    SDL_BlitSurface(cases[score[1]],NULL,ecran,&casep[n/2-3][n/2-1]);
                    SDL_BlitSurface(cases[score[2]],NULL,ecran,&casep[n/2-2][n/2-1]);
                    SDL_BlitSurface(cases[score[3]],NULL,ecran,&casep[n/2-1][n/2-1]);
                    SDL_BlitSurface(cases[score[4]],NULL,ecran,&casep[n/2][n/2-1]);
                    SDL_BlitSurface(cases[score[5]],NULL,ecran,&casep[n/2+1][n/2-1]);
                    SDL_BlitSurface(cases[score[6]],NULL,ecran,&casep[n/2+2][n/2-1]);
                    SDL_Flip(ecran);
                    e=2;


                }

                if(casen[x][y]==0)           /// ETALAGE SI CASE VIDE
                {
                    i=0; x=0; y=0;
                    while(i<50)
                    {
                        while(y<n)
                        {
                            while(x<n)
                            {
                                if(vu[x][y]==0)
                                {
                                    if     ((x>0  && y>0  && casen[x-1][y-1]==0 )&& vu[x-1][y-1]==1) { vu[x][y]=1; vus++; }
                                    else if((x>0  &&         casen[x-1][y]==0   )&& vu[x-1][y]==1)   { vu[x][y]=1; vus++; }
                                    else if((x>0  && y<n-1 && casen[x-1][y+1]==0 )&& vu[x-1][y+1]==1) { vu[x][y]=1; vus++; }
                                    else if((        y>0  && casen[x][y-1]==0   )&& vu[x][y-1]==1)   { vu[x][y]=1; vus++; }
                                    else if((        y<n-1 && casen[x][y+1]==0   )&& vu[x][y+1]==1)   { vu[x][y]=1; vus++; }
                                    else if((x<n-1 && y>0  && casen[x+1][y-1]==0 )&& vu[x+1][y-1]==1) { vu[x][y]=1; vus++; }
                                    else if((x<n-1 &&         casen[x+1][y]==0   )&& vu[x+1][y]==1)   { vu[x][y]=1; vus++; }
                                    else if((x<n-1 && y<n-1 && casen[x+1][y+1]==0 )&& vu[x+1][y+1]==1) { vu[x][y]=1; vus++; }
                                }
                                x++;
                            }
                            x=0;
                            y++;
                        }
                        y=0;
                        i++;
                    }
                }



                x=0;
                y=0;
                while(y<n && e==1)          /// AFFICHAGE
                {
                    while(x<n)
                    {
                        if(vu[x][y]==0)
                            SDL_BlitSurface(cases[10],NULL,ecran,&casep[x][y]);
                        else if(casen[x][y]==-1 && vu[x][y]!=2)
                            SDL_BlitSurface(cases[11],NULL,ecran,&casep[x][y]);
                        else if(vu[x][y]==1)
                            SDL_BlitSurface(cases[casen[x][y]],NULL,ecran,&casep[x][y]);
                        x++;
                    }
                    y++;
                    x=0;
                }
                x=0;
                y=0;
                SDL_Flip(ecran);
            }
            break;

        }
    }
}
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(cases[0]);
    SDL_FreeSurface(cases[1]);
    SDL_FreeSurface(cases[2]);
    SDL_FreeSurface(cases[3]);
    SDL_FreeSurface(cases[4]);
    SDL_FreeSurface(cases[5]);
    SDL_FreeSurface(cases[6]);
    SDL_FreeSurface(cases[7]);
    SDL_FreeSurface(cases[8]);
    SDL_FreeSurface(cases[9]);
    SDL_FreeSurface(cases[10]);
    SDL_FreeSurface(cases[11]);

     return 0;
}
