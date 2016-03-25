#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>








int main ( int argc, char** argv )
{

    int x[5],y[5],r[4],gtot=0,gx[80],gy[80],bm=0,bmax=1, cible[4], telemax=0,telex[26], teley[26],jx[4],jy[4];

     float D[4],ax[4],ay[4],vx[4],vy[4],px[4],py[4],Dp[4], ix[4],iy[4];

    SDL_Surface *fond,*bloc,*target[4],*ball[4], *titre,*cachecache, *cacheball, *teleport;
    SDL_Rect pos[4], cache, cachep[61];


cible[0]=0; cible[1]=0; cible[2]=0; cible[3]=0;



    FILE* txt = NULL, *log = NULL;

    txt = fopen("0.yf", "r+");
    log = fopen("log.txt", "a");

    char c='EOF';
    char logline[20];
    int casen[120][80], i=0,j=0,e=1,A=0,B=0, X=1, Y=-1 , fin=1, K[4],L[4];
    SDL_Surface *ecran,*puits,*puitsneg;
    SDL_Rect casep[120][80];

    SDL_Event event;

if (txt== NULL || (fgetc(txt)!='0' && fgetc(txt)!='1' && fgetc(txt)!='2' && fgetc(txt)!='3'))
{
    fclose(txt);
    txt=fopen("0.yf","w");
 while (i<=120*80)
{
    if(i<=120 || i>=9480 || i%120==0 || i%120==119 ) fputc('1',txt);
    else fputc('0',txt);
    i++;
}
   fclose(txt);
   txt=fopen("0.yf","r+");
}

x[4]=0;
y[4]=0;
i=0;
fseek(txt, 0, SEEK_SET);

    while(y[4]<80)
    {
        while(x[4]<120)
        {
            c=fgetc(txt);

            casep[x[4]][y[4]].y=8*y[4];
            casep[x[4]][y[4]].x=8*x[4];
            if(c=='0')casen[x[4]][y[4]]=0;
            else if(c=='1')casen[x[4]][y[4]]=1;
            else if(c=='2') { casen[x[4]][y[4]]=2; cible[0]++; }
            else if(c=='3') { casen[x[4]][y[4]]=3; gx[gtot]=x[4]*8; gy[gtot]=y[4]*8; gtot++; }
            else if(c=='4') { casen[x[4]][y[4]]=4; gx[gtot]=-x[4]*8; gy[gtot]=-y[4]*8; gtot++; }
            else if(c=='5') { casen[x[4]][y[4]]=5; if(bmax<2) bmax=2; cible[1]++;}
            else if(c=='6') { casen[x[4]][y[4]]=6; if(bmax<3) bmax=3; cible[2]++;}
            else if(c=='7') { casen[x[4]][y[4]]=7; if(bmax<4) bmax=4; cible[3]++;}
            else if(c=='A'){casen[x[4]][y[4]]=100; if(telemax<0) telemax=0; telex[0]=x[4]*8; teley[0]=y[4]*8;}
            else if(c=='B'){casen[x[4]][y[4]]=101; if(telemax<1) telemax=1; telex[1]=x[4]*8; teley[1]=y[4]*8;}
            else if(c=='C'){casen[x[4]][y[4]]=102; if(telemax<2) telemax=2; telex[2]=x[4]*8; teley[2]=y[4]*8;}
            else if(c=='D'){casen[x[4]][y[4]]=103; if(telemax<3) telemax=3; telex[3]=x[4]*8; teley[3]=y[4]*8;}
            else if(c=='E'){casen[x[4]][y[4]]=104; if(telemax<4) telemax=4; telex[4]=x[4]*8; teley[4]=y[4]*8;}
            else if(c=='F'){casen[x[4]][y[4]]=105; if(telemax<5) telemax=5; telex[5]=x[4]*8; teley[5]=y[4]*8;}
            else if(c=='G'){casen[x[4]][y[4]]=106; if(telemax<6) telemax=6; telex[6]=x[4]*8; teley[6]=y[4]*8;}
            else if(c=='H'){casen[x[4]][y[4]]=107; if(telemax<7) telemax=7; telex[7]=x[4]*8; teley[7]=y[4]*8;}
            else if(c=='I'){casen[x[4]][y[4]]=108; if(telemax<8) telemax=8; telex[8]=x[4]*8; teley[8]=y[4]*8;}
            else if(c=='J'){casen[x[4]][y[4]]=109; if(telemax<9) telemax=9; telex[9]=x[4]*8; teley[9]=y[4]*8;}
            else if(c=='K'){casen[x[4]][y[4]]=110; if(telemax<10) telemax=10; telex[10]=x[4]*8; teley[10]=y[4]*8;}
            else if(c=='L'){casen[x[4]][y[4]]=111; if(telemax<11) telemax=11; telex[11]=x[4]*8; teley[11]=y[4]*8;}
            else return 85;
            x[4]++;
        }
        y[4]++;
        x[4]=0;
    }
    x[4]=0;
    y[4]=0;





        SDL_Init(SDL_INIT_VIDEO);

    /*ico=SDL_LoadBMP("hidden\\9.bmp");
    SDL_SetColorKey(ico, SDL_SRCCOLORKEY, SDL_MapRGB(ico->format, 255, 255, 255));
    SDL_WM_SetIcon(ico, NULL);
*/
    ecran = SDL_SetVideoMode(960, 640, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    SDL_WM_SetCaption("Editeur Ricochet Kill v0.7", NULL);

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







                        while(j<80)
                        {
                            while(i<120)
                            {
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
                        SDL_Flip(ecran);











    while(e)
    {


        SDL_WaitEvent(&event);
        switch(event.key.keysym.sym)
        {
            case SDLK_ESCAPE:
                e = 0;
            break;
            case SDLK_r:
                bm=0;
                while(j<80)
                        {
                            while(i<120)
                            {
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
                        SDL_Flip(ecran);



            break;
            case SDLK_t:
            if(event.type==SDL_KEYUP)
            {
                fseek(txt, y[4]*960/8+x[4], SEEK_SET);

                     if(casen[x[4]][y[4]]==0) {casen[x[4]][y[4]]=100; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('A',txt);}
                else if(casen[x[4]][y[4]]==100) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('B',txt);}
                else if(casen[x[4]][y[4]]==101) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('C',txt);}
                else if(casen[x[4]][y[4]]==102) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('D',txt);}
                else if(casen[x[4]][y[4]]==103) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('E',txt);}
                else if(casen[x[4]][y[4]]==104) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('F',txt);}
                else if(casen[x[4]][y[4]]==105) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('G',txt);}
                else if(casen[x[4]][y[4]]==106) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('H',txt);}
                else if(casen[x[4]][y[4]]==107) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('I',txt);}
                else if(casen[x[4]][y[4]]==108) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('J',txt);}
                else if(casen[x[4]][y[4]]==109) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('K',txt);}
                else if(casen[x[4]][y[4]]==110) {casen[x[4]][y[4]]++; SDL_BlitSurface(teleport,NULL,ecran,&casep[x[4]][y[4]]); fputc('L',txt);}
                else                            {casen[x[4]][y[4]]=0; SDL_BlitSurface(fond,NULL,ecran,&casep[x[4]][y[4]]); fputc('0',txt);}
                SDL_Flip(ecran);
            }

            break;

            case SDLK_SPACE:

            x[4]=0;
y[4]=0;

gtot=0; bmax=1; cible[0]=0; cible[1]=0; cible[2]=0; cible[3]=0;

fseek(txt, 0, SEEK_SET);

    while(y[4]<80)
    {
        while(x[4]<120)
        {
            c=fgetc(txt);

            casep[x[4]][y[4]].y=8*y[4];
            casep[x[4]][y[4]].x=8*x[4];
            if(c=='0')casen[x[4]][y[4]]=0;
            else if(c=='1')casen[x[4]][y[4]]=1;
            else if(c=='2') { casen[x[4]][y[4]]=2; cible[0]++; }
            else if(c=='3') { casen[x[4]][y[4]]=3; gx[gtot]=x[4]*8; gy[gtot]=y[4]*8; gtot++; }
            else if(c=='4') { casen[x[4]][y[4]]=4; gx[gtot]=-x[4]*8; gy[gtot]=-y[4]*8; gtot++; }
            else if(c=='5') { casen[x[4]][y[4]]=5; if(bmax<2) bmax=2; cible[1]++;}
            else if(c=='6') { casen[x[4]][y[4]]=6; if(bmax<3) bmax=3; cible[2]++;}
            else if(c=='7') { casen[x[4]][y[4]]=7; if(bmax<4) bmax=4; cible[3]++;}
            else if(c=='A'){casen[x[4]][y[4]]=100; if(telemax<0) telemax=0; telex[0]=x[4]*8; teley[0]=y[4]*8;}
            else if(c=='B'){casen[x[4]][y[4]]=101; if(telemax<1) telemax=1; telex[1]=x[4]*8; teley[1]=y[4]*8;}
            else if(c=='C'){casen[x[4]][y[4]]=102; if(telemax<2) telemax=2; telex[2]=x[4]*8; teley[2]=y[4]*8;}
            else if(c=='D'){casen[x[4]][y[4]]=103; if(telemax<3) telemax=3; telex[3]=x[4]*8; teley[3]=y[4]*8;}
            else if(c=='E'){casen[x[4]][y[4]]=104; if(telemax<4) telemax=4; telex[4]=x[4]*8; teley[4]=y[4]*8;}
            else if(c=='F'){casen[x[4]][y[4]]=105; if(telemax<5) telemax=5; telex[5]=x[4]*8; teley[5]=y[4]*8;}
            else if(c=='G'){casen[x[4]][y[4]]=106; if(telemax<6) telemax=6; telex[6]=x[4]*8; teley[6]=y[4]*8;}
            else if(c=='H'){casen[x[4]][y[4]]=107; if(telemax<7) telemax=7; telex[7]=x[4]*8; teley[7]=y[4]*8;}
            else if(c=='I'){casen[x[4]][y[4]]=108; if(telemax<8) telemax=8; telex[8]=x[4]*8; teley[8]=y[4]*8;}
            else if(c=='J'){casen[x[4]][y[4]]=109; if(telemax<9) telemax=9; telex[9]=x[4]*8; teley[9]=y[4]*8;}
            else if(c=='K'){casen[x[4]][y[4]]=110; if(telemax<10) telemax=10; telex[10]=x[4]*8; teley[10]=y[4]*8;}
            else if(c=='L'){casen[x[4]][y[4]]=111; if(telemax<11) telemax=11; telex[11]=x[4]*8; teley[11]=y[4]*8;}
            else return 85;
            x[4]++;
        }
        y[4]++;
        x[4]=0;
    }
    y[4]=0;


                fputs("\n\n--------------------\n",log);

                while(bmax>bm)
                {
                    fin=1;
                    while(fin)
                    {
                        SDL_WaitEvent(&event);
                        if(event.key.keysym.sym==SDLK_ESCAPE) return 0;
                        if(event.type==SDL_MOUSEBUTTONUP && event.button.button==SDL_BUTTON_LEFT)
                        {
                            K[bm]=event.button.x;
                            L[bm]=event.button.y;
                            fin=0;

                            bm++;
                            sprintf(logline,"\n%d :  %d  -  %d",bm,K[bm-1],L[bm-1]);
                            fputs(logline,log);
                        }
                    }
                }
                bm=0;
                while(bmax>bm)
                {
                            if(bm==0 || bm==2) x[bm]=K[bm]-8;
                            else               x[bm]=951-K[bm];
                            if(bm==3 || bm==2) y[bm]=L[bm]-8;
                            else               y[bm]=631-L[bm];

                            D[bm]=sqrt(x[bm]*x[bm]+y[bm]*y[bm]);

                            if(bm==0 || bm==2) vx[bm]=(double)x[bm]/D[bm];
                            else               vx[bm]=-(double)x[bm]/D[bm];
                            if(bm==3 || bm==2) vy[bm]=(double)y[bm]/D[bm];
                            else               vy[bm]=-(double)y[bm]/D[bm];

                            bm++;
                }
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
                        SDL_Flip(ecran);

                    px[0]=8;    py[0]=629;
                    pos[0].x=8; pos[0].y=629;

                    px[1]=949;    py[1]=629;
                    pos[1].x=949; pos[1].y=629;

                    px[2]=8;    py[2]=8;
                    pos[2].x=8; pos[2].y=8;

                    px[3]=949;    py[3]=8;
                    pos[3].x=949; pos[3].y=8;

                    r[0]=0; r[1]=0; r[2]=0; r[3]=0;

                while((r[0]<6 && cible[0]!=0) || (r[1]<6 && cible[1]!=0) || (r[2]<6 && cible[2]!=0) || (r[3]<6 && cible[3]!=0))
                {
                    ///     :: CACHES 5 cases ::

                    bm=0;

                    while(bm<bmax)
                    {
                                if(casen[pos[bm].x/8-1][pos[bm].y/8]>99 && casen[pos[bm].x/8-1][pos[bm].y/8]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8-1][pos[bm].y/8]);
                                if(casen[pos[bm].x/8][pos[bm].y/8+1]>99 && casen[pos[bm].x/8][pos[bm].y/8+1]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8+1]);
                                if(casen[pos[bm].x/8][pos[bm].y/8-1]>99 && casen[pos[bm].x/8][pos[bm].y/8-1]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8-1]);
                                if(casen[pos[bm].x/8+1][pos[bm].y/8]>99 && casen[pos[bm].x/8+1][pos[bm].y/8]<126) SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8+1][pos[bm].y/8]);
                                if(casen[pos[bm].x/8][pos[bm].y/8]>99 && casen[pos[bm].x/8][pos[bm].y/8]<126)     SDL_BlitSurface(teleport,NULL,ecran,&casep[pos[bm].x/8][pos[bm].y/8]);

                        bm++;
                    }


                    bm=0;
                    while(bm<bmax)
                    {




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

                }
                bm=10;

                    SDL_WaitEvent(&event);
                    break;












        }
        switch(event.type)
        {

            case SDL_QUIT:
                e = 0;
            break;


            case SDL_MOUSEBUTTONUP:
            if(event.button.button==SDL_BUTTON_LEFT && e==1)    /// CLIC GAUCHE : Bloc 1
            {
                A=event.button.x;
                B=event.button.y;
                x[4]=(event.button.x-event.button.x%8)/8;
                y[4]=(event.button.y-event.button.y%8)/8;

                fseek(txt, y[4]*960/8+x[4], SEEK_SET);


                if(casen[x[4]][y[4]]==0)      {casen[x[4]][y[4]]=1; SDL_BlitSurface(bloc,NULL,ecran,&casep[x[4]][y[4]]); fputc('1',txt);}
                else if(casen[x[4]][y[4]]!=0) {casen[x[4]][y[4]]=0; SDL_BlitSurface(fond,NULL,ecran,&casep[x[4]][y[4]]);fputc('0',txt);}

                SDL_Flip(ecran);



            }
            else if(event.button.button==SDL_BUTTON_RIGHT && e==1)    /// CLIC DROIT : Cibles 2/5/6/7
            {
                A=event.button.x;
                B=event.button.y;
                x[4]=(event.button.x-event.button.x%8)/8;
                y[4]=(event.button.y-event.button.y%8)/8;

                fseek(txt, y[4]*960/8+x[4], SEEK_SET);


                if(casen[x[4]][y[4]]==0)      {casen[x[4]][y[4]]=2; SDL_BlitSurface(target[0],NULL,ecran,&casep[x[4]][y[4]]); fputc('2',txt);}
                else if(casen[x[4]][y[4]]==2) {casen[x[4]][y[4]]=5; SDL_BlitSurface(target[1],NULL,ecran,&casep[x[4]][y[4]]); fputc('5',txt);}
                else if(casen[x[4]][y[4]]==5) {casen[x[4]][y[4]]=6; SDL_BlitSurface(target[2],NULL,ecran,&casep[x[4]][y[4]]); fputc('6',txt);}
                else if(casen[x[4]][y[4]]==6) {casen[x[4]][y[4]]=7; SDL_BlitSurface(target[3],NULL,ecran,&casep[x[4]][y[4]]); fputc('7',txt);}
                else if(casen[x[4]][y[4]]!=0) {casen[x[4]][y[4]]=0; SDL_BlitSurface(fond,NULL,ecran,&casep[x[4]][y[4]]); fputc('0',txt);}

                SDL_Flip(ecran);

                if(cible[3]==0) bmax=3;
                if(cible[2]==0) bmax=2;
                if(cible[1]==0) bmax=1;
                if(cible[0]==0) bmax=0;



            }
            else if(event.button.button==SDL_BUTTON_MIDDLE && e==1)    /// CLIC CENTRAL : Puits 3 ou 4
            {
                A=event.button.x;
                B=event.button.y;
                x[4]=(event.button.x-event.button.x%8)/8;
                y[4]=(event.button.y-event.button.y%8)/8;

                fseek(txt, y[4]*960/8+x[4], SEEK_SET);


                if(casen[x[4]][y[4]]==0)      {casen[x[4]][y[4]]=3; SDL_BlitSurface(puits,NULL,ecran,&casep[x[4]][y[4]]); fputc('3',txt);}
                else if(casen[x[4]][y[4]]==3) {casen[x[4]][y[4]]=4; SDL_BlitSurface(puitsneg,NULL,ecran,&casep[x[4]][y[4]]); fputc('4',txt);}
                else if(casen[x[4]][y[4]]==4) {casen[x[4]][y[4]]=0; SDL_BlitSurface(fond,NULL,ecran,&casep[x[4]][y[4]]); fputc('0',txt);}

                SDL_Flip(ecran);



            }
        }
    }




fclose(txt);
fclose(log);


SDL_FreeSurface(ball[0]);
SDL_FreeSurface(ball[1]);
SDL_FreeSurface(ball[2]);
SDL_FreeSurface(ball[3]);
SDL_FreeSurface(ecran);
SDL_FreeSurface(target[0]);
SDL_FreeSurface(target[1]);
SDL_FreeSurface(target[2]);
SDL_FreeSurface(target[3]);
SDL_FreeSurface(bloc);
SDL_FreeSurface(fond);
SDL_FreeSurface(titre);
SDL_FreeSurface(cachecache);
SDL_FreeSurface(puits);
SDL_FreeSurface(puitsneg);
SDL_FreeSurface(cacheball);
SDL_FreeSurface(teleport);


    return 0;
}
