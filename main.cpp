/*
Equipo 7

Kanaru Ito A01723367
Armando Tamez Larragoity A01723342
Tomas Sommer A01781292

Para compilar: g++ -std=c++17 -o main *.cpp
Para ejecutar: ./main
El archivo BitacoraHeap.txt debe estar en el mismo directorio.
*/

#include <iostream>
#include "BitacoraProcessor.h"

int main() {
    try {
        BitacoraProcessor bp("bitacoraHeap.txt");
        bp.loadData();

        // Extraer y guardar IPs ordenadas
        MyVector<string> sortedIPs = bp.extractSortedIPs();
        bp.saveToFile("log_sorted.txt", sortedIPs);
        cout << "IPs ordenadas guardadas en bitacora_ips_ordenadas.txt" << endl;

        // Guardar las 10 IPs mas frecuentes
        bp.saveTopIPs("ips_con_mayor_acceso.txt", 10);
        cout << "Las 10 IPs con mas accesos guardadas en ips_con_mayor_acceso.txt" << endl;

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
