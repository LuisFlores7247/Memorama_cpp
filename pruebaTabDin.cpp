// Prueba temporal de la creacion del tablero dinamico de structs

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#define CAT1 "categoria1.txt"
#define CAT2 "categoria2.txt"
#define CAT3 "categoria3.txt"

using namespace std;

struct casilla
{
    string palabra;
    bool estado;
    int posicion;
};

casilla **pedirEspacio(int pal, int *ren, int *col);
string *pedirEspVec(int tam);
void llenarTab(casilla **mat, int ren, int col, string *v, string cat, int pal);
void imprimirTab(casilla **mat, int ren, int col);
void shuffle(string *v, int tam);
bool validarRepetidos(int *v, int num, int k);

int main(int argc, char const *argv[])
{
    int ren, col, pal;
    casilla **tableroDinamico;
    string *vecDina, cat;
    cin >> pal;
    fflush(stdin);
    getline(cin, cat);
    tableroDinamico = pedirEspacio(pal, &ren, &col);
    vecDina = pedirEspVec(ren * col);
    llenarTab(tableroDinamico, ren, col, vecDina, cat, pal);
    imprimirTab(tableroDinamico,ren,col);
    return 0;
}
casilla **pedirEspacio(int pal, int *ren, int *col)
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
string *pedirEspVec(int tam)
{
    return new string[tam];
}

void llenarTab(casilla **mat, int ren, int col, string *v, string cat, int pal)
{
    // Primero se llena el vector dinamico con los nombres de la categoria a buscar
    srand(time(NULL));
    int posicion, k = 0,j=0, total = 0, tam=ren*col, *posiciones=new int[pal];
    fstream categoria;
    string aux;
    // Saber cual es la categoria que se ocupa
    if (cat == "Dispositivos electronicos")
    {
        categoria.open(CAT1, ios::in);
    }
    if (cat == "Lenguajes de programacion")
    {
        categoria.open(CAT2, ios::in);
    }
    if (cat == "Paises")
    {
        categoria.open(CAT3, ios::in);
    }
    categoria.clear();
    categoria.seekg(0);
    if (!categoria)
    {
        cout << "El archivo no pudo ser abierto" << endl;
    }
    else
    {
        // Saber el total de registros existentes en el archivo abierto
        while (getline(categoria, aux))
        {
            total++;
        }
        categoria.clear();
        categoria.seekg(0);
        //crear un vector de las posiciones sin repetidos
        do
        {
            posicion = rand() % total;
            if (validarRepetidos(posiciones,posicion,k))
            {
                posiciones[k]=posicion;
                k++;
            }                
        } while (k<pal);
        
        for (int i = 0; i < tam; i++)
        {
            k=0;
            categoria.clear();
            categoria.seekg(0);
            while (getline(categoria,aux))
            {
                if (k==posiciones[j])
                {
                    v[i]=aux;
                    v[i+1]=aux;
                    j++;
                    i++;
                    break;
                }
                k++;
            }            
        }
        shuffle(v,tam);
        shuffle(v,tam);
        categoria.close();
        k=0;
        j=0;
        //Llenar la matriz dinamica de structs con el vector dinamico, la posicion con un contador y el bool en falso
        for (int i = 0; i < ren; i++)
        {
            for (int j = 0; j < col; j++)
            {
                mat[i][j].palabra=v[k];
                mat[i][j].estado=false;
                mat[i][j].posicion=k+1;
                k++;
            }            
        }        
    }
    delete []v;
}
void imprimirTab(casilla **mat, int ren, int col){
    for (int i = 0; i < ren; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (mat[i][j].estado)
            {
                cout<<setw(15)<<mat[i][j].palabra;
            }
            else
            {
                cout<<setw(15)<<mat[i][j].posicion;
            }
        }
        cout<<endl;
    }
    cout<<"Ahora destapado: "<<endl<<endl;
    for (int i = 0; i < ren; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (!mat[i][j].estado)
            {
                cout<<setw(15)<<mat[i][j].palabra;
            }
            else
            {
                cout<<setw(15)<<mat[i][j].posicion;
            }
        }
        cout<<endl;
    }
    
}
bool validarRepetidos(int *v, int num, int k){
    bool aux=true;
    for (int j = 0; j < k; j++)
    {
        if (v[j]==num)
        {
            aux=false;
            break;
        }        
    }
    return aux;
}
void shuffle(string *v, int tam){
    if (tam>1)
    {
        for (int i = 0; i < tam-1; i++)
        {
            int j=i+rand()/(RAND_MAX/(tam-i)+1);
            string t=v[j];
            v[j]=v[i];
            v[i]=t;
        }        
    }    
}