// Categorias del Memorama: Lenguajes de Programacion, Dispositivos electronicos, paises
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cstring>

#define CAT1 "categoria1.txt"
#define CAT2 "categoria2.txt"
#define CAT3 "categoria3.txt"
#define color SetConsoleTextAttribute

using namespace std;

// Aqui van las librerias .h

#include "lib/creaTablas.h"
#include "lib/perritos.h"
#include "lib/archivos.h"
#include "lib/memDinamica.h"
#include "lib/datos.h"

// Portada
void portada(int consoleWidth);      /* Caso 2 */
void portada2(int consoleWidth);     /*Caso 2*/
void presentacion(int consoleWidth); /* Caso 2 */

// Menus
int menu(int consoleWidth);                             /* Caso 4 */
void menuJuego(int consoleWidth);                       /* Caso 2 */
void mantenimiento();                                   /* Caso 1 */
void opcionesMantenimiento(int arch, int consoleWidth); /* Caso 2 */

// Fundamentales
casilla **crearTablero(int pal, char categoria[], int *ren, int *col); /* Caso 4 */
void juego(dato info, int consoleWith, int opc);
void menuReportes(int consoleWidth);

// Assets
bool validarAlias(char alias[], int consoleWidth);                                   /* Caso 2 */
bool validarCategoria(char cat[], int consoleWidth);                                 /* Caso 2 */
bool validarPalabras(int words, int consoleWidth);                                   /* Caso 2 */
void llenarTab(casilla **mat, int ren, int col, string *v, char cat[], int pal);     /* Caso 2*/
void imprimirTab(dato info, int seleccion, int seleccionAnterior, int consoleWidth); /* Caso 2 */
void shuffle(string *v, int tam);                                                    /* Caso 2*/
bool validarRepetidos(int *v, int num, int k);                                       /* Caso 4*/
void clearLines(int inicio, int lineas);                                             /* Caso 2 */
clock_t medirT();                                                                    /* Caso 3 */
string palabraSeleccion(dato info, int posicion);
void quitarMayus(char str[], char aux[]);
int generarNumeroAleatorio(int min, int max);
bool numeroSeleccionadoAnteriormente(int *numerosSeleccionados, int size, int numero);

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
        {
            int palAUsar, leftPadding;
            bool band1, band2, band3;
            string line;
            dato datos;
            {
                system("cls");
                strcpy(datos.alias, "Makina");
                line = "Dime cual de las 3 categorias quieres jugar: ";
                leftPadding = (consoleWidth - line.length()) / 2;
                gotoxy(leftPadding, 6);
                cout << line;
                line = "1.- Dispositivos";
                leftPadding = (consoleWidth - line.length()) / 2;
                gotoxy(leftPadding, 8);
                cout << line;
                line = "2.- Programacion";
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
                cin.getline(datos.catAJugar, 40);
                band2 = validarCategoria(datos.catAJugar, consoleWidth);
                if (!band2) // Borra de pantalla cosas basura
                {
                    clearLines(12, 2);
                    clearLines(19, 3);
                }
            }
            while (!band2)
                ;
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
            switch (datos.palAUsar)
            {
            case 3:
                datos.ren = 3;
                break;
            case 6:
                datos.ren = 4;
                break;
            case 8:
                datos.ren = 4;

            default:
                break;
            }

            datos.tableroDinamico = crearTablero(datos.palAUsar, datos.catAJugar, &datos.ren, &datos.col);
            time_t now = time(0);
            struct tm *time = localtime(&now);
            strftime(datos.dia, 12, "%d/%m/%Y", time);
            strftime(datos.hora, 10, "%H:%M:%S", time);
            registrarjugador(datos, consoleWidth);
            juego(datos, consoleWidth, 2);
            break;
        }
        case 3:
            menuReportes(consoleWidth);
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 1);
    // PlaySound("assets/Time.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP );
    Sleep(500);
    string line = "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    Sleep(500);
    line = "Ingenieria en sistemas computacionales";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    Sleep(500);
    line = "Programacion I";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    color(hConsole, 11);
    Sleep(500);
    line = "Nombre";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    Sleep(1000);
    line = "Sergio Eder Cervantes Rincon";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;
    Sleep(1000);
    line = "Daan Jostin Carabez Garcia";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    Sleep(1000);
    line = "Luis Alberto Pedroza Diaz";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;
    Sleep(1000);
    line = "Luis David Flores Martinez";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 17);
    cout << line;
    Sleep(1000);
    line = "Maestra Georgina Salazar Partida";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 19);
    cout << line;
    Sleep(1000);
    line = "09/06/2023";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 21);
    cout << line;
    Sleep(1000);

    system("cls");
    color(hConsole, 240);
    line = "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    line = "Ingenieria en sistemas computacionales";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    line = "Programacion I";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    line = "Nombre";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    line = "Sergio Eder Cervantes Rincon";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;
    line = "Daan Jostin Carabez Garcia";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    line = "Luis Alberto Pedroza Diaz";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;
    line = "Luis David Flores Martinez";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 17);
    cout << line;
    system("cls");
    color(hConsole, 15);
    line = "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    line = "Ingenieria en sistemas computacionales";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    line = "Programacion I";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    color(hConsole, 15);
    line = "Nombre";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    line = "Sergio Eder Cervantes Rincon";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;
    line = "Daan Jostin Carabez Garcia";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    line = "Luis Alberto Pedroza Diaz";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;
    line = "Luis David Flores Martinez";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 17);
    cout << line;
    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 19);
    portada2(consoleWidth);
    line = "Maestra Georgina Salazar Partida";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 19);
    cout << line;
    line = "09/06/2023";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 21);
    cout << line;
}

void portada2(int consoleWidth)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 1);
    string line = "UNIVERSIDAD AUTONOMA DE AGUASCALIENTES";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    line = "Ingenieria en sistemas computacionales";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    line = "Programacion I";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    color(hConsole, 11);
    line = "Nombre";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    line = "Sergio Eder Cervantes Rincon";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;
    line = "Daan Jostin Carabez Garcia";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 13);
    cout << line;
    line = "Luis Alberto Pedroza Diaz";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 15);
    cout << line;
    line = "Luis David Flores Martinez";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 17);
    cout << line;
    line = "Maestra Georgina Salazar Partida";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 19);
    cout << line;
    line = "09/06/2023";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 21);
    cout << line;
    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 23);
    system("Pause");
}

void presentacion(int consoleWidth)
{

    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int k = 15;
    color(hConsole, 5);
    string line = "Las Memorables Aventuras De Memorin";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    Sleep(200);
    leftPadding = (consoleWidth - 35) / 2;
    gotoxy(leftPadding, 6);
    color(hConsole, 13);
    cout << "Programando Sue" << char(164) << "os, Maquinando Ideas";
    Sleep(200);
    imprimirMatrizCentrada();

    leftPadding = (consoleWidth - 32) / 2;
    gotoxy(leftPadding, 9);

    system("Pause");
}

// Menus

int menu(int consoleWidth)
{

    int opc;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");
    // PlaySound(NULL,0,0);
    // PlaySound("assets/Time.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP );
    Sleep(500);
    color(hConsole, 5);
    string line = "MENU";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line;
    Sleep(500);
    color(hConsole, 10);
    line = "1.- Jugar";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 3);
    cout << line;
    Sleep(500);
    color(hConsole, 6);
    line = "2.- Simulacion";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 5);
    cout << line;
    Sleep(500);
    color(hConsole, 3);
    line = "3.- Reporte";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 7);
    cout << line;
    Sleep(500);
    color(hConsole, 8);
    line = "4.- Mantenimiento";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 9);
    cout << line;
    Sleep(500);
    color(hConsole, 12);
    line = "5.- Salir";
    leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 11);
    cout << line;
    Sleep(500);
    perrito1();
    color(hConsole, 11);
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
    color(hConsole, 8);
    // PlaySound(NULL, 0, 0);
    // PlaySound("assets/sans.wav", NULL, SND_ASYNC | SND_NOSTOP | SND_LOOP | SND_FILENAME);
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
        string line = "Que deseas hacer?";
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
    // PlaySound(NULL,0,0);
}

void menuJuego(int consoleWidth)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    color(hConsole, 10);
    int palAUsar, leftPadding;
    bool band1, band2, band3;
    string line;
    dato datos;
    // PlaySound(NULL,0,0);
    // PlaySound("assets/snail.wav", NULL, SND_ASYNC | SND_NOSTOP | SND_LOOP| SND_FILENAME);

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
        cin.getline(datos.alias, 15);
        band1 = validarAlias(datos.alias, consoleWidth);
    } while (!band1);

    do // Capturar Categoria
    {
        line = "Dime cual de las 3 categorias quieres jugar: ";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 6);
        cout << line;
        line = "1.- Dispositivos";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 8);
        cout << line;
        line = "2.- Programacion";
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
        cin.getline(datos.catAJugar, 40);
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
    time_t now = time(0);
    struct tm *time = localtime(&now);
    strftime(datos.dia, 12, "%d/%m/%Y", time);
    strftime(datos.hora, 10, "%H:%M:%S", time);
    registrarjugador(datos, consoleWidth);
    // tablero dinamico es casilla**
    juego(datos, consoleWidth, 1);
}

// Fundamentales

casilla **crearTablero(int pal, char categoria[], int *ren, int *col)
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

void juego(dato info, int consoleWidth, int opc)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int seleccion = 0, selecAnterior = 0, palabrasRestantes = info.palAUsar, intentos = 0;
    info.par = 0;
    bool win = false;
    string symbl = "#";
    clock_t start, end;
    // PlaySound(NULL, 0, 0);
    start = medirT();
    switch (opc)
    {
    case JUGAR:
        system("cls");
        imprimirTab(info, seleccion, selecAnterior, consoleWidth);
        cout << endl;
        do
        {
            // PreguntarCasilla
            do
            {
                string line = "Selecciona una casilla: ";
                int leftPadding = (consoleWidth - line.length()) / 2;
                gotoxy(leftPadding, 22);
                cout << line;
                leftPadding = (consoleWidth) / 2;
                gotoxy(leftPadding, 23);
                cin >> seleccion;

                for (int i = 0; i < info.ren; i++)
                {
                    for (int j = 0; j < info.col; j++)
                    {
                        if (info.tableroDinamico[i][j].posicion == seleccion && info.tableroDinamico[i][j].estado == true)
                        {
                            // PlaySound(NULL, 0, 0);
                            // PlaySound("assets/Error.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
                            line = "La casilla ya ha sido destapada, por favor elija otra";
                            leftPadding = (consoleWidth - line.length()) / 2;
                            gotoxy(leftPadding, 25);
                            cout << line;
                            Sleep(500);
                        }
                    }
                }

                if (seleccion == selecAnterior)
                {
                    // PlaySound(NULL,0,0);
                    // PlaySound("assets/Error.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP );
                    line = "La casilla ya ha sido destapada, por favor elija otra";
                    leftPadding = (consoleWidth - line.length()) / 2;
                    gotoxy(leftPadding, 25);
                    cout << line;
                    Sleep(500);
                }
                if (seleccion > (info.palAUsar * 2) || seleccion < 1)
                {
                    // PlaySound(NULL, 0, 0);
                    // PlaySound("assets/Error.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
                    line = "Valor fuera de rango";
                    leftPadding = (consoleWidth - line.length()) / 2;
                    gotoxy(leftPadding, 25);
                    cout << line;
                    Sleep(500);
                }

            } while (seleccion < 1 || seleccion > (info.palAUsar * 2) || seleccion == selecAnterior);

            // Validar casilla que este dentro de lo rangos y que no se haya seleccionado anteriormente
            intentos++;
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
                // PlaySound(NULL,0,0);
                // PlaySound("assets/Correct.wav",NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
                info.par = info.par + 1;
                palabrasRestantes--;
                seleccion = 0; // Reset de variables
                selecAnterior = 0;
                intentos = 0;
            }
            Sleep(500);
            system("cls");
            imprimirTab(info, seleccion, selecAnterior, consoleWidth);
            if (intentos == 2)
            {
                seleccion = 0; // Reset de variables
                selecAnterior = 0;
                intentos = 0;
                Sleep(1500);
                system("cls");
                imprimirTab(info, seleccion, selecAnterior, consoleWidth);
            }

            if (palabrasRestantes == 0)
            {
                win = true;
            }
            if (palabrasRestantes == 0)
            {
                win = true;
                // PlaySound(NULL, 0, 0 );
                // PlaySound("assets/Yay.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP );
            }

            selecAnterior = seleccion;
        } while (!win);
        break;
    case SIMULAR:
        system("cls");
        BorrarEspMemDina(info.tableroDinamico, info.ren);
        info.tableroDinamico = crearTablero(info.palAUsar, info.catAJugar, &info.ren, &info.col);
        imprimirTab(info, 0, 0, consoleWidth);
        cout << endl;

        int valorMaximo;
        valorMaximo = (info.palAUsar) * 2;
        int *numerosSeleccionados;
        numerosSeleccionados = pedirMemVector(valorMaximo);
        int val1, val2;
        int size;
        size = 0;
        for (int i = 0; i < sizeof(numerosSeleccionados); i++)
        {
            numerosSeleccionados[i] = 0;
        }

        do
        {
            do
            {
                val1 = generarNumeroAleatorio(1, valorMaximo);
            } while (numeroSeleccionadoAnteriormente(numerosSeleccionados, size, val1));

            do
            {
                val2 = generarNumeroAleatorio(1, valorMaximo);
            } while (val2 == val1 || numeroSeleccionadoAnteriormente(numerosSeleccionados, size, val2));

            // Validar casilla que este dentro de lo rangos y que no se haya seleccionado anteriormente
            intentos++;
            Sleep(500);
            system("cls");
            imprimirTab(info, val1, 0, consoleWidth);
            if (palabraSeleccion(info, val1) == palabraSeleccion(info, val2))
            {

                for (int i = 0; i < info.ren; i++)
                {
                    for (int j = 0; j < info.col; j++)
                    {
                        if (info.tableroDinamico[i][j].posicion == val1)
                        {
                            info.tableroDinamico[i][j].estado = true;
                        }
                        if (info.tableroDinamico[i][j].posicion == val2)
                        {
                            info.tableroDinamico[i][j].estado = true;
                        }
                    }
                }
                // PlaySound(NULL, 0, 0);
                // PlaySound("assets/Correct.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
                numerosSeleccionados[size] = val1;
                size++;
                numerosSeleccionados[size] = val2;
                size++;
                info.par = info.par + 1;
                palabrasRestantes--;
                val1 = 0; // Reset de variables
                val2 = 0;
                intentos = 0;
            }
            Sleep(500);
            imprimirTab(info, val1, val2, consoleWidth);
            intentos = 2;
            if (intentos == 2)
            {
                // PlaySound(NULL, 0, 0);
                // PlaySound("assets/Error.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP);
                val1 = 0; // Reset de variables
                val2 = 0;
                intentos = 0;
                Sleep(1500);
                system("cls");
                imprimirTab(info, val1, val2, consoleWidth);
            }

            if (palabrasRestantes == 0)
            {
                win = true;
            }

        } while (!win);
        break;
    default:
        break;
    }

    end = medirT();
    info.duracDeJueg = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    Sleep(6000);
    system("cls");
    registrobin(info);
    BorrarEspMemDina(info.tableroDinamico, info.ren);
    // regreso al menu
    color(hConsole, 6);
    // PlaySound(NULL,0,0);
    // PlaySound("assets/maxwell.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP | SND_LOOP );
    for (int i = 0; i < 8; i++)
    {
        Sleep(800);
        string line = "______________________________________________________________";
        int leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 4);
        cout << line;
        line = "|                                                              |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 5);
        cout << line;
        line = "|                                                              |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 6);
        cout << line;
        line = "|  ##      ##    ####    ##    ##    ##      ##  ##  ##    ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 7);
        cout << line;
        line = "|  ##      ##    ####    ##    ##    ##      ##  ##  ##    ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 8);
        cout << line;
        line = "|    ##  ##    ##    ##  ##    ##    ##      ##  ##  ####  ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 9);
        cout << line;
        line = "|    ##  ##    ##    ##  ##    ##    ##      ##  ##  ####  ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 10);
        cout << line;
        line = "|      ##      ##    ##  ##    ##    ##  ##  ##  ##  ##  ####  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 11);
        cout << line;
        line = "|      ##      ##    ##  ##    ##    ##  ##  ##  ##  ##  ####  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 12);
        cout << line;
        line = "|      ##        ####      ####        ##  ##    ##  ##    ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 13);
        cout << line;
        line = "|      ##        ####      ####        ##  ##    ##  ##    ##  |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 14);
        cout << line;
        line = "|                                                              |";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 15);
        cout << line;
        line = "|______________________________________________________________|";
        leftPadding = (consoleWidth - line.length()) / 2;
        gotoxy(leftPadding, 16);
        cout << line;
        Sleep(800);
        if (i < 6)
        {
            system("cls");
        }
    }
    string line = "Tiempo De Juego:";
    int leftPadding = (consoleWidth - line.length()) / 2;
    gotoxy(leftPadding, 18);
    cout << line;
    leftPadding = (consoleWidth - 8) / 2;
    gotoxy(leftPadding, 19);
    cout << info.duracDeJueg << " seg";
    leftPadding = (consoleWidth - 20) / 2;
    gotoxy(leftPadding, 22);
    system("pause");
    // PlaySound(NULL, 0, 0 );
}

// Assets

bool validarAlias(char alias[], int consoleWidth)
{
    int leftPadding;
    bool aux = true;
    string line;
    // condiciones de validacion
    if (strlen(alias) < 4 || strlen(alias) > 12)
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
    for (int i = 1; i < strlen(alias); i++) // desde i=1 pk i=0 ya se valido
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

bool validarCategoria(char cat[], int consoleWidth)
{
    string line;
    int leftPadding;
    bool aux = false;
    // condiciones de validacion
    if (strcmp(cat, "Dispositivos") == 0)
    {
        aux = true;
    }
    if (strcmp(cat, "Programacion") == 0)
    {
        aux = true;
    }
    if (strcmp(cat, "Paises") == 0)
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
void llenarTab(casilla **mat, int ren, int col, string *v, char cat[], int pal)
{
    // Primero se llena el vector dinamico con los nombres de la categoria a buscar
    srand(time(NULL));
    int posicion, k = 0, j = 0, total = 0, tam = ren * col, *posiciones = new int[pal];
    fstream categoria;
    string aux;
    // Saber cual es la categoria que se ocupa
    if (strcmp(cat, "Dispositivos") == 0)
    {
        categoria.open(CAT1, ios::in);
    }
    if (strcmp(cat, "Programacion") == 0)
    {
        categoria.open(CAT2, ios::in);
    }
    if (strcmp(cat, "Paises") == 0)
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    char diaA[12], horaA[10];
    int leftPadding, k = 3;
    time_t now = time(0);
    struct tm *time = localtime(&now);
    color(hConsole, 15);
    strftime(diaA, 12, "%d/%m/%Y", time);
    strftime(horaA, 10, "%H:%M:%S", time);
    // PlaySound("assets/Shop.wav", NULL, SND_ASYNC | SND_NOSTOP | SND_LOOP| SND_FILENAME);
    if (info.palAUsar == 8)
    {
        leftPadding = (consoleWidth - (info.ren * 16)) / 2;
    }
    else
    {
        if (info.palAUsar == 6 || info.palAUsar == 3)
        {
            leftPadding = (consoleWidth - (info.ren * 12)) / 2;
        }
    }

    gotoxy(leftPadding, 1);
    cout << "Alias: " << info.alias << setw(18) << "Fecha: " << diaA;
    gotoxy(leftPadding, 2);
    cout << "Total de pares: " << info.par << setw(16) << "Hora: " << horaA;

    for (int i = 0; i < info.ren; i++)
    {

        if (i == 0)
        {
            gotoxy((leftPadding - 1), k);
            cout << esquinas(0);
            if (info.palAUsar == 8)
            {
                cout << lRecta(3);
            }
            if (info.palAUsar == 6)
            {
                cout << lRecta(2);
            }
            if (info.palAUsar == 3)
            {
                cout << lRecta(1);
            }
            for (int j = 0; j < info.col; j++)
            {
                cout << lRecta(16);
            }
            cout << esquinas(1);
        }
        else
        {
            gotoxy(leftPadding, k);
            for (int j = 0; j < info.col; j++)
            {
                cout << lRecta(16) << lLateral();
            }
        }
        cout << endl
             << setw(leftPadding) << lLateral();
        for (int k = 0; k < info.col; k++)
        {
            cout << setw(17) << lLateral();
        }
        cout << endl
             << setw(leftPadding) << lLateral();
        for (int j = 0; j < info.col; j++)
        {
            if (info.tableroDinamico[i][j].posicion == seleccion || info.tableroDinamico[i][j].posicion == seleccionAnterior || info.tableroDinamico[i][j].estado)
            {
                if (info.tableroDinamico[i][j].estado)
                {
                    color(hConsole, 2);
                    cout << setw(10) << info.tableroDinamico[i][j].palabra << setw(7);
                    color(hConsole, 7);
                    cout << lLateral();
                }
                else
                {
                    if (seleccionAnterior == 0)
                    {
                        color(hConsole, 6);
                        cout << setw(10) << info.tableroDinamico[i][j].palabra << setw(7);
                        color(hConsole, 7);
                        cout << lLateral();
                    }
                    else
                    {
                        // PlaySound(NULL,0,0);
                        // PlaySound("assets/Error.wav", NULL, SND_ASYNC | SND_FILENAME | SND_NOSTOP );
                        color(hConsole, 12);
                        cout << setw(10) << info.tableroDinamico[i][j].palabra << setw(7);
                        color(hConsole, 7);
                        cout << lLateral();
                    }
                }
            }
            else
            {
                cout << setw(9) << info.tableroDinamico[i][j].posicion << setw(8) << lLateral();
            }
        }
        cout << endl
             << setw(leftPadding);
        if (i == info.ren - 1)
        {
            cout << esquinas(2);
            if (info.palAUsar == 8)
            {
                cout << lRecta(3);
            }
            if (info.palAUsar == 6)
            {
                cout << lRecta(2);
            }
            if (info.palAUsar == 3)
            {
                cout << lRecta(1);
            }
            for (int j = 0; j < info.col; j++)
            {
                cout << lRecta(16);
            }
            cout << esquinas(3);
        }
        else
        {
            cout << lLateral();
        }
        k += 3;
    }
    color(hConsole, 15);
    perrito2();
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

    if (seleccion != 0)
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

// Reportes

int generarNumeroAleatorio(int min, int max)
{
    return min + rand() % (max - min + 1);
}
bool numeroSeleccionadoAnteriormente(int *numerosSeleccionados, int size, int numero)
{
    for (int i = 0; i < size; i++)
    {
        if (numerosSeleccionados[i] == numero)
        {
            return true;
        }
    }
    return false;
}