#ifndef REGISTRO_H
#define REGISTRO_H

#include <string>

// La clase Registro sirve para almacenar y manejar datos provenientes de un archivo .txt.
// Cada registro contiene informacion sobre la fecha, hora, direccion IP y razon asociada.

class Registro {
private:
    // Atributos privados que representan las partes de un registro.
    std::string mes;
    int dia;
    int hora;
    int minuto;
    int segundo;
    std::string ip;
    std::string razon;      

    // Convierte un mes en formato texto (ejemplo: "Jan") a un numero entero (ejemplo: 1 para enero).
    int convertirMesANumero(const std::string& mes) const;

public:
    // Constructor que inicializa un registro con los valores proporcionados.
    Registro(const std::string& mes, int dia, int hora, int minuto, int segundo,
             const std::string& ip, const std::string& razon);

    // Devuelve una representacion en texto del registro en un formato legible.
    std::string toString() const;

    // Sobrecarga de operadores relacionales para comparar registros.
    // Estas comparaciones se basan en la fecha y hora del registro.
    bool operator<(const Registro& other) const;  // Verifica si este registro es anterior a otro.
    bool operator>(const Registro& other) const;  // Verifica si este registro es posterior a otro.
    bool operator<=(const Registro& other) const; // Verifica si este registro es anterior o igual a otro.
    bool operator>=(const Registro& other) const; // Verifica si este registro es posterior o igual a otro.
    bool operator==(const Registro& other) const; // Verifica si dos registros son iguales.
};

#endif
