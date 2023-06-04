// Categorias del Memorama: Lenguajes de Programacion, Dispositivos electronicos, paises
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>

#define CAT1 "categoria1.txt"
#define CAT2 "categoria2.txt"
#define CAT3 "categoria3.txt"
#define color SetConsoleTextAttribute

using namespace std;

struct casilla
{
    string palabra;
    bool estado;
    int posicion;
};

struct dato
{
    string alias;
    string catAJugar;
    int palAUsar;
    int ren;
    int col;
    casilla **tableroDinamico;
    int horaIn; // No se si la hora se pueda guardar asi pero aja, se entiende la idea
    double duracDeJueg;
};

// Portada
void portada(int consoleWidth);      /* Caso 2 */
void presentacion(int consoleWidth); /* Caso 2 */

// Menus
int menu(int consoleWidth);                             /* Caso 4 */
void menuJuego(int consoleWidth);                       /* Caso 2 */
void mantenimiento();                                   /* Caso 1 */
void opcionesMantenimiento(int arch, int consoleWidth); /* Caso 2 */

// Fundamentales
void gotoxy(int x, int y);                                             /* Caso 2 */
casilla **crearTablero(int pal, string categoria, int *ren, int *col); /* Caso 4 */
void juego(dato info, int consoleWith);

// Assets
bool validarAlias(string alias, int consoleWidth);                                   /* Caso 2 */
bool validarCategoria(string cat, int consoleWidth);                                 /* Caso 2 */
bool validarPalabras(int words, int consoleWidth);                                   /* Caso 2 */
casilla **pedirMemoriaMat(int pal, int *ren, int *col);                              /* Caso 4 */
string *pedirMemVec(int tam);                                                        /* Caso 4*/
void llenarTab(casilla **mat, int ren, int col, string *v, string cat, int pal);     /* Caso 2*/
void imprimirTab(dato info, int seleccion, int seleccionAnterior, int consoleWidth); /* Caso 2 */
void shuffle(string *v, int tam);                                                    /* Caso 2*/
bool validarRepetidos(int *v, int num, int k);                                       /* Caso 4*/
void clearLines(int inicio, int lineas);                                             /* Caso 2 */
clock_t medirT();                                                                    /* Caso 3 */
string palabraSeleccion(dato info, int posicion);

// Archivos
void leerArch(int arch, int consoleWidth);          /* Caso 2*/
void agregar(int arch, int consoleWidth);           /* Caso 2*/
void eliminar(int arch, int consoleWidth);          /* Caso 2*/
void registrarjugador(dato info, int consoleWidth); /* Caso 2*/
bool validarPalabrasArch(int arch);                 /* Caso 4 */
void registrobin(dato info);                        /* Caso 2 */

int main(int argc, char const *argv[])
{
    srand(time(NULL));
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.dwSize.X;
    int opc;
    portada(consoleWidth);
    presentacion(consoleWidth);
    do
    {
        opc = menu(consoleWidth);

        switch (opc)
        {
        case 1:
            menuJuego(consoleWidth);
            break;
        case 2:
            /* code */
            break;
        case 3:
            /* code */
            break;
        case 4:
            mantenimiento();
            break;
        case 5:
            break;

        default:
            cout << "Opcion no valida, por favor intente de nuevo. " << endl;
            break;
        }
    } while (opc != 5 || (opc < 1 || opc > 5));

    return 0;
}

// Portada

void portada(int consoleWidth)
{
    system("cls");
    string line = "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line;

    line = "Ingenieria en sistemas computacionales";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;

    line = "Programacion I";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;

    line = "Nombre";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;

    line = "Sergio Eder Cervantes Rincon";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;

    line = "Daan Jostin Carabez Garcia";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;

    line = "Luis Alberto Pedroza Diaz";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;

    line = "Luis David Flores Martinez";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;

    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 17);
    system("Pause");
}

void presentacion(int consoleWidth)
{
    system("cls");
    string line = "Nombre";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 10);
    cout << line;

    line = "Lema";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;

    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 20);
    system("Pause");
}

// Menus

int menu(int consoleWidth)
{
    int opc;
    system("cls");
    string line = "MENU";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line;
    line = "1.- Jugar";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    line = "2.- Simulacion";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    line = "3.- Reporte";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    line = "4.- Mantenimiento";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    line = "5.- Salir";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;

    line = "Opcion: ";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    cin >> opc;
    return opc;
}

void mantenimiento()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.dwSize.X;
    int opc;
    system("cls");
    string line = "Categoria a modificar";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line;
    line = "1.- Dispositivos electronicos";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    line = "2.- Lenguajes de programacion";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    line = "3.- Paises";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;

    line = "Opcion: ";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    cin >> opc;
    switch (opc)
    {
    case 1:
        opcionesMantenimiento(1, consoleWidth);
        break;
    case 2:
        opcionesMantenimiento(2, consoleWidth);
        break;
    case 3:
        opcionesMantenimiento(3, consoleWidth);
        break;
    default:
        line = "Opcion incorrecta";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 13);
        cout << line;

        break;
    }
}

void opcionesMantenimiento(int arch, int consoleWidth)
{
    system("cls");
    int opc;
    do
    {
        system("cls");
        string line = "¿Que deseas hacer?";
        int leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;

        line = "1.- Listar";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 3);
        cout << line;

        line = "2.- Agregar";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 5);
        cout << line;

        line = "3.- Eliminar";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 7);
        cout << line;

        line = "4.- Salir";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 9);
        cout << line;

        line = "Opcion: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 11);
        cout << line;
        cin >> opc;
        switch (opc)
        {
        case 1:
            leerArch(arch, consoleWidth);
            break;
        case 2:
            agregar(arch, consoleWidth);
            break;
        case 3:
            eliminar(arch, consoleWidth);
            break;
        default:
            break;
        }

    } while (opc != 4 || (opc < 1 || opc > 5));
}

void menuJuego(int consoleWidth)
{
    int palAUsar, leftPadding;
    bool band1, band2, band3;
    string line;
    dato datos;

    do // captura alias
    {
        system("cls");
        line = "JUGAR";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
        line = "Dame tu Alias para jugar: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 3);
        cout << line;
        fflush(stdin);
        leftPadding = (consoleWidth - 15) / 2;
        gotoxy(leftPadding, 4);
        getline(cin, datos.alias);
        band1 = validarAlias(datos.alias, consoleWidth);
    } while (!band1);

    do // Capturar Categoria
    {
        line = "Dime cual de las 3 categorias quieres jugar: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 6);
        cout << line;
        line = "1.- Dispositivos electronicos";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 8);
        cout << line;
        line = "2.- Lenguajes de programacion";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 9);
        cout << line;
        line = "3.- Paises";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 10);
        cout << line;
        line = "Opcion: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 12);
        cout << line;
        fflush(stdin);
        getline(cin, datos.catAJugar);
        band2 = validarCategoria(datos.catAJugar, consoleWidth);
        if (!band2) // Borra de pantalla cosas basura
        {
            clearLines(12, 2);
            clearLines(19, 3);
        }

    } while (!band2);
    do // Capurar palabras
    {
        line = "Con cuantas Palabras deseas Jugar (3,6 u 8 palabras): ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 15);
        cout << line;
        line = "Opcion: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 16);
        cout << line;
        cin >> datos.palAUsar;
        band3 = validarPalabras(datos.palAUsar, consoleWidth);
        if (!band3) // Borra de pantalla cosas basura
        {
            clearLines(16, 2);
            clearLines(20, 3);
        }

    } while (!band3);

    datos.tableroDinamico = crearTablero(datos.palAUsar, datos.catAJugar, &datos.ren, &datos.col);
    registrarjugador(datos, consoleWidth);
    // tablero dinamico es casilla**
    juego(datos, consoleWidth);
    system("pause");
}

// Fundamentales

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

casilla **crearTablero(int pal, string categoria, int *ren, int *col)
{
    int aux1, aux2;
    string *vecDina;
    casilla **tableroDinamico;
    tableroDinamico = pedirMemoriaMat(pal, &aux1, &aux2);
    *ren = aux1;
    *col = aux2;
    vecDina = pedirMemVec((*ren) * (*col));
    llenarTab(tableroDinamico, *ren, *col, vecDina, categoria, pal);

    return tableroDinamico;
}

void juego(dato info, int consoleWidth)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int seleccion = 0, selecAnterior = 0, palabrasRestantes = info.palAUsar, intentos = 0;
    bool win = false;
    clock_t start, end;
    start = medirT();
    system("cls");
    imprimirTab(info, seleccion, selecAnterior, consoleWidth);
    cout << endl;
    do
    {
        bool seleccionada;
        // PreguntarCasilla
        do
        {
            string line = "Selecciona una casilla: ";
            int leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 16);
            cout << line;
            leftPadding = (consoleWidth) / 2;
            gotoxy(leftPadding, 17);
            cin >> seleccion;
            for (int i = 0; i < info.ren; i++)
            {
                for (int j = 0; j < info.col; j++)
                {
                    if (info.tableroDinamico[i][j].posicion == seleccion && info.tableroDinamico[i][j].estado == true)
                    {
                        seleccionada = true;
                        line = "La casilla ya ha sido destapada, por fvaor elija otra";
                        leftPadding = (consoleWidth - line.length()) / 2;
                        gotoxy(leftPadding, 15);
                        cout << line;
                        Sleep(3000);
                    }
                }
            }

        } while (seleccion < 1 || seleccion > (info.palAUsar * 2));

        // Validar casilla que este dentro de lo rangos y que no se haya seleccionado anteriormente
        intentos++;
        Sleep(1000);
        system("cls");
        imprimirTab(info, seleccion, selecAnterior, consoleWidth);
        if (palabraSeleccion(info, seleccion) == palabraSeleccion(info, selecAnterior))
        {

            for (int i = 0; i < info.ren; i++)
            {
                for (int j = 0; j < info.col; j++)
                {
                    if (info.tableroDinamico[i][j].posicion == seleccion)
                    {
                        info.tableroDinamico[i][j].estado = true;
                    }
                    if (info.tableroDinamico[i][j].posicion == selecAnterior)
                    {
                        info.tableroDinamico[i][j].estado = true;
                    }
                }
            }
            palabrasRestantes--;
            seleccion = 0; // Reset de variables
            selecAnterior = 0;
            intentos = 0;
        }
        if (intentos == 2)
        {
            seleccion = 0; // Reset de variables
            selecAnterior = 0;
            intentos = 0;
            Sleep(3000);
            system("cls");
            imprimirTab(info, seleccion, selecAnterior, consoleWidth);
        }

        if (palabrasRestantes == 0)
        {
            win = true;
        }

        selecAnterior = seleccion;

    } while (!win);
    end = medirT();
    registrobin( info);
    info.duracDeJueg = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    Sleep(2000);
    system("cls");
    // Guardar Todo en el Bin
    // regreso al menu
    color(hConsole, 6);
    for (int i = 0; i < 15; i++)
    {
        Sleep(800);
        string line = " _______________________________";
        int leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 14);
        cout << line;
        line = "|                               |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 15);
        cout << line;
        line = "| #   #  ##  #  #  #   # # #  # |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 16);
        cout << line;
        line = "|  # #  #  # #  #  #   # # ## # |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 17);
        cout << line;
        line = "|   #   #  # #  #  # # # # # ## |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 18);
        cout << line;
        line = "|   #    ##   ##    # #  # #  # |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 19);
        cout << line;
        line = "|_______________________________|";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 20);
        cout << line;
        Sleep(800);
        if (i < 14)
        {
            system("cls");
        }
    }
}
// Assets

bool validarAlias(string alias, int consoleWidth)
{
    int leftPadding;
    bool aux = true;
    string line;
    // condiciones de validacion
    if (alias.length() < 4 || alias.length() > 12)
    {
        aux = false;
        line = "La longitud del Alias no es permitida, por favor inserte un alias con mas de 4 caracteres y menos de 12";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 17);
        cout << line;
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 18);
        system("pause");
        return aux;
    }
    if (!isalpha(alias[0]))
    {
        aux = false;
        line = "El primer caracter del alias debe de ser una letra, intentelo de nuevo";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 17);
        cout << line;
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 18);
        system("pause");
        return aux;
    }
    for (int i = 1; i < alias.size(); i++) // desde i=1 pk i=0 ya se valido
    {
        if (isspace(alias[i]))
        {
            aux = false;
            line = "Caracter invalido en el alias, solo se permiten letras, numeros y guiones bajos";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 17);
            cout << line;
            leftPadding = (consoleWidth - 32) / 2;
            gotoxy(leftPadding, 18);
            system("pause");
            return aux;
        }
    }
    return aux;
}

bool validarCategoria(string cat, int consoleWidth)
{
    string line;
    int leftPadding;
    bool aux = false;
    // condiciones de validacion
    if (cat == "Dispositivos electronicos")
    {
        aux = true;
    }
    if (cat == "Lenguajes de programacion")
    {
        aux = true;
    }
    if (cat == "Paises")
    {
        aux = true;
    }
    if (!aux)
    {
        line = "La categoria ingresada no es correcta, por favor intente de nuevo";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 19);
        cout << line;
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 20);
        system("pause");
    }
    return aux;
}

bool validarPalabras(int words, int consoleWidth)
{
    bool aux = false;
    string line;
    int leftPadding;
    // condiciones de validacion
    if (words == 3)
    {
        aux = true;
    }
    if (words == 6)
    {
        aux = true;
    }
    if (words == 8)
    {
        aux = true;
    }

    if (!aux)
    {
        line = "La opcion de palabras ingresada no es correcta, por favor intente de nuevo";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 20);
        cout << line;
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 21);
        system("pause");
    }
    return aux;
}

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

void llenarTab(casilla **mat, int ren, int col, string *v, string cat, int pal)
{
    // Primero se llena el vector dinamico con los nombres de la categoria a buscar
    srand(time(NULL));
    int posicion, k = 0, j = 0, total = 0, tam = ren * col, *posiciones = new int[pal];
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
        // crear un vector de las posiciones sin repetidos
        do
        {
            posicion = rand() % total;
            if (validarRepetidos(posiciones, posicion, k))
            {
                posiciones[k] = posicion;
                k++;
            }
        } while (k < pal);

        for (int i = 0; i < tam; i++)
        {
            k = 0;
            categoria.clear();
            categoria.seekg(0);
            while (getline(categoria, aux))
            {
                if (k == posiciones[j])
                {
                    v[i] = aux;
                    v[i + 1] = aux;
                    j++;
                    i++;
                    break;
                }
                k++;
            }
        }
        shuffle(v, tam);
        shuffle(v, tam);
        shuffle(v, tam);
        shuffle(v, tam);
        categoria.close();
        k = 0;
        j = 0;
        // Llenar la matriz dinamica de structs con el vector dinamico, la posicion con un contador y el bool en falso
        for (int i = 0; i < ren; i++)
        {
            for (int j = 0; j < col; j++)
            {
                mat[i][j].palabra = v[k];
                mat[i][j].estado = false;
                mat[i][j].posicion = k + 1;
                k++;
            }
        }
    }
    delete[] v;
}

void imprimirTab(dato info, int seleccion, int seleccionAnterior, int consoleWidth)
{
    system("cls");
    int leftPadding = (consoleWidth - (info.ren * 16)) / 2, k = 1;
    for (int i = 0; i < info.ren; i++)
    {

        if (i == 0)
        {
            gotoxy((leftPadding - 1), k);
            for (int j = 0; j < info.col; j++)
            {
                cout << "________________";
            }
        }
        else
        {
            gotoxy(leftPadding, k);
            for (int j = 0; j < info.col; j++)
            {
                cout << "_______________|";
            }
        }
        cout << endl
             << setw(leftPadding) << "|";
        for (int k = 0; k < info.col; k++)
        {
            cout << setw(16) << "|";
        }
        cout << endl
             << setw(leftPadding) << "|";
        for (int j = 0; j < info.col; j++)
        {
            if (info.tableroDinamico[i][j].posicion == seleccion || info.tableroDinamico[i][j].estado || info.tableroDinamico[i][j].posicion == seleccionAnterior)
            {
                cout << setw(12) << info.tableroDinamico[i][j].palabra << setw(4) << "|";
            }
            else
            {
                cout << setw(12) << info.tableroDinamico[i][j].posicion << setw(4) << "|";
            }
        }
        cout << endl
             << setw(leftPadding) << "|";
        if (i == info.ren - 1)
        {
            for (int j = 0; j < info.col; j++)
            {
                cout << "_______________|";
            }
        }
        k += 3;
    }
}

bool validarRepetidos(int *v, int num, int k)
{
    bool aux = true;
    for (int j = 0; j < k; j++)
    {
        if (v[j] == num)
        {
            aux = false;
            break;
        }
    }
    return aux;
}

void shuffle(string *v, int tam)
{
    if (tam > 1)
    {
        for (int i = 0; i < tam - 1; i++)
        {
            int j = i + rand() / (RAND_MAX / (tam - i) + 1);
            string t = v[j];
            v[j] = v[i];
            v[i] = t;
        }
    }
}

void clearLines(int inicio, int lineas)
{
    // Mover el cursor a la línea especificada
    cout << "\033[" << inicio << ";1H";

    // Borrar las líneas desde la posición actual
    for (int i = 0; i < lineas; i++)
    {
        cout << "\033[K"; // Borrar hasta el final de la línea
        if (i < lineas - 1)
        {
            cout << "\033[E"; // Mover el cursor al principio de la siguiente línea
        }
    }
}

clock_t medirT()
{
    clock_t time = clock();
    return time;
}

string palabraSeleccion(dato info, int seleccion)
{

    if (seleccion!=0)
    {
        for (int i = 0; i < info.ren; i++)
        {
            for (int j = 0; j < info.col; j++)
            {
                if (info.tableroDinamico[i][j].posicion == seleccion)
                {
                    return info.tableroDinamico[i][j].palabra;
                }
            }
        }        
    }
    else
    {
        return " ";
    }
}

// Archivos

void leerArch(int arch, int consoleWidth)
{
    fstream file;
    string line;
    int leftPadding;
    system("cls");
    if (arch == 1)
    {
        file.open(CAT1, ios::in);
        line = "DISPOSITIVOS MOVILES";
        int leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    if (arch == 2)
    {
        file.open(CAT2, ios::in);
        line = "LENGUAJES DE PROGRAMACION";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    if (arch == 3)
    {
        file.open(CAT3, ios::in);
        line = "PAISES";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    int i = 3, j = 1;
    while (getline(file, line))
    {
        leftPadding = (consoleWidth - (line.length() + 3)) / 2;
        gotoxy(leftPadding, i);
        cout << j << ".-";
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '_')
            {
                cout << " ";
            }
            else
            {
                cout << line[i];
            }
        }

        i += 2;
        j++;
    }
    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, i);
    system("pause");
}

void agregar(int arch, int consoleWidth)
{
    system("cls");
    fstream file;
    string line;
    int leftPadding;

    if (arch == 1)
    {
        file.open(CAT1, ios::out | ios::app);
        line = "DISPOSITIVOS MOVILES";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    if (arch == 2)
    {
        file.open(CAT2, ios::out | ios::app);
        line = "LENGUAJES DE PROGRAMACION";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    if (arch == 3)
    {
        file.open(CAT3, ios::out | ios::app);
        line = "PAISES";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
    }
    string palabra;

    line = "Ingresa la palabra a agregar: ";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    fflush(stdin);
    getline(cin, palabra);
    for (int i = 0; i < palabra.length(); i++)
    {
        if (palabra[i] == ' ')
        {
            palabra[i] = '_';
        }
    }
    file << palabra << endl;
    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 17);
    system("Pause");
}

void eliminar(int arch, int consoleWidth)
{
    system("cls");
    fstream file, temp;
    temp.open("temp.txt", ios::out);

    string line = "";
    int leftPadding;
    bool status = validarPalabrasArch(arch);
    if (!status)
    {
        line = "El numero de palabras es menor a ocho";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;

        line = "Por favor agregue mas palabras";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 3);
        cout << line;

        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 17);
        system("Pause");

        while (!status)
        {
            system("cls");
            agregar(arch, consoleWidth);
            status = validarPalabrasArch(arch);
        }
    }
    else
    {
        if (arch == 1)
        {
            file.open(CAT1, ios::in | ios::out);
            line = "DISPOSITIVOS MOVILES";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 1);
            cout << line;
        }
        if (arch == 2)
        {
            file.open(CAT2, ios::in | ios::out);
            line = "LENGUAJES DE PROGRAMACION";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 1);
            cout << line;
        }
        if (arch == 3)
        {
            file.open(CAT3, ios::in | ios::out);
            line = "PAISES";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 1);
            cout << line;
        }

        int i = 1, aux;
        bool flag;
        string palabra;

        line = "Ingresa el ID: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 3);
        cout << line;
        cin >> aux;
        while (getline(file, palabra))
        {
            if (aux != i)
            {
                temp << palabra << endl;
            }
            i++;
        }
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, 7);
        temp.close();
        file.close();
        if (arch == 1)
        {
            system("del categoria1.txt");
            system("ren temp.txt categoria1.txt");
        }
        if (arch == 2)
        {
            system("del categoria2.txt");
            system("ren temp.txt categoria2.txt");
        }
        if (arch == 3)
        {
            system("del categoria3.txt");
            system("ren temp.txt categoria3.txt");
        }
        leftPadding = (consoleWidth - 32) / 2;
        gotoxy(leftPadding, i);
        system("Pause");
    }
}

void registrarjugador(dato info, int consoleWidth)
{
    fstream juga;
    char nomarch[30] = "registrojugadores.txt";
    juga.open(nomarch, ios::out | ios::app);
    time_t now = time(0);
    struct tm *time = localtime(&now);
    char dia[12];
    char hora[10];
    strftime(dia, 12, "%d/%m/%Y", time);
    strftime(hora, 10, "%H:%M:%S", time);
    if (!juga)
        cout << " No se pudo hacer el registro " << endl;
    else
    {
        juga << info.alias << " " << info.catAJugar << " " << info.palAUsar << " " << hora << " " << dia << endl;
        system("cls");
        for (int i = 0; i < info.ren; i++)
        {

            if (i == 0)
            {
                for (int j = 0; j < info.col; j++)
                {
                    juga << setw(16) << "________________";
                }
            }
            else
            {
                for (int j = 0; j < info.col; j++)
                {
                    juga << "_______________|";
                }
            }
            juga << endl << "|";
            for (int k = 0; k < info.col; k++)
            {
                juga << setw(16) << "|";
            }
            juga << endl << "|";
            for (int j = 0; j < info.col; j++)
            {
                if (info.tableroDinamico[i][j].posicion == 0 || info.tableroDinamico[i][j].estado)
                {
                    juga << setw(12) << info.tableroDinamico[i][j].palabra << setw(4) << "|";
                }
                else
                {
                    juga << setw(12) << info.tableroDinamico[i][j].palabra << setw(4) << "|";
                }
            }
            juga << endl << "|";
            if (i == info.ren - 1)
            {
                for (int j = 0; j < info.col; j++)
                {
                    juga << "_______________|";
                }
            }
        }
        juga << endl;
        juga.close();
    }
}

bool validarPalabrasArch(int arch)
{
    fstream file;
    bool status;
    string palabra;
    int palabras = 0;
    if (arch == 1)
    {
        file.open(CAT1, ios::in | ios::out);
    }
    if (arch == 2)
    {
        file.open(CAT2, ios::in | ios::out);
    }
    if (arch == 3)
    {
        file.open(CAT3, ios::in | ios::out);
    }
    while (getline(file, palabra))
    {
        palabras++;
    }
    status = palabras < 8 ? false : true;
    return status;
}
void registrobin(dato info){
	fstream regs;
    regs.open("registrobinario.dat", ios::binary|ios::out|ios::app);
    if (!regs)      
    {
        cerr<<"No se puede hacer el registro binario "<<endl;
        cin.get();
    }
    // char dia[12];
    // strftime(dia, 12, "%d/%m/%Y", time);
    // regs << dia << " ";
    regs.write((char *)(&info),sizeof(dato));
    regs.close();
}
