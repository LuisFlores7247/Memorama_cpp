#ifndef DATOS
#define DATOS

#include <string>

using namespace std;
struct casilla
{
    string palabra;
    bool estado;
    int posicion;
};

struct dato
{
    char alias[15];
    char catAJugar[40];
    int palAUsar;
    int ren;
    int col;
    int par;
    casilla **tableroDinamico;
    double duracDeJueg;
    char dia[12];
    char hora[10];
};
enum modo
{
    JUGAR = 1,
    SIMULAR
};

#endif