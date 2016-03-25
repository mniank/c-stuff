#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <math.h>
#include <fmod.h>
#include <SDL_getenv.h>

//****************************************************
//
//               One Shot for a lot
//
//              Par Maxime Niankouri
//
//                    FIN 2010
//
//****************************************************





int main ( int argc, char** argv )
{

    putenv("SDL_VIDEO_WINDOW_POS=center");



     int x[4],y[4],e=1,r[4], i=0,j=0,up=0,gtot=0,gx[80],gy[80],bm=0,bmax=1, temps=0, telemax=0,telex[12], teley[12],jx[4],jy[4];
     int mousex=0, mousey=0;

     float D[4],ax[4],ay[4],vx[4],vy[4],px[4],py[4],Dp[4], ix[4],iy[4];

    unsigned char casen[120][80];
    SDL_Surface *fond,*bloc,*target[4], *ecran, *ico,*ball[4], *titre,*cachecache, *cachenumber, *puits, *puitsneg, *cacheball, *teleport, *reset,*english,*francais;
    SDL_Rect casep[120][80], pos[4], cache, cachep[61], numberp[11],numbert[10],pressenter;

    SDL_Event event;



int lvl=0, cible[4], debloc=0,veriflvl=0, score=0,pause=1, fullscreen=0;
char lvls[12]="data\\1.yf";
char c='EOF';
FILE *level=NULL;



        SDL_Init(SDL_INIT_VIDEO);

    ico=SDL_LoadBMP("data\\00.yf");
    SDL_SetColorKey(ico, SDL_SRCCOLORKEY, SDL_MapRGB(ico->format, 255, 255, 255));
    SDL_WM_SetIcon(ico, NULL);

    ecran = SDL_SetVideoMode(960, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("One Shot for a lot 0.7", NULL);

    reset= SDL_LoadBMP("data\\-1.yf");
    english= SDL_LoadBMP("data\\-2.yf");
    francais= SDL_LoadBMP("data\\-3.yf");

    ball[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
    ball[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
    ball[2] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
    ball[3] = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));

    cacheball = SDL_CreateRGBSurface(SDL_HWSURFACE, 3, 3, 32, 0, 0, 0, 0);
    SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    bloc = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

    target[0] = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
    target[1] = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
    target[2] = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
    target[3] = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));

    fond = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    puits = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));
    puitsneg = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 255));

    teleport = SDL_CreateRGBSurface(SDL_HWSURFACE, 8, 8, 32, 0, 0, 0, 0);
    SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 167, 50, 200));


cible[0]=0; cible[1]=0; cible[2]=0; cible[3]=0;


/// ECRAN TITRE

i=0;
while(i<10)
{
    numberp[i].x=175+11*i; numberp[i].y=606;
    numbert[i].y=606; numbert[i].w=11;  numbert[i].h=15;
    i++;
}
numbert[1].x=302;
numbert[2].x=318;
numbert[3].x=333;
numbert[4].x=349;
numbert[5].x=363;
numbert[6].x=378;
numbert[7].x=394;
numbert[8].x=410;
numbert[9].x=426;

numberp[10].x=302;   numberp[10].y=606;
i=0;


casep[59][76].x=472;   casep[59][76].y=608;
pressenter.w=126;    pressenter.h=14;   pressenter.x=472;   pressenter.y=608;


    cachep[0].x= 960-70;
    cachep[0].y=0;
    i=1;
    while(i<61)
    {
        if(i<51)
        {
            cachep[i].x=131+70*((i-1)%10);
            cachep[i].y=241+70*((i-1)-(i-1)%10)/10;
        }
        else if(i<56)
        {
            cachep[i].x=37;
            cachep[i].y=241+70*(i-51);
        }
        else
        {
            cachep[i].x=854;
            cachep[i].y=241+70*(i-56);
        }
        i++;
    }

  // Chercher niveau débloqué dans 2.yf (trois derniers caractères) ( ordre AZERTYUIOP)

  level=fopen("data\\2.yf","r");
  fseek(level, -6, SEEK_END);
  switch(fgetc(level))
    {
        case 'A': debloc=0*100+debloc; break;
        case 'Z': debloc=1*100+debloc; break;
        case 'E': debloc=2*100+debloc; break;
        case 'R': debloc=3*100+debloc; break;
        case 'T': debloc=4*100+debloc; break;
        case 'Y': debloc=5*100+debloc; break;
        case 'U': debloc=6*100+debloc; break;
        case 'I': debloc=7*100+debloc; break;
        case 'O': debloc=8*100+debloc; break;
        case 'P': debloc=9*100+debloc; break;
    }
  switch(fgetc(level))
    {
        case 'A': debloc=0*10+debloc; break;
        case 'Z': debloc=1*10+debloc; break;
        case 'E': debloc=2*10+debloc; break;
        case 'R': debloc=3*10+debloc; break;
        case 'T': debloc=4*10+debloc; break;
        case 'Y': debloc=5*10+debloc; break;
        case 'U': debloc=6*10+debloc; break;
        case 'I': debloc=7*10+debloc; break;
        case 'O': debloc=8*10+debloc; break;
        case 'P': debloc=9*10+debloc; break;
    }
  switch(fgetc(level))
    {
        case 'A': debloc=0+debloc; break;
        case 'Z': debloc=1+debloc; break;
        case 'E': debloc=2+debloc; break;
        case 'R': debloc=3+debloc; break;
        case 'T': debloc=4+debloc; break;
        case 'Y': debloc=5+debloc; break;
        case 'U': debloc=6+debloc; break;
        case 'I': debloc=7+debloc; break;
        case 'O': debloc=8+debloc; break;
        case 'P': debloc=9+debloc; break;
    }
    fclose(level);
    level=NULL;
    i=debloc+1;


    cachecache=SDL_CreateRGBSurface(SDL_HWSURFACE, 70, 70, 32, 0, 0, 0, 0);
    cachenumber=SDL_CreateRGBSurface(SDL_HWSURFACE, 135, 15, 32, 0, 0, 0, 0);
    SDL_FillRect(cachecache, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_FillRect(cachenumber, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

    cache.x=960-70; cache.y=0;     cache.w=70;    cache.h=70;

    titre = SDL_LoadBMP("data\\0.yf");
    SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
    SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
    SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
    SDL_BlitSurface(cachenumber,NULL,ecran,&casep[59][76]);
    while(i<61)
    {
         SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
         i++;
    }
    i=0;

    level=fopen("data\\36.yf","r");
    fseek(level,-13,SEEK_END);

        i--;
          switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*1000000000+score; break;
        case 'E': score=2*1000000000+score; break;
        case 'R': score=3*1000000000+score; break;
        case 'T': score=4*1000000000+score; break;
        case 'Y': score=5*1000000000+score; break;
        case 'U': score=6*1000000000+score; break;
        case 'I': score=7*1000000000+score; break;
        case 'O': score=8*1000000000+score; break;
        case 'P': score=9*1000000000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*100000000+score; break;
        case 'E': score=2*100000000+score; break;
        case 'R': score=3*100000000+score; break;
        case 'T': score=4*100000000+score; break;
        case 'Y': score=5*100000000+score; break;
        case 'U': score=6*100000000+score; break;
        case 'I': score=7*100000000+score; break;
        case 'O': score=8*100000000+score; break;
        case 'P': score=9*100000000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*10000000+score; break;
        case 'E': score=2*10000000+score; break;
        case 'R': score=3*10000000+score; break;
        case 'T': score=4*10000000+score; break;
        case 'Y': score=5*10000000+score; break;
        case 'U': score=6*10000000+score; break;
        case 'I': score=7*10000000+score; break;
        case 'O': score=8*10000000+score; break;
        case 'P': score=9*10000000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*1000000+score; break;
        case 'E': score=2*1000000+score; break;
        case 'R': score=3*1000000+score; break;
        case 'T': score=4*1000000+score; break;
        case 'Y': score=5*1000000+score; break;
        case 'U': score=6*1000000+score; break;
        case 'I': score=7*1000000+score; break;
        case 'O': score=8*1000000+score; break;
        case 'P': score=9*1000000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*100000+score; break;
        case 'E': score=2*100000+score; break;
        case 'R': score=3*100000+score; break;
        case 'T': score=4*100000+score; break;
        case 'Y': score=5*100000+score; break;
        case 'U': score=6*100000+score; break;
        case 'I': score=7*100000+score; break;
        case 'O': score=8*100000+score; break;
        case 'P': score=9*100000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*10000+score; break;
        case 'E': score=2*10000+score; break;
        case 'R': score=3*10000+score; break;
        case 'T': score=4*10000+score; break;
        case 'Y': score=5*10000+score; break;
        case 'U': score=6*10000+score; break;
        case 'I': score=7*10000+score; break;
        case 'O': score=8*10000+score; break;
        case 'P': score=9*10000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*1000+score; break;
        case 'E': score=2*1000+score; break;
        case 'R': score=3*1000+score; break;
        case 'T': score=4*1000+score; break;
        case 'Y': score=5*1000+score; break;
        case 'U': score=6*1000+score; break;
        case 'I': score=7*1000+score; break;
        case 'O': score=8*1000+score; break;
        case 'P': score=9*1000+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*100+score; break;
        case 'E': score=2*100+score; break;
        case 'R': score=3*100+score; break;
        case 'T': score=4*100+score; break;
        case 'Y': score=5*100+score; break;
        case 'U': score=6*100+score; break;
        case 'I': score=7*100+score; break;
        case 'O': score=8*100+score; break;
        case 'P': score=9*100+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1*10+score; break;
        case 'E': score=2*10+score; break;
        case 'R': score=3*10+score; break;
        case 'T': score=4*10+score; break;
        case 'Y': score=5*10+score; break;
        case 'U': score=6*10+score; break;
        case 'I': score=7*10+score; break;
        case 'O': score=8*10+score; break;
        case 'P': score=9*10+score; break;
    }
    switch(fgetc(level))
    {
        case 'A': score=0+score; break;
        case 'Z': score=1+score; break;
        case 'E': score=2+score; break;
        case 'R': score=3+score; break;
        case 'T': score=4+score; break;
        case 'Y': score=5+score; break;
        case 'U': score=6+score; break;
        case 'I': score=7+score; break;
        case 'O': score=8+score; break;
        case 'P': score=9+score; break;
    }

    fclose(level);
    level=NULL;

    i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;
    SDL_Flip(ecran);












    /// Son


    FMOD_SYSTEM *system;
	FMOD_SOUND *musique;
	int musiccours=61;

   	FMOD_System_Create(&system);
	FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(system, "data\\61.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
	FMOD_Sound_SetLoopCount(musique, -1);
	FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);



















    while(e)
    {

        if(up==0 && lvl>0)
        {
                        while(j<80)
                        {
                            while(i<120)
                            {
                                 if(casen[i][j]==20) { casen[i][j]=2; cible[0]++;}
                                 else if(casen[i][j]==50) { casen[i][j]=5; cible[1]++;}
                                 else if(casen[i][j]==60) { casen[i][j]=6; cible[2]++;}
                                 else if(casen[i][j]==70) { casen[i][j]=7; cible[3]++;}
                                if(casen[i][j]==1) SDL_BlitSurface(bloc,NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==2) SDL_BlitSurface(target[0],NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==3) SDL_BlitSurface(puits,NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==4) SDL_BlitSurface(puitsneg,NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==5) SDL_BlitSurface(target[1],NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==6) SDL_BlitSurface(target[2],NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==7) SDL_BlitSurface(target[3],NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]==0) SDL_BlitSurface(fond,NULL,ecran,&casep[i][j]);
                                else if(casen[i][j]>99 && casen[i][j]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[i][j]);
                                i++;
                            }
                            j++;
                            i=0;
                        }
                        j=0;



                            if(bmax>0) SDL_BlitSurface(target[0],NULL,ecran,&casep[0][79]);
                            if(bmax>1) SDL_BlitSurface(target[1],NULL,ecran,&casep[119][79]);
                            if(bmax>2) SDL_BlitSurface(target[2],NULL,ecran,&casep[0][0]);
                            if(bmax>3) SDL_BlitSurface(target[3],NULL,ecran,&casep[119][0]);




                        SDL_Flip(ecran);
        }


if(fullscreen && event.motion.x==448 && event.motion.y==256) SDL_WarpMouse(mousex,mousey);     // Empeche la téléportation de la souris en fullscreen
mousex=event.motion.x;
mousey=event.motion.y;


        SDL_EventState(SDL_VIDEORESIZE,1);
        SDL_EventState(SDL_VIDEOEXPOSE,1);
        SDL_EventState(SDL_MOUSEBUTTONDOWN,1);
        SDL_EventState(SDL_KEYDOWN,1);
        SDL_EventState(SDL_MOUSEBUTTONUP,1);
        SDL_EventState(SDL_KEYUP,1);
        SDL_EventState(SDL_QUIT,1);



        SDL_WaitEvent(&event);



        SDL_ShowCursor(0);
        SDL_EventState(SDL_MOUSEBUTTONDOWN,0);
        SDL_EventState(SDL_KEYDOWN,0);
        SDL_EventState(SDL_MOUSEBUTTONUP,0);
        SDL_EventState(SDL_KEYUP,0);
        SDL_EventState(SDL_QUIT,0);
        SDL_EventState(SDL_VIDEORESIZE,0);
        SDL_EventState(SDL_VIDEOEXPOSE,0);






        switch(event.key.keysym.sym)
        {
            case SDLK_F4:
                if(event.type==SDL_KEYUP) e=0;
            break;

            case SDLK_F1:
                if(event.type==SDL_KEYUP)
                {
                    if(fullscreen) {      ecran = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);                   fullscreen=0; }
                    else           {      ecran = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);  fullscreen=1; }


                    if(lvl<=0)
                    {
                        lvl=0;

                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;
                  i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;

                    }

                    SDL_Flip(ecran);
                }
            break;

            case SDLK_p:
                if(event.type==SDL_KEYUP)
                {
                    FMOD_CHANNELGROUP *canal;
                    FMOD_BOOL etat;
                    FMOD_System_GetMasterChannelGroup(system, &canal);
                    FMOD_ChannelGroup_GetPaused(canal, &etat);

                    if (etat)
                    {
                         FMOD_ChannelGroup_SetPaused(canal, 0);
                         pause=1;
                         FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                    }
                    else
                    {  FMOD_ChannelGroup_SetPaused(canal, 1); pause=0; }
                }
            break;


            case SDLK_ESCAPE:
if(event.type==SDL_KEYUP)
{

    bm=0; bmax=1;
    if(musiccours!=61)
    {
    FMOD_System_CreateSound(system, "data\\61.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
	FMOD_Sound_SetLoopCount(musique, -1);
	if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
	musiccours=61;
    }
                SDL_WM_SetCaption("One Shot for a lot 0.7", NULL);
                lvl=0;
                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;
                  i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;

                SDL_Flip(ecran);
}

            break;





            case SDLK_RETURN:
if(event.type==SDL_KEYUP && lvl>0)
{
                        if(up) lvl++;

                        if(debloc<lvl)                        /// SAVE la progression
                        {
                            debloc++;
    /// NIVEAUX BONUS DU SCORE
    if(lvl==52 && score>999999998) debloc--;
    else if(lvl==53 && score>1000000) debloc--;
    else if(lvl==54 && score>100000) debloc--;
    else if(lvl==55 && score>30000) debloc--;
    else if(lvl==56 && score>10000) debloc--;
    else if(lvl==57 && score>5000) debloc--;
    else if(lvl==58 && score>1000) debloc--;
    else if(lvl==59 && score>400) debloc--;
    else if(lvl==60 && score>91) debloc--;




                              level=fopen("data\\2.yf","r+");
  fseek(level, -6, SEEK_END);
  switch(debloc/100)
    {
        case 0: fputc('A',level); break;
        case 1: fputc('Z',level); break;
        case 2: fputc('E',level); break;
        case 3: fputc('R',level); break;
        case 4: fputc('T',level); break;
        case 5: fputc('Y',level); break;
        case 6: fputc('U',level); break;
        case 7: fputc('I',level); break;
        case 8: fputc('O',level); break;
        case 9: fputc('P',level); break;
    }
  switch((debloc%100)/10)
    {
        case 0: fputc('A',level); break;
        case 1: fputc('Z',level); break;
        case 2: fputc('E',level); break;
        case 3: fputc('R',level); break;
        case 4: fputc('T',level); break;
        case 5: fputc('Y',level); break;
        case 6: fputc('U',level); break;
        case 7: fputc('I',level); break;
        case 8: fputc('O',level); break;
        case 9: fputc('P',level); break;
    }
  switch(debloc%10)
    {
        case 0: fputc('A',level); break;
        case 1: fputc('Z',level); break;
        case 2: fputc('E',level); break;
        case 3: fputc('R',level); break;
        case 4: fputc('T',level); break;
        case 5: fputc('Y',level); break;
        case 6: fputc('U',level); break;
        case 7: fputc('I',level); break;
        case 8: fputc('O',level); break;
        case 9: fputc('P',level); break;
    }
    fclose(level);
    level=NULL;

                        }

                        switch(lvl)                                                                  /// Lancement du nouveau lvl
                        {
                            case 1: SDL_WM_SetCaption("Level 1 : Just touch it", NULL); break;
                            case 2: SDL_WM_SetCaption("Level 2 : Just touch them", NULL); break;
                            case 3: SDL_WM_SetCaption("Level 3 : Coco", NULL); break;
                            case 4: SDL_WM_SetCaption("Level 4 : PiR", NULL); break;
                            case 5: SDL_WM_SetCaption("Level 5 : Kleber Tower", NULL); break;
                            case 6: SDL_WM_SetCaption("Level 6 : Snow", NULL); break;
                            case 7: SDL_WM_SetCaption("Level 7 : Integral", NULL); break;
                            case 8: SDL_WM_SetCaption("Level 8 : Exclamation", NULL); break;
                            case 9: SDL_WM_SetCaption("Level 9 : Pool", NULL); break;
                            case 10: SDL_WM_SetCaption("Level 10 : The first one", NULL); break;
                            case 11: SDL_WM_SetCaption("Level 11 : Crazy", NULL); break;
                            case 12: SDL_WM_SetCaption("Level 12 : MPSI2", NULL); break;
                            case 13: SDL_WM_SetCaption("Level 13 : Trust", NULL); break;
                            case 14: SDL_WM_SetCaption("Level 14 : The last ...", NULL); break;
                            case 15: SDL_WM_SetCaption("Level 15 : Fifteen", NULL); break;
                            case 16: SDL_WM_SetCaption("Level 16 : Post-Gravity", NULL); break;
                            case 17: SDL_WM_SetCaption("Level 17 : Gravity", NULL); break;
                            case 18: SDL_WM_SetCaption("Level 18 : Bermuda", NULL); break;
                            case 19: SDL_WM_SetCaption("Level 19 : Easy", NULL); break;
                            case 20: SDL_WM_SetCaption("Level 20 : Double 0", NULL); break;
                            case 21: SDL_WM_SetCaption("Level 21 : Reversed", NULL); break;
                            case 22: SDL_WM_SetCaption("Level 22 : Effect", NULL); break;
                            case 23: SDL_WM_SetCaption("Level 23 : Corner", NULL); break;
                            case 24: SDL_WM_SetCaption("Level 24 : Arrow", NULL); break;
                            case 25: SDL_WM_SetCaption("Level 25 : Insane", NULL); break;
                            case 26: SDL_WM_SetCaption("Level 26 : ?", NULL); break;
                            case 27: SDL_WM_SetCaption("Level 27 : No name", NULL); break;
                            case 28: SDL_WM_SetCaption("Level 28 : Tank", NULL); break;
                            case 29: SDL_WM_SetCaption("Level 29 : Double", NULL); break;
                            case 30: SDL_WM_SetCaption("Level 30 : Triple", NULL); break;
                            case 31: SDL_WM_SetCaption("Level 31 : Timing", NULL); break;
                            case 32: SDL_WM_SetCaption("Level 32 : Magnet", NULL); break;
                            case 33: SDL_WM_SetCaption("Level 33 : Storm", NULL); break;
                            case 34: SDL_WM_SetCaption("Level 34 : Wind", NULL); break;
                            case 35: SDL_WM_SetCaption("Level 35 : Rain", NULL); break;
                            case 36: SDL_WM_SetCaption("Level 36 : Star", NULL); break;
                            case 37: SDL_WM_SetCaption("Level 37 : Trajectory", NULL); break;
                            case 38: SDL_WM_SetCaption("Level 38 : Ultime frontier", NULL); break;
                            case 39: SDL_WM_SetCaption("Level 39 : On fire", NULL); break;
                            case 40: SDL_WM_SetCaption("Level 40 : Teleportation", NULL); break;
                            case 41: SDL_WM_SetCaption("Level 41 : Bazar", NULL); break;
                            case 42: SDL_WM_SetCaption("Level 42 : The answer is ...", NULL); break;
                            case 43: SDL_WM_SetCaption("Level 43 : Cell", NULL); break;
                            case 44: SDL_WM_SetCaption("Level 44 : Pong", NULL); break;
                            case 45: SDL_WM_SetCaption("Level 45 : Thermo", NULL); break;
                            case 46: SDL_WM_SetCaption("Level 46 : Minesfield", NULL); break;
                            case 47: SDL_WM_SetCaption("Level 47 : Superlevel", NULL); break;
                            case 48: SDL_WM_SetCaption("Level 48 : Spiral", NULL); break;
                            case 49: SDL_WM_SetCaption("Level 49 : Infinity", NULL); break;
                            case 50: SDL_WM_SetCaption("Level 50 : Random", NULL); break;

                            case 51: SDL_WM_SetCaption("Level A : You beat the game", NULL); break;
                            case 52: SDL_WM_SetCaption("Level B : Poor - 999 999 998", NULL); break;
                            case 53: SDL_WM_SetCaption("Level C : Weak - 1 000 000", NULL); break;
                            case 54: SDL_WM_SetCaption("Level D : Okay - 100 000", NULL); break;
                            case 55: SDL_WM_SetCaption("Level E : Well - 30 000", NULL); break;
                            case 56: SDL_WM_SetCaption("Level F : Nice - 10 000", NULL); break;
                            case 57: SDL_WM_SetCaption("Level G : Great - 5 000", NULL); break;
                            case 58: SDL_WM_SetCaption("Level H : Pro - 1 000", NULL); break;
                            case 59: SDL_WM_SetCaption("Level I : Insane - 400", NULL); break;
                            case 60: SDL_WM_SetCaption("Level J : Cheater - 91", NULL); break;
                        }
                        up=0;
                        sprintf(lvls, "data\\%d.yf", lvl);
                        level=fopen(lvls,"r");


veriflvl=0;
                        fseek(level, -3, SEEK_END);
  switch(fgetc(level))
    {
        case 'A': veriflvl=0*100+veriflvl; break;
        case 'Z': veriflvl=1*100+veriflvl; break;
        case 'E': veriflvl=2*100+veriflvl; break;
        case 'R': veriflvl=3*100+veriflvl; break;
        case 'T': veriflvl=4*100+veriflvl; break;
        case 'Y': veriflvl=5*100+veriflvl; break;
        case 'U': veriflvl=6*100+veriflvl; break;
        case 'I': veriflvl=7*100+veriflvl; break;
        case 'O': veriflvl=8*100+veriflvl; break;
        case 'P': veriflvl=9*100+veriflvl; break;
    }
  switch(fgetc(level))
    {
        case 'A': veriflvl=0*10+veriflvl; break;
        case 'Z': veriflvl=1*10+veriflvl; break;
        case 'E': veriflvl=2*10+veriflvl; break;
        case 'R': veriflvl=3*10+veriflvl; break;
        case 'T': veriflvl=4*10+veriflvl; break;
        case 'Y': veriflvl=5*10+veriflvl; break;
        case 'U': veriflvl=6*10+veriflvl; break;
        case 'I': veriflvl=7*10+veriflvl; break;
        case 'O': veriflvl=8*10+veriflvl; break;
        case 'P': veriflvl=9*10+veriflvl; break;
    }
  switch(fgetc(level))
    {
        case 'A': veriflvl=0+veriflvl; break;
        case 'Z': veriflvl=1+veriflvl; break;
        case 'E': veriflvl=2+veriflvl; break;
        case 'R': veriflvl=3+veriflvl; break;
        case 'T': veriflvl=4+veriflvl; break;
        case 'Y': veriflvl=5+veriflvl; break;
        case 'U': veriflvl=6+veriflvl; break;
        case 'I': veriflvl=7+veriflvl; break;
        case 'O': veriflvl=8+veriflvl; break;
        case 'P': veriflvl=9+veriflvl; break;
    }

     if(veriflvl!=lvl)   return 960;
fseek(level, 0, SEEK_SET);


                        if(level==NULL) return 15;
                        cible[0]=0; cible[1]=0; cible[2]=0; cible[3]=0; bmax=1; telemax=0;

                        if(lvl>0 && lvl<=10)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

                            if(musiccours!=62)
                            {
                            FMOD_System_CreateSound(system, "data\\62.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=62;
                            }

                        }
                        if(lvl>10 && lvl<=20)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 56, 232));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 205, 205, 205));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 205, 205, 205));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 56, 232));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

                            if(musiccours!=63)
                            {
                            FMOD_System_CreateSound(system, "data\\63.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=63;
                            }
                        }
                        else if(lvl>20 && lvl<=28)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=64)
                            {
                            FMOD_System_CreateSound(system, "data\\64.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=64;
                            }
                        }
                        else if(lvl==29 || lvl==30)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 0, 200, 0));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 0, 0, 128));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 128, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 128, 128, 128));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 128, 128, 128));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 0, 200, 0));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 0, 0, 128));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=65)
                            {
                            FMOD_System_CreateSound(system, "data\\65.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=65;
                            }
                        }
                        else if(lvl>30 && lvl<=39)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 240, 240, 240));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 15, 15, 15));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 15, 15, 15));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=66)
                            {
                            FMOD_System_CreateSound(system, "data\\66.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=66;
                            }
                        }
                        else if(lvl==47)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 50, 50, 50));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 100, 100, 100));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 150, 150, 150));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 50, 50, 50));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 100, 100, 100));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 150, 150, 150));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 175, 0));

                            if(musiccours!=67)
                            {
                            FMOD_System_CreateSound(system, "data\\67.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=67;
                            }

                        }
                        else if(lvl>39 && lvl<=50)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 227, 174, 201));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 112, 146, 190));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 135, 72, 37));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 135, 72, 37));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 227, 174, 201));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 237, 28, 36));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 63, 72, 204));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 127, 39));

                            if(musiccours!=68)
                            {
                            FMOD_System_CreateSound(system, "data\\68.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=68;
                            }

                        }
                        else if(lvl>50)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 4, 147, 46));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 14, 157, 56));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 24, 167, 66));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 185, 122, 87));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 239, 228, 176));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 239, 228, 176));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 4, 147, 46));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 14, 157, 56));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 24, 167, 66));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 237, 28, 36));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 63, 72, 204));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 127, 39));

                            if(musiccours!=69)
                            {
                            FMOD_System_CreateSound(system, "data\\69.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=69;
                            }

                        }

                        i=0;j=0;

                        gtot=0;
                        while(j<80)
    {
        while(i<120)
        {
            c=fgetc(level);

            casep[i][j].y=8*j;
            casep[i][j].x=8*i;
            if(c=='0')casen[i][j]=0;
            else if(c=='1')casen[i][j]=1;
            else if(c=='2'){casen[i][j]=2;cible[0]++;}
            else if(c=='3') { casen[i][j]=3; gx[gtot]=i*8; gy[gtot]=j*8; gtot++; }
            else if(c=='4') { casen[i][j]=4; gx[gtot]=-i*8; gy[gtot]=-j*8; gtot++; }
            else if(c=='5'){casen[i][j]=5;cible[1]++; if(bmax<2) bmax=2;}
            else if(c=='6'){casen[i][j]=6;cible[2]++; if(bmax<3) bmax=3;}
            else if(c=='7'){casen[i][j]=7;cible[3]++; if(bmax<4) bmax=4;}
            else if(c=='A'){casen[i][j]=100; if(telemax<0) telemax=0; telex[0]=i*8; teley[0]=j*8;}
            else if(c=='B'){casen[i][j]=101; if(telemax<1) telemax=1; telex[1]=i*8; teley[1]=j*8;}
            else if(c=='C'){casen[i][j]=102; if(telemax<2) telemax=2; telex[2]=i*8; teley[2]=j*8;}
            else if(c=='D'){casen[i][j]=103; if(telemax<3) telemax=3; telex[3]=i*8; teley[3]=j*8;}
            else if(c=='E'){casen[i][j]=104; if(telemax<4) telemax=4; telex[4]=i*8; teley[4]=j*8;}
            else if(c=='F'){casen[i][j]=105; if(telemax<5) telemax=5; telex[5]=i*8; teley[5]=j*8;}
            else if(c=='G'){casen[i][j]=106; if(telemax<6) telemax=6; telex[6]=i*8; teley[6]=j*8;}
            else if(c=='H'){casen[i][j]=107; if(telemax<7) telemax=7; telex[7]=i*8; teley[7]=j*8;}
            else if(c=='I'){casen[i][j]=108; if(telemax<8) telemax=8; telex[8]=i*8; teley[8]=j*8;}
            else if(c=='J'){casen[i][j]=109; if(telemax<9) telemax=9; telex[9]=i*8; teley[9]=j*8;}
            else if(c=='K'){casen[i][j]=110; if(telemax<10) telemax=10; telex[10]=i*8; teley[10]=j*8;}
            else if(c=='L'){casen[i][j]=111; if(telemax<11) telemax=11; telex[11]=i*8; teley[11]=j*8;}
            else return 85;
            i++;
        }
        j++;
        i=0;
    }
    j=0;



                        fclose(level);
}

    break;

        }
        switch(event.type)
        {

            case SDL_QUIT:
                e = 0;
            break;


            case SDL_MOUSEBUTTONUP:

            if(event.button.button==SDL_BUTTON_LEFT && e==1 && (lvl==-2 || lvl==-3))
            {
                if(event.button.x>=839 && event.button.x<=952 && event.button.y>=18 && event.button.y<=54 && lvl==-2 )     /// Francais
                {
                    lvl=-3;
                    SDL_BlitSurface(francais,NULL,ecran,&casep[0][0]);
                    SDL_Flip(ecran);

                }
                else if(event.button.x>=8 && event.button.x<=99 && event.button.y>=15 && event.button.y<=47 && lvl==-3 )     /// English
                {
                    lvl=-2;
                    SDL_BlitSurface(english,NULL,ecran,&casep[0][0]);
                    SDL_Flip(ecran);

                }
                else if(event.button.x>=868 && event.button.x<=960 && event.button.y>=570 && event.button.y<=640 )     /// Main menu
                {
                    lvl=0;
                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;
                  i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;

                SDL_Flip(ecran);
                }
            }

            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==0 && event.button.x>=895 && event.button.x<=960 && event.button.y>=604 && event.button.y<=640)   /// CLIC SUR HELP
            {
               lvl=-2;
               SDL_BlitSurface(english,NULL,ecran,&casep[0][0]);
               SDL_Flip(ecran);

            }
            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==0 && event.button.x>=825 && event.button.x<=886 && event.button.y>=613 && event.button.y<=633)   /// CLIC SUR RESET
            {
               lvl=-1;
               SDL_BlitSurface(reset,NULL,ecran,&casep[0][0]);
               SDL_Flip(ecran);

            }
            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==0 && event.button.x>=648 && event.button.x<=748 && event.button.y>=611 && event.button.y<=634)   /// CLIC SUR FULLSCREEN
            {
              if(fullscreen) {      ecran = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);                   fullscreen=0; }
                    else           {      ecran = SDL_SetVideoMode(0, 0, 0, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);  fullscreen=1; }


                    if(lvl==0)
                    {

                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;
                  i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;

                    }

                    SDL_Flip(ecran);

            }
            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==0 && event.button.x>=759 && event.button.x<=812 && event.button.y>=611 && event.button.y<=634)   /// CLIC SUR MUTE
            {
                    FMOD_CHANNELGROUP *canal;
                    FMOD_BOOL etat;
                    FMOD_System_GetMasterChannelGroup(system, &canal);
                    FMOD_ChannelGroup_GetPaused(canal, &etat);

                    if (etat)
                    {
                         FMOD_ChannelGroup_SetPaused(canal, 0);
                         pause=1;
                         FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                    }
                    else
                    {  FMOD_ChannelGroup_SetPaused(canal, 1); pause=0; }

            }

            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==-1)    /// ECRAN RESET
            {

                if(event.button.x>=504 && event.button.x<=634 && event.button.y>=416 && event.button.y<=497 )     /// NO
                {


                lvl=0;
                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;
                  i=(score/1000000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[0]);
    i=(score/100000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[1]);
    i=(score/10000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[2]);
    i=(score/1000000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[3]);
    i=(score/100000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[4]);
    i=(score/10000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[5]);
    i=(score/1000)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[6]);
    i=(score/100)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[7]);
    i=(score/10)%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[8]);
    i=score%10;
    if(i!=0) SDL_BlitSurface(titre,&numbert[i],ecran,&numberp[9]);


i=0;

                SDL_Flip(ecran);
                }



                else if(event.button.x>=252 && event.button.x<=418 && event.button.y>=415 && event.button.y<=502 )                     /// YES
                {
                    score=0;
                    debloc=1;

                    level=fopen("data\\2.yf","r+");
                    fseek(level, -6, SEEK_END);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('Z',level);
                    fclose(level);

                    level=fopen("data\\36.yf","r+");
                    fseek(level,-13,SEEK_END);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fputc('A',level);
                    fclose(level);

                lvl=0;
                i=debloc+1;
                SDL_BlitSurface(titre,NULL,ecran,&casep[0][0]);
                SDL_BlitSurface(cachecache,NULL,ecran,&cachep[0]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&numberp[10]);
                SDL_BlitSurface(cachenumber,NULL,ecran,&casep[472/8][608/8]);

                while(i<61)
                {
                    SDL_BlitSurface(titre,&cache,ecran,&cachep[i]);
                    i++;
                }
                i=0;

                SDL_Flip(ecran);

                }

            }


            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl==0)    /// ECRAN TITRE
            {
                i=1;
                while(i<=debloc && lvl==0)
                {
                    if(event.button.y>=cachep[i].y && event.button.y<cachep[i].y+70 && event.button.x>=cachep[i].x && event.button.x<cachep[i].x+70)
                    lvl=i;
                    i++;
                }
if(lvl!=0)
{
                        switch(lvl)
                        {
                            case 1: SDL_WM_SetCaption("Level 1 : Just touch it", NULL); break;
                            case 2: SDL_WM_SetCaption("Level 2 : Just touch them", NULL); break;
                            case 3: SDL_WM_SetCaption("Level 3 : Coco", NULL); break;
                            case 4: SDL_WM_SetCaption("Level 4 : PiR", NULL); break;
                            case 5: SDL_WM_SetCaption("Level 5 : Kleber Tower", NULL); break;
                            case 6: SDL_WM_SetCaption("Level 6 : Snow", NULL); break;
                            case 7: SDL_WM_SetCaption("Level 7 : Integral", NULL); break;
                            case 8: SDL_WM_SetCaption("Level 8 : Exclamation", NULL); break;
                            case 9: SDL_WM_SetCaption("Level 9 : Pool", NULL); break;
                            case 10: SDL_WM_SetCaption("Level 10 : The first one", NULL); break;
                            case 11: SDL_WM_SetCaption("Level 11 : Crazy", NULL); break;
                            case 12: SDL_WM_SetCaption("Level 12 : MPSI2", NULL); break;
                            case 13: SDL_WM_SetCaption("Level 13 : Trust", NULL); break;
                            case 14: SDL_WM_SetCaption("Level 14 : The last ...", NULL); break;
                            case 15: SDL_WM_SetCaption("Level 15 : Fifteen", NULL); break;
                            case 16: SDL_WM_SetCaption("Level 16 : Post-Gravity", NULL); break;
                            case 17: SDL_WM_SetCaption("Level 17 : Gravity", NULL); break;
                            case 18: SDL_WM_SetCaption("Level 18 : Bermuda", NULL); break;
                            case 19: SDL_WM_SetCaption("Level 19 : Easy", NULL); break;
                            case 20: SDL_WM_SetCaption("Level 20 : Double 0", NULL); break;
                            case 21: SDL_WM_SetCaption("Level 21 : Reversed", NULL); break;
                            case 22: SDL_WM_SetCaption("Level 22 : Effect", NULL); break;
                            case 23: SDL_WM_SetCaption("Level 23 : Corner", NULL); break;
                            case 24: SDL_WM_SetCaption("Level 24 : Arrow", NULL); break;
                            case 25: SDL_WM_SetCaption("Level 25 : Insane", NULL); break;
                            case 26: SDL_WM_SetCaption("Level 26 : ?", NULL); break;
                            case 27: SDL_WM_SetCaption("Level 27 : No name", NULL); break;
                            case 28: SDL_WM_SetCaption("Level 28 : Tank", NULL); break;
                            case 29: SDL_WM_SetCaption("Level 29 : Double", NULL); break;
                            case 30: SDL_WM_SetCaption("Level 30 : Triple", NULL); break;
                            case 31: SDL_WM_SetCaption("Level 31 : Timing", NULL); break;
                            case 32: SDL_WM_SetCaption("Level 32 : Magnet", NULL); break;
                            case 33: SDL_WM_SetCaption("Level 33 : Storm", NULL); break;
                            case 34: SDL_WM_SetCaption("Level 34 : Wind", NULL); break;
                            case 35: SDL_WM_SetCaption("Level 35 : Rain", NULL); break;
                            case 36: SDL_WM_SetCaption("Level 36 : Star", NULL); break;
                            case 37: SDL_WM_SetCaption("Level 37 : Trajectory", NULL); break;
                            case 38: SDL_WM_SetCaption("Level 38 : Ultime frontier", NULL); break;
                            case 39: SDL_WM_SetCaption("Level 39 : On fire", NULL); break;
                            case 40: SDL_WM_SetCaption("Level 40 : Teleportation", NULL); break;
                            case 41: SDL_WM_SetCaption("Level 41 : Bazar", NULL); break;
                            case 42: SDL_WM_SetCaption("Level 42 : The answer is ...", NULL); break;
                            case 43: SDL_WM_SetCaption("Level 43 : Cell", NULL); break;
                            case 44: SDL_WM_SetCaption("Level 44 : Pong", NULL); break;
                            case 45: SDL_WM_SetCaption("Level 45 : Thermo", NULL); break;
                            case 46: SDL_WM_SetCaption("Level 46 : Minesfield", NULL); break;
                            case 47: SDL_WM_SetCaption("Level 47 : Superlevel", NULL); break;
                            case 48: SDL_WM_SetCaption("Level 48 : Spiral", NULL); break;
                            case 49: SDL_WM_SetCaption("Level 49 : Infinity", NULL); break;
                            case 50: SDL_WM_SetCaption("Level 50 : Random", NULL); break;

                            case 51: SDL_WM_SetCaption("Level A : You beat the game", NULL); break;
                            case 52: SDL_WM_SetCaption("Level B : Poor - 999 999 999", NULL); break;
                            case 53: SDL_WM_SetCaption("Level C : Weak - 1 000 000", NULL); break;
                            case 54: SDL_WM_SetCaption("Level D : Okay - 100 000", NULL); break;
                            case 55: SDL_WM_SetCaption("Level E : Well - 30 000", NULL); break;
                            case 56: SDL_WM_SetCaption("Level F : Nice - 10 000", NULL); break;
                            case 57: SDL_WM_SetCaption("Level G : Great - 5 000", NULL); break;
                            case 58: SDL_WM_SetCaption("Level H : Pro - 1 000", NULL); break;
                            case 59: SDL_WM_SetCaption("Level I : Insane - 400", NULL); break;
                            case 60: SDL_WM_SetCaption("Level J : Cheater - 91", NULL); break;
                        }
                        up=0;
                        sprintf(lvls, "data\\%d.yf", lvl);
                        level=fopen(lvls,"r");

    veriflvl=0;
                        fseek(level, -3, SEEK_END);
  switch(fgetc(level))
    {
        case 'A': veriflvl=0*100+veriflvl; break;
        case 'Z': veriflvl=1*100+veriflvl; break;
        case 'E': veriflvl=2*100+veriflvl; break;
        case 'R': veriflvl=3*100+veriflvl; break;
        case 'T': veriflvl=4*100+veriflvl; break;
        case 'Y': veriflvl=5*100+veriflvl; break;
        case 'U': veriflvl=6*100+veriflvl; break;
        case 'I': veriflvl=7*100+veriflvl; break;
        case 'O': veriflvl=8*100+veriflvl; break;
        case 'P': veriflvl=9*100+veriflvl; break;
    }
  switch(fgetc(level))
    {
        case 'A': veriflvl=0*10+veriflvl; break;
        case 'Z': veriflvl=1*10+veriflvl; break;
        case 'E': veriflvl=2*10+veriflvl; break;
        case 'R': veriflvl=3*10+veriflvl; break;
        case 'T': veriflvl=4*10+veriflvl; break;
        case 'Y': veriflvl=5*10+veriflvl; break;
        case 'U': veriflvl=6*10+veriflvl; break;
        case 'I': veriflvl=7*10+veriflvl; break;
        case 'O': veriflvl=8*10+veriflvl; break;
        case 'P': veriflvl=9*10+veriflvl; break;
    }
  switch(fgetc(level))
    {
        case 'A': veriflvl=0+veriflvl; break;
        case 'Z': veriflvl=1+veriflvl; break;
        case 'E': veriflvl=2+veriflvl; break;
        case 'R': veriflvl=3+veriflvl; break;
        case 'T': veriflvl=4+veriflvl; break;
        case 'Y': veriflvl=5+veriflvl; break;
        case 'U': veriflvl=6+veriflvl; break;
        case 'I': veriflvl=7+veriflvl; break;
        case 'O': veriflvl=8+veriflvl; break;
        case 'P': veriflvl=9+veriflvl; break;
    }

     if(veriflvl!=lvl)   return 4;
     fseek(level, 0, SEEK_SET);

                        if(level==NULL) return 15;
                        cible[0]=0; cible[1]=0; cible[2]=0; cible[3]=0; bmax=1;telemax=0;

                        if(lvl>0 && lvl<=10)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));

                            if(musiccours!=62)
                            {
                            FMOD_System_CreateSound(system, "data\\62.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=62;
                            }

                        }
                        if(lvl>10 && lvl<=20)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 56, 232));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 205, 205, 205));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 205, 205, 205));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 56, 232));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

                            if(musiccours!=63)
                            {
                            FMOD_System_CreateSound(system, "data\\63.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=63;
                            }
                        }
                        else if(lvl>20 && lvl<=28)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=64)
                            {
                            FMOD_System_CreateSound(system, "data\\64.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=64;
                            }
                        }
                        else if(lvl==29 || lvl==30)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 0, 200, 0));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 0, 0, 128));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 128, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 128, 128, 128));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 128, 128, 128));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 0, 200, 0));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 0, 0, 128));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=65)
                            {
                            FMOD_System_CreateSound(system, "data\\65.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=65;
                            }
                        }
                        else if(lvl>30 && lvl<=39)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 240, 240, 240));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 15, 15, 15));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 15, 15, 15));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 0, 255, 0));

                            if(musiccours!=66)
                            {
                            FMOD_System_CreateSound(system, "data\\66.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=66;
                            }
                        }
                        else if(lvl==47)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 50, 50, 50));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 100, 100, 100));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 150, 150, 150));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 255, 0, 0));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 50, 50, 50));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 100, 100, 100));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 150, 150, 150));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 175, 0));

                            if(musiccours!=67)
                            {
                            FMOD_System_CreateSound(system, "data\\67.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=67;
                            }

                        }
                        else if(lvl>39 && lvl<=50)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 227, 174, 201));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 112, 146, 190));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 135, 72, 37));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 135, 72, 37));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 227, 174, 201));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 237, 28, 36));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 63, 72, 204));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 127, 39));

                            if(musiccours!=68)
                            {
                            FMOD_System_CreateSound(system, "data\\68.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=68;
                            }

                        }
                        else if(lvl>50)
                        {
                            SDL_FillRect(ball[0], NULL, SDL_MapRGB(ecran->format, 4, 147, 46));
                            SDL_FillRect(ball[1], NULL, SDL_MapRGB(ecran->format, 14, 157, 56));
                            SDL_FillRect(ball[2], NULL, SDL_MapRGB(ecran->format, 24, 167, 66));
                            SDL_FillRect(ball[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(bloc, NULL, SDL_MapRGB(ecran->format, 185, 122, 87));
                            SDL_FillRect(fond, NULL, SDL_MapRGB(ecran->format, 239, 228, 176));
                            SDL_FillRect(cacheball, NULL, SDL_MapRGB(ecran->format, 239, 228, 176));
                            SDL_FillRect(target[0], NULL, SDL_MapRGB(ecran->format, 4, 147, 46));
                            SDL_FillRect(target[1], NULL, SDL_MapRGB(ecran->format, 14, 157, 56));
                            SDL_FillRect(target[2], NULL, SDL_MapRGB(ecran->format, 24, 167, 66));
                            SDL_FillRect(target[3], NULL, SDL_MapRGB(ecran->format, 34, 177, 76));
                            SDL_FillRect(puits, NULL, SDL_MapRGB(ecran->format, 237, 28, 36));
                            SDL_FillRect(puitsneg, NULL, SDL_MapRGB(ecran->format, 63, 72, 204));
                            SDL_FillRect(teleport, NULL, SDL_MapRGB(ecran->format, 255, 127, 39));

                            if(musiccours!=69)
                            {
                            FMOD_System_CreateSound(system, "data\\69.yf", FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
                            FMOD_Sound_SetLoopCount(musique, -1);
                            if (pause) FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
                            musiccours=69;
                            }

                        }

                        i=0;j=0;

                        gtot=0;
                        while(j<80)
    {
        while(i<120)
        {
            c=fgetc(level);

            casep[i][j].y=8*j;
            casep[i][j].x=8*i;
            if(c=='0')casen[i][j]=0;
            else if(c=='1')casen[i][j]=1;
            else if(c=='2'){casen[i][j]=2;cible[0]++;}
            else if(c=='3') { casen[i][j]=3; gx[gtot]=i*8; gy[gtot]=j*8; gtot++; }
            else if(c=='4') { casen[i][j]=4; gx[gtot]=-i*8; gy[gtot]=-j*8; gtot++; }
            else if(c=='5'){casen[i][j]=5;cible[1]++; if(bmax<2) bmax=2;}
            else if(c=='6'){casen[i][j]=6;cible[2]++; if(bmax<3) bmax=3;}
            else if(c=='7'){casen[i][j]=7;cible[3]++; if(bmax<4) bmax=4;}
            else if(c=='A'){casen[i][j]=100; if(telemax<0) telemax=0; telex[0]=i*8; teley[0]=j*8;}
            else if(c=='B'){casen[i][j]=101; if(telemax<1) telemax=1; telex[1]=i*8; teley[1]=j*8;}
            else if(c=='C'){casen[i][j]=102; if(telemax<2) telemax=2; telex[2]=i*8; teley[2]=j*8;}
            else if(c=='D'){casen[i][j]=103; if(telemax<3) telemax=3; telex[3]=i*8; teley[3]=j*8;}
            else if(c=='E'){casen[i][j]=104; if(telemax<4) telemax=4; telex[4]=i*8; teley[4]=j*8;}
            else if(c=='F'){casen[i][j]=105; if(telemax<5) telemax=5; telex[5]=i*8; teley[5]=j*8;}
            else if(c=='G'){casen[i][j]=106; if(telemax<6) telemax=6; telex[6]=i*8; teley[6]=j*8;}
            else if(c=='H'){casen[i][j]=107; if(telemax<7) telemax=7; telex[7]=i*8; teley[7]=j*8;}
            else if(c=='I'){casen[i][j]=108; if(telemax<8) telemax=8; telex[8]=i*8; teley[8]=j*8;}
            else if(c=='J'){casen[i][j]=109; if(telemax<9) telemax=9; telex[9]=i*8; teley[9]=j*8;}
            else if(c=='K'){casen[i][j]=110; if(telemax<10) telemax=10; telex[10]=i*8; teley[10]=j*8;}
            else if(c=='L'){casen[i][j]=111; if(telemax<11) telemax=11; telex[11]=i*8; teley[11]=j*8;}
            else return 85;
            i++;
        }
        j++;
        i=0;
    }
    j=0;


                        fclose(level);
}
                i=0;
            }
            else if(event.button.button==SDL_BUTTON_LEFT && e==1 && lvl>0)    /// CLIC GAUCHE JEU DEMARRE
            {
                    px[0]=8;    py[0]=629;
                    pos[0].x=8; pos[0].y=629;

                    px[1]=949;    py[1]=629;
                    pos[1].x=949; pos[1].y=629;

                    px[2]=8;    py[2]=8;
                    pos[2].x=8; pos[2].y=8;

                    px[3]=949;    py[3]=8;
                    pos[3].x=949; pos[3].y=8;
                if(bm<bmax)
                {

                    if(bm==0 || bm==2) x[bm]=event.button.x-8;
                    else               x[bm]=951-event.button.x;
                    if(bm==3 || bm==2) y[bm]=event.button.y-8;
                    else               y[bm]=631-event.button.y;

                    D[bm]=sqrt(x[bm]*x[bm]+y[bm]*y[bm]);

                    if(bm==0 || bm==2) vx[bm]=(double)x[bm]/D[bm];
                    else               vx[bm]=-(double)x[bm]/D[bm];
                    if(bm==3 || bm==2) vy[bm]=(double)y[bm]/D[bm];
                    else               vy[bm]=-(double)y[bm]/D[bm];


                    r[bm]=0;
                    bm++;
                }
                if(bm==bmax)
                {
                    if(lvl==debloc && lvl<51)       /// SCORING
                    {
                        if(score<999999999) score++;
                        level=fopen("data\\36.yf","r+");
                        fseek(level,-13,SEEK_END);

                            switch((score/1000000000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/100000000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/10000000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/1000000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/100000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/10000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/1000)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/100)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch((score/10)%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }
                            switch(score%10)
                            {
                                case 0: fputc('A',level); break;
                                case 1: fputc('Z',level); break;
                                case 2: fputc('E',level); break;
                                case 3: fputc('R',level); break;
                                case 4: fputc('T',level); break;
                                case 5: fputc('Y',level); break;
                                case 6: fputc('U',level); break;
                                case 7: fputc('I',level); break;
                                case 8: fputc('O',level); break;
                                case 9: fputc('P',level); break;
                            }

                            fclose(level);
                            level=NULL;
                            i=0;

                    }



                    while((r[0]<6 && cible[0]!=0) || (r[1]<6 && cible[1]!=0) || (r[2]<6 && cible[2]!=0) || (r[3]<6 && cible[3]!=0))
                {



                    // BOUCLE ANTI PERTE FOCUS
                    while(SDL_PollEvent(&event))
                        ;


                    ///     :: CACHES 5 cases ::


                    temps=SDL_GetTicks();
                    bm=0;

                    while(bm<bmax)
                    {
                    //    SDL_BlitSurface(cacheball,NULL,ecran,&pos[bm]);        // CACHE
                        switch(casen[pos[bm].x/8][pos[bm].y/8])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]); break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);break;
                        }
                        if(pos[bm].x/8+1<=120) switch(casen[pos[bm].x/8+1][pos[bm].y/8])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);break;
                        }
                        if(pos[bm].y/8+1<=80) switch(casen[pos[bm].x/8][pos[bm].y/8+1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);break;
                        }
                        if(pos[bm].x/8-1>=0) switch(casen[pos[bm].x/8-1][pos[bm].y/8])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);break;
                        }
                        if(pos[bm].y/8-1>=0) switch(casen[pos[bm].x/8][pos[bm].y/8-1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);break;
                        }
                        if(pos[bm].x/8-1>=0 && pos[bm].y/8-1>=0) switch(casen[pos[bm].x/8-1][pos[bm].y/8-1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8-1]);break;
                        }
                        if(pos[bm].x/8+1<=120 && pos[bm].y/8-1>=0) switch(casen[pos[bm].x/8+1][pos[bm].y/8-1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8-1]);break;
                        }
                        if(pos[bm].x/8+1<=120 && pos[bm].y/8+1<=80) switch(casen[pos[bm].x/8+1][pos[bm].y/8+1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8+1]);break;
                        }
                        if(pos[bm].x/8-1>=0 && pos[bm].y/8+1<=80) switch(casen[pos[bm].x/8-1][pos[bm].y/8+1])
                        {
                            case 0: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 20: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 50: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 60: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 70: SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 1: SDL_BlitSurface(bloc,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 2: SDL_BlitSurface(target[0],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 3: SDL_BlitSurface(puits,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 4: SDL_BlitSurface(puitsneg,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 5: SDL_BlitSurface(target[1],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 6: SDL_BlitSurface(target[2],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                            case 7: SDL_BlitSurface(target[3],NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8+1]);break;
                        }

                                if(casen[pos[bm].x/8-1][pos[bm].y/8]>99 && casen[pos[bm].x/8-1][pos[bm].y/8]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);
                                if(casen[pos[bm].x/8][pos[bm].y/8+1]>99 && casen[pos[bm].x/8][pos[bm].y/8+1]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);
                                if(casen[pos[bm].x/8][pos[bm].y/8-1]>99 && casen[pos[bm].x/8][pos[bm].y/8-1]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);
                                if(casen[pos[bm].x/8+1][pos[bm].y/8]>99 && casen[pos[bm].x/8+1][pos[bm].y/8]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);
                                if(casen[pos[bm].x/8][pos[bm].y/8]>99 && casen[pos[bm].x/8][pos[bm].y/8]<126)     SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);

                        bm++;
                    }
                            if(bmax>0) SDL_BlitSurface(target[0],NULL,ecran,&casep[0][79]);
                            else       SDL_BlitSurface(bloc,NULL,ecran,&casep[0][79]);
                            if(bmax>1) SDL_BlitSurface(target[1],NULL,ecran,&casep[119][79]);
                            else       SDL_BlitSurface(bloc,NULL,ecran,&casep[119][79]);
                            if(bmax>2) SDL_BlitSurface(target[2],NULL,ecran,&casep[0][0]);
                            else       SDL_BlitSurface(bloc,NULL,ecran,&casep[0][0]);
                            if(bmax>3) SDL_BlitSurface(target[3],NULL,ecran,&casep[119][0]);
                            else       SDL_BlitSurface(bloc,NULL,ecran,&casep[119][0]);



                    bm=0;
                    while(bm<bmax)
                    {


/// RICOCHETS

                    if((casen[pos[bm].x/8][(pos[bm].y+1)/8]==1 || casen[pos[bm].x/8][(pos[bm].y+1)/8]==3 || casen[pos[bm].x/8][(pos[bm].y+1)/8]==4 || (casen[pos[bm].x/8][(pos[bm].y+1)/8]==2 && bm!=0) || ( casen[pos[bm].x/8][(pos[bm].y+1)/8]==5 && bm!=1) || (casen[pos[bm].x/8][(pos[bm].y+1)/8]==6 && bm!=2) || (casen[pos[bm].x/8][(pos[bm].y+1)/8]==7 && bm!=3)) || (casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==1 || casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==3 || casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==4 || (casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==2 && bm!=0) || ( casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==5 && bm!=1) || (casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==6 && bm!=2) || (casen[(pos[bm].x+2)/8][(pos[bm].y+1)/8]==7 && bm!=3)))
                    {
                        pos[bm].x=jx[bm];
                        px[bm]=ix[bm];
                        vx[bm]=-vx[bm];
                        r[bm]++;
                    }
                    if((casen[(pos[bm].x+1)/8][pos[bm].y/8]==1 || casen[(pos[bm].x+1)/8][pos[bm].y/8]==3 || casen[(pos[bm].x+1)/8][pos[bm].y/8]==4 || (casen[(pos[bm].x+1)/8][pos[bm].y/8]==2 && bm!=0) || ( casen[(pos[bm].x+1)/8][pos[bm].y/8]==5 && bm!=1) || (casen[(pos[bm].x+1)/8][pos[bm].y/8]==6 && bm!=2) || (casen[(pos[bm].x+1)/8][pos[bm].y/8]==7 && bm!=3)) || (casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==1 || casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==3 || casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==4 || (casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==2 && bm!=0) || ( casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==5 && bm!=1) || (casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==6 && bm!=2) || (casen[(pos[bm].x+1)/8][(pos[bm].y+2)/8]==7 && bm!=3)))
                    {
                        pos[bm].y=jy[bm];
                        py[bm]=iy[bm];
                        vy[bm]=-vy[bm];
                        r[bm]++;
                    }
                //
                    else if((casen[pos[bm].x/8][pos[bm].y/8]==1 || casen[pos[bm].x/8][pos[bm].y/8]==3 || casen[pos[bm].x/8][pos[bm].y/8]==4 || (casen[pos[bm].x/8][pos[bm].y/8]==2 && bm!=0) || ( casen[pos[bm].x/8][pos[bm].y/8]==5 && bm!=1) || (casen[pos[bm].x/8][pos[bm].y/8]==6 && bm!=2) || (casen[pos[bm].x/8][pos[bm].y/8]==7 && bm!=3)) && ((iy[bm]>=ix[bm]-pos[bm].x+pos[bm].y && ix[bm]>pos[bm].x) || iy[bm]<=pos[bm].y ))
                    {
                        pos[bm].x++;
                        px[bm]++;
                        vx[bm]=-vx[bm];
                        r[bm]++;
                    }
                    else if((casen[pos[bm].x/8][pos[bm].y/8]==1 || casen[pos[bm].x/8][pos[bm].y/8]==3 || casen[pos[bm].x/8][pos[bm].y/8]==4 || (casen[pos[bm].x/8][pos[bm].y/8]==2 && bm!=0) || ( casen[pos[bm].x/8][pos[bm].y/8]==5 && bm!=1) || (casen[pos[bm].x/8][pos[bm].y/8]==6 && bm!=2) || (casen[pos[bm].x/8][pos[bm].y/8]==7 && bm!=3)))
                    {
                        pos[bm].y++;
                        py[bm]++;
                        vy[bm]=-vy[bm];
                        r[bm]++;
                    }
               //
                    else if((casen[(pos[bm].x+2)/8][pos[bm].y/8]==1 || casen[(pos[bm].x+2)/8][pos[bm].y/8]==3 || casen[(pos[bm].x+2)/8][pos[bm].y/8]==4 || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==2 && bm!=0) || ( casen[(pos[bm].x+2)/8][pos[bm].y/8]==5 && bm!=1) || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==6 && bm!=2) || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==7 && bm!=3)) && ((iy[bm]>=-ix[bm]-2-pos[bm].x+pos[bm].y && ix[bm]<pos[bm].x)||iy[bm]<=pos[bm].y))
                    {
                        pos[bm].x--;
                        px[bm]--;
                        vx[bm]=-vx[bm];
                        r[bm]++;
                    }
                    else if((casen[(pos[bm].x+2)/8][pos[bm].y/8]==1 || casen[(pos[bm].x+2)/8][pos[bm].y/8]==3 || casen[(pos[bm].x+2)/8][pos[bm].y/8]==4 || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==2 && bm!=0) || ( casen[(pos[bm].x+2)/8][pos[bm].y/8]==5 && bm!=1) || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==6 && bm!=2) || (casen[(pos[bm].x+2)/8][pos[bm].y/8]==7 && bm!=3)))
                    {
                        pos[bm].y++;
                        py[bm]++;
                        vy[bm]=-vy[bm];
                        r[bm]++;
                    }
             //
                    else if((casen[pos[bm].x/8][(pos[bm].y+2)/8]==1 || casen[pos[bm].x/8][(pos[bm].y+2)/8]==3 || casen[pos[bm].x/8][(pos[bm].y+2)/8]==4 || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==2 && bm!=0) || ( casen[pos[bm].x/8][(pos[bm].y+2)/8]==5 && bm!=1) || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==6 && bm!=2) || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==7 && bm!=3)) && ((iy[bm]>=-ix[bm]-2-pos[bm].x+pos[bm].y && ix[bm]>pos[bm].x)||iy[bm]>=pos[bm].y) )
                    {
                        pos[bm].x++;
                        px[bm]++;
                        vx[bm]=-vx[bm];
                        r[bm]++;
                    }
                    else if((casen[pos[bm].x/8][(pos[bm].y+2)/8]==1 || casen[pos[bm].x/8][(pos[bm].y+2)/8]==3 || casen[pos[bm].x/8][(pos[bm].y+2)/8]==4 || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==2 && bm!=0) || ( casen[pos[bm].x/8][(pos[bm].y+2)/8]==5 && bm!=1) || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==6 && bm!=2) || (casen[pos[bm].x/8][(pos[bm].y+2)/8]==7 && bm!=3)))
                    {
                        pos[bm].y--;
                        py[bm]--;
                        vy[bm]=-vy[bm];
                        r[bm]++;
                    }
               //
                    else if((casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==1 || casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==3 || casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==4 || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==2 && bm!=0) || ( casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==5 && bm!=1) || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==6 && bm!=2) || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==7 && bm!=3)) && ((iy[bm]>=ix[bm]-pos[bm].x+pos[bm].y && ix[bm]<pos[bm].x)||iy[bm]<=pos[bm].y))
                    {
                        pos[bm].x--;
                        px[bm]--;
                        vx[bm]=-vx[bm];
                        r[bm]++;
                    }
                    else if((casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==1 || casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==3 || casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==4 || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==2 && bm!=0) || ( casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==5 && bm!=1) || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==6 && bm!=2) || (casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==7 && bm!=3)))
                    {
                        pos[bm].y--;
                        py[bm]--;
                        vy[bm]=-vy[bm];
                        r[bm]++;
                    }
                    //else if(casen[pos[bm].x/8][(pos[bm].y+2)/8]==1 || casen[(pos[bm].x+2)/8][pos[bm].y/8]==1 || casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==1 || casen[pos[bm].x/8][(pos[bm].y)/8]==1) return 59;


             /// IF teleportation


                    else if (casen[pos[bm].x/8][pos[bm].y/8]>=100 && casen[(pos[bm].x+2)/8][pos[bm].y/8]>=100 && casen[pos[bm].x/8][(pos[bm].y+2)/8]>=100 && casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]>=100)
                    {

                          if(casen[(jx[bm])/8][(jy[bm])/8]<100 ||casen[(jx[bm]+2)/8][(jy[bm])/8]<100 || casen[(jx[bm])/8][(jy[bm]+2)/8]<100 || casen[(jx[bm]+2)/8][(jy[bm]+2)/8]<100)
                          {
                             if(casen[(pos[bm].x+1)/8][(pos[bm].y+1)/8]-100==telemax)
                             {
                                px[bm]=telex[0] + pos[bm].x%8;
                                py[bm]=teley[0] + pos[bm].y%8;
                             }
                             else
                             {
                                px[bm]=telex[casen[(pos[bm].x+1)/8][(pos[bm].y+1)/8]-99] + pos[bm].x%8;
                                py[bm]=teley[casen[(pos[bm].x+1)/8][(pos[bm].y+1)/8]-99] + pos[bm].y%8;
                             }
                          }
                        ix[bm]=px[bm];
                        iy[bm]=py[bm];
                        jx[bm]=pos[bm].x;
                        jy[bm]=pos[bm].y;

                        px[bm]=(double)px[bm]+vx[bm]*0.5;
                        py[bm]=(double)py[bm]+vy[bm]*0.5;
                        pos[bm].x=px[bm];
                        pos[bm].y=py[bm];

                        SDL_BlitSurface(ball[bm],NULL,ecran,&pos[bm]);

                    }





                    else if((casen[pos[bm].x/8][pos[bm].y/8]==0 || casen[pos[bm].x/8][pos[bm].y/8]>=20 || (casen[pos[bm].x/8][pos[bm].y/8]==2 && bm==0) || (casen[pos[bm].x/8][pos[bm].y/8]==bm+4 && bm!=0))  && cible[bm]!=0 && r[bm]<6 )
                    {


                        ix[bm]=px[bm];
                        iy[bm]=py[bm];
                        jx[bm]=pos[bm].x;
                        jy[bm]=pos[bm].y;

                        ax[bm]=0; ay[bm]=0;
                        while(i<gtot)
                        {

                            if(gx[i]<0)                                         /// PUITS NEGATIF
                            {
                                Dp[bm]=(px[bm]+gx[i])*(px[bm]+gx[i])+(py[bm]+gy[i])*(py[bm]+gy[i]);
                                ax[bm]=ax[bm]+(double)(gx[i]+px[bm])*0.3/Dp[bm];
                                ay[bm]=ay[bm]+(double)(gy[i]+py[bm])*0.3/Dp[bm];
                            }
                            else                                                /// PUITS POSITIF
                            {
                                Dp[bm]=(px[bm]-gx[i])*(px[bm]-gx[i])+(py[bm]-gy[i])*(py[bm]-gy[i]);
                                ax[bm]=ax[bm]+(double)(gx[i]-px[bm])*0.3/Dp[bm];
                                ay[bm]=ay[bm]+(double)(gy[i]-py[bm])*0.3/Dp[bm];
                            }
                            i++;
                        }
                        i=0;

                        px[bm]=(double)px[bm]+vx[bm]*0.5;
                        py[bm]=(double)py[bm]+vy[bm]*0.5;
                        vx[bm]=vx[bm]+ax[bm];
                        vy[bm]=vy[bm]+ay[bm];
                        pos[bm].x=px[bm];
                        pos[bm].y=py[bm];


                        if(casen[pos[bm].x/8][pos[bm].y/8]==2 && bm==0)
                        {
                            casen[pos[bm].x/8][pos[bm].y/8]=20;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);
                            cible[bm]--;
                        }
                        else  if(casen[(pos[bm].x+2)/8][pos[bm].y/8]==2 && bm==0)
                        {
                            casen[(pos[bm].x+2)/8][pos[bm].y/8]=20;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[(pos[bm].x+2)/8][pos[bm].y/8]);
                            cible[bm]--;
                        }
                        else  if(casen[pos[bm].x/8][(pos[bm].y+2)/8]==2 && bm==0)
                        {
                            casen[pos[bm].x/8][(pos[bm].y+2)/8]=20;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][(pos[bm].y+2)/8]);
                            cible[bm]--;
                        }
                        else  if(casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==2 && bm==0)
                        {
                            casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]=20;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[(pos[bm].x+2)/8][(pos[bm].y+2)/8]);
                            cible[bm]--;
                        }
                        else  if(casen[pos[bm].x/8][pos[bm].y/8]==bm+4 && bm!=0)
                        {
                            casen[pos[bm].x/8][pos[bm].y/8]=(bm+4)*10;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);
                            cible[bm]--;
                        }
                        else  if(casen[(pos[bm].x+2)/8][pos[bm].y/8]==bm+4 && bm!=0)
                        {
                            casen[(pos[bm].x+2)/8][pos[bm].y/8]=(bm+4)*10;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[(pos[bm].x+2)/8][pos[bm].y/8]);
                            cible[bm]--;
                        }
                        else  if(casen[pos[bm].x/8][(pos[bm].y+2)/8]==bm+4 && bm!=0)
                        {
                            casen[pos[bm].x/8][(pos[bm].y+2)/8]=(bm+4)*10;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[pos[bm].x/8][(pos[bm].y+2)/8]);
                            cible[bm]--;
                        }
                        else  if(casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]==bm+4 && bm!=0)
                        {
                            casen[(pos[bm].x+2)/8][(pos[bm].y+2)/8]=(bm+4)*10;
                            SDL_BlitSurface(fond,NULL,ecran,&casep[(pos[bm].x+2)/8][(pos[bm].y+2)/8]);
                            cible[bm]--;
                        }
                        SDL_BlitSurface(ball[bm],NULL,ecran,&pos[bm]);

                        }

                        bm++;
                    }
                    SDL_Flip(ecran);
                    temps=SDL_GetTicks()-temps;
                    if(temps<3) SDL_Delay(3-temps);
                    if(cible[0]==0 && cible[1]==0 && cible[2]==0 && cible[3]==0) up=1;
                    if(up==1 && (lvl==1 || lvl==2)) { SDL_BlitSurface(titre,&pressenter,ecran,&casep[80][50]); SDL_Flip(ecran); }

            } bm=0;
        }
    }}
    SDL_ShowCursor(1);
    }



SDL_FreeSurface(ball[0]);
SDL_FreeSurface(ball[1]);
SDL_FreeSurface(ball[2]);
SDL_FreeSurface(ball[3]);
SDL_FreeSurface(ecran);
SDL_FreeSurface(ico);
SDL_FreeSurface(target[0]);
SDL_FreeSurface(target[1]);
SDL_FreeSurface(target[2]);
SDL_FreeSurface(target[3]);
SDL_FreeSurface(bloc);
SDL_FreeSurface(fond);
SDL_FreeSurface(titre);
SDL_FreeSurface(cachecache);
SDL_FreeSurface(cachenumber);
SDL_FreeSurface(puits);
SDL_FreeSurface(puitsneg);
SDL_FreeSurface(cacheball);
SDL_FreeSurface(teleport);
SDL_FreeSurface(english);
SDL_FreeSurface(reset);
SDL_FreeSurface(francais);

SDL_VideoQuit();

FMOD_System_Close(system);
FMOD_System_Release(system);



    return 0;
}
