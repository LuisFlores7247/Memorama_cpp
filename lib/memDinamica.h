#ifndef MEMDINAMICA
#define MEMDINAMICA

#include "datos.h"

casilla **pedirMemoriaMat(int pal, int *ren, int *col); /* Caso 4 */
string *pedirMemVec(int tam);                           /* Caso 4*/
int *pedirMemVector(int tam);                           /* Caso 4*/

casilla **pedirMemoriaMat(int pal, int *ren, int *col)
{
    casilla **aux;
    switch (pal)
    {
    case 3:
        *ren = 3;
        *col = 2;
        break;
    case 6:
        *ren = 4;
        *col = 3;
        break;
    case 8:
        *ren = 4;
        *col = 4;
        break;
    }
    aux = new casilla *[*ren];
    for (int i = 0; i < *ren; i++)
    {
        aux[i] = new casilla[*col];
    }

    return aux;
}
string *pedirMemVec(int tam)
{
    return new string[tam];
}
int *pedirMemVector(int tam)
{
    return new int[tam];
}
void BorrarEspMemDina(casilla **mat, int ren)
{
    for (int i = 0; i < ren; i++)
    {
        delete[] mat[i];
    }
    delete[] mat;
}
void BorrarEspMemDina(casilla **mat, int ren);

#endif
