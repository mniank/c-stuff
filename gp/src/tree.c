#include <stdio.h>
#include <stdlib.h>

#define LONGUEUR_LIGNE 2000

/// Convertir convenablement ce qui sort de mon GP en un joli arbre
/// Maxime Niankouri - 11.07.11



int noeud(FILE *output, char* s, int i);
void binarise(int n, int *t, int p);
void get_fonction(FILE* gen, char *fonction);
int evalue(char* fonction, int a, int b, int c, int d, int e, int f, int g, int h, int i, int j,int k, int l, int m, int n, int o, int p,int q, int r, int s, int t, int u, int v, int w, int x, int y, int z);
int isprime(int n);

int main()
{
	FILE* input=NULL, *output=NULL;
	output=fopen("tree.gv","w");
	input=fopen("generation0001.txt", "r");

	// On commence par récupérer la fonction à modéliser dans un string.
	char s[LONGUEUR_LIGNE];
	char c=fgetc(input);
	int i=0;
	while(c!='F')
	{
		s[i]=c;
		i++;
		c=fgetc(input);
	}
	i--; // i prend la position du noeud racine

	fclose(input);

	// On balance le header
    fprintf(output,"graph{\n");

    // Le corps
	noeud(output,s,i);

	// Et le finish
	fprintf(output,"}");

	fclose(output);

	// Avant de quitter, on en profite pour afficher à la console le nombre de composants.
	int E=0, O=0, N=0, autre=0;
	while(i>=0)
	{
	    if(s[i]=='E') E++;
	    else if(s[i]=='O') O++;
	    else if(s[i]=='N') N++;
	    else autre++;
	    i--;
	}
	printf("La nombre de chaque composant est :\n\n\n\tE\t%d\n\n\tO\t%d\n\n\tN\t%d\n\n\tAutres\t%d\n\n\n\tTotal\t%d\n\n", E, O, N, autre, E+O+N+autre);


	printf("--------------------------------\n\n");
	// On passe ensuite au test d'efficacité.

	i=0;
	int t[26], j=2;
	while(i<256)
    {
        binarise(i,t,0);
        j=i;
        if(isprime(i)!=evalue(s,t[25],t[24],t[23],t[22],t[21],t[20],t[19],t[18],t[17],t[16],t[15],t[14],t[13],t[12],t[11],t[10],t[9],t[8],t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0]))
				printf("On devrait avoir %d pour %d,\t as %d%d%d%d%d%d%d%d.\n", isprime(j),j,t[7],t[6],t[5],t[4],t[3],t[2],t[1],t[0]);
        i=j;
        i++;
    }


	getchar();

	return 0;
}


int noeud(FILE *output, char* s, int i) // s étant le string à lire et i la position dans le string.
{
    int j=i;

	if(s[i]=='E')
	{
	    fprintf(output,"A%d [label=\"E\", color=red, style=filled];\n", j);

		fprintf(output,"A%d -- A%d;\n",j,i-1);
		i=noeud(output, s, i-1);

		fprintf(output,"A%d -- A%d;\n",j,i-1);
		i=noeud(output,s,i-1);
	}
	else if(s[i]=='O')
	{
		fprintf(output,"A%d [label=\"O\", color=green, style=filled];\n", j);

		fprintf(output,"A%d -- A%d;\n",j,i-1);
		i=noeud(output, s, i-1);

		fprintf(output,"A%d -- A%d;\n",j,i-1);
		i=noeud(output,s,i-1);
	}
	else if(s[i]=='N')
	{
	    fprintf(output,"A%d [label=\"N\", color=blue, style=filled];\n", j);

		fprintf(output,"A%d -- A%d;\n",j,i-1);
		i=noeud(output,s,i-1);
	}
	else
	{
	    fprintf(output,"A%d [label=\"%c\"];\n", j, s[i]);
	}

	return i;
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

void binarise(int n, int *t, int p) // binarise un entier dans un tableau à 26 cases;
{
    t[p]=n%2;
    if(p<26) binarise(n/2,t,p+1);
}

