#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "MyVector.h"
#include <stdexcept> // Para manejo de excepciones

template <class T>
class PriorityQueue {
private:
    struct Node {
        T key;  // Elemento de la cola de prioridad
        int frequency;  // Frecuencia del elemento
        bool operator<(const Node& other) const {
            return frequency < other.frequency;  // Comparacion basada en la frecuencia
        }
    };
    
    MyVector<Node> heap;  // Vector que almacena el heap

    void heapifyUp(size_t index);  // Funcion privada para reorganizar hacia arriba
    void heapifyDown(size_t index);  // Funcion privada para reorganizar hacia abajo

public:
    void push(const T& key, int frequency);  // Inserta un elemento con su frecuencia
    T pop();  // Extrae el elemento con mayor prioridad
    T getTop() const; // obtener el máximo sin eliminarlo
    bool isEmpty() const;  // Verifica si el heap esta vacio
    void clear();  // Vacia completamente el heap
};

// Reordena el heap hacia arriba
template <class T>
void PriorityQueue<T>::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parent = (index - 1) / 2;
        if (!(heap[parent] < heap[index])) {  // Si el padre tiene mayor o igual frecuencia, se detiene
            break;
        }
        std::swap(heap[parent], heap[index]);  // Intercambia el nodo con el padre
        index = parent;
    }
    // Complejidad: O(log n), ya que en el peor caso, la funcion realiza log(n) intercambios
}

// Reordena el heap hacia abajo
template <class T>
void PriorityQueue<T>::heapifyDown(size_t index) {
    size_t size = heap.gettingSize();
    while (true) {
        size_t left = 2 * index + 1;
        size_t right = 2 * index + 2;
        size_t largest = index;

        if (left < size && !(heap[left] < heap[largest]))  // Si el hijo izquierdo tiene mayor o igual frecuencia
            largest = left;
        if (right < size && !(heap[right] < heap[largest]))  // Si el hijo derecho tiene mayor o igual frecuencia
            largest = right;

        if (largest != index) {  // Si el nodo actual no tiene la mayor prioridad
            std::swap(heap[index], heap[largest]);  // Intercambia el nodo con el hijo de mayor prioridad
            index = largest;
        } else {
            break;  // Si no se necesita mas reordenacion, sale del ciclo
        }
    }
    // Complejidad: O(log n), ya que se puede recorrer la altura del arbol completo
}

// Inserta una nueva IP con su frecuencia
template <class T>
void PriorityQueue<T>::push(const T& key, int frequency) {
    Node newNode = {key, frequency};  // Crea un nodo con la clave y la frecuencia
    heap.pushing(newNode);  // Inserta el nodo en el heap
    heapifyUp(heap.gettingSize() - 1);  // Reordena hacia arriba el nuevo nodo
    // Complejidad: O(log n), debido a la operacion de heapifyUp
}

// Extrae la IP con mayor frecuencia
template <class T>
T PriorityQueue<T>::pop() {
    if (heap.gettingSize() == 0)
        throw std::runtime_error("Priority queue is empty");  // Lanza excepcion si el heap esta vacio

    T topValue = heap[0].key;  // Toma la clave del primer nodo
    heap[0] = heap[heap.gettingSize() - 1];  // Mueve el ultimo nodo a la raiz
    heap.removeLast();  // Elimina el ultimo nodo
    heapifyDown(0);  // Reorganiza el heap hacia abajo desde la raiz
    return topValue;  // Devuelve el valor de mayor prioridad
    // Complejidad: O(log n), debido a la operacion de heapifyDown
}

template <class T>
T PriorityQueue<T>::getTop() const {
    if (heap.getSize() == 0)
        throw std::runtime_error("Priority queue is empty");
    return heap[0].key;
    // Complejidad: O(1)
}

// Verifica si el heap esta vacio
template <class T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.gettingSize() == 0;  // Devuelve verdadero si el heap esta vacio
    // Complejidad: O(1), ya que solo se realiza una comparacion
}

// Vacia completamente la cola de prioridad
template <class T>
void PriorityQueue<T>::clear() {
    while (!isEmpty()) {
        pop();  // Extrae los elementos hasta que el heap este vacio
    }
    // Complejidad: O(n log n), ya que pop tiene O(log n) de complejidad y se llama n veces
}

#endif // PRIORITY_QUEUE_H
