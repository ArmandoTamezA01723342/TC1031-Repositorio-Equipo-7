#include "Registro.h"
#include <sstream>


// Convierte un mes en formato texto ("Jan", "Feb", etc.) a su numero correspondiente.
// Complejidad: O(1)
int Registro::convertirMesANumero(const std::string& mes) const {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;
    return -1;
}

// Constructor de la clase Registro
// Complejidad: O(1)
Registro::Registro(const std::string& mes, int dia, int hora, int minuto, int segundo,
                   const std::string& ip, const std::string& razon)
    : mes(mes), dia(dia), hora(hora), minuto(minuto), segundo(segundo),
      ip(ip), razon(razon) {}

// Convierte un Registro en una cadena con el formato de la bitacora.
// Complejidad: O(1)
std::string Registro::toString() const {
    std::ostringstream oss;
    oss << mes << " " << dia << " "
        << (hora < 10 ? "0" : "") << hora << ":"
        << (minuto < 10 ? "0" : "") << minuto << ":"
        << (segundo < 10 ? "0" : "") << segundo << " "
        << ip << " " << razon;
    return oss.str();
}

// Sobrecarga del operador '<'
// Complejidad: O(1)
bool Registro::operator<(const Registro& other) const {
    if (convertirMesANumero(mes) != convertirMesANumero(other.mes))
        return convertirMesANumero(mes) < convertirMesANumero(other.mes);
    if (dia != other.dia)
        return dia < other.dia;
    if (hora != other.hora)
        return hora < other.hora;
    if (minuto != other.minuto)
        return minuto < other.minuto;
    return segundo < other.segundo;
}

// Sobrecarga del operador '>'
// Complejidad: O(1)
bool Registro::operator>(const Registro& other) const {
    return other < *this;
}

// Sobrecarga del operador '<='
// Complejidad: O(1)
bool Registro::operator<=(const Registro& other) const {
    return !(other < *this);
}

// Sobrecarga del operador '>='
// Complejidad: O(1)
bool Registro::operator>=(const Registro& other) const {
    return !(*this < other);
}

// Sobrecarga del operador '=='
// Complejidad: O(1)
bool Registro::operator==(const Registro& other) const {
    return mes == other.mes && dia == other.dia && hora == other.hora &&
           minuto == other.minuto && segundo == other.segundo;
}
