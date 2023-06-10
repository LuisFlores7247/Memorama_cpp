#ifndef ARCHIVOS
#define ARCHIVOS

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "creaTablas.h"
#include "perritos.h"
#include "datos.h"
#define CAT1 "categoria1.txt"
#define CAT2 "categoria2.txt"
#define CAT3 "categoria3.txt"
#define color SetConsoleTextAttribute

// Mantenimiento
void leerArch(int arch, int consoleWidth);          /* Caso 2*/
void agregar(int arch, int consoleWidth);           /* Caso 2*/
void eliminar(int arch, int consoleWidth);          /* Caso 2*/
void registrarjugador(dato info, int consoleWidth); /* Caso 2*/
bool validarPalabrasArch(int arch);                 /* Caso 4 */
void registrobin(dato info);                        /* Caso 2 */
// Reportes
void repXCategoria(int total, dato *v, int consoleWith);
void repXNombre(int total, dato *v, int consoleWith);
void repXTiempo(int total, dato *v, int consoleWith);
void imprimirRep(dato registro, int consoleWith);
void quitarMayus(char str[], char aux[]);

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

    if (!juga)
        cout << " No se pudo hacer el registro " << endl;
    else
    {
        juga << info.alias << " " << info.catAJugar << " " << info.palAUsar << " " << info.hora << " " << info.dia << endl;
        system("cls");
        for (int i = 0; i < info.ren; i++)
        {

            if (i == 0)
            {
                for (int j = 0; j < info.col; j++)
                {
                    juga << setw(16) << " _______________";
                }
            }
            else
            {
                for (int j = 0; j < info.col; j++)
                {
                    juga << "_______________|";
                }
            }
            juga << endl
                 << "|";
            for (int k = 0; k < info.col; k++)
            {
                juga << setw(16) << "|";
            }
            juga << endl
                 << "|";
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
            juga << endl
                 << "|";
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
void registrobin(dato info)
{
    fstream regs;
    regs.open("registrosBin.dat", ios::binary | ios::out | ios::app);
    if (!regs)
    {
        cerr << "No se puede hacer el registro binario " << endl;
        cin.get();
    }
    regs.write((char *)(&info), sizeof(dato));
    regs.close();
}

void menuReportes(int consoleWidth)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    dato aux, *registros;
    fstream file;
    int leftPadding;
    int opc = 0, k = 0;
    string line;
    do
    {
        k = 0;
        do
        {
            system("cls");
            color(hConsole, 3);
            // PlaySound(NULL,0,0);
            // PlaySound("assets/sans.wav",NULL,SND_ASYNC | SND_NOSTOP | SND_LOOP| SND_FILENAME);
            line = "Reportes";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 1);
            cout << line;
            line = "Lugar donde puedes ver todos los registros de juegos pasados";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 3);
            cout << line;
            line = "Como quieres que sea ordenado el reporte?";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 5);
            cout << line;
            line = "1.-Por categoria";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 7);
            cout << line;
            line = "2.-Por nombre";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 8);
            cout << line;
            line = "3.-Por Tiempo";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 9);
            cout << line;
            line = "4.-Salir";
            leftPadding = (consoleWidth - line.length()) / 2;
            gotoxy(leftPadding, 10);
            cout << line;
            leftPadding = consoleWidth / 2;
            gotoxy(leftPadding, 11);
            cin >> opc;
            if (opc < 1 || opc > 4)
            {
                line = "Opcion invalida, por favor intente de nuevo";
                leftPadding = (consoleWidth - line.length()) / 2;
                gotoxy(leftPadding, 13);
                cout << line << endl;
                leftPadding = consoleWidth / 2;
                gotoxy(leftPadding, 14);
                system("Pause");
            }

        } while (opc < 1 || opc > 4);

        // Contando la cantidad de registros existentes en el archivo binario

        file.open("registrosbin.dat", ios::binary | ios::in);
        while (file.read((char *)(&aux), sizeof(dato)))
        {
            k++;
        }
        registros = new dato[k];

        file.close();
        file.open("registrosbin.dat", ios::binary | ios::in); // Para resetear el cursor del archivo

        // Llenando el vector dinamico de structs con todos los registros del archivo binario
        for (int i = 0; i < k; i++)
        {
            file.read((char *)(&aux), sizeof(dato));
            registros[i] = aux;
        }
        file.close();
        // Switch para las opciones
        switch (opc)
        {
        case 1:
            repXCategoria(k, registros, consoleWidth);
            system("cls");
            Sleep(1000);
            break;
        case 2:
            repXNombre(k, registros, consoleWidth);
            system("cls");
            Sleep(1000);
            break;
        case 3:
            repXTiempo(k, registros, consoleWidth);
            system("cls");
            Sleep(1000);
            break;
        }
    } while (opc != 4);
    // PlaySound(NULL,0,0);
}

// Reportes
void repXCategoria(int total, dato *v, int consoleWith)
{
    char catSeleccionada[40];
    string resp;
    do
    {
        system("cls");
        string line = "Cual categoria deseas buscar?", tabla;
        int leftpadding = (consoleWith - line.length()) / 2, lfinal = 0, k = 0;
        bool encontrado = false;
        gotoxy(leftpadding, 1);
        fflush(stdin);
        cout << line;
        leftpadding = consoleWith / 2;
        gotoxy(leftpadding, 3);
        cin.getline(catSeleccionada, 40);

        line = lLateral() + "     Alias     " + lLateral() + "  Tiempo(segs) " + lLateral() + "     Dia     " + lLateral() + "     hora     " + lLateral() + "      Categoria      " + lLateral() + "  Dimensiones   " + lLateral();
        leftpadding = (consoleWith - line.length()) / 2;
        gotoxy(leftpadding, 4);
        tabla = esquinas(0) + lRecta(line.length()) + esquinas(1);
        cout << tabla;
        gotoxy(leftpadding, 5);
        cout << line;
        tabla = lLatDivisoria(0) + lRecta(line.length()) + lLatDivisoria(1);
        gotoxy(leftpadding, 6);
        cout << tabla << endl;
        for (int i = 0; i < total; i++)
        {
            if (strcmp(v[i].catAJugar, catSeleccionada) == 0)
            {
                encontrado = true;
                gotoxy(leftpadding, 7 + k);
                imprimirRep(v[i], consoleWith);
                lfinal = 7 + k;
                k++;
            }
        }
        tabla = esquinas(2) + lRecta(line.length()) + esquinas(3);
        gotoxy(leftpadding, lfinal + 1);
        cout << tabla;
        if (!encontrado)
        {
            system("cls");
            line = "Categoria no encontrada";
            leftpadding = (consoleWith - line.length()) / 2;
            gotoxy(leftpadding, 6);
            cout << line;
        }
        line = "Quieres buscar otra categoria? si/no";
        leftpadding = (consoleWith - line.length()) / 2;
        gotoxy(leftpadding, 20);
        cout << line;
        leftpadding = consoleWith / 2;
        gotoxy(leftpadding, 21);
        cin >> resp;
    } while (resp == "si");
}
void repXNombre(int total, dato *v, int consoleWith)
{
    // Ordenamiento del vector con respecto al nombre usando el algoritmo de ordenamiento por seleccion
    dato aux;
    int posMin;
    char straux1[15], straux2[15], c;

    for (int i = 0; i < total; i++)
    {
        posMin = i;
        for (int j = i + 1; j < total; j++)
        {
            quitarMayus(v[j].alias, straux1);
            quitarMayus(v[posMin].alias, straux2);
            cout << straux1 << " " << straux2 << endl;
            if (strcmp(straux1, straux2) < 0) // Busqueda del valor menor
            {
                posMin = j;
            }
        }
        // cambio de posicion
        aux = v[i];
        v[i] = v[posMin];
        v[posMin] = aux;
    }
    // Impresion del arreglo ordenado
    system("cls");
    string line = "Aqui esta el reporte ordenado alfabeticamente por el alias:", tabla;
    int lfinal = 0;
    int leftPadding = (consoleWith - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line << endl;

    line = lLateral() + "     Alias     " + lLateral() + "  Tiempo(segs) " + lLateral() + "     Dia     " + lLateral() + "     hora     " + lLateral() + "      Categoria      " + lLateral() + "  Dimensiones    " + lLateral();
    leftPadding = (consoleWith - line.length()) / 2;
    gotoxy(leftPadding, 4);
    tabla = esquinas(0) + lRecta(line.length()) + esquinas(1);
    cout << tabla;
    gotoxy(leftPadding, 5);
    cout << line;
    tabla = lLatDivisoria(0) + lRecta(line.length()) + lLatDivisoria(1);
    gotoxy(leftPadding, 6);
    cout << tabla << endl;

    for (int i = 0; i < total; i++)
    {
        gotoxy(leftPadding, 7 + i);
        imprimirRep(v[i], leftPadding);
        lfinal = 7 + i;
    }
    tabla = esquinas(2) + lRecta(line.length()) + esquinas(3);
    gotoxy(leftPadding, lfinal + 1);
    cout << tabla << endl;
    leftPadding = consoleWith / 2;
    gotoxy(leftPadding - 16, lfinal + 2);
    system("Pause");
}
void repXTiempo(int total, dato *v, int consoleWith)
{
    // Ordenamiento del vector con respecto al tiempo usando el algoritmo de ordenamiento por seleccion
    dato aux;
    int posMin, lfinal;
    for (int i = 0; i < total; i++)
    {
        posMin = i;
        for (int j = i + 1; j < total; j++)
        {
            if (v[j].duracDeJueg < v[posMin].duracDeJueg) // Busca el numero menor de lo que queda del arreglo
            {
                posMin = j;
            }
        }
        // Cambio de posicion
        aux = v[i];
        v[i] = v[posMin];
        v[posMin] = aux;
    }

    // Impresion del arreglo odenado
    system("cls");
    string line = "Aqui esta el reporte del 'Paseo de la fama':", tabla;
    int leftPadding = (consoleWith - line.length()) / 2;
    gotoxy(leftPadding, 1);
    cout << line << endl;

    line = lLateral() + "     Alias     " + lLateral() + "  Tiempo(segs) " + lLateral() + "     Dia     " + lLateral() + "     hora     " + lLateral() + "      Categoria      " + lLateral() + "    Dimensiones     " + lLateral();
    leftPadding = (consoleWith - line.length()) / 2;
    gotoxy(leftPadding, 4);
    tabla = esquinas(0) + lRecta(line.length()) + esquinas(1);
    cout << tabla;
    gotoxy(leftPadding, 5);
    cout << line;
    tabla = lLatDivisoria(0) + lRecta(line.length()) + lLatDivisoria(1);
    gotoxy(leftPadding, 6);
    cout << tabla << endl;

    for (int i = 0; i < total; i++)
    {
        gotoxy(leftPadding, 7 + i);
        imprimirRep(v[i], leftPadding);
        lfinal = 7 + i;
    }
    tabla = esquinas(2) + lRecta(line.length()) + esquinas(3);
    gotoxy(leftPadding, lfinal + 1);
    cout << tabla << endl;
    leftPadding = consoleWith / 2;
    gotoxy(leftPadding - 16, lfinal + 2);
    system("Pause");
}
void imprimirRep(dato registro, int consoleWith)
{
    string line;
    char *aux = strtok(registro.catAJugar, " ");
    cout << lLateral() << setw(9) << registro.alias << setw(17) << registro.duracDeJueg << setw(18) << registro.dia << setw(13) << registro.hora << setw(20) << aux << setw(11) << registro.ren << "x" << registro.col << setw(9) << lLateral();
}
void quitarMayus(char str[], char aux[])
{
    strcpy(aux, str);
    for (int i = 0; i < strlen(aux); i++)
    {
        aux[i] = tolower(aux[i]);
    }
}

#endif