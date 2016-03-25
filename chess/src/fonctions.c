#include "fonctions.h"

jeu Definir_Jeu()                  // Placage des pièces initial
{
    jeu plan;
    plan.exit=1;
    plan.shut=1;
    plan.tour=0;
    plan.avant_x=-1;
    plan.avant_y=-1;
    plan.apres_x=-1;
    plan.apres_y=-1;

    plan.menu=-1;


    char i=0,j=0;
    while(i<8)
    {
        while(j<8)
        {
            if      (j==1) plan.lieu[i][j]=PION_N;
            else if (j==6) plan.lieu[i][j]=PION_B;
            else           plan.lieu[i][j]=VIDE;
            j++;
        }
        i++;
        j=0;
    }
    plan.lieu[0][0]=TOUR_N;
    plan.lieu[1][0]=CAVALIER_N;
    plan.lieu[2][0]=FOU_N;
    plan.lieu[3][0]=DAME_N;
    plan.lieu[4][0]=ROI_N;
    plan.lieu[5][0]=FOU_N;
    plan.lieu[6][0]=CAVALIER_N;
    plan.lieu[7][0]=TOUR_N;

    plan.lieu[0][7]=TOUR_B;
    plan.lieu[1][7]=CAVALIER_B;
    plan.lieu[2][7]=FOU_B;
    plan.lieu[3][7]=DAME_B;
    plan.lieu[4][7]=ROI_B;
    plan.lieu[5][7]=FOU_B;
    plan.lieu[6][7]=CAVALIER_B;
    plan.lieu[7][7]=TOUR_B;

    return plan;
}


void Blit_Jeu(SDL_Surface *ecran, jeu plan)            // Valable pour TAILLE = 80
{
    SDL_Surface *composante=SDL_LoadBMP("chipset.bmp"), *carre_bleu= SDL_CreateRGBSurface(SDL_HWSURFACE, TAILLE-4, TAILLE-4, 32, 0, 0, 0, 0);
    SDL_Rect pion_n, pion_b, cavalier_n, cavalier_b, tour_n, tour_b, dame_n, dame_b, fou_n, fou_b, roi_n, roi_b, vide_n, vide_b;
    SDL_Rect position[8][8];

    SDL_SetColorKey(composante, SDL_SRCCOLORKEY, SDL_MapRGB(composante->format, 34, 177, 76));  // transparence des pièces
    SDL_FillRect(carre_bleu, NULL, SDL_MapRGB(ecran->format, 70, 90, 230));
    SDL_SetAlpha(carre_bleu, SDL_SRCALPHA, 90);   // transparence des carrés bleus   ( 0 - 255 )


    vide_b.x=0;   vide_b.y=0;   vide_b.w=80;   vide_b.h=80;
    vide_n.x=0;   vide_n.y=80;   vide_n.w=80;   vide_n.h=80;
    pion_b.x=80;   pion_b.y=0;   pion_b.w=80;   pion_b.h=80;
    pion_n.x=80;   pion_n.y=80;   pion_n.w=80;   pion_n.h=80;
    tour_b.x=160;   tour_b.y=0;   tour_b.w=80;   tour_b.h=80;
    tour_n.x=160;   tour_n.y=80;   tour_n.w=80;   tour_n.h=80;
    cavalier_b.x=240;   cavalier_b.y=0;   cavalier_b.w=80;   cavalier_b.h=80;
    cavalier_n.x=240;   cavalier_n.y=80;   cavalier_n.w=80;   cavalier_n.h=80;
    fou_b.x=320;   fou_b.y=0;   fou_b.w=80;   fou_b.h=80;
    fou_n.x=320;   fou_n.y=80;   fou_n.w=80;   fou_n.h=80;
    dame_b.x=400;   dame_b.y=0;   dame_b.w=80;   dame_b.h=80;
    dame_n.x=400;   dame_n.y=80;   dame_n.w=80;   dame_n.h=80;
    roi_b.x=480;   roi_b.y=0;   roi_b.w=80;   roi_b.h=80;
    roi_n.x=480;   roi_n.y=80;   roi_n.w=80;   roi_n.h=80;


    char i=0,j=0;

    while(i<8)
    {
        while(j<8)
        {
            position[i][j].x = i*TAILLE;
            position[i][j].y = j*TAILLE;
            if((i+j)%2)   SDL_BlitSurface(composante, &vide_n, ecran, &position[i][j]);
            else          SDL_BlitSurface(composante, &vide_b, ecran, &position[i][j]);
            j++;
        }
        i++;
        j=0;
    }
    i=0;

    while(i<8)
    {
        while(j<8)
        {
            switch(plan.lieu[i][j])
            {
                case PION_N: SDL_BlitSurface(composante, &pion_n, ecran, &position[i][j]); break;
                case PION_B: SDL_BlitSurface(composante, &pion_b, ecran, &position[i][j]); break;
                case TOUR_N: SDL_BlitSurface(composante, &tour_n, ecran, &position[i][j]); break;
                case TOUR_B: SDL_BlitSurface(composante, &tour_b, ecran, &position[i][j]); break;
                case CAVALIER_N: SDL_BlitSurface(composante, &cavalier_n, ecran, &position[i][j]); break;
                case CAVALIER_B: SDL_BlitSurface(composante, &cavalier_b, ecran, &position[i][j]); break;
                case FOU_N: SDL_BlitSurface(composante, &fou_n, ecran, &position[i][j]); break;
                case FOU_B: SDL_BlitSurface(composante, &fou_b, ecran, &position[i][j]); break;
                case DAME_N: SDL_BlitSurface(composante, &dame_n, ecran, &position[i][j]); break;
                case DAME_B: SDL_BlitSurface(composante, &dame_b, ecran, &position[i][j]); break;
                case ROI_N: SDL_BlitSurface(composante, &roi_n, ecran, &position[i][j]); break;
                case ROI_B: SDL_BlitSurface(composante, &roi_b, ecran, &position[i][j]); break;
            }
            j++;
        }
        i++;
        j=0;
    }


    // Blittage des indicateur de déplacement :
    if(plan.avant_x!=-1)
    {
        position[0][0].x=plan.avant_x*TAILLE+2;
        position[0][0].y=plan.avant_y*TAILLE+2;
        position[0][1].x=plan.apres_x*TAILLE+2;
        position[0][1].y=plan.apres_y*TAILLE+2;
        SDL_BlitSurface(carre_bleu, NULL, ecran, &position[0][0]);
        SDL_BlitSurface(carre_bleu, NULL, ecran, &position[0][1]);
    }


    SDL_FreeSurface(composante);
    SDL_FreeSurface(carre_bleu);
}



void Blit(SDL_Surface *ecran, char PIECE, int pos_x, int pos_y) // Blit la piece en position posx;posy. Pour le VIDE, donne la couleur.
{
    SDL_Surface *composante=SDL_LoadBMP("chipset.bmp");
    SDL_Rect pion_n, pion_b, cavalier_n, cavalier_b, tour_n, tour_b, dame_n, dame_b, fou_n, fou_b, roi_n, roi_b, vide_n, vide_b;
    SDL_Rect position;
    SDL_SetColorKey(composante, SDL_SRCCOLORKEY, SDL_MapRGB(composante->format, 34, 177, 76));

    vide_b.x=0;   vide_b.y=0;   vide_b.w=80;   vide_b.h=80;
    vide_n.x=0;   vide_n.y=80;   vide_n.w=80;   vide_n.h=80;
    pion_b.x=80;   pion_b.y=0;   pion_b.w=80;   pion_b.h=80;
    pion_n.x=80;   pion_n.y=80;   pion_n.w=80;   pion_n.h=80;
    tour_b.x=160;   tour_b.y=0;   tour_b.w=80;   tour_b.h=80;
    tour_n.x=160;   tour_n.y=80;   tour_n.w=80;   tour_n.h=80;
    cavalier_b.x=240;   cavalier_b.y=0;   cavalier_b.w=80;   cavalier_b.h=80;
    cavalier_n.x=240;   cavalier_n.y=80;   cavalier_n.w=80;   cavalier_n.h=80;
    fou_b.x=320;   fou_b.y=0;   fou_b.w=80;   fou_b.h=80;
    fou_n.x=320;   fou_n.y=80;   fou_n.w=80;   fou_n.h=80;
    dame_b.x=400;   dame_b.y=0;   dame_b.w=80;   dame_b.h=80;
    dame_n.x=400;   dame_n.y=80;   dame_n.w=80;   dame_n.h=80;
    roi_b.x=480;   roi_b.y=0;   roi_b.w=80;   roi_b.h=80;
    roi_n.x=480;   roi_n.y=80;   roi_n.w=80;   roi_n.h=80;


    position.x = pos_x;
    position.y = pos_y;

    switch(PIECE)
    {
        case PION_N: SDL_BlitSurface(composante, &pion_n, ecran, &position); break;
        case PION_B: SDL_BlitSurface(composante, &pion_b, ecran, &position); break;
        case TOUR_N: SDL_BlitSurface(composante, &tour_n, ecran, &position); break;
        case TOUR_B: SDL_BlitSurface(composante, &tour_b, ecran, &position); break;
        case CAVALIER_N: SDL_BlitSurface(composante, &cavalier_n, ecran, &position); break;
        case CAVALIER_B: SDL_BlitSurface(composante, &cavalier_b, ecran, &position); break;
        case FOU_N: SDL_BlitSurface(composante, &fou_n, ecran, &position); break;
        case FOU_B: SDL_BlitSurface(composante, &fou_b, ecran, &position); break;
        case DAME_N: SDL_BlitSurface(composante, &dame_n, ecran, &position); break;
        case DAME_B: SDL_BlitSurface(composante, &dame_b, ecran, &position); break;
        case ROI_N: SDL_BlitSurface(composante, &roi_n, ecran, &position); break;
        case ROI_B: SDL_BlitSurface(composante, &roi_b, ecran, &position); break;
        case VIDE:
            if((position.x/TAILLE + position.y/TAILLE)%2)   SDL_BlitSurface(composante, &vide_n, ecran, &position);
            else                                            SDL_BlitSurface(composante, &vide_b, ecran, &position);
            break;
    }


    SDL_FreeSurface(composante);
}


void Save(jeu plan) // Sauvegarde le dernier coup dans le fichier plan.nom
{
    FILE* fichier=fopen(plan.nom,"a"); //on se place à la fin du fichier.

    switch(plan.avant_x)
    {
        case 0: fputc('a',fichier); break;
        case 1: fputc('b',fichier); break;
        case 2: fputc('c',fichier); break;
        case 3: fputc('d',fichier); break;
        case 4: fputc('e',fichier); break;
        case 5: fputc('f',fichier); break;
        case 6: fputc('g',fichier); break;
        case 7: fputc('h',fichier); break;
    }
    switch(plan.avant_y)
    {
        case 0: fputc('8',fichier); break;
        case 1: fputc('7',fichier); break;
        case 2: fputc('6',fichier); break;
        case 3: fputc('5',fichier); break;
        case 4: fputc('4',fichier); break;
        case 5: fputc('3',fichier); break;
        case 6: fputc('2',fichier); break;
        case 7: fputc('1',fichier); break;
    }
    switch(plan.apres_x)
    {
        case 0: fputc('a',fichier); break;
        case 1: fputc('b',fichier); break;
        case 2: fputc('c',fichier); break;
        case 3: fputc('d',fichier); break;
        case 4: fputc('e',fichier); break;
        case 5: fputc('f',fichier); break;
        case 6: fputc('g',fichier); break;
        case 7: fputc('h',fichier); break;
    }
    switch(plan.apres_y)
    {
        case 0: fputc('8',fichier); break;
        case 1: fputc('7',fichier); break;
        case 2: fputc('6',fichier); break;
        case 3: fputc('5',fichier); break;
        case 4: fputc('4',fichier); break;
        case 5: fputc('3',fichier); break;
        case 6: fputc('2',fichier); break;
        case 7: fputc('1',fichier); break;
    }


    fclose(fichier);
}

jeu Load(jeu plan)
{
    FILE* fichier=fopen(plan.nom,"r");

    fseek(fichier, plan.tour*4,SEEK_SET); // on se place au niveau de la lecture
    switch(fgetc(fichier))
    {
        case 'a': plan.avant_x=0; break;
        case 'b': plan.avant_x=1; break;
        case 'c': plan.avant_x=2; break;
        case 'd': plan.avant_x=3; break;
        case 'e': plan.avant_x=4; break;
        case 'f': plan.avant_x=5; break;
        case 'g': plan.avant_x=6; break;
        case 'h': plan.avant_x=7; break;
    }
    switch(fgetc(fichier))
    {
        case '8': plan.avant_y=0; break;
        case '7': plan.avant_y=1; break;
        case '6': plan.avant_y=2; break;
        case '5': plan.avant_y=3; break;
        case '4': plan.avant_y=4; break;
        case '3': plan.avant_y=5; break;
        case '2': plan.avant_y=6; break;
        case '1': plan.avant_y=7; break;
    }
    switch(fgetc(fichier))
    {
        case 'a': plan.apres_x=0; break;
        case 'b': plan.apres_x=1; break;
        case 'c': plan.apres_x=2; break;
        case 'd': plan.apres_x=3; break;
        case 'e': plan.apres_x=4; break;
        case 'f': plan.apres_x=5; break;
        case 'g': plan.apres_x=6; break;
        case 'h': plan.apres_x=7; break;
    }
    switch(fgetc(fichier))
    {
        case '8': plan.apres_y=0; break;
        case '7': plan.apres_y=1; break;
        case '6': plan.apres_y=2; break;
        case '5': plan.apres_y=3; break;
        case '4': plan.apres_y=4; break;
        case '3': plan.apres_y=5; break;
        case '2': plan.apres_y=6; break;
        case '1': plan.apres_y=7; break;
    }

    fclose(fichier);
    plan.lieu[plan.apres_x][plan.apres_y]=plan.lieu[plan.avant_x][plan.avant_y];
    plan.lieu[plan.avant_x][plan.avant_y]=VIDE;

    return plan;
}

//Renvoie 1 si la piece peut etre prise, 0 sinon
char Verification_echec(jeu newplan, char newx, char newy)   // plan avec position de la pièce à étudier
{
    char i=0,j=0;
/// newplan n'a aucune signification. il est équivalent à plan

    if(newplan.lieu[newx][newy]>NOIR)
    {
        if((newplan.lieu[newx+1][newy+2]==CAVALIER_B && newx<7 && newy<6) ||       // Si un cavalier met en echec.
           (newplan.lieu[newx+1][newy-2]==CAVALIER_B && newx<7 && newy>1) ||
           (newplan.lieu[newx-1][newy+2]==CAVALIER_B && newx>0 && newy<6) ||
           (newplan.lieu[newx-1][newy-2]==CAVALIER_B  && newx>0 && newy>1)||
           (newplan.lieu[newx+2][newy+1]==CAVALIER_B  && newx<6 && newy<7)||
           (newplan.lieu[newx+2][newy-1]==CAVALIER_B && newx<6 && newy>0) ||
           (newplan.lieu[newx-2][newy+1]==CAVALIER_B && newx>1 && newy<7) ||
           (newplan.lieu[newx-2][newy-1]==CAVALIER_B && newx>1 && newy>0)   )          return 1;

        if(              newplan.lieu[newx][newy]==ROI_N &&
           ((newplan.lieu[newx+1][newy+1]==ROI_B && newx<7 && newy<7 ) ||            // Si le roi adverse met en échec
           (newplan.lieu[newx+1][newy]==ROI_B && newx<7 ) ||
           (newplan.lieu[newx+1][newy-1]==ROI_B && newx<7 && newy>0) ||
           (newplan.lieu[newx][newy+1]==ROI_B && newy<7) ||
           (newplan.lieu[newx][newy-1]==ROI_B && newy>0 ) ||
           (newplan.lieu[newx-1][newy+1]==ROI_B && newx>0 && newy<7) ||
           (newplan.lieu[newx-1][newy]==ROI_B && newx>0) ||
           (newplan.lieu[newx-1][newy-1]==ROI_B && newx>0 && newy>0))   )                return 1;

        if(                              newplan.lieu[newx][newy]!=ROI_N &&
           ((newplan.lieu[newx+1][newy+1]==ROI_B && newx<7 && newy<7 && Verification_mouvement(newplan,newx+1,newy+1,newx,newy)) ||            // Si le roi adverse met en échec
           (newplan.lieu[newx+1][newy]==ROI_B && newx<7 &&             Verification_mouvement(newplan,newx+1,newy,newx,newy)) ||
           (newplan.lieu[newx+1][newy-1]==ROI_B && newx<7 && newy>0 && Verification_mouvement(newplan,newx+1,newy-1,newx,newy)) ||
           (newplan.lieu[newx][newy+1]==ROI_B && newy<7 &&             Verification_mouvement(newplan,newx,newy+1,newx,newy)) ||
           (newplan.lieu[newx][newy-1]==ROI_B && newy>0 &&             Verification_mouvement(newplan,newx,newy-1,newx,newy)) ||
           (newplan.lieu[newx-1][newy+1]==ROI_B && newx>0 && newy<7 && Verification_mouvement(newplan,newx-1,newy+1,newx,newy)) ||
           (newplan.lieu[newx-1][newy]==ROI_B && newx>0 &&             Verification_mouvement(newplan,newx-1,newy,newx,newy)) ||
           (newplan.lieu[newx-1][newy-1]==ROI_B && newx>0 && newy>0 && Verification_mouvement(newplan,newx-1,newy-1,newx,newy)))   )                return 1;


        if((newplan.lieu[newx+1][newy+1]==PION_B && newx<7 && newy>0) ||
           (newplan.lieu[newx-1][newy+1]==PION_B && newx>0 && newy>0))                 return 1;






        i=newy+1;
        while(i<8)                                          // On regarde en dessous ( en colonne )
        {
            if(newplan.lieu[newx][i]!=VIDE)
            {
                if(newplan.lieu[newx][i]==TOUR_B || newplan.lieu[newx][i]==DAME_B) return 1;
                i=8;
            }
            i++;
        }
        i=newx+1;
        while(i<8)                                          // On regarde à droite ( en ligne )
        {
            if(newplan.lieu[i][newy]!=VIDE)
            {
                if(newplan.lieu[i][newy]==TOUR_B || newplan.lieu[i][newy]==DAME_B) return 1;
                i=8;
            }
            i++;
        }
        i=newy-1;
        while(i>-1)                                          // On regarde au dessus ( en colonne )
        {
            if(newplan.lieu[newx][i]!=VIDE)
            {
                if(newplan.lieu[newx][i]==TOUR_B || newplan.lieu[newx][i]==DAME_B) return 1;
                i=-1;
            }
            i--;
        }
        i=newx-1;
        while(i>-1)                                          // On regarde à gauche ( en ligne )
        {
            if(newplan.lieu[i][newy]!=VIDE)
            {
                if(newplan.lieu[i][newy]==TOUR_B || newplan.lieu[i][newy]==DAME_B) return 1;
                i=-1;
            }
            i--;
        }



        // On passe aux diagonales ( FOU + DAME )
        i=newx+1;
        j=newy+1;
        while(j<8 && i<8)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_B || newplan.lieu[i][j]==DAME_B) return 1;
                i=8;
            }
            i++;
            j++;
        }
        i=newx+1;
        j=newy-1;
        while(j>-1 && i<8)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_B || newplan.lieu[i][j]==DAME_B) return 1;
                i=8;
            }
            i++;
            j--;
        }
        i=newx-1;
        j=newy+1;
        while(j<8 && i>-1)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_B || newplan.lieu[i][j]==DAME_B) return 1;
                i=-1;
            }
            i--;
            j++;
        }
        i=newx-1;
        j=newy-1;
        while(j>-1 && i>-1)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_B || newplan.lieu[i][j]==DAME_B) return 1;
                i=-1;
            }
            i--;
            j--;
        }



    }



    if(newplan.lieu[newx][newy]<NOIR)
    {
        if((newplan.lieu[newx+1][newy+2]==CAVALIER_N && newx<7 && newy<6) ||       // Si un cavalier met en echec.
           (newplan.lieu[newx+1][newy-2]==CAVALIER_N && newx<7 && newy>1) ||
           (newplan.lieu[newx-1][newy+2]==CAVALIER_N && newx>0 && newy<6) ||
           (newplan.lieu[newx-1][newy-2]==CAVALIER_N  && newx>0 && newy>1)||
           (newplan.lieu[newx+2][newy+1]==CAVALIER_N  && newx<6 && newy<7)||
           (newplan.lieu[newx+2][newy-1]==CAVALIER_N && newx<6 && newy>0) ||
           (newplan.lieu[newx-2][newy+1]==CAVALIER_N && newx>1 && newy<7) ||
           (newplan.lieu[newx-2][newy-1]==CAVALIER_N && newx>1 && newy>0)   )          return 1;

        if(              newplan.lieu[newx][newy]==ROI_B &&
           ((newplan.lieu[newx+1][newy+1]==ROI_N && newx<7 && newy<7 ) ||            // Si le roi adverse met en échec
           (newplan.lieu[newx+1][newy]==ROI_N && newx<7 ) ||
           (newplan.lieu[newx+1][newy-1]==ROI_N && newx<7 && newy>0) ||
           (newplan.lieu[newx][newy+1]==ROI_N && newy<7) ||
           (newplan.lieu[newx][newy-1]==ROI_N && newy>0 ) ||
           (newplan.lieu[newx-1][newy+1]==ROI_N && newx>0 && newy<7) ||
           (newplan.lieu[newx-1][newy]==ROI_N && newx>0) ||
           (newplan.lieu[newx-1][newy-1]==ROI_N && newx>0 && newy>0))   )                return 1;

        if(                              newplan.lieu[newx][newy]!=ROI_B &&
           ((newplan.lieu[newx+1][newy+1]==ROI_N && newx<7 && newy<7 && Verification_mouvement(newplan,newx+1,newy+1,newx,newy)) ||            // Si le roi adverse met en échec
           (newplan.lieu[newx+1][newy]==ROI_N && newx<7 &&             Verification_mouvement(newplan,newx+1,newy,newx,newy)) ||
           (newplan.lieu[newx+1][newy-1]==ROI_N && newx<7 && newy>0 && Verification_mouvement(newplan,newx+1,newy-1,newx,newy)) ||
           (newplan.lieu[newx][newy+1]==ROI_N && newy<7 &&             Verification_mouvement(newplan,newx,newy+1,newx,newy)) ||
           (newplan.lieu[newx][newy-1]==ROI_N && newy>0 &&             Verification_mouvement(newplan,newx,newy-1,newx,newy)) ||
           (newplan.lieu[newx-1][newy+1]==ROI_N && newx>0 && newy<7 && Verification_mouvement(newplan,newx-1,newy+1,newx,newy)) ||
           (newplan.lieu[newx-1][newy]==ROI_N && newx>0 &&             Verification_mouvement(newplan,newx-1,newy,newx,newy)) ||
           (newplan.lieu[newx-1][newy-1]==ROI_N && newx>0 && newy>0 && Verification_mouvement(newplan,newx-1,newy-1,newx,newy)))   )                return 1;


        if((newplan.lieu[newx+1][newy-1]==PION_N && newx<7 && newy>0) ||
           (newplan.lieu[newx-1][newy-1]==PION_N && newx>0 && newy>0))                 return 1;






        i=newy+1;
        while(i<8)                                          // On regarde en dessous ( en colonne )
        {
            if(newplan.lieu[newx][i]!=VIDE)
            {
                if(newplan.lieu[newx][i]==TOUR_N || newplan.lieu[newx][i]==DAME_N) return 1;
                i=8;
            }
            i++;
        }
        i=newx+1;
        while(i<8)                                          // On regarde à droite ( en ligne )
        {
            if(newplan.lieu[i][newy]!=VIDE)
            {
                if(newplan.lieu[i][newy]==TOUR_N || newplan.lieu[i][newy]==DAME_N) return 1;
                i=8;
            }
            i++;
        }
        i=newy-1;
        while(i>-1)                                          // On regarde au dessus ( en colonne )
        {
            if(newplan.lieu[newx][i]!=VIDE)
            {
                if(newplan.lieu[newx][i]==TOUR_N || newplan.lieu[newx][i]==DAME_N) return 1;
                i=-1;
            }
            i--;
        }
        i=newx-1;
        while(i>-1)                                          // On regarde à gauche ( en ligne )
        {
            if(newplan.lieu[i][newy]!=VIDE)
            {
                if(newplan.lieu[i][newy]==TOUR_N || newplan.lieu[i][newy]==DAME_N) return 1;
                i=-1;
            }
            i--;
        }



        // On passe aux diagonales ( FOU + DAME )
        i=newx+1;
        j=newy+1;
        while(j<8 && i<8)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_N || newplan.lieu[i][j]==DAME_N) return 1;
                i=8;
            }
            i++;
            j++;
        }
        i=newx+1;
        j=newy-1;
        while(j>-1 && i<8)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_N || newplan.lieu[i][j]==DAME_N) return 1;
                i=8;
            }
            i++;
            j--;
        }
        i=newx-1;
        j=newy+1;
        while(j<8 && i>-1)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_N || newplan.lieu[i][j]==DAME_N) return 1;
                i=-1;
            }
            i--;
            j++;
        }
        i=newx-1;
        j=newy-1;
        while(j>-1 && i>-1)
        {
            if(newplan.lieu[i][j]!=VIDE)
            {
                if(newplan.lieu[i][j]==FOU_N || newplan.lieu[i][j]==DAME_N) return 1;
                i=-1;
            }
            i--;
            j--;
        }



    }

    return 0;
}


char Verification_mouvement(jeu plan, char oldx, char oldy, char newx, char newy)   // renvoie 1 si bon, renvoie 0 si pas bon. (-1 si problème)
{
    char OLD=plan.lieu[oldx][oldy], NEW=plan.lieu[newx][newy];
    char i=0,j=0;
    jeu plan_echec=plan;             // plan d'arrivée ( pour vérifier si le roi est en échec )
    plan_echec.lieu[newx][newy]=plan_echec.lieu[oldx][oldy];
    plan_echec.lieu[oldx][oldy]=VIDE;

    // D'abord : le coup met-il le roi en échec ? -> Mouvement du roi + clouage

    if(OLD<BLANC)
    {
        while(plan_echec.lieu[i][j]!=ROI_B)
        {
            i++;
            if(i==8)
            {
                i=0;
                j++;
            }
        }
        if(Verification_echec(plan_echec,i,j)) return 0;
    }
    else if(OLD>NOIR)
    {
        while(plan_echec.lieu[i][j]!=ROI_N)
        {
            i++;
            if(i==8)
            {
                i=0;
                j++;
            }
        }
        if(Verification_echec(plan_echec,i,j)) return 0;
    }

        // Ensuite on vérifie si le coup est bien possible en fonction des pièces.

    if(OLD==PION_B)
    {
        if(newx==oldx && newy==oldy-1 && NEW==VIDE) return 1;                                    // Une case vers l'avant
        if(newx==oldx && oldy==6 && newy==oldy-2 && plan.lieu[oldx][5]==VIDE && NEW==VIDE) return 1;    // Deux cases vers l'avant
        if((newx==oldx+1 || newx==oldx-1) && newy==oldy-1 && NEW > NOIR) return 1;             // Prendre pièce
        return 0;
    }
    else if(OLD==PION_N)
    {
        if(newx==oldx && newy==oldy+1 && NEW==VIDE) return 1;                                                 // Une case vers l'avant
        if(newx==oldx && oldy==1 && newy==oldy+2 && plan.lieu[oldx][2]==VIDE && NEW==VIDE) return 1;                 // Deux cases vers l'avant
        if((newx==oldx+1 || newx==oldx-1) && newy==oldy+1 && NEW < BLANC && NEW!=VIDE) return 1;            // Prendre pièce
        return 0;
    }

    else if(OLD==ROI_B)
    {
        if(-1 <= newx-oldx && newx-oldx <= 1 && -1 <= newy-oldy && newy-oldy <= 1 && (NEW > NOIR || NEW==VIDE)) return 1;    // Toute case autour excepté occupée
        if(!Verification_echec(plan,4,7) && !Verification_echec(plan,5,7) && oldx==4 && oldy==7 && newx==6 && oldy==7 && plan.lieu[5][7]==VIDE && plan.lieu[6][7]==VIDE && plan.lieu[7][7]==TOUR_B)
        {
            plan_echec=plan;
            plan_echec.lieu[5][7]=ROI_B;
            plan_echec.lieu[4][7]=VIDE;
            if(!Verification_echec(plan_echec,5,7))  return ROQUE_B_petit;
        }
        if(!Verification_echec(plan,4,7) && !Verification_echec(plan,3,7) && oldx==4 && oldy==7 && newx==2 && oldy==7
            && plan.lieu[3][7]==VIDE && plan.lieu[2][7]==VIDE && plan.lieu[1][7]==VIDE && plan.lieu[0][7]==TOUR_B)
        {
            plan_echec=plan;
            plan_echec.lieu[3][7]=ROI_B;
            plan_echec.lieu[4][7]=VIDE;
            if(!Verification_echec(plan_echec,3,7))  return ROQUE_B_grand;
        }
        return 0;
    }
    else if(OLD==ROI_N)
    {
        if(-1 <= newx-oldx && newx-oldx <= 1 && -1 <= newy-oldy && newy-oldy <= 1 && NEW < BLANC) return 1;                 // Toute case autour excepté occupée
        if(!Verification_echec(plan,4,0) &&oldx==4 && oldy==0 && newx==6 && oldy==0 && plan.lieu[5][0]==VIDE && plan.lieu[6][0]==VIDE && plan.lieu[7][0]==TOUR_N)
        {
            plan_echec=plan;
            plan_echec.lieu[5][0]=ROI_N;
            plan_echec.lieu[4][0]=VIDE;
            if(!Verification_echec(plan_echec,5,0))  return ROQUE_N_petit;
        }
        if(!Verification_echec(plan,4,0)&&oldx==4 && oldy==0 && newx==2 && oldy==0&& plan.lieu[3][0]==VIDE && plan.lieu[2][0]==VIDE && plan.lieu[1][0]==VIDE && plan.lieu[0][0]==TOUR_N)
        {
            plan_echec=plan;
            plan_echec.lieu[3][0]=ROI_N;
            plan_echec.lieu[4][0]=VIDE;
            if(!Verification_echec(plan_echec,3,0))  return ROQUE_N_grand;
        }
        return 0;
    }

    else if(OLD==CAVALIER_B)
    {
        if(newx==oldx+1 && (newy == oldy+2 || newy == oldy-2) && (NEW > NOIR || NEW==VIDE)) return 1;
        if(newx==oldx-1 && (newy == oldy+2 || newy == oldy-2) && (NEW > NOIR || NEW==VIDE)) return 1;
        if(newx==oldx+2 && (newy == oldy+1 || newy == oldy-1) && (NEW > NOIR || NEW==VIDE)) return 1;
        if(newx==oldx-2 && (newy == oldy+1 || newy == oldy-1) && (NEW > NOIR || NEW==VIDE)) return 1;
        return 0;
    }
    else if(OLD==CAVALIER_N)
    {
        if(newx==oldx+1 && (newy == oldy+2 || newy == oldy-2) && NEW < BLANC) return 1;
        if(newx==oldx-1 && (newy == oldy+2 || newy == oldy-2) && NEW < BLANC) return 1;
        if(newx==oldx+2 && (newy == oldy+1 || newy == oldy-1) && NEW < BLANC) return 1;
        if(newx==oldx-2 && (newy == oldy+1 || newy == oldy-1) && NEW < BLANC) return 1;
        return 0;
    }
    else if(OLD==TOUR_B)
    {
        if(NEW>NOIR || NEW==VIDE)
        {
            if(newx==oldx)
            {
                if(newy<oldy)
                {
                    i=newy+1;
                    while(i<oldy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newy>oldy)
                {
                    i=oldy+1;
                    while(i<newy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
            if(newy==oldy)
            {
                if(newx<oldx)
                {
                    i=newx+1;
                    while(i<oldx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newx>oldx)
                {
                    i=oldx+1;
                    while(i<newx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
        }
        return 0;
    }
    else if(OLD==TOUR_N)
    {
        if(NEW<BLANC)
        {
            if(newx==oldx)
            {
                if(newy<oldy)
                {
                    i=newy+1;
                    while(i<oldy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newy>oldy)
                {
                    i=oldy+1;
                    while(i<newy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
            if(newy==oldy)
            {
                if(newx<oldx)
                {
                    i=newx+1;
                    while(i<oldx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newx>oldx)
                {
                    i=oldx+1;
                    while(i<newx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
        }
        return 0;
    }
    else if(OLD==FOU_B)
    {
        if((NEW>NOIR || NEW==VIDE) && newx-oldx == newy-oldy)
        {
            if(newy<oldy)
            {
                i=newx+1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx+1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            return 1;
        }
        if((NEW>NOIR || NEW==VIDE) && newx-oldx == oldy-newy)
        {
            if(newy<oldy)
            {
                i=newx-1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx-1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            return 1;
        }
    return 0;
    }
    else if(OLD==FOU_N)
    {
        if(NEW<BLANC && newx-oldx == newy-oldy)
        {
            if(newy<oldy)
            {
                i=newx+1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx+1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            return 1;
        }
        if(NEW<BLANC && newx-oldx == oldy-newy)
        {
            if(newy<oldy)
            {
                i=newx-1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx-1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            return 1;
        }
    return 0;
    }
    else if(OLD==DAME_B)
    {
        if((NEW>NOIR || NEW==VIDE) && newx-oldx == newy-oldy)
        {
            if(newy<oldy)
            {
                i=newx+1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx+1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            return 1;
        }
        if((NEW>NOIR || NEW==VIDE) && newx-oldx == oldy-newy)
        {
            if(newy<oldy)
            {
                i=newx-1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx-1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            return 1;
        }
        if(NEW>NOIR || NEW==VIDE)
        {
            if(newx==oldx)
            {
                if(newy<oldy)
                {
                    i=newy+1;
                    while(i<oldy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newy>oldy)
                {
                    i=oldy+1;
                    while(i<newy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
            if(newy==oldy)
            {
                if(newx<oldx)
                {
                    i=newx+1;
                    while(i<oldx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newx>oldx)
                {
                    i=oldx+1;
                    while(i<newx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
        }
        return 0;
    }
    else if(OLD==DAME_N)
    {
        if(NEW<BLANC && newx-oldx == newy-oldy)
        {
            if(newy<oldy)
            {
                i=newx+1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx+1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i++;
                    j++;
                }
            }
            return 1;
        }
        if(NEW<BLANC && newx-oldx == oldy-newy)
        {
            if(newy<oldy)
            {
                i=newx-1;
                j=newy+1;
                while(j<oldy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            if(newy>oldy)
            {
                i=oldx-1;
                j=oldy+1;
                while(j<newy)
                {
                    if(plan.lieu[i][j]!=VIDE) return 0;
                    i--;
                    j++;
                }
            }
            return 1;
        }
        if(NEW<BLANC)
        {
            if(newx==oldx)
            {
                if(newy<oldy)
                {
                    i=newy+1;
                    while(i<oldy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newy>oldy)
                {
                    i=oldy+1;
                    while(i<newy)
                    {
                        if(plan.lieu[newx][i]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
            if(newy==oldy)
            {
                if(newx<oldx)
                {
                    i=newx+1;
                    while(i<oldx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                if(newx>oldx)
                {
                    i=oldx+1;
                    while(i<newx)
                    {
                        if(plan.lieu[i][newy]!=VIDE) return 0;
                        i++;
                    }
                }
                return 1;
            }
        }
        return 0;
    }
   return -1;
}


char Echec_mat(jeu plan)   // renvoie 1 si echec et mat, 0 sinon
{
    char i=0,j=0, a=0,b=0, k=0,l=0;

    if(!plan.tour%2)   // plan.tour%2 = 0 : tour aux blancs
    {

        while(plan.lieu[i][j]!=ROI_B)              // On vérifie que le roi blanc n'est pas mat
        {
            i++;
            if(i==8)
            {
                i=0;
                j++;
            }
        }

        if(!Verification_echec(plan,i,j)) return 0;                                  // CAS : Mouvements du roi
        if(Verification_mouvement(plan,i,j,i-1,j-1) && i>0 && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i-1,j) && i>0) return 0;
        if(Verification_mouvement(plan,i,j,i-1,j+1) && i>0 && j<7) return 0;
        if(Verification_mouvement(plan,i,j,i,j-1) && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i,j+1) && j<7) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j-1) && i<7 && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j) && i<7) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j+1) && i<7 && j<7) return 0;

        if(Verification_echec(plan,plan.apres_x,plan.apres_y)) return 0;            // CAS : prise de la pièce attaquante

        if(plan.lieu[plan.apres_x][plan.apres_y]==FOU_N || plan.lieu[plan.apres_x][plan.apres_y]==DAME_N)     // cas : Intercalage en diagonale
        {
            if(plan.apres_x<i && plan.apres_y<j)
            {
                a=plan.apres_x+1;
                b=plan.apres_y+1;
                while(a<i && b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                    b++;
                }
            }
            if(plan.apres_x>i && plan.apres_y<j)
            {
                a=plan.apres_x-1;
                b=plan.apres_y+1;
                while(a>i && b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                    b++;
                }
            }
            if(plan.apres_x<i && plan.apres_y>j)
            {
                a=plan.apres_x+1;
                b=plan.apres_y-1;
                while(a<i && b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                    b--;
                }
            }
            if(plan.apres_x>i && plan.apres_y>j)
            {
                a=plan.apres_x-1;
                b=plan.apres_y-1;
                while(a>i && b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                    b--;
                }
            }
        }

        if(plan.lieu[plan.apres_x][plan.apres_y]==TOUR_N || plan.lieu[plan.apres_x][plan.apres_y]==DAME_N)     // cas : Intercalage en colonne/ligne
        {
            if(plan.apres_x==i && plan.apres_y<j)
            {
                b=plan.apres_y+1;
                while(b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,plan.apres_x,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    b++;
                }
            }
            if(plan.apres_x>i && plan.apres_y==j)
            {
                a=plan.apres_x-1;
                while(a>i)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,plan.apres_y)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                }
            }
            if(plan.apres_x<i && plan.apres_y==j)
            {
                a=plan.apres_x+1;
                while(a<i)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,a,plan.apres_y)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                }
            }
            if(plan.apres_x==i && plan.apres_y>j)
            {
                b=plan.apres_y-1;
                while(b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]<BLANC || plan.lieu[k][l]!=VIDE) if(Verification_mouvement(plan,k,l,plan.apres_x,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    b--;
                }
            }
        }

    }











    else        // plan.tour%2 = 1 : tour aux noirs
    {
        while(plan.lieu[i][j]!=ROI_N)              // On vérifie que le roi noir n'est pas mat
        {
            i++;
            if(i==8)
            {
                i=0;
                j++;
            }
        }

        if(!Verification_echec(plan,i,j)) return 0;
        if(Verification_mouvement(plan,i,j,i-1,j-1) && i>0 && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i-1,j) && i>0) return 0;
        if(Verification_mouvement(plan,i,j,i-1,j+1) && i>0 && j<7) return 0;
        if(Verification_mouvement(plan,i,j,i,j-1) && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i,j+1) && j<7) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j-1) && i<7 && j>0) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j) && i<7) return 0;
        if(Verification_mouvement(plan,i,j,i+1,j+1) && i<7 && j<7) return 0;

        if(Verification_echec(plan,plan.apres_x,plan.apres_y)) return 0;

         if(plan.lieu[plan.apres_x][plan.apres_y]==FOU_B || plan.lieu[plan.apres_x][plan.apres_y]==DAME_B)     // cas : Intercalage en diagonale
        {
            if(plan.apres_x<i && plan.apres_y<j)
            {
                a=plan.apres_x+1;
                b=plan.apres_y+1;
                while(a<i && b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                    b++;
                }
            }
            if(plan.apres_x>i && plan.apres_y<j)
            {
                a=plan.apres_x-1;
                b=plan.apres_y+1;
                while(a>i && b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                    b++;
                }
            }
            if(plan.apres_x<i && plan.apres_y>j)
            {
                a=plan.apres_x+1;
                b=plan.apres_y-1;
                while(a<i && b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                    b--;
                }
            }
            if(plan.apres_x>i && plan.apres_y>j)
            {
                a=plan.apres_x-1;
                b=plan.apres_y-1;
                while(a>i && b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                    b--;
                }
            }
        }

        if(plan.lieu[plan.apres_x][plan.apres_y]==TOUR_B || plan.lieu[plan.apres_x][plan.apres_y]==DAME_B)     // cas : Intercalage en colonne/ligne
        {
            if(plan.apres_x==i && plan.apres_y<j)
            {
                b=plan.apres_y+1;
                while(b<j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,plan.apres_x,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    b++;
                }
            }
            if(plan.apres_x>i && plan.apres_y==j)
            {
                a=plan.apres_x-1;
                while(a>i)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,plan.apres_y)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a--;
                }
            }
            if(plan.apres_x<i && plan.apres_y==j)
            {
                a=plan.apres_x+1;
                while(a<i)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,a,plan.apres_y)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    a++;
                }
            }
            if(plan.apres_x==i && plan.apres_y>j)
            {
                b=plan.apres_y-1;
                while(b>j)
                {
                    k=0;
                    l=0;
                    while(l<8)
                    {
                        while(k<8)
                        {
                            if(plan.lieu[k][l]>NOIR) if(Verification_mouvement(plan,k,l,plan.apres_x,b)) return 0;
                            k++;
                        }
                        l++;
                        k=0;
                    }
                    b--;
                }
            }
        }

    }


    return 1;
}


jeu Deplacement(SDL_Surface *ecran, jeu plan)
{
    SDL_Event event;
    char fin=1, clic=0, pos_clic_x=0, pos_clic_y=0, pos_final_x=0, pos_final_y=0, verif=0;

    while(fin)
    {
        SDL_WaitEvent(&event);

        if(event.type==SDL_QUIT)                                                 // Si on quitte la partie.
        {
            fin=0;
            plan.shut=0;
            plan.exit=0;
        }
        else if(event.key.keysym.sym==SDLK_F4 && event.type==SDL_KEYUP)
        {
            fin=0;
            plan.shut=0;
            plan.exit=0;
        }
        else if(event.key.keysym.sym==SDLK_ESCAPE && event.type==SDL_KEYUP)    // Pour retourner au menu
        {
            fin=0;
            plan.shut=1;
            plan.exit=0;
        }







        else if(event.type==SDL_MOUSEBUTTONDOWN && clic==0)    // Si le clic s'enfonce
        {
            SDL_ShowCursor(0);
            clic=1;
            pos_clic_x=event.motion.x/TAILLE;
            pos_clic_y=event.motion.y/TAILLE;
        }
        else if(event.type==SDL_MOUSEBUTTONUP & clic==1)   // Si le clic se relache
        {
            SDL_ShowCursor(1);
            clic=0;
            pos_final_x=event.motion.x/TAILLE;
            pos_final_y=event.motion.y/TAILLE;

            if(!(pos_clic_x==pos_final_x && pos_clic_y==pos_final_y) && ((plan.tour%2==0 && plan.lieu[pos_clic_x][pos_clic_y]<BLANC && plan.lieu[pos_clic_x][pos_clic_y]!=VIDE)||(plan.tour%2==1 && plan.lieu[pos_clic_x][pos_clic_y]>NOIR)))
                // si la pièce n'est pas relaché à son emplacement d'origine et que ce fut une pièce valable
            {
                verif=Verification_mouvement(plan, pos_clic_x, pos_clic_y, pos_final_x, pos_final_y);
                if(verif) // si le mouvement est possible
                {
                    plan.lieu[pos_final_x][pos_final_y] = plan.lieu[pos_clic_x][pos_clic_y];
                    plan.lieu[pos_clic_x][pos_clic_y] = VIDE;
                    plan.avant_x=pos_clic_x;   // On indique la case pour les marquages
                    plan.avant_y=pos_clic_y;   // en couleur indiquant la pièce déplacée
                    plan.apres_x=pos_final_x;  // et dans la fonction Echec_mat()
                    plan.apres_y=pos_final_y;  // pour connaitre la pièce attaquant le roi


                    fin=0;
                }
                while(plan.lieu[pos_final_x][0] == PION_B)   // Si Pion arrive au bout, on propose un changement de pièce
                {
                    SDL_WaitEvent(&event);

                         if(event.key.keysym.sym==SDLK_d && event.type==SDL_KEYUP) plan.lieu[pos_final_x][0] = DAME_B;
                    else if(event.key.keysym.sym==SDLK_f && event.type==SDL_KEYUP) plan.lieu[pos_final_x][0] = FOU_B;
                    else if(event.key.keysym.sym==SDLK_c && event.type==SDL_KEYUP) plan.lieu[pos_final_x][0] = CAVALIER_B;
                    else if(event.key.keysym.sym==SDLK_t && event.type==SDL_KEYUP) plan.lieu[pos_final_x][0] = TOUR_B;
                }
                while(plan.lieu[pos_final_x][7] == PION_N)   // Si Pion arrive au bout, on propose un changement de pièce
                {
                    SDL_WaitEvent(&event);

                         if(event.key.keysym.sym==SDLK_d && event.type==SDL_KEYUP) plan.lieu[pos_final_x][7] = DAME_N;
                    else if(event.key.keysym.sym==SDLK_f && event.type==SDL_KEYUP) plan.lieu[pos_final_x][7] = FOU_N;
                    else if(event.key.keysym.sym==SDLK_c && event.type==SDL_KEYUP) plan.lieu[pos_final_x][7] = CAVALIER_N;
                    else if(event.key.keysym.sym==SDLK_t && event.type==SDL_KEYUP) plan.lieu[pos_final_x][7] = TOUR_N;
                }
                if(verif==ROQUE_B_grand)    // En cas de roque
                {
                    plan.lieu[0][7]=VIDE;
                    plan.lieu[3][7]=TOUR_B;
                }
                else if(verif==ROQUE_N_grand)    // En cas de roque
                {
                    plan.lieu[0][0]=VIDE;
                    plan.lieu[3][0]=TOUR_N;
                }
                else if(verif==ROQUE_B_petit)    // En cas de roque
                {
                    plan.lieu[7][7]=VIDE;
                    plan.lieu[5][7]=TOUR_B;
                }
                else if(verif==ROQUE_N_petit)    // En cas de roque
                {
                    plan.lieu[7][0]=VIDE;
                    plan.lieu[5][0]=TOUR_N;
                }
            }
            Blit_Jeu(ecran,plan);
        }

        if(clic && ((plan.tour%2==0 && plan.lieu[pos_clic_x][pos_clic_y]<BLANC && plan.lieu[pos_clic_x][pos_clic_y]!=VIDE)||(plan.tour%2==1 && plan.lieu[pos_clic_x][pos_clic_y]>NOIR)))
            // Si le clic est enfoncé et ayant pris une pièce valable (blanc au tour blanc ... )
        {
            Blit_Jeu(ecran,plan);                                                            // Reblitte l'echiquier
            Blit(ecran,VIDE, pos_clic_x*TAILLE, pos_clic_y*TAILLE);                                        // Vide la case de la pièce en déplacement
            Blit(ecran,plan.lieu[pos_clic_x][pos_clic_y], event.motion.x-TAILLE/2, event.motion.y-TAILLE/2);   // Place la pièce à la place du curseur


        }
            SDL_Flip(ecran);


    }



    return plan;
}

int Valeur_Attaque(jeu plan, char COULEUR)  // Retourne une valeur correspondant aux points des pièces attaquées par couleur.
{
    int valeur=0;
    char i=0, j=0, a=0, b=0;

        plan.tour=0;
        if(Echec_mat(plan)) return 10000;
        plan.tour=1;
        if(Echec_mat(plan)) return -10000; /// SOUCI INCONNU et dans la grande boucle aussi
        while(i<8)
        {
            while(j<8)
            {
                if(plan.lieu[i][j]<BLANC && plan.lieu[i][j]!=VIDE)
                {
                    if(plan.lieu[i][j]==PION_B) valeur=valeur-10;
                    else if(plan.lieu[i][j]==TOUR_B) valeur=valeur-50;
                    else if(plan.lieu[i][j]==CAVALIER_B) valeur=valeur-35;
                    else if(plan.lieu[i][j]==FOU_B) valeur=valeur-35;
                    else if(plan.lieu[i][j]==DAME_B) valeur=valeur-100;
                    while(a<8)
                    {
                        while(b<8)
                        {
                            if(plan.lieu[a][b]>NOIR)
                            if(Verification_mouvement(plan,i,j,a,b))
                            {
                                if(plan.lieu[a][b]==PION_N) valeur=valeur-1;
                                else if(plan.lieu[a][b]==TOUR_N) valeur=valeur-5;
                                else if(plan.lieu[a][b]==CAVALIER_N) valeur=valeur-3;
                                else if(plan.lieu[a][b]==FOU_N) valeur=valeur-3;
                                else if(plan.lieu[a][b]==DAME_N) valeur=valeur-10;
                                else if(plan.lieu[a][b]==ROI_N) valeur=valeur-20;
                            }
                            b++;
                        }
                        b=0;
                        a++;
                    }
                    a=0;
                }
                else if(plan.lieu[i][j]>NOIR)
                {
                    if(plan.lieu[i][j]==PION_N) valeur=valeur+10;
                    else if(plan.lieu[i][j]==TOUR_N) valeur=valeur+50;
                    else if(plan.lieu[i][j]==CAVALIER_N) valeur=valeur+35;
                    else if(plan.lieu[i][j]==FOU_N) valeur=valeur+35;
                    else if(plan.lieu[i][j]==DAME_N) valeur=valeur+100;
                    while(a<8)
                    {
                        while(b<8)
                        {
                            if(plan.lieu[a][b]<BLANC && plan.lieu[a][b]!=VIDE)
                            if(Verification_mouvement(plan,i,j,a,b))
                            {
                                if(plan.lieu[a][b]==PION_B) valeur=valeur+1;
                                else if(plan.lieu[a][b]==TOUR_B) valeur=valeur+5;
                                else if(plan.lieu[a][b]==CAVALIER_B) valeur=valeur+3;
                                else if(plan.lieu[a][b]==FOU_B) valeur=valeur+3;
                                else if(plan.lieu[a][b]==DAME_B) valeur=valeur+10;
                                else if(plan.lieu[a][b]==ROI_B) valeur=valeur+20;
                            }
                            b++;
                        }
                        b=0;
                        a++;
                    }
                    a=0;
                }
                j++;
            }
            j=0;
            i++;
        }

    if(COULEUR==BLANC) return -valeur;

    return valeur;
}


jeu Meilleur_coup(jeu plan, int nb_coup)
{

    jeu faux_plan1, faux_plan2;
    char i=0, j=0, a=0, b=0, i1=0, j1=0, a1=0, b1=0;
    int  max_i1=0, max_j1=0, max_a1=0, max_b1=0, MAX2=-100000, max_i2=0, max_j2=0, max_a2=0, max_b2=0, c=-100000;

    // max2 retient le nombre total de coup possible au dernier tour.
    // maxi2 et maxj2 désigneront le "plus grand actuel"

    if(nb_coup==0)  // Regarder juste à un coup d'avance
    {
        while(i1<8)
        {
            while(j1<8)
            {
                if((plan.lieu[i1][j1]>NOIR && plan.tour%2==1) || (plan.lieu[i1][j1]<BLANC && plan.lieu[i1][j1]!=VIDE && plan.tour%2==0))
                {
                    while(a1<8)
                    {
                        while(b1<8)
                        {
                            if(Verification_mouvement(plan,i1,j1,a1,b1))
                            {
                                faux_plan1=plan;
                                faux_plan1.lieu[a1][b1]=faux_plan1.lieu[i1][j1];
                                faux_plan1.lieu[i1][j1]=VIDE;
                                faux_plan1.avant_x=i1;
                                faux_plan1.avant_y=j1;
                                faux_plan1.apres_x=a1;
                                faux_plan1.apres_y=b1;

                                if(plan.tour%2==1) c=Valeur_Attaque(faux_plan1,NOIR);
                                else c=Valeur_Attaque(faux_plan1,BLANC);
                                if(c>MAX2)
                                {
                                    MAX2=c;
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
        plan.lieu[max_a1][max_b1]=plan.lieu[max_i1][max_j1];
        plan.lieu[max_i1][max_j1]=VIDE;
        plan.avant_x=max_i1;
        plan.avant_y=max_j1;
        plan.apres_x=max_a1;
        plan.apres_y=max_b1;
        return plan;

    }




    while(i<8)
    {
        while(j<8)
        {
            if((plan.lieu[i][j]>NOIR && plan.tour%2==1) || (plan.lieu[i][j]<BLANC && plan.lieu[i][j]!=VIDE && plan.tour%2==0))
            {
                while(a<8)
                {
                    while(b<8)
                    {
                        if(Verification_mouvement(plan,i,j,a,b))
                        {
                            // On effectue un premier coup.
                            faux_plan1=plan;
                            faux_plan1.lieu[a][b]=plan.lieu[i][j];
                            faux_plan1.lieu[i][j]=VIDE;
                            faux_plan1.tour++;
                            faux_plan1.avant_x=i;
                            faux_plan1.avant_y=j;
                            faux_plan1.apres_x=a;
                            faux_plan1.apres_y=b;
                            if(plan.tour%2==1) c=Valeur_Attaque(faux_plan1,NOIR);
                            else c=Valeur_Attaque(faux_plan1,BLANC);
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
                            faux_plan1=Meilleur_coup(faux_plan1,nb_coup-1);
                            faux_plan1.tour++;


                            while(i1<8)
                            {
                                while(j1<8)
                                {
                                    if((plan.lieu[i1][j1]>NOIR && plan.tour%2==1) || (plan.lieu[i1][j1]<BLANC && plan.lieu[i1][j1]!=VIDE && plan.tour%2==0))
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
                                                    faux_plan2.tour++;
                                                    faux_plan2.avant_x=i1;
                                                    faux_plan2.avant_y=j1;
                                                    faux_plan2.apres_x=a1;
                                                    faux_plan2.apres_y=b1;
                                                    if(plan.tour%2==1) c=Valeur_Attaque(faux_plan2,NOIR);
                                                    else c=Valeur_Attaque(faux_plan2,BLANC);
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
                            i1=0;
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
    return plan;

}





