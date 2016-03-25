#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>


int main ( int argc, char** argv )
{

    int x=0,y=0,z=0,X=0,Y=0,e=1,i=0,f=0;
    int n=14,a=2,p=0;                                              // n pair > 5
    int vus=0,mines=0,score[7],partie[9], RESTART=1;

    int casen[26][26][26], vu[26][26][26];
    SDL_Surface *cases[31], *ecran, *ico, *fond;
    SDL_Rect casep[26][26];

    SDL_Event event;

    // Si mine case[x][y]=-1, sinon = mines alentours

while(z<26)
{
    while(y<26)
    {
        while(x<26)
        {
            vu[x][y][z]=0;
            casep[x][y].y=32*y;
            casep[x][y].x=32*x;
            x++;
        }
        y++;
        x=0;
    }
    z++;
    y=0;
}
    x=0;
    y=0;
    z=0;

            partie[7]=1;
            partie[8]=4;


/// VIDEO START

    SDL_Init(SDL_INIT_VIDEO);

    ico=SDL_LoadBMP("hidden\\9.bmp");
    SDL_SetColorKey(ico, SDL_SRCCOLORKEY, SDL_MapRGB(ico->format, 255, 255, 255));
    SDL_WM_SetIcon(ico, NULL);

    ecran = SDL_SetVideoMode(32*(n+5), 32*n, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("MaxCorp vous propose son demineur 3D", NULL);


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
    cases[10] = SDL_LoadBMP("hidden\\10.bmp");
    cases[11] = SDL_LoadBMP("hidden\\11.bmp");
    cases[12] = SDL_LoadBMP("hidden\\12.bmp");
    cases[13] = SDL_LoadBMP("hidden\\13.bmp");
    cases[14] = SDL_LoadBMP("hidden\\14.bmp");
    cases[15] = SDL_LoadBMP("hidden\\15.bmp");
    cases[16] = SDL_LoadBMP("hidden\\16.bmp");
    cases[17] = SDL_LoadBMP("hidden\\17.bmp");
    cases[18] = SDL_LoadBMP("hidden\\18.bmp");
    cases[19] = SDL_LoadBMP("hidden\\19.bmp");
    cases[20] = SDL_LoadBMP("hidden\\20.bmp");
    cases[21] = SDL_LoadBMP("hidden\\21.bmp");
    cases[22] = SDL_LoadBMP("hidden\\22.bmp");
    cases[23] = SDL_LoadBMP("hidden\\23.bmp");
    cases[24] = SDL_LoadBMP("hidden\\24.bmp");
    cases[25] = SDL_LoadBMP("hidden\\25.bmp");
    cases[26] = SDL_LoadBMP("hidden\\26.bmp");
    cases[27] = SDL_LoadBMP("hidden\\x.bmp");    // covered
    cases[28] = SDL_LoadBMP("hidden\\m.bmp");    // mine
    cases[29] = SDL_LoadBMP("hidden\\00.bmp");   // 0 du score
    cases[30] = SDL_LoadBMP("hidden\\n.bmp");    // mine pensée

while(RESTART)    /// En cas de restart. Réinitialisation des variables.
{
    RESTART=0;
    e=1; i=0; x=0; y=0; z=0; f=0; vus=0; mines=0; while(f<7) { score[f]=0; partie[f]=0; f++;} f=0; a=2; p=0;

    while(z<n){
    while(y<n)
    {
        while(x<n)
        {
            vu[x][y][z]=0;
            x++;
        }
        y++;
        x=0;
    }
    z++;
    y=0;
              }
    x=0;
    y=0;
    z=0;


    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);



    while(y<n)
    {
        while(x<n)
        {
            SDL_BlitSurface(cases[27],NULL,ecran,&casep[x][y]);
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
                SDL_BlitSurface(cases[29],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=0; f++; SDL_BlitSurface(cases[29],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
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
                SDL_BlitSurface(cases[29],NULL,ecran,&casep[n/2-4+f][n/2-1]);
                SDL_Flip(ecran);
            }
            else if(f<9 && f>6) {partie[f]=0; f++; SDL_BlitSurface(cases[29],NULL,ecran,&casep[n/2-9+f][n/2]); SDL_Flip(ecran);}
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

    ecran = SDL_SetVideoMode(32*(n+5), 32*n, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);

    while(y<n)
    {
        while(x<n)
        {
            SDL_BlitSurface(cases[27],NULL,ecran,&casep[x][y]);
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

SDL_WM_SetCaption("MaxCorp vous propose son demineur 3D", NULL);
    while(z<n){
        while(y<n)
    {
        while(x<n)
        {
            casen[x][y][z]=(rand()+x*y*z)%(partie[1]*3+2);
                if(casen[x][y][z]==0) casen[x][y][z]=-1;
                else               casen[x][y][z]=0;
            x++;
        }
        y++;
        x=0;
    }
    z++;
    y=0;
    }
    x=0;
    y=0;
    z=0;

while(z<n){
    while(y<n)
    {
        while(x<n)
        {
            if(casen[x][y][z]==-1)
            {
                mines++;
                if(x>0   && y>0   && z>0   && casen[x-1][y-1][z-1]!=-1) casen[x-1][y-1][z-1]++;
                if(x>0   &&          z>0   && casen[x-1][y][z-1]!=-1)   casen[x-1][y][z-1]++;
                if(x>0   && y<n-1 && z>0   && casen[x-1][y+1][z-1]!=-1) casen[x-1][y+1][z-1]++;
                if(         y>0   && z>0   && casen[x][y-1][z-1]!=-1)   casen[x][y-1][z-1]++;
                if(         y<n-1 && z>0   && casen[x][y+1][z-1]!=-1)   casen[x][y+1][z-1]++;
                if(x<n-1 && y>0   && z>0   && casen[x+1][y-1][z-1]!=-1) casen[x+1][y-1][z-1]++;
                if(x<n-1 &&          z>0   && casen[x+1][y][z-1]!=-1)   casen[x+1][y][z-1]++;
                if(x<n-1 && y<n-1 && z>0   && casen[x+1][y+1][z-1]!=-1) casen[x+1][y+1][z-1]++;
                if(x>0   && y>0   &&          casen[x-1][y-1][z]!=-1)   casen[x-1][y-1][z]++;
                if(x>0   &&                   casen[x-1][y][z]!=-1)     casen[x-1][y][z]++;
                if(x>0   && y<n-1 &&          casen[x-1][y+1][z]!=-1)   casen[x-1][y+1][z]++;
                if(         y>0   &&          casen[x][y-1][z]!=-1)     casen[x][y-1][z]++;
                if(         y<n-1 &&          casen[x][y+1][z]!=-1)     casen[x][y+1][z]++;
                if(x<n-1 && y>0   &&          casen[x+1][y-1][z]!=-1)   casen[x+1][y-1][z]++;
                if(x<n-1 &&                   casen[x+1][y][z]!=-1)     casen[x+1][y][z]++;
                if(x<n-1 && y<n-1 &&          casen[x+1][y+1][z]!=-1)   casen[x+1][y+1][z]++;
                if(x>0   && y>0   && z<n-1 && casen[x-1][y-1][z+1]!=-1) casen[x-1][y-1][z+1]++;
                if(x>0   &&          z<n-1 && casen[x-1][y][z+1]!=-1)   casen[x-1][y][z+1]++;
                if(x>0   && y<n-1 && z<n-1 && casen[x-1][y+1][z+1]!=-1) casen[x-1][y+1][z+1]++;
                if(         y>0   && z<n-1 && casen[x][y-1][z+1]!=-1)   casen[x][y-1][z+1]++;
                if(         y<n-1 && z<n-1 && casen[x][y+1][z+1]!=-1)   casen[x][y+1][z+1]++;
                if(x<n-1 && y>0   && z<n-1 && casen[x+1][y-1][z+1]!=-1) casen[x+1][y-1][z+1]++;
                if(x<n-1 &&          z<n-1 && casen[x+1][y][z+1]!=-1)   casen[x+1][y][z+1]++;
                if(x<n-1 && y<n-1 && z<n-1 && casen[x+1][y+1][z+1]!=-1) casen[x+1][y+1][z+1]++;
                if(                  z<n-1 && casen[x][y][z+1]!=-1)     casen[x][y][z+1]++;
                if(                  z>0   && casen[x][y][z-1]!=-1)     casen[x][y][z-1]++;
            }
            x++;
        }
        y++;
        x=0;
    }
    z++;
    y=0;
}
    x=0;
    y=0;
    z=0;

  /// JEU START

    score[0]=(SDL_GetTicks()-SDL_GetTicks()%1000)/1000;

    while(e)
    {
        SDL_WaitEvent(&event);
        if(event.type==SDL_KEYUP)
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                e = 0;
            break;

            case SDLK_r:
                e = 0;
                RESTART=1;
            break;

            case SDLK_UP:
                if(a==4 || a==3 || a==2) a--;
                Y=p;  X=p;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                 if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
                SDL_Flip(ecran);
            break;

            case SDLK_DOWN:
                if(a==1 || a==3 || a==2) a++;
                Y=p;  X=p;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                 if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
                SDL_Flip(ecran);
            break;

            case SDLK_LEFT:
                if(a==2) a=5;
                else if(a==6) a=2;
                Y=p;  X=p;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                 if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}

                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
                SDL_Flip(ecran);
            break;

            case SDLK_RIGHT:
                if(a==2) a=6;
                else if(a==5) a=2;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                Y=p;  X=p;
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
                SDL_Flip(ecran);
            break;

            case SDLK_q:
                if(p>0) p--;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                Y=p;  X=p;
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
                SDL_Flip(ecran);
            break;

            case SDLK_w:
                if(p<n/2-1) p++;
                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                Y=p;  X=p;
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                           if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;
                    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    SDL_BlitSurface(cases[0],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    if(a==1) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-2]);
    else if(a==2) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2-1]);
    else if(a==3) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2]);
    else if(a==4) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+2][(n+n%2)/2+1]);
    else if(a==5) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+1][(n+n%2)/2-1]);
    else if(a==6) SDL_BlitSurface(cases[30],NULL,ecran,&casep[n+3][(n+n%2)/2-1]);

                SDL_Flip(ecran);
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
                X=(event.button.x - event.button.x%32)/32;
                Y=(event.button.y - event.button.y%32)/32;
            if(Y<n && X<n)
            {
                            if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                if(vu[x][y][z]==0)
                {
                    vu[x][y][z]=2;
                    SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                }
                else if(vu[x][y][z]==2)
                {
                    vu[x][y][z]=0;
                    SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                }
                SDL_Flip(ecran);
                x=0; y=0; z=0;
            }}
            else if(event.button.button==SDL_BUTTON_LEFT && e==1)     /// CLIC GAUCHE
            {
                X=(event.button.x - event.button.x%32)/32;
                Y=(event.button.y - event.button.y%32)/32;


                  if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}

                if(vu[x][y][z]==0) vus++;
                vu[x][y][z]=1;

                if(casen[x][y][z]==-1)          /// FIN DU JEU
                {
                    x=0; y=0; z=0;
                    while(z<n) {while(y<n)
                    {
                        while(x<n)
                        {
                            vu[x][y][z]=1;
                            x++;
                        }
                        y++;
                        x=0;
                    }
                    z++;
                    y=0;
                    }
                }
                else if(vus+mines==n*n*n)       /// WINNER + AFFICHAGE SCORE
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
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[x][y]);
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

                if(casen[x][y][z]==0)           /// ETALAGE SI CASE VIDE
                {
                    i=0; x=0; y=0; z=0;
                    while(i<50)
                    {
                        while(z<n) {
                        while(y<n)
                        {
                            while(x<n)
                            {
                                if(vu[x][y][z]==0)
                                {
                                         if(x>0   && y>0   && z>0   && casen[x-1][y-1][z-1]==0 && vu[x-1][y-1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   &&          z>0   && casen[x-1][y][z-1]==0   && vu[x-1][y][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   && y<n-1 && z>0   && casen[x-1][y+1][z-1]==0 && vu[x-1][y+1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y>0   && z>0   && casen[x][y-1][z-1]==0   && vu[x][y-1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y<n-1 && z>0   && casen[x][y+1][z-1]==0   && vu[x][y+1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y>0   && z>0   && casen[x+1][y-1][z-1]==0 && vu[x+1][y-1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 &&          z>0   && casen[x+1][y][z-1]==0   && vu[x+1][y][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y<n-1 && z>0   && casen[x+1][y+1][z-1]==0 && vu[x+1][y+1][z-1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   && y>0   &&          casen[x-1][y-1][z]==0   && vu[x-1][y-1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   &&                   casen[x-1][y][z]==0     && vu[x-1][y][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   && y<n-1 &&          casen[x-1][y+1][z]==0   && vu[x-1][y+1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y>0   &&          casen[x][y-1][z]==0     && vu[x][y-1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y<n-1 &&          casen[x][y+1][z]==0     && vu[x][y+1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y>0   &&          casen[x+1][y-1][z]==0   && vu[x+1][y-1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 &&                   casen[x+1][y][z]==0     && vu[x+1][y][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y<n-1 &&          casen[x+1][y+1][z]==0   && vu[x+1][y+1][z]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   && y>0   && z<n-1 && casen[x-1][y-1][z+1]==0 && vu[x-1][y-1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   &&          z<n-1 && casen[x-1][y][z+1]==0   && vu[x-1][y][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x>0   && y<n-1 && z<n-1 && casen[x-1][y+1][z+1]==0 && vu[x-1][y+1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y>0   && z<n-1 && casen[x][y-1][z+1]==0   && vu[x][y-1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(         y<n-1 && z<n-1 && casen[x][y+1][z+1]==0   && vu[x][y+1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y>0   && z<n-1 && casen[x+1][y-1][z+1]==0 && vu[x+1][y-1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 &&          z<n-1 && casen[x+1][y][z+1]==0   && vu[x+1][y][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(x<n-1 && y<n-1 && z<n-1 && casen[x+1][y+1][z+1]==0 && vu[x+1][y+1][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(                  z<n-1 && casen[x][y][z+1]==0     && vu[x][y][z+1]==1) { vu[x][y][z]=1; vus++; }
                                    else if(                  z>0   && casen[x][y][z-1]==0     && vu[x][y][z-1]==1) { vu[x][y][z]=1; vus++; }
                                }
                                x++;
                            }
                            x=0;
                            y++;
                        }
                        y=0;
                        z++;
                        }
                        z=0;
                        i++;
                    }
                }

                Y=p;  X=p;
                while(Y<n-p && e==1)          /// AFFICHAGE
                {
                    while(X<n-p)
                    {
                                 if(a==1) {x=X; y=p; z=n-Y-1;}
                            else if(a==2) {x=X; y=Y; z=p;}
                            else if(a==3) {x=X; y=n-p-1; z=Y;}
                            else if(a==4) {x=X; y=n-Y-1; z=n-p-1;}
                            else if(a==5) {x=p; y=Y; z=n-X-1;}
                            else if(a==6) {x=n-p-1; y=Y; z=X;}


                        if(vu[x][y][z]==0)
                            SDL_BlitSurface(cases[27],NULL,ecran,&casep[X][Y]);
                            else if(vu[x][y][z]==2)
                            SDL_BlitSurface(cases[30],NULL,ecran,&casep[X][Y]);
                        else if(casen[x][y][z]==-1 && vu[x][y][z]!=2)
                            SDL_BlitSurface(cases[28],NULL,ecran,&casep[X][Y]);
                        else if(vu[x][y][z]==1)
                            SDL_BlitSurface(cases[casen[x][y][z]],NULL,ecran,&casep[X][Y]);
                        X++;
                    }
                    Y++;
                    X=p;
                }
                Y=p;

                SDL_Flip(ecran);
            }
            break;

        }
    }
}
    SDL_FreeSurface(ecran);
    i=0;
    while(i<31)
    {
        SDL_FreeSurface(cases[i]);
        i++;
    }

     return 0;
}
