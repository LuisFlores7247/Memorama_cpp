//Prueba temporal de la creacion del tablero dinamico de structs

#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

struct casilla
{
    string palabra;
    bool estado;
    int posicion; 
};

casilla **pedirEspacio(int pal, int *ren, int *col);
void llenarTab(casilla **mat,int ren, int col);
void imprimirTab(casilla **mat,int ren, int col);


int main(int argc, char const *argv[])
{
    int ren, col, pal;
    casilla **tableroDinamico;
    cin>>pal;
    tableroDinamico=pedirEspacio(pal,&ren,&col);

    return 0;
}
casilla **pedirEspacio(int pal, int *ren, int *col){
    casilla **aux;
    switch (pal)
    {
    case 3:
        *ren=3;
        *col=2;
        break;
    case 6:
        *ren=4;
        *col=3;
        break;
    case 8:
        *ren=4;
        *col=4;
        break;
    }
    aux=new casilla *[*ren];
    for (int i = 0; i < *ren; i++)
    {
        aux[i]=new casilla [*col];
    }
    
    return aux;
}
void llenarTab(casilla **mat,int ren, int col)
{

}
void imprimirTab(casilla **mat,int ren, int col);