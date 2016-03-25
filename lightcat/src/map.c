#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Graphique.h"

/*struct Coord // Pour Case.
    {
        long x;
        long y;
    };


SDL_Surface *Case[50][50];
SDL_Rect casexy[50][50];
struct Coord coord[50];
long c = 0, z=0;

//while(c < 51 || z < 51)
//        {
//            coord[c].x = 16*c;
//            coord[c].y = 16*c;
//            casexy[z][c].x = 16*z;
//            casexy[z][c].y = 16*c;
//            c++;
//            if(c == 51)
//            {
//                c = 0;
//                z++;
//            }
//        }

// Fonction de Rapport : *.map1 ---> Case[][]

struct GraphMapEdit
{
    int file; // Nom du chipset
    int x; // X de la case à recuperer
    int y; // Y "
};
struct GraphMapEdit2
{
    char file[20];
    int x;
    int y;
};
*/



// Maintenant on doit assigné chaque file000 + x000 +y000 a ce qui convient.
// file = Chipset n°XXX --> Chaque Chipset commencera par : 001-xxxxx.bmp . Ainsi il est facile de reconnaire chaque chip'
// Assignation en String modifiable si nécéssare
// x = X abscisse --> X de la case à chopper (une case = 16X)
// y "

SDL_Rect C00(struct GraphMapEdit cxy) // C00(CASE(Case[][], 000)) par exemple
{
    SDL_Rect retour;
    //retour.file[0] = 'A';
    retour.x = cxy.x;
    retour.y = cxy.y;
    retour.w = 16;
    retour.h = 16;
    return retour;
}
//Il faudra initialiser le retour à -1 pour que la case deviennent Noire en cas de map trop petite, quand on aura melanger les struct en une seule.
// Il faudra donc faire une case spéciale NOIRE pour le vide.

// PARTIE CRUCIALE : Prendre le chipset et choisir la bonne case.

// Idée : Blitter chaque chaque fois un .bmp chipset et cacher une partie avec une couleur de transparence ce qui laissera voir un autre chipset
//qui sera en dessous et encore en transparence ...

