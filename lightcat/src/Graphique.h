struct Coord
{
    long x;
    long y;
};
struct GraphMapEdit
{
    char file; // Nom du chipset
    char x; // X de la case à recuperer
    char y; // Y "
};
struct GraphMapEdit2
{
    char file[20];
    int x;
    int y;
    int w;
    int h;
};
void IntialGraphique();
