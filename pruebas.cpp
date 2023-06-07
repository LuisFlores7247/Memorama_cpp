#include <iostream>
#include <iomanip>
#include <string>


using namespace std;
string lRecta(int n);
string lLateral();
string esquinas(int n);
string lLatDivisoria(int n);

int main(int argc, char const *argv[])
{
    string line=lLateral()+"   Alias   "+lLateral()+"  Tiempo(segs) "+lLateral()+"     Dia     "+lLateral()+"     hora     "+lLateral()+"     Categoria     "+lLateral()+"  Dimensiones "+lLateral();   
    string lr=esquinas(0)+lRecta(line.length())+esquinas(1);
    cout<<setw(10)<<lr<<endl;
    cout<<setw(10)<<line<<endl;
    lr=lLatDivisoria(0)+lRecta(line.length())+lLatDivisoria(1);
    cout<<setw(10)<<lr<<endl;
    return 0;
}


//Creadores de tablas

string esquinas(int n)  // n=0 Esquina superior izquierda, n=1 Esquina superior derecha, n=2 Esquina inferior izquierda, n=3 Esquina inferior derecha
{
    if (n==0)
    {
        return string(1,char(201));
    }
    if (n==1)
    {
        return string(1,char(187));
    }   
    if (n==2)
    {
        return string(1,char(200));
    }
    if (n==3)
    {
        return string(1,char(188));
    }
    
    
}
string lRecta(int n){       // n=Longitud de la linea recta

    return string(n-2,char(205));
}
string lLateral(){
    return string(1,char(186));
}  
string lLatDivisoria(int n){   //n=0 linea divisoria izquierda, n=1 linea divisoria derecha
    if (n==0) 
    {
        return string(1,char(204));
    }
    if (n==1)
    {
        return string(1,char(185));
    }    
}