/*
Este archivo define funciones alternativas para evitar 
el uso de funciones stl como push_back() y getSize() de <vector>.
 */


#ifndef MY_VECTOR
#define MY_VECTOR

#include <iostream>

using namespace std;

// Implementacion de una estructura de datos similar a vector
template <class T>
class MyVector {
private:
    T* data;
    size_t capacity;
    size_t size;
    void resize();  // Funcion privada para redimensionar el vector cuando sea necesario
public:
    MyVector();  // Constructor
    ~MyVector();  // Destructor
    void pushing(const T& value);  // Agrega un elemento al final
    size_t gettingSize() const;  // Obtiene el tamaño actual
    T& operator[](size_t index);  // Operador de acceso a elementos
    const T& operator[](size_t index) const;  // Version para objetos const
    void removeLast();  // Elimina el ultimo elemento
    void clear();  // Vacia el vector
};

// Constructor
template <class T>
MyVector<T>::MyVector() : capacity(10), size(0) {
    data = new T[capacity];
    // Complejidad: O(1), ya que solo se inicializan los valores
}

// Destructor
template <class T>
MyVector<T>::~MyVector() {
    delete[] data;
    data = nullptr;
    // Complejidad: O(1), solo se realiza una operacion de liberacion de memoria
}

// Redimensiona el array cuando es necesario
template <class T>
void MyVector<T>::resize() {
    size_t newCapacity = capacity * 2;
    T* newData = new T[newCapacity];  
    if (!newData) {
        throw bad_alloc();
    }
    for (size_t i = 0; i < size; i++) {  
        newData[i] = data[i];  // Copia los elementos del viejo array al nuevo
    }
    delete[] data;  // Libera la memoria antigua
    data = newData;
    capacity = newCapacity;
    // Complejidad: O(n), donde n es el tamaño del vector, ya que se copian todos los elementos
}

// Agrega un elemento al final
template <class T>
void MyVector<T>::pushing(const T& value) {
    if (size == capacity) {
        resize();  // Si el tamaño alcanza la capacidad, redimensiona
    }
    data[size++] = value;  // Inserta el nuevo valor y aumenta el tamaño
    // Complejidad: Promedio O(1), pero puede ser O(n) en el peor caso cuando se redimensiona
}

// Obtiene el tamaño actual
template <class T>
size_t MyVector<T>::gettingSize() const {
    return size;  // Devuelve el tamaño actual del vector
    // Complejidad: O(1), ya que solo se devuelve un valor
}

// Operador de acceso a elementos
template <class T>
T& MyVector<T>::operator[](size_t index) {
    if (index >= size) {
        throw out_of_range("Index out of range");  // Lanza excepcion si el indice es invalido
    }
    return data[index];  // Devuelve el elemento en la posicion indicada
    // Complejidad: O(1), ya que es una operacion de acceso directo
}

template <class T>
const T& MyVector<T>::operator[](size_t index) const {  // Version para objetos const
    if (index >= size) {
        throw out_of_range("Index out of range");  // Lanza excepcion si el indice es invalido
    }
    return data[index];  // Devuelve el elemento en la posicion indicada
    // Complejidad: O(1), ya que es una operacion de acceso directo
}

// Elimina el ultimo elemento
template <class T>
void MyVector<T>::removeLast() {
    if (size > 0) {
        size--;  // Disminuye el tamaño del vector
    }
    // Complejidad: O(1), ya que solo se reduce el tamaño
}

// Vacia el vector
template <class T>
void MyVector<T>::clear() {
    size = 0;  // Establece el tamaño a cero, efectivamente vaciando el vector
    // Complejidad: O(1), ya que solo se actualiza el tamaño
}

#endif // MY_VECTOR
