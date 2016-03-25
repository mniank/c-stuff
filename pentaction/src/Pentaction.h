#include <fmod.h>
#define TAILLE_X  960
#define TAILLE_Y  640

int Affichage_score(SDL_Surface *ecran, int score, int TYPE);
void Gestion_musique(FMOD_SYSTEM *system, char *nom);
void Affichage_score2(SDL_Surface *ecran, int score, int x, int y);

// COPTER

#define ECART_MIN        50
#define MAX_OBSTACLE     30
#define HAUTEUR_OBSTACLE 20
#define TAILLE_CARRE      9
#define POSITION_X      250

extern int L;
int Copter(SDL_Surface *ecran);
void Genere_couloir(SDL_Surface *ecran, int *couloir_b, int *couloir_h);
void Definir_couloir(int *couloir_b, int *couloir_h);
void Genere_obstacle(SDL_Surface *ecran, int fin_couloir_b, int fin_couloir_h, int *obstacle_x, int *obstacle_y, int *obstacle_t);
int Move(SDL_Surface *ecran, int py);
void Trainee_carre(SDL_Surface *ecran, int py);
int collide(int py, int *obstacle_x, int *obstacle_y, int *obstacle_t, int *couloir_b, int *couloir_h);



// FASTCLIC

extern int N;
int Fastclic(SDL_Surface *ecran);
int Genere_carre(SDL_Surface *ecran, int *carre_x, int *carre_y, int *carre_t, int *carre_c);
int Gerer_clic(int *carre_x, int *carre_y, int *carre_t);


// LONGER HIGHER

#define SUPPORT_X     100
#define SUPPORT_Y      20
#define MARTEAU_X      38  // Assimilé à 38 mais un cercle en réalité
#define MARTEAU_Y      38

int Longer_Higher(SDL_Surface *ecran);
void Mouvement_depart(SDL_Surface *ecran, int *a);
void Mouvement_reel(SDL_Surface *ecran, int *a);
int Gestion_lanceur(SDL_Surface *ecran, int *a, int *tir);

// FURTHERRUN

int Further_Run(SDL_Surface *ecran);
int Bouge_bonshommes(SDL_Surface *ecran, int *v, int *py, int *sup1, int *sup2, int *sup3);
void Saut_bonshommes(int *v);
void Gestion_support(SDL_Surface *ecran, int *sup1, int *sup2, int *sup3, int nb_en_jeu);

// DODGEALL

int Dodgeall (SDL_Surface *ecran);
int Collision(int px, int py, int *y, int *xdeb, int *xfin, int sens);
void Genere_mobile(SDL_Surface *ecran, int sens, int *y, int *xdeb, int *xfin, int ecart_moyen, int trou_moyen, int affichage);
void Bouge_souris(SDL_Surface *ecran, int *p);


/// MYSQL

int Envoie_donnee(int score, int score1, int score2, int score3, int score4, int score5, int t1, int t2, int t3, int t4, int t5);

