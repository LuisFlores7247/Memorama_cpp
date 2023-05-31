#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <tchar.h>
#include<mmsystem.h>

using namespace std;

int main(){

    sndPlaySound(_T("Wii.wav"), SND_ASYNC | SND_FILENAME | SND_LOOP);


    system("pause");
    return 0;
}