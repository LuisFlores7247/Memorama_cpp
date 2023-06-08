#include <iostream>
#include <windows.h>

#define color SetConsoleTextAttribute

using namespace std;

int main(){
    HANDLE hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
    for (int i = 0; i < 243; i++)
    {
        color(hconsole, i);
        cout<<"Color: "<<i<<endl;
    }
    return 0;
}