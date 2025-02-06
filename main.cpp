/*
Equipo 7

Kanaru Ito A01723367
Armando Tamez Larragoity A01723342
Tomas Sommer A01781292

Para compilar: g++ -std=c++17 -o main *.cpp
Para ejecutar: ./main
El archivo BitacoraGrafos.txt debe estar en el mismo directorio.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include "Metodos.h"

using namespace std;

int main() {
    // paso 1: Leer la bitacora
    vector<string> ips;
    auto adj_list = leerBitacora("bitacoraGrafos.txt", ips);

    //calcular el grado de salida
    auto grados = calcularGrados(adj_list);


    ofstream grados_file("grados_ips.txt");
    for (const auto& pair : grados) {
        grados_file << pair.first << " " << pair.second << endl;
    }
    grados_file.close();

    // encontrar las 7 IPs con mayor grado de salida usando Heap
    MaxHeap heap;
    for (const auto& pair : grados) {
        heap.push(pair);
    }

    vector<pair<string, int>> top_7;
    for (int i = 0; i < 7 && !heap.empty(); ++i) {
        top_7.push_back(heap.pop());
    }

    // Guardar las 7 IPs con mayor grado
    ofstream mayores_file("mayores_grados_ips.txt");
    for (const auto& pair : top_7) {
        mayores_file << pair.first << " " << pair.second << endl;
    }
    mayores_file.close();

    // Paso 4: IP del boot master
    string boot_master = top_7[0].first;
    cout << "1. La IP presumiblemente del boot master es: " << boot_master << endl;

    // Paso 5: Camino mas corto desde el boot master
    auto distancias = dijkstra(adj_list, boot_master);

    ofstream distancias_file("distancia_bootmaster.txt");
    for (const auto& pair : distancias) {
        distancias_file << pair.first << " " << pair.second << endl;
    }
    distancias_file.close();

    // Paso 6: IP mas dificil de atacar (mayor distancia)
    auto ip_mas_esfuerzo = max_element(distancias.begin(), distancias.end(),
        [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.second < b.second;
        });

    cout << "2. La IP que requiere mas esfuerzo para ser atacada por el boot master es: " 
         << ip_mas_esfuerzo->first << endl;

    return 0;
}
