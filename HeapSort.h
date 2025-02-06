#ifndef HEAPSORT_H
#define HEAPSORT_H

#include "MyVector.h"

template <class T>
class HeapSort {
public:
    static void swapElements(T&a, T& b);   // Para evitar el uso del swap de stl
    static void sort(MyVector<T>& arr);  // Funcion publica para ordenar el vector
private:
    static void heapify(MyVector<T>& arr, size_t n, size_t i);  // Funcion privada para organizar el heap
};

template <class T>
void HeapSort<T>::swapElements(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
    // Complejidad: O(1)
}

template <class T>
void HeapSort<T>::heapify(MyVector<T>& arr, size_t n, size_t i) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])  // Si el hijo izquierdo es mayor que el nodo actual
        largest = left;
    
    if (right < n && arr[right] > arr[largest])  // Si el hijo derecho es mayor que el nodo actual
        largest = right;
    
    if (largest != i) {  // Si el nodo actual no es el mas grande
        swapElements(arr[i], arr[largest]);  // Intercambia el nodo actual con el mas grande
        heapify(arr, n, largest);  // Recursivamente organiza el sub-arbol
    }
    // Complejidad: O(log n), ya que en el peor caso se realiza una llamada recursiva hasta la altura del arbol
}

template <class T>
void HeapSort<T>::sort(MyVector<T>& arr) {
    size_t n = arr.gettingSize();
    
    for (size_t i = n / 2; i > 0; i--)  // Construye el heap
        heapify(arr, n, i - 1);
    // Complejidad: O(n), porque se realiza el heapify para cada nodo no hoja, lo cual es O(n) en total

    for (int i = static_cast<int>(n) - 1; i > 0; i--) {  // Ordena el heap
        swapElements(arr[0], arr[i]);  // Intercambia el primer elemento (maximo) con el ultimo
        heapify(arr, i, 0);  // Ajusta el heap despues del intercambio
    }
    // Complejidad: O(n log n), ya que en cada iteracion se realiza un heapify que tiene O(log n) de complejidad
}

#endif // HEAPSORT_H
