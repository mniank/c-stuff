#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>


typedef struct _ecrire
{
    SDL_Rect pos;          // (x,y) placement du début d'écriture // (w,h)  longueur maximale ( donc longueur du cache éventuel )
    SDL_Color fond;        // Couleur du fond
    SDL_Color couleur;     // Couleur d'ecriture
    TTF_Font *police;      // Police utilisée
    char txt[100];             // Texte préinscrit
}
_ecrire;



_ecrire Definir_ecrire();


char *Ecrire(SDL_Surface *ecran, _ecrire recu);  // Renvoi ce qui a été tapé
