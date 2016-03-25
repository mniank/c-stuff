#include "maxcorp_SDL.h"

#define TAILLE 80

#define NOIR         9
#define BLANC        6

#define PION_N      10
#define PION_B       0
#define TOUR_N      11
#define TOUR_B       1
#define CAVALIER_N  12
#define CAVALIER_B   2
#define FOU_N       13
#define FOU_B        3
#define DAME_N      14
#define DAME_B       4
#define ROI_N       15
#define ROI_B        5
#define VIDE        -1

#define ROQUE_B_petit   21
#define ROQUE_N_petit   22
#define ROQUE_B_grand   23
#define ROQUE_N_grand   24

#define NB_COUP   3



typedef struct jeu
{
    char exit;        // 0 doit quitter, 1 continue
    char shut;        // 0 ferme complétement, 1 retour menu
    int tour;         // pair aux blancs  , impair aux noirs
    char lieu[8][8];  // Sur telle case on a telle pièce
    char avant_x;
    char avant_y;     // Placement de la dernière pièce déplacée : avant et après le mouvement.
    char apres_x;
    char apres_y;
    char nom[100];        // Nom du fichier si enregistrement
    char menu;        // Choix en sortie de menu
}
jeu;



char Echec_mat(jeu plan);

jeu Definir_Jeu();

void Blit_Jeu(SDL_Surface *ecran, jeu plan);

void Blit(SDL_Surface *ecran, char PIECE, int pos_x, int pos_y);

char Verification_echec(jeu plan, char newx, char newy);

char Verification_mouvement(jeu plan, char oldx, char oldy, char newx, char newy);

jeu Deplacement(SDL_Surface *ecran, jeu plan);

jeu menu(SDL_Surface *ecran);

char jouer(SDL_Surface *ecran, jeu choix_menu);

int Valeur_Attaque(jeu plan, char COULEUR);

jeu IA(jeu plan);

jeu Load(jeu plan);

void Save(jeu plan);

jeu Meilleur_coup(jeu plan, int nb_coup);
