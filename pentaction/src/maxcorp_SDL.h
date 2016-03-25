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
    char txt[100];         // Texte préinscrit
}
_ecrire;

typedef struct situation
{
    int enfoncees;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;
    int o;
    int p;
    int q;
    int r;
    int s;
    int t;
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;
    int k0;
    int k1;
    int k2;
    int k3;
    int k4;
    int k5;
    int k6;
    int k7;
    int k8;
    int k9;
    int kp0;
    int kp1;
    int kp2;
    int kp3;
    int kp4;
    int kp5;
    int kp6;
    int kp7;
    int kp8;
    int kp9;
    int enter;
    int backspace;
    int space;
    int capslock;
    int maj;
    int tab;
    int f1;
    int f2;
    int f3;
    int f4;
    int f5;
    int f6;
    int f7;
    int f8;
    int f9;
    int f10;
    int f11;
    int f12;
    int escape;
    int clic_d;
    int clic_g;
    int clic_m;
    int mousex;
    int mousey;
    int kp_point;
    int kp_plus;
    int kp_moins;
    int kp_etoile;
    int kp_slash;
    int k_point;
    int k_ask;
    int k_slash;
    int k_exclam;
    int k_plus;
    int k_degre;
    int k_circonflexe;
    int k_dollar;
    int k_pourcentage;
    int k_micro;
    int haut;
    int bas;
    int gauche;
    int droite;
    int exit;
    int kp_enter;
    int clicx;
    int clicy;
}
situation;

extern situation Situation;

_ecrire Definir_ecrire();
situation Definir_situation();
char *Ecrire(SDL_Surface *ecran, _ecrire recu);  // Renvoi ce qui a été tapé
void Blit(SDL_Surface *ecran, int x, int y, int w, int h, int R, int V, int B);
void Changer_situation();
void BlitBall(SDL_Surface *ecran, int x, int y, int r, int R, int V, int B) ;
void BlitLine(SDL_Surface *ecran, int x1, int y1, int x2, int y2, int R, int V, int B);
