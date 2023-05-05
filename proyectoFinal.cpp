#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>

using namespace std;

void portada(int consoleWidth);
int menu(int consoleWidth);
void presentacion(int consoleWidth);
void gotoxy(int x, int y);

int main(int argc, char const *argv[])
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int consoleWidth = consoleInfo.dwSize.X;

    portada(consoleWidth);
    presentacion(consoleWidth);
    cout << "Hola Mundo";
    return 0;
}

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

int menu(int consoleWidth)
{
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