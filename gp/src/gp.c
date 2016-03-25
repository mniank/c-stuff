#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

/// Pour le moment : manipuler de 200 générations max, pour 4 variables max et 200 fonctions max par génération.
/// Faudrait mettre des DEFINE pour ca ...

#define SCORE_MAX 256
#define LONGUEUR_LIGNE 2000
#define NOMBRE_LIGNE 200

/* --------------------------------------------------------------

                        Maxime Niankouri
                           21.06.2011
                              TIPE

    But : Créer, par l'intermédiaire d'un algorithme génétique
    une fonction isprime se basant sur l'ecriture binaire d'un
    entier, et d'ainsi développer, par la suite, un circuit
    électronique ayant la même fonction.

    -------------------------------------------------------------*/

int nextgen(FILE* parents, FILE* generation, int n);
int calcul_score(FILE* parents);
int lecture(FILE *generation, int position, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,int k, int l, int m, int n, int o, int p,int q, int r, int s, int t, int u, int v, int w, int x, int y, int z);
void mutation(FILE* parents, FILE* generation, char *insert);
void genere_fichier_aleatoire();
void mutation_aleatoire(FILE* parents, FILE *generation);
char variable_aleatoire();
void crossover(FILE* parents, FILE* generation);
FILE* genere_fichier(int n);
FILE* ouvre_fichier(int n);
int isprime(int n);
int issquare(int n);
void binarise(int n, int *t, int p);
void Convertisseur_longueur_ligne(int avant); // Convertit generation0001 dans le format utilisé
int calcul_taille(FILE* gen);
int evalue(char* fonction, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,int k, int l, int m, int n, int o, int p,int q, int r, int s, int t, int u, int v, int w, int x, int y, int z);
void get_fonction(FILE* gen, char *fonction);

void* thread_score1(void* arg);
void* thread_score2(void* arg);
void* thread_score3(void* arg);
void* thread_score4(void* arg);
void* thread_score5(void* arg);
void* thread_score6(void* arg);
void* thread_score7(void* arg);
void* thread_score8(void* arg);


int prime[SCORE_MAX+1];

int main()
{
    srand(time(NULL));

    int t1,t2;
    t1=clock();
    //Convertisseur_longueur_ligne(10000);
    int p=0;
    while(p<=SCORE_MAX)
    {
        prime[p]=isprime(p);
        p++;
    }


    FILE *generation[10000];
    generation[1]=NULL;
    generation[1]=fopen("generation0001.txt","r");  // A générer aléatoirement à la base, (200 blocs simples aléatoires) ou préfaire un fichier

    if(generation[1]==NULL) // On part d'un fichier frais
    {
        genere_fichier_aleatoire();
        generation[1]=fopen("generation0001.txt","r");
    }

    int i=2, j=2;
    int final=-1;
    while(i<10000 && final==-1)
    {
        printf("%d\n",j);
        fseek(generation[i-1],0,SEEK_SET);
        generation[i]=genere_fichier(i);
        final = nextgen(generation[i-1], generation[i], i);
        fclose(generation[i-1]);
        i++;
        j++;
        if(i==9901) // Si on veut une boucle infinie.
        {
            rename("generation9900.txt","generation0100.txt");
            i=101;

        }
    }
    fclose(generation[i-1]);

    printf("La ligne finale : %d", final);
    t2=clock();
    printf("\n\n Temps d'execution : %d s\n\n", t2/CLOCKS_PER_SEC);

	system("speaker-test -t sine");

    //getchar();
    return 0;
}

// Fonction qui passe d'une génération à la suivante :

 int nextgen(FILE* parents, FILE* generation, int n)
 {
     int t1,t5; /// POUR LES TESTS DE TEMPS
    t1=clock();
     // Supposons que l'ont ait en permanence 200 fonctions. (On garde alors ensuite les 100 meilleures et on en recrée 10 mutées et 90 crossovées)
     int score[200];
     int i=0;
     while(i<200)
     {
         fseek(parents,LONGUEUR_LIGNE*i,SEEK_SET);
         score[i]=calcul_score(parents);
	 if(!i) 
	 {
		fseek(parents,LONGUEUR_LIGNE*i,SEEK_SET);
		score[i]=calcul_score(parents);
	 }
        /// if(score[i]==SCORE_MAX) return i+1; // On a fini le prog, la solution se trouvant à la ième ligne
         i++;
     }
     // Ici il faut trier score[]. Ou, en tout cas, récupérer les lignes des 100 meilleurs.
     int repartition[SCORE_MAX+1];

     i=0;
     while(i<=SCORE_MAX) // On commence par tout mettre à 0 ...
     {
         repartition[i]=0;
         i++;
     }
     i=0;
     while(i<200)
     {
         repartition[score[i]]++;
         i++;
     }

     int min=SCORE_MAX;
     int tot=0;
     while(tot<100)
     {
         tot+=repartition[min];
         min--;
     }
     min++;


     /// TEST DE REPARTITION
     i=min-10;
     if(i<0) i=0;
     printf("\nEtat de la Repartition :\n");
     while(i<=min+10 && i<=SCORE_MAX)
     {
         printf("Score : %d -- %d\n", i, repartition[i]);
         i++;
     }
        /// A SUPPRIMER



     // On peut donc descendre jusqu'a un score de min sans oublier de raser après le centième concerné
     // Puis on copie les 100 concernés.
     char s[LONGUEUR_LIGNE];
     i=0;
     int j=0;
     int k=0, taille[200], max_taille=0, repartition_taille[LONGUEUR_LIGNE+1];

     while(i<=LONGUEUR_LIGNE) // On commence par tout mettre à 0 ...
     {
         repartition_taille[i]=0;
         i++;
     }

     i=0;

     while(j<100) /// On pourrait commencer par prendre ceux de la fin du fichier, afin de privilégier les nouveaux. => Augmentation rapide la longueur d'une ligne ...
                    /// Il faudrait donc ajouter un critère de sélection : la longueur de la fonction ( bon pour la vitesse aussi )
     {
         if(i==200) // On se prépare à entrer dans le deuxième mode en regardant les longueurs
         {
             while(k<200)
             {
                 if(score[k]==min)
                 {
                     fseek(parents,k*LONGUEUR_LIGNE,SEEK_SET);
                     taille[k]=calcul_taille(parents);
                     repartition_taille[taille[k]]++;
                 }
                 k++;
            }
            k=0;
            while(k+j<100)
            {
                k+=repartition_taille[max_taille];
                max_taille++;

            }
            printf("MAX_TAILLE=%d", max_taille-1);

         }
         if(score[i]>min && i<200) // On prend ceux la quelle que soit la situation
         {
             // On copie la ligne ( faudrait faire que chaque ligne ait 200 caractères ( ou plus ) en remplissant par des espaces et en terminant la fonction par F).
             fseek(parents,LONGUEUR_LIGNE*i,SEEK_SET);
             fscanf(parents,"%s",s);
             fseek(generation,LONGUEUR_LIGNE*j,SEEK_SET);
             fprintf(generation,"%s",s);
             j++;
         }
         else if (score[399-i]==min && (taille[399-i]<max_taille-1 || taille[399-i]<1000) && i>=200 && i<400) /// On commence par la fin et on prend les plus courts ...
         {
             fseek(parents,LONGUEUR_LIGNE*(399-i),SEEK_SET);
             fscanf(parents,"%s",s);
             fseek(generation,LONGUEUR_LIGNE*j,SEEK_SET);
             fprintf(generation,"%s",s);
             j++;
         }
	else if (score[599-i]==min && taille[599-i]==max_taille-1 && i>=400) // Si on veut compresser le résultat
         {
             fseek(parents,LONGUEUR_LIGNE*(599-i),SEEK_SET);
             fscanf(parents,"%s",s);
             fseek(generation,LONGUEUR_LIGNE*j,SEEK_SET);
             fprintf(generation,"%s",s);
             j++;
         }
         i++;
     }
     /// Et on se démerde pour du crossover et des mutations.
     /// Avant la mutation, se placer aléatoirement sur une ligne du nouveau fichier, et si possible muter en "a", en dessous.
     /// On fait au moins un crossover||mutation sur chacun des 100. On les parcourt progressivement et met un taux 1/9 de mut/cross.

     // On ouvre un deuxième stream sur l'enfant.
     int r=0;
     FILE* enfants=NULL;
     enfants=ouvre_fichier(n);

     i=0;
     while(i<100)
     {
         fseek(generation,LONGUEUR_LIGNE*i,SEEK_SET);  // La zone des 100 premiers
         fseek(enfants,LONGUEUR_LIGNE*(i+100),SEEK_SET);    // La zone des transformés






         r=rand()%10;
         if(r) crossover(generation,enfants);
         else mutation_aleatoire(generation,enfants);

         i++;
     }
     fclose(enfants);
    t5=clock();

    printf("\n---> %d ms\n", 1000*(t5-t1)/CLOCKS_PER_SEC);


    return -1; // Cette génération n'apporte pas encore de solutions.
 }


int calcul_score(FILE* parents)
{


    char fonction[LONGUEUR_LIGNE+3];
    get_fonction(parents,fonction);
	
    int *a1=NULL, *a2=NULL, *a3=NULL, *a4=NULL, *a5=NULL, *a6=NULL, *a7=NULL, *a8=NULL;
	
	pthread_t thread1, thread2, thread3, thread4, thread5, thread6, thread7, thread8;

  
    pthread_create(&thread1,NULL,thread_score1, (void*) fonction);
    pthread_create(&thread2,NULL,thread_score2, (void*) fonction);
    pthread_create(&thread3,NULL,thread_score3, (void*) fonction);
    pthread_create(&thread4,NULL,thread_score4, (void*) fonction);
    pthread_create(&thread5,NULL,thread_score5, (void*) fonction);
    pthread_create(&thread6,NULL,thread_score6, (void*) fonction);
    pthread_create(&thread7,NULL,thread_score7, (void*) fonction);
    pthread_create(&thread8,NULL,thread_score8, (void*) fonction);

    int v1=0, v2=0, v3=0, v4=0, v5=0, v6=0, v7=0, v8=0;
	

    pthread_join(thread1,(void*)&a1);
    pthread_join(thread2,(void*)&a2);
    pthread_join(thread3,(void*)&a3);
    pthread_join(thread4,(void*)&a4);
    pthread_join(thread5,(void*)&a5);
    pthread_join(thread6,(void*)&a6);
    pthread_join(thread7,(void*)&a7);
    pthread_join(thread8,(void*)&a8);

	
	v1=*a1; v2=*a2; v3=*a3; v4=*a4; v5=*a5; v6=*a6; v7=*a7; v8=*a8;

    return v1+v2+v3+v4+v5+v6+v7+v8;
}


// Fonction de lecture de fonctions pour le score

int lecture(FILE *generation, int position, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,int k, int l, int m, int n, int o, int p,int q, int r, int s, int t, int u, int v, int w, int x, int y, int z)
{
    fseek(generation,position,SEEK_SET);

    int pile[LONGUEUR_LIGNE/2]; /// Le /2 est pris pour diminuer un peu la taille. Peut etre est-ce trop ...
    char caractere='0';
    pile[0]=0;

    while(caractere!='\n' && caractere!='EOF' && caractere!='F')
    {
        caractere=fgetc(generation);
        switch(caractere)
        {
            case '1':                   // TRUE
                pile[0]++;
                pile[pile[0]]=1;
                break;
            case '0':                   // FALSE
                pile[0]++;
                pile[pile[0]]=0;
                break;
            case 'N':                   // NON
                if(pile[pile[0]]) pile[pile[0]]=0;
                else pile[pile[0]]=1;
                break;
            case 'E':                   // ET
                if(pile[pile[0]]&&pile[pile[0]-1]) pile[pile[0]-1]=1;
                else pile[pile[0]-1]=0;
                pile[0]--;
                break;
            case 'O':                   // OU
                if(pile[pile[0]]||pile[pile[0]-1]) pile[pile[0]-1]=1;
                else pile[pile[0]-1]=0;
                pile[0]--;
                break;

            // VARIABLES

            case 'a':
                pile[0]++;
                pile[pile[0]]=a;
                break;
            case 'b':
                pile[0]++;
                pile[pile[0]]=b;
                break;
            case 'c':
                pile[0]++;
                pile[pile[0]]=c;
                break;
            case 'd':
                pile[0]++;
                pile[pile[0]]=d;
                break;
            case 'e':
                pile[0]++;
                pile[pile[0]]=e;
                break;
            case 'f':
                pile[0]++;
                pile[pile[0]]=f;
                break;
            case 'g':
                pile[0]++;
                pile[pile[0]]=g;
                break;
            case 'h':
                pile[0]++;
                pile[pile[0]]=h;
                break;
            case 'i':
                pile[0]++;
                pile[pile[0]]=i;
                break;
            case 'j':
                pile[0]++;
                pile[pile[0]]=j;
                break;
            case 'k':
                pile[0]++;
                pile[pile[0]]=k;
                break;
            case 'l':
                pile[0]++;
                pile[pile[0]]=l;
                break;
            case 'm':
                pile[0]++;
                pile[pile[0]]=m;
                break;
            case 'n':
                pile[0]++;
                pile[pile[0]]=n;
                break;
            case 'o':
                pile[0]++;
                pile[pile[0]]=o;
                break;
            case 'p':
                pile[0]++;
                pile[pile[0]]=p;
                break;
            case 'q':
                pile[0]++;
                pile[pile[0]]=q;
                break;
            case 'r':
                pile[0]++;
                pile[pile[0]]=r;
                break;
            case 's':
                pile[0]++;
                pile[pile[0]]=s;
                break;
            case 't':
                pile[0]++;
                pile[pile[0]]=t;
                break;
            case 'u':
                pile[0]++;
                pile[pile[0]]=u;
                break;
            case 'v':
                pile[0]++;
                pile[pile[0]]=v;
                break;
            case 'w':
                pile[0]++;
                pile[pile[0]]=w;
                break;
            case 'x':
                pile[0]++;
                pile[pile[0]]=x;
                break;
            case 'y':
                pile[0]++;
                pile[pile[0]]=y;
                break;
            case 'z':
                pile[0]++;
                pile[pile[0]]=z;
                break;
        }
    }
    if(caractere=='EOF') return -1;
    else return pile[1];
}

// Fonction de mutation
void mutation(FILE* parents, FILE* generation, char *insert)
{
    int taille=-1;
    char c='0';
    while(c!='\n' && c!='EOF' && c!='F')
    {
        c=fgetc(parents);
        taille++;
    }
    fseek(parents,-taille-1,SEEK_CUR);
    // Après avoir relevé la taille de l'engin, on choisit un noeud a modifier.
    int lieu=rand()%taille;
    fseek(parents,lieu,SEEK_CUR);
    // On regarde ensuite jusqu'ou s'étend son évaluation.
    int eval=1;
    int longueur=0;
    char lu='0';
    while(eval)
    {
        longueur++;
        lu=fgetc(parents);
        if(lu=='O' || lu=='E') eval++;
        else if(lu!='N') eval--;
        if(eval)fseek(parents,-2,SEEK_CUR);
        else fseek(parents,-1,SEEK_CUR);
    }

    // On va ensuite lire la fonction en omettant la partie ainsi définie.
    fseek(parents, longueur-lieu-1, SEEK_CUR);
    char s1[LONGUEUR_LIGNE], s2[LONGUEUR_LIGNE];
    if(lieu-longueur+2>0) fgets(s1,lieu-longueur+2, parents);
    fseek(parents,longueur, SEEK_CUR);
    if(taille-lieu>0)fgets(s2,taille-lieu, parents);

    // Puis on printf ca, intercalé par le string désiré dans la génération enfant.
    fprintf(generation,"%s%s%sF",s1,insert,s2);
    // A la fin, on se situe au début de la prochaine fonction., dans les deux fichiers.
}


void genere_fichier_aleatoire()
{
    FILE *gen=NULL;
    gen=genere_fichier(1);
    int i=0;
    while(i<200)
    {

        fseek(gen,i*LONGUEUR_LIGNE,SEEK_SET);
        switch(rand()%5)
        {
        case 0:
            fprintf(gen,"%cF", variable_aleatoire());
            break;
        case 1:
            fprintf(gen,"%cF", variable_aleatoire());
            break;
        case 2:
            fprintf(gen,"%cNF", variable_aleatoire());
            break;
        case 3:
            fprintf(gen,"%c%cEF", variable_aleatoire(), variable_aleatoire());
            break;
        case 4:
            fprintf(gen,"%c%cOF", variable_aleatoire(), variable_aleatoire());
            break;
        }

        i++;
    }
    fclose(gen);
}

void mutation_aleatoire(FILE* parents, FILE *generation)
{
    char insert[]="000";
    switch(rand()%5)
    {
        case 0:
            insert[0]=variable_aleatoire();
            insert[1]='\0';
            break;
        case 1:
            insert[0]=variable_aleatoire();
            insert[1]='\0';
            break;
        case 2:
            insert[0]=variable_aleatoire();
            insert[1]='N';
            insert[2]='\0';
            break;
        case 3:
            insert[0]=variable_aleatoire();
            insert[1]=variable_aleatoire();
            insert[2]='E';
            insert[3]='\0';
            break;
        case 4:
            insert[0]=variable_aleatoire();
            insert[1]=variable_aleatoire();
            insert[2]='O';
            insert[3]='\0';
            break;
    }

    mutation(parents, generation, insert);
}

char variable_aleatoire()       /// Quand on montera le nombre de variables, ne pas oublier de modifier cette fonction.
{
    switch(20+rand()%8)
    {
        case 0:
            return '0';
            break;
        case 1:
            return '1';
            break;
        case 2:
            return 'a';
            break;
        case 3:
            return 'b';
            break;
        case 4:
            return 'c';
            break;
        case 5:
            return 'd';
            break;
        case 6:
            return 'e';
            break;
        case 7:
            return 'f';
            break;
        case 8:
            return 'g';
            break;
        case 9:
            return 'h';
            break;
        case 10:
            return 'i';
            break;
        case 11:
            return 'j';
            break;
        case 12:
            return 'k';
            break;
        case 13:
            return 'l';
            break;
        case 14:
            return 'm';
            break;
        case 15:
            return 'n';
            break;
        case 16:
            return 'o';
            break;
        case 17:
            return 'p';
            break;
        case 18:
            return 'q';
            break;
        case 19:
            return 'r';
            break;
        case 20:
            return 's';
            break;
        case 21:
            return 't';
            break;
        case 22:
            return 'u';
            break;
        case 23:
            return 'v';
            break;
        case 24:
            return 'w';
            break;
        case 25:
            return 'x';
            break;
        case 26:
            return 'y';
            break;
        case 27:
            return 'z';
            break;
    }
}


// Fonction de crossover

void crossover(FILE* parents, FILE* generation)
{
    char insert[LONGUEUR_LIGNE];
    // On prend l'insert aléatoirement

    int taille=-1;
    char c='0';
    while(c!='\n' && c!='EOF' && c!='F')
    {
        c=fgetc(parents);
        taille++;
    }
    fseek(parents,-taille-1,SEEK_CUR);
    // Après avoir relevé la taille de l'engin, on choisit un noeud a modifier.
    int lieu=rand()%taille;
    fseek(parents,lieu,SEEK_CUR);
    // On regarde ensuite jusqu'ou s'étend son évaluation.
    int eval=1;
    int longueur=0;
    char lu='0';
    while(eval)
    {
        longueur++;
        lu=fgetc(parents);
        if(lu=='O' || lu=='E') eval++;
        else if(lu!='N') eval--;
        if(eval)fseek(parents,-2,SEEK_CUR);
        else fseek(parents,-1,SEEK_CUR);
    }

    // Et on balance ce qu'on veut dans l'insert
    fgets(insert,longueur+1,parents);

    // On se place sur le deuxième parent (avec i entre 0 et 99) de l'enfant et on mute.
    fseek(parents,LONGUEUR_LIGNE*(rand()%100),SEEK_SET);
    mutation(parents,generation,insert);
}






FILE* genere_fichier(int n)
{
    char s[]="generation0000.txt";
    /// On supprime le fichier inutilisé pour économise de l'espace disque.
    if(n>3)
    {
        sprintf(s,"generation%d%d%d%d.txt",(n-2)/1000,((n-2)%1000)/100, ((n-2)%100)/10, (n-2)%10);
        remove(s);
    }
    sprintf(s,"generation%d%d%d%d.txt",n/1000,(n%1000)/100, (n%100)/10, n%10);
    FILE* out=NULL;
    out=fopen(s,"w");

    int i=0,j=0;
    while(i<200)
    {
        while(j<LONGUEUR_LIGNE-1)
        {
            fputc(' ',out);
            j++;
        }
        fputc('\n',out);
        j=0;
        i++;
    }
    fclose(out);
    return fopen(s,"r+");
}

FILE* ouvre_fichier(int n)
{
    char s[]="generation0000.txt";
    sprintf(s,"generation%d%d%d%d.txt",n/1000,(n%1000)/100, (n%100)/10, n%10);
    return fopen(s,"r+");
}




int isprime(int n) // Check si un nombre est premier ou non.
{
    if(n<2) return 0;
    if(n==2) return 1;
    if(n%2==0) return 0;
    int i=3;
    while(i*i<=n)
    {
        if(n%i==0) return 0;
        i+=2;
    }
    return 1;
}

int issquare(int n) // Check si un entier est un carre parfait ou non
{
    if(!n) return 1;
    int i=1;
    while(i*i<n) i++;
    return (i*i==n);
}

void binarise(int n, int *t, int p) // binarise un entier dans un tableau à 26 cases;
{
    t[p]=n%2;
    if(p<26) binarise(n/2,t,p+1);
}


void Convertisseur_longueur_ligne(int avant)
{
    FILE *genbis=NULL, *gen=NULL;
    genbis=genere_fichier(0);
    gen=fopen("generation0001.txt", "r");
    int i=0;
    char s[avant];
    while(i<200)
    {
        fseek(gen,avant*i,SEEK_SET);
        fscanf(gen,"%s",s);
        fseek(genbis,LONGUEUR_LIGNE*i,SEEK_SET);
        fprintf(genbis,"%s",s);
        i++;
    }
    fclose(gen);
    fclose(genbis);
}

int calcul_taille(FILE* gen)
{
    int taille=0;
    while(fgetc(gen)!='F') taille++;
    return taille;
}


void get_fonction(FILE* gen, char *fonction) // doit a la base etre de taille LONGUEUR_LIGNE
{
    int i=0;
    fonction[0]=fgetc(gen);
    while(fonction[i]!='F')
    {
        i++;
        fonction[i]=fgetc(gen);
    }
}

int evalue(char* fonction, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,int k, int l, int m, int n, int o, int p,int q, int r, int s, int t, int u, int v, int w, int x, int y, int z)
{
    int pile[LONGUEUR_LIGNE/2]; /// Le /2 est pris pour diminuer un peu la taille. Peut etre est-ce trop ...
    int i0=0;
    pile[0]=0;

    while(fonction[i0]!='F')
    {
        switch(fonction[i0])
        {
            case '1':                   // TRUE
                pile[0]++;
                pile[pile[0]]=1;
                break;
            case '0':                   // FALSE
                pile[0]++;
                pile[pile[0]]=0;
                break;
            case 'N':                   // NON
                if(pile[pile[0]]) pile[pile[0]]=0;
                else pile[pile[0]]=1;
                break;
            case 'E':                   // ET
                if(pile[pile[0]]&&pile[pile[0]-1]) pile[pile[0]-1]=1;
                else pile[pile[0]-1]=0;
                pile[0]--;
                break;
            case 'O':                   // OU
                if(pile[pile[0]]||pile[pile[0]-1]) pile[pile[0]-1]=1;
                else pile[pile[0]-1]=0;
                pile[0]--;
                break;

            // VARIABLES

            case 'a':
                pile[0]++;
                pile[pile[0]]=a;
                break;
            case 'b':
                pile[0]++;
                pile[pile[0]]=b;
                break;
            case 'c':
                pile[0]++;
                pile[pile[0]]=c;
                break;
            case 'd':
                pile[0]++;
                pile[pile[0]]=d;
                break;
            case 'e':
                pile[0]++;
                pile[pile[0]]=e;
                break;
            case 'f':
                pile[0]++;
                pile[pile[0]]=f;
                break;
            case 'g':
                pile[0]++;
                pile[pile[0]]=g;
                break;
            case 'h':
                pile[0]++;
                pile[pile[0]]=h;
                break;
            case 'i':
                pile[0]++;
                pile[pile[0]]=i;
                break;
            case 'j':
                pile[0]++;
                pile[pile[0]]=j;
                break;
            case 'k':
                pile[0]++;
                pile[pile[0]]=k;
                break;
            case 'l':
                pile[0]++;
                pile[pile[0]]=l;
                break;
            case 'm':
                pile[0]++;
                pile[pile[0]]=m;
                break;
            case 'n':
                pile[0]++;
                pile[pile[0]]=n;
                break;
            case 'o':
                pile[0]++;
                pile[pile[0]]=o;
                break;
            case 'p':
                pile[0]++;
                pile[pile[0]]=p;
                break;
            case 'q':
                pile[0]++;
                pile[pile[0]]=q;
                break;
            case 'r':
                pile[0]++;
                pile[pile[0]]=r;
                break;
            case 's':
                pile[0]++;
                pile[pile[0]]=s;
                break;
            case 't':
                pile[0]++;
                pile[pile[0]]=t;
                break;
            case 'u':
                pile[0]++;
                pile[pile[0]]=u;
                break;
            case 'v':
                pile[0]++;
                pile[pile[0]]=v;
                break;
            case 'w':
                pile[0]++;
                pile[pile[0]]=w;
                break;
            case 'x':
                pile[0]++;
                pile[pile[0]]=x;
                break;
            case 'y':
                pile[0]++;
                pile[pile[0]]=y;
                break;
            case 'z':
                pile[0]++;
                pile[pile[0]]=z;
                break;
        }
        i0++;
    }
    return pile[1];
}


void* thread_score1(void* arg) // THREAD 1
{
    int *score= malloc(sizeof(int));
	*score=2;
    int s=SCORE_MAX/8;
    int i=2, j=0, t[26];
    while(i<s)
    {
	j=i;
        binarise(i,t,0);
	i=j;
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score2(void* arg) // THREAD 2
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=s, j=0, t[26];
    while(i<2*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score3(void* arg) // THREAD 3
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=2*s, j=0, t[26];
    while(i<3*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score4(void* arg) // THREAD 4
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=3*s, j=0, t[26];
    while(i<4*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score5(void* arg) // THREAD 5
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=4*s, j=0, t[26];
    while(i<5*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score6(void* arg) // THREAD 6
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=5*s, j=0, t[26];
    while(i<6*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score7(void* arg) // THREAD 7
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=6*s, j=0, t[26];
    while(i<7*s)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}

void* thread_score8(void* arg) // THREAD 8
{
    int *score= malloc(sizeof(int));
	*score=0;
    int s=SCORE_MAX/8;
    int i=7*s, j=0, t[26];
    while(i<SCORE_MAX)
    {
	j=i;
        binarise(i,t,0);
	i=j;	
        j=i;
        if(prime[i]==evalue(arg,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0])) *score+=1;
        i=j;
        i++;
    }
    pthread_exit(score);
}


