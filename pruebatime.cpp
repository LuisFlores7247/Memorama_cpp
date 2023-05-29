#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
clock_t medirT() {
    // Obtiene el tiempo actual antes de comenzar el proceso
    clock_t start = clock();

    system("pause");
    // Obtiene el tiempo actual después de que el proceso haya terminado
    clock_t end = clock();

    // Calcula la duración en segundos
    double duration = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    // Imprime el tiempo transcurrido
    cout << "Tiempo transcurrido: " << duration << " segundos" << endl;

    return start;
}
