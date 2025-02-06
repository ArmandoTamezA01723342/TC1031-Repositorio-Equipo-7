#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>

using namespace std;

// Estructura para almacenar la información de un incidente
// Esta estructura almacena la información de un incidente, incluyendo la IP de destino y el peso de la conexión.
struct Incident {
    string ip_destino;
    int peso;
};

// Clase MaxHeap para encontrar las 7 IPs con mayor grado de salida
class MaxHeap {
private:
    vector<pair<string, int>> heap;

    // Complejidad: O(log n)
    // Reorganiza el heap para mantener la propiedad de heap después de una extracción.
void heapify_down(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap.size() && heap[left].second > heap[largest].second)
            largest = left;
        if (right < heap.size() && heap[right].second > heap[largest].second)
            largest = right;
        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify_down(largest);
        }
    }

    // Complejidad: O(log n)
    // Ajusta el heap después de insertar un nuevo elemento para mantener la propiedad de heap.
void heapify_up(int i) {
        while (i > 0 && heap[(i - 1) / 2].second < heap[i].second) {
            swap(heap[i], heap[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

public:
    // Complejidad: O(log n)
    void push(pair<string, int> val) {
        heap.push_back(val);
        heapify_up(heap.size() - 1);
    }

    // Complejidad: O(log n)
    pair<string, int> pop() {
        if (heap.empty()) return {"", -1};

        pair<string, int> max_val = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify_down(0);

        return max_val;
    }

    // Complejidad: O(1)
    bool empty() {
        return heap.empty();
    }
};

// Complejidad: O(n + m)
// Lee el archivo de bitácora y construye la lista de adyacencia.
unordered_map<string, vector<Incident>> leerBitacora(const string& archivo, vector<string>& ips) {
    ifstream file(archivo);
    if (!file) {
        cerr << "Error al abrir el archivo: " << archivo << endl;
        exit(1);
    }

    unordered_map<string, vector<Incident>> adj_list;
    string line;

    // Leer la primera línea para obtener n y m
    getline(file, line);
    istringstream iss(line);
    int n, m;
    iss >> n >> m;

    // Leer las direcciones IP
    for (int i = 0; i < n; ++i) {
        getline(file, line);
        ips.push_back(line);
    }

    // Leer las incidencias
    while (getline(file, line)) {
        istringstream iss(line);
        string mes, dia, hora, ip_origen, ip_destino;
        int peso;
        
        if (!(iss >> mes >> dia >> hora >> ip_origen >> ip_destino >> peso))
            continue;

        // Eliminar puertos
        ip_origen = ip_origen.substr(0, ip_origen.find(':'));
        ip_destino = ip_destino.substr(0, ip_destino.find(':'));

        adj_list[ip_origen].push_back({ip_destino, peso});
    }

    file.close();
    return adj_list;
}

// Complejidad: O(n)
map<string, int> calcularGrados(const unordered_map<string, vector<Incident>>& adj_list) {
    map<string, int> grados;
    for (const auto& pair : adj_list) {
        grados[pair.first] = pair.second.size();
    }
    return grados;
}

// Complejidad: O((n + m) log n)
// Implementa el algoritmo de Dijkstra para encontrar las distancias más cortas desde el nodo inicial.
map<string, int> dijkstra(const unordered_map<string, vector<Incident>>& adj_list, const string& start) {
    map<string, int> distancias;
    for (const auto& pair : adj_list) {
        distancias[pair.first] = INT_MAX;
    }
    distancias[start] = 0;

    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        string ip_actual = pq.top().second;
        int distancia_actual = pq.top().first;
        pq.pop();

        if (distancia_actual > distancias[ip_actual]) continue;

        for (const auto& incidente : adj_list.at(ip_actual)) {
            string vecino = incidente.ip_destino;
            int peso = incidente.peso;
            int nueva_distancia = distancia_actual + peso;

            if (nueva_distancia < distancias[vecino]) {
                distancias[vecino] = nueva_distancia;
                pq.push({nueva_distancia, vecino});
            }
        }
    }
    return distancias;
}
