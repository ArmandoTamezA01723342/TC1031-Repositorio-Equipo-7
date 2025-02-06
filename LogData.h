    #ifndef LOGDATA_H
    #define LOGDATA_H

    #include <string>
    #include <sstream>
    #include <iostream>
    #include <map>

    using namespace std;

    class LogData {
    public:
        int month;  // Guarda el mes como un número entero
        int day;
        int hour;
        int minute;
        int second;
        string ip_address;
        string reason; // Se eliminó el puerto, y ahora se guarda la razón

        // Diccionario para mapear los nombres de los meses a números
        static map<string, int> month_map;

        // Constructor
        LogData(int m, int d, int h, int min, int sec, string ip, string r)
            : month(m), day(d), hour(h), minute(min), second(sec), ip_address(ip), reason(r) {}

        // Método estático para convertir un nombre de mes en su valor entero
        // Complejidad: O(1)
        static int monthNameToInt(const string& month_name) {
            return month_map[month_name];
        }

        // Convierte el mes a una cadena de 3 letras
        // Complejidad: O(1)
        string monthToString() const {
            for (const auto& entry : month_map) {
                if (entry.second == month) {
                    return entry.first;
                }
            }
            return ""; // Devuelve una cadena vacía si no se encuentra el mes
        }

        // Operador de comparación (necesario para el ordenamiento por mes)
        // Complejidad: O(1)
        bool operator<(const LogData& other) const {
            if (month != other.month) return month < other.month;
            if (day != other.day) return day < other.day;
            if (hour != other.hour) return hour < other.hour;
            if (minute != other.minute) return minute < other.minute;
            return second < other.second;
        }

        // Operador de comparación (>=) para verificar si el primer log es mayor o igual que el otro
        // Complejidad: O(1)
        bool operator>=(const LogData& other) const {
            return !(*this < other);  // Es el opuesto de <, así que lo implementamos como !(*this < other)
        }

        // Operador de comparación (<=) para verificar si el primer log es menor o igual que el otro
        // Complejidad: O(1)
        bool operator<=(const LogData& other) const {
            return (*this < other) || (*this == other);  // Es una combinación de < o ==
        }

        // Operador de comparación (==) para verificar si los logs son iguales
        // Complejidad: O(1)
        bool operator==(const LogData& other) const {
            return (this->month == other.month) && 
                (this->day == other.day) && 
                (this->hour == other.hour) && 
                (this->minute == other.minute) && 
                (this->second == other.second) &&
                (this->ip_address == other.ip_address) &&
                (this->reason == other.reason);
        }
    };

    // Mapeo de los nombres de los meses a sus respectivos números
    map<string, int> LogData::month_map = {
        {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
        {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
        {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
    };

    #endif // LOGDATA_H
