// Categorias del Memorama: Lenguajes de Programacion, Dispositivos electronicos, paises
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>

#define CAT1 "categoria1.txt"
#define CAT2 "categoria2.txt"
#define CAT3 "categoria3.txt"

using namespace std;

// Portada
void portada(int consoleWidth);      /* Caso 2 */
void presentacion(int consoleWidth); /* Caso 2 */

// Menus
int menu(int consoleWidth);                             /* Caso 4 */
void menuJuego(int consoleWidth);                       /* Caso 2 */
void mantenimiento();                                   /* Caso 1 */
void opcionesMantenimiento(int arch, int consoleWidth); /* Caso 2 */

// Fundamentales
int **pedirMemoria(int ren, int col); /* Caso 4 */
void gotoxy(int x, int y);            /* Caso 2 */
void quitarYponerDiag(char[], bool);  /* Caso 2 */

// Assets
bool validarAlias(string alias);   /* Caso 2 */
bool validarCategoria(string cat); /* Caso 2 */
bool validarPalabras(int words);   /* Caso 2 */

// Archivos
void leerArch(int arch, int consoleWidth);
void agregar(int arch, int consoleWidth);
void eliminar(int arch, int consoleWidth);

int main(int argc, char const *argv[])
{
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

    line = "Programacion 1";
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
    int palAUsar;
    string alias, catAJugar, line;
    do
    {
        system("cls");
        line = "JUGAR";
        int leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 1);
        cout << line;
        line = "Dame tu Alias para jugar: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 3);
        cout << line;
        fflush(stdin);
        getline(cin, alias);
        // Validar Alias
        line = "Dime cual de las 3 categorias quieres jugar: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 5);
        cout << line;
        line = "1.- Dispositivos electronicos";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 7);
        cout << line;
        line = "2.- Lenguajes de programacion";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 8);
        cout << line;
        line = "3.- Paises";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 9);
        cout << line;
        line = "Opcion: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 10);
        cout << line;
        fflush(stdin);
        getline(cin, catAJugar);
        // Validar cat
        line = "Con cuantas Palabras deseas Jugar (3,6 u 8 palabras): ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 12);
        cout << line;
        line = "Opcion: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 13);
        cout << line;
        cin >> palAUsar;
        // validar palabras
    } while (!validarAlias(alias) || !validarCategoria(catAJugar) || !validarPalabras(palAUsar));
}

// Fundamentales

int **pedirMemoria(int ren, int col)
{
    int **aux = new int *[ren];
    for (int i = 0; i < ren; i++)
    {
        aux[i] = new int[col];
    }
    return aux;
}

void gotoxy(int x, int y)
{
    HANDLE hcon;
    hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

// Assets

bool validarAlias(string alias)
{
    bool aux = true;
    // condiciones de validacion
    if (alias.length() < 4 || alias.length() > 12)
    {
        aux = false;
        cout << "La longitud del Alias no es permitida, por favor inserte un alias con mas de 4 caracteres y menos de 12" << endl;
    }
    if (!isalpha(alias[0]))
    {
        aux = false;
        cout << "El primer caracter del alias debe de ser una letra, intentelo de nuevo" << endl;
    }
    for (int i = 1; i < alias.size(); i++) // desde i=1 pk i=0 ya se valido
    {
        if (isspace(alias[i]))
        {
            aux = false;
            cout << "Caracter invalido en el alias, solo se permiten letras, numeros y guiones bajos" << endl;
        }
    }
    if (!aux)
    {
        cout << "El alias Ingresado no es correcto, por favor intente de nuevo" << endl;
        system("pause");
    }
    return aux;
}
bool validarCategoria(string cat)
{
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
        cout << "La categoria ingresada no es correcta, por favor intente de nuevo" << endl;
        system("pause");
    }
    return aux;
}
bool validarPalabras(int words)
{
    bool aux = false;
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
        cout << "La opcion de palabras ingresada no es correcta, por favor intente de nuevo" << endl;
        system("pause");
    }
    return aux;
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
    file << palabra;

    system("Pause");
}

void eliminar(int arch, int consoleWidth)
{
    system("cls");
    fstream file, temp;
    temp.open("temp.txt", ios::out);

    string line;
    int leftPadding;

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
        else
        {
            flag = true;
        }
        i++;
    }
    if (!flag)
    {
        line = "ID no encontrado";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 5);
        cout << line;
    }
    else
    {
        line = "Se ha eliminado correctamente";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 5);
        cout << line;
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
    system("pause");
}