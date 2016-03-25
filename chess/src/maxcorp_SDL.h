#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include <SDL_ttf.h>


typedef struct _ecrire
{
    SDL_Rect pos;          // (x,y) placement du d�but d'�criture // (w,h)  longueur maximale ( donc longueur du cache �ventuel )
    SDL_Color fond;        // Couleur du fond
    SDL_Color couleur;     // Couleur d'ecriture
    TTF_Font *police;      // Police utilis�e
    char txt[100];             // Texte pr�inscrit
}
_ecrire;



_ecrire Definir_ecrire();


char *Ecrire(SDL_Surface *ecran, _ecrire recu);  // Renvoi ce qui a �t� tap�
