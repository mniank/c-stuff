#include <stdio.h>
#include <stdlib.h>

#define ESPECE_MAX 500

/*** IDEES ***/

// Température : Un espèce est adapté à la température du jour où elle est née.
// La température peut varier de -2 à +2 degré par jour (selon les probas, ca restera aux alentours de 20 )
// Plus on est proche de sa température de départ, plus on est favorisé ...

// Possibilité de mort. Aléatoire de 0 à x% de la population peut mourir à la fin de chaque jour. Peut etre faire jouer la température.

///*********///


typedef struct espece   // qui sera issu de vie ( vie[1] sera le tableau de l'espece 1)
{
    int nombre; /// nombre total d'individu de l'espece, on pourra eventuellement ajouter male/femelle
                /// On pourra alors ajouter une variable "Trouver la femelle"
    int chaine; // Donne la hauteur dans la chaine alimentaire
    int force; // Un niveau de force en opposition avec la defense
    int defense; // Un niveau de defense = resistance
    int vitesse; // Vitesse qui permet ou non rencontre avec une proie
    int portee; // Taille de la portee maximale d'une femelle
    int gestation; // Duree de gestation d'une femelle, en jours DEPENDANT DES AUTRES
    int aliment; // Quantité de nourriture nécessaire à la survie journalière DEPENDANT DES AUTRES
    int nourri; // Aliment procuré lorsque mangé par un autre animal DEPENDANT DES AUTRES
    int intelligence; // Apporte de nouvelles facultés et départage en cas de vitesse, ou de force/défense égale.
    int dechet; // Dechets organiques augmentant le niveau d'aliment mais aussi l'intensite de l'herbe
    int cible[ESPECE_MAX]; // Enregistre les cibles potentielles. (Evite de tout recalculer) -> A changer à l'extinction ou l'apparition d'une espece.
                    // Rempli de -1 à l'origine, de manière à ce qu'on s'arrete au premier -1 rencontré.
    int temperature; /// Température de naissance de l'espèce. Va influer sur l'herbe et les espèces en elles-memes.
    int capacite[10]; /// le vol, la plongée, sang chaud, ... qui serait un tableau regroupant les capacités ( 0 non acquise / 1 acquise )
}
espece;


void procedure(int nbjours, int periode_herbe, int intensite_herbe, int catastrophe);
void Calcul_cible(espece vie[], int viemax);


int main()
{
    srand(time(NULL));
    printf("C'est parti :\n");

// Initialisation du options.ini
    int nbjours=10000, periode_herbe=1, intensite_herbe=5000 ,catastrophe=0;
    // Catastrophe : 0 si non présentes, 1 si présentes.
    // Periode d'herbe : temps avant renouvellement
    // Intensité d'herbe, quantité d'herbe apportée à chaque renouvellement.



// Démarrage de l'etude
    procedure(nbjours, periode_herbe, intensite_herbe, catastrophe);

    printf("\nTermine !\n\n");
    system("PAUSE");
    return 0;
}



void procedure(int nbjours, int periode_herbe, int intensite_herbe, int catastrophe)
{
    int rapide[ESPECE_MAX]; // Qui va classer les espèce de la plus rapide à la plus lente ( pour se servir dans le garde-manger )
    int i=0;
    int j=0;
    int k=0;
    int p=0;
    int q=0;
    int s=0;
    int t=0;
    char ligne[2000];
    FILE* log=fopen("log.csv","w");                 /// Faire des log numéroté, pour le moment, un seul log enregistrable.
    FILE* fiche=fopen("fiche.csv","w");
    // Premiere ligne de fiche ( pour une meilleure lisibilité ) :
    fputs("Espèce;Naissance;Espèce mère;Hauteur de chaîne;Force;Défense;Vitesse;Portée;Intelligence;Déchet;Température;Durée de Gestation;Alimentation nécessaire;Nutriment",fiche);
// Initialisation de la base

    int temperature=20; // Température. Initialement 20.

    espece vie[ESPECE_MAX];      // L'ensemble des especes vivantes
    while(i<ESPECE_MAX)
    {
        vie[i].nombre=0;
        j=0;
        i++;
    }
    int viemax=1; // Le dernier slot utilisé dans vie
    // On donne le nombre d'herbe de départ :
    vie[0].nombre=intensite_herbe;
    vie[0].nourri=1; // L'herbe a une valeur nutritive de 1
    vie[0].chaine=0;
    vie[0].force=-1;
    vie[0].defense=-1;
    vie[0].vitesse=-1;
    vie[0].portee=0;
    vie[0].intelligence=0;
    vie[0].dechet=0;
    vie[0].temperature=20;

    // Définition de la première espèce :
    vie[1].nombre=2;
    vie[1].chaine=1;
    vie[1].force=0;
    vie[1].defense=0;
    vie[1].vitesse=0;
    vie[1].portee=7;
    vie[1].intelligence=0;
    vie[1].dechet=0;
    vie[1].temperature=20;

    vie[1].gestation = 1 + 5*vie[1].force + 5*vie[1].defense + vie[1].portee/2 + 10*vie[1].chaine;
    vie[1].aliment = 1 + vie[1].vitesse + 2*vie[1].force + 2*vie[1].defense + 2*vie[1].dechet;
    vie[1].nourri = 10 + 6*vie[1].force + 8*vie[1].defense;

    // On cible la vie[1] sur l'herbe.
    Calcul_cible(vie,viemax);
    rapide[1]=1;

// Lancement de la procedure
    int jour_actuel=1;

    while(jour_actuel<=nbjours)
    {
        printf("Jour : %d\n", jour_actuel); // On affiche la progression
        t=1;

        // Variation de température : [-2,2]
        temperature -= 1;
        temperature += rand()%3;
        if(temperature<-20) temperature=-20;
        else if(temperature>60) temperature=60;

        // Renouvellement d'herbe si jour modulo periode = 0
        if(jour_actuel%periode_herbe==0 && vie[0].nombre < intensite_herbe*(80+temperature)/100) vie[0].nombre=intensite_herbe*(80+temperature)/100;
        ///if(jour_actuel%periode_herbe==0 && vie[0].nombre < intensite_herbe) vie[0].nombre=intensite_herbe;

        while(t<=viemax)
        { // Premier arrivé, premier servi !
            i = rapide[t]; // On prend la tième plus rapide espèce.
            if(vie[i].nombre!=0)
            {
                // Chaque individu à un niveau a de dechet rapporte ax herbes ( 10a par exemple )
                vie[0].nombre += vie[i].nombre*2*vie[i].dechet;


        // SE NOURRIR

                // On fouille les cibles pour manger la quantité totale de nourriture necessaire. Le surplus survit, s'il y en a pas assez, l'espèce perd des individus.
                            // On décompte le nombre de cibles.
                j=0;
                while(vie[i].cible[j]!=-1 && j<=viemax) j++;
                            // Cas où pas de cibles :
                if(j==0)
                {
                    vie[i].nombre/=10;
                }

                            // Cas où cible unique
                else if(j==1)
                {
                    q = vie[vie[i].cible[0]].nombre; // on enregistre le nombre actuel de cible
                    vie[vie[i].cible[0]].nombre -= vie[i].aliment * vie[i].nombre / vie[vie[i].cible[0]].nourri * 8 / 10;
                    if(vie[vie[i].cible[0]].nombre<=q*2/5) // Cas où on bouffe plus de 60% de l'espèce ciblée
                    {
                        vie[i].nombre -= ((q*2/5) - vie[vie[i].cible[0]].nombre) * vie[vie[i].cible[0]].nourri / vie[i].aliment; // on supprime ceux qui n'ont pas bouffé
                        vie[vie[i].cible[0]].nombre = q*2/5; // on restaure la quantité de la cible
                        // Changement des cibles des autres espèces.
                        if(vie[vie[i].cible[0]].nombre==0) Calcul_cible(vie,viemax);
                    }
                }

                            // Cas où cible multiple :  10 aléatoires vont sélectionner une cible dont 10% des individus devront se nourrir s'ils le peuvent.
                else if(j>=2)           /// On pourra peut etre faire influer l'intelligence.
                {
                    k=0;
                    while(k<8)
                    {
                        p=rand()%j;  // On définit la cible aléatoirement.

                        q = vie[vie[i].cible[p]].nombre;
                        vie[vie[i].cible[p]].nombre -= vie[i].aliment * vie[i].nombre / vie[vie[i].cible[p]].nourri /10;
                        if(vie[vie[i].cible[p]].nombre<= q*23/25)
                        {
                            vie[i].nombre -= ((q*23/25) - vie[vie[i].cible[p]].nombre) * vie[vie[i].cible[p]].nourri / vie[i].aliment;
                            vie[vie[i].cible[0]].nombre = q*23/25;
                            if(vie[vie[i].cible[p]].nombre==0) Calcul_cible(vie,viemax);
                        }

                        k++;
                    }
                }

                // Vérification au cas où l'espèce attaquante est morte -> Changement de cibles si nécessaire.
                if(vie[i].nombre<=0)
                {
                    vie[i].nombre=0;
                    Calcul_cible(vie,viemax);
                }

        // SE REPRODUIRE

            if(vie[i].nombre>=2) /// Pas de distinction male/femelle donc 2 individus quelconques suffisent
            {
                j=0;
                k=vie[i].nombre/2/vie[i].gestation +1;
                while(j<k)
                {
                    // Si pas de mutation :
                    if(rand()%1000 || rand()%10) /// Je prends un degré de mutation de 0.0001% ... à ajuster ( peut etre dans option.ini)
                    {
                        vie[i].nombre += vie[i].portee;  /// On pourra éventuellement faire varier la portée
                    }
                    // Si mutation :
                    else
                    {
                        viemax++;   // On va travailler sur la nouvelle espèce qu'est viemax.
                        vie[viemax].nombre = vie[i].portee;

                        // On lui attribue toutes les fonctionnalités de i.
                        vie[viemax].chaine = vie[i].chaine;
                        vie[viemax].force = vie[i].force;
                        vie[viemax].defense = vie[i].defense;
                        vie[viemax].vitesse = vie[i].vitesse;
                        vie[viemax].portee = vie[i].portee;
                        vie[viemax].intelligence = vie[i].intelligence;
                        vie[viemax].dechet = vie[i].dechet;
                        vie[viemax].temperature=temperature;
                        /// Ne pas oublier les capacités quand elles seront introduites.

                        // On lui mute l'une de ses caractéristiques.
                        /// Ou on mute une capacité, à un pourcentage de chance plutot faible.
                        p=rand()%7;
                        switch(p)
                        {
                            case 0: /*if(vie[viemax].chaine>1 && rand()%2) vie[viemax].chaine--; else*/ vie[viemax].chaine++; break;
                            case 1: /*if(vie[viemax].force>0 && rand()%2) vie[viemax].force--; else*/ vie[viemax].force++; break;
                            case 2: /*if(vie[viemax].defense>0 && rand()%2) vie[viemax].defense--; else*/ vie[viemax].defense++; break;
                            case 3: /**if(vie[viemax].vitesse>0 && rand()%2) vie[viemax].vitesse--; else*/ vie[viemax].vitesse++; break;
                            case 4: if(vie[viemax].portee>2 && rand()%2) vie[viemax].portee--; else vie[viemax].portee++; break;
                            case 5: /*if(vie[viemax].intelligence>0 && rand()%2) vie[viemax].intelligence--; else*/ vie[viemax].intelligence++; break;
                            case 6: /*if(vie[viemax].dechet>0 && rand()%2) vie[viemax].dechet--; else*/ vie[viemax].dechet++; break;
                        }

                        // On définit ensuite les caractéristiques dépendantes :

                        vie[viemax].gestation = 1 + 5*vie[viemax].force + 5*vie[viemax].defense + vie[viemax].portee + 10*vie[viemax].chaine;
                        vie[viemax].aliment = 1 + vie[viemax].vitesse + 2*vie[viemax].force + 2*vie[viemax].defense + 2*vie[viemax].dechet;
                        vie[viemax].nourri = 10 + 6*vie[viemax].force + 8*vie[viemax].defense;

                        // On classe l'espèce dans rapide
                        /// On pourra éventuellement faire intervenir l'intelligence

                        p=1;
                        while(vie[rapide[p]].vitesse > vie[viemax].vitesse) p++;
                        s=rapide[p];
                        rapide[p]=viemax;
                        p++;
                        while(p<=viemax) // On déplace tous les suivants.
                        {
                            q=rapide[p];
                            rapide[p]=s;
                            p++;
                            s=rapide[p];
                            rapide[p]=q;
                            p++;
                        }

                        // On crée la fiche caractéristique de l'espèce

                            sprintf(ligne,"\n%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d;%d",viemax, jour_actuel,i, vie[viemax].chaine, vie[viemax].force, vie[viemax].defense,
                                                                                  vie[viemax].vitesse, vie[viemax].portee, vie[viemax].intelligence,vie[viemax].dechet,
                                                                                  vie[viemax].temperature, vie[viemax].gestation, vie[viemax].aliment, vie[viemax].nourri);
                            fputs(ligne,fiche);

                        // On revérifie les cibles
                        Calcul_cible(vie,viemax);
                    }
                    j++;
                }
            }

    /// MORTS DUES aux catastrophes et éventuelles incompatibilités de température.

                q = vie[i].temperature - temperature;   // On met une tolérance de 10%
                if(q<-10) q = -q;
                else if(q<=10) q=0;
                vie[i].nombre -= vie[i].nombre*(q-10)/200;

            }

            t++;
        }


// LOG lisible Excel TOUS LES 10 JOURS
   /// if(jour_actuel%10==0)
   /// {
        i=0;
         // On commence par creer le string ligne
        sprintf(ligne,"\n%d;%d",jour_actuel,temperature);
        while(i<=viemax)
        {
            sprintf(ligne,"%s;%d",ligne,vie[i].nombre);
            i++;
        }
        // On l'ajoute dans le log
        fputs(ligne,log);
   /// }

        jour_actuel++;
    }

    fclose(log);
    fclose(fiche);
}







// Fonction qui va calculer les cibles de chaque espèce.

void Calcul_cible(espece vie[], int viemax)
{
            // En fonction de la hauteur de chaine -> On peut descendre de 3 au maximum.
            // Un certain niveau d'intelligence permettra de se focaliser sur la cible la plus nourrissante.
            // Si chaine > 1 : Aléatoirement, les individus vont manger les espèces à defense plus faible que leur force et vitesse inferieure à la leur.
            // l'intelligence permettra de traiter les cas d'egalité.

    // On va devoir établir une double boucle jusqu'à viemax
    int i=1,j=0,k=0;

    while(i<=viemax)
    {
        while(j<=viemax) /// Pour le moment, l'intelligence n'est pas implémentée
        {
            if( vie[i].chaine-vie[j].chaine > 0 &&
                vie[i].chaine-vie[j].chaine <=2 &&
                    ( vie[i].force-vie[j].defense > 0 ||                                                    // Si la force est supérieure à la défense
                      (vie[i].force-vie[j].defense == 0 && vie[i].intelligence-vie[j].intelligence > 0)))   // ou en cas d'égalité, si l'intelligence est supérieure ...
            {
               vie[i].cible[k] = j;
               k++;
            }
            // En tenant compte de l'intelligence :
            j++;
        }
        vie[i].cible[k]=-1; // on indique la fin de l'information.
        i++;
        j=0;
    }

}

