//Arturo Dix Cedeño
//A00835802
//ITD
//Evidencia 2
//Fecha de modificación: 02/10/2023

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <string>
#include <ctime>
#include <map>
#include "Log.h"
#include "DoublyLinkedList.h"
#include "formato.h"


using namespace std;

// Mapeo de nombres de meses a números de mes para ordenarlos numéricamente.
map<string, int> monthMap = {
    {"Jan", 1}, {"Feb", 2}, {"Mar", 3}, {"Apr", 4},
    {"May", 5}, {"Jun", 6}, {"Jul", 7}, {"Aug", 8},
    {"Sep", 9}, {"Oct", 10}, {"Nov", 11}, {"Dec", 12}
};

//Mapeo inverso de números de mes a nombres de meses para imprimirlos en el archivo de salida
map<int, string> monthMapReverse = {
    {1, "Jan"}, {2, "Feb"}, {3, "Mar"}, {4, "Apr"},
    {5, "May"}, {6, "Jun"}, {7, "Jul"}, {8, "Aug"},
    {9, "Sep"}, {10, "Oct"}, {11, "Nov"}, {12, "Dec"}
};

//Función para intercambiar dos registros de log
void swap(Log* a, Log* b) {
    Log t = *a;
    *a = *b;
    *b = t;
}

// Función para realizar el ordenamiento Quicksort por fecha y hora
void quicksortByDate(vector<Log>& logs, int low, int high) {
    if (low < high) {
        int pi = low + (high - low) / 2;
        Log pivot = logs[pi];
        int i = low, j = high;
        while (i <= j) {
            while (logs[i] < pivot) {
                i++;
            }
            while (logs[j] > pivot) {
                j--;
            }
            if (i <= j) {
                swap(&logs[i], &logs[j]);
                i++;
                j--;
            }
        }
        if (low < j) {
            quicksortByDate(logs, low, j);
        }
        if (i < high) {
            quicksortByDate(logs, i, high);
        }
    }
}

// Función para realizar el ordenamiento Quicksort por IP, fecha y hora
void quicksortByIP(vector<Log>& logs, int low, int high) {
    if (low < high) {
        int pi = low + (high - low) / 2;
        Log pivot = logs[pi];
        int i = low, j = high;
        while (i <= j) {
            while (formatearIP(logs[i].ip) < formatearIP(pivot.ip)) {
                i++;
            }
            while (formatearIP(logs[j].ip) > formatearIP(pivot.ip)) {
                j--;
            }
            if (i <= j) {
                swap(&logs[i], &logs[j]);
                i++;
                j--;
            }
        }
        if (low < j) {
            quicksortByIP(logs, low, j);
        }
        if (i < high) {
            quicksortByIP(logs, i, high);
        }
    }
}

int main() {
    ifstream fileIn("log602.txt");
    ofstream fileOut("output602.txt");
    vector<Log> logs;
    string line;

    map<pair<int, int>, int> ipCountByYearMonth; // Mapa para almacenar el recuento de IPs por año y mes

    // Leer registros de log desde el archivo de entrada.
    while (getline(fileIn, line)) {
        stringstream ss(line);
        string monthStr, dayStr, yearStr, time, ip, message;
        ss >> monthStr >> dayStr >> yearStr >> time >> ip;
        getline(ss, message);
        // Convertir los datos a los tipos de datos correspondientes.
        int year = stoi(yearStr);
        int month = monthMap[monthStr];
        int day = stoi(dayStr);
        int hour, minute, second;
        // Leer la hora desde el string y darle el formato deseado utilizando los ":"
        sscanf(time.c_str(), "%d:%d:%d", &hour, &minute, &second);

        logs.push_back(Log(year, month, day, hour, minute, second, ip, message));
        // Agregar el registro al mapa de recuento
        pair<int, int> yearMonth = make_pair(year, month);
        ipCountByYearMonth[yearMonth]++;
    }

    //Ciclo para mostrar el menú de opciones
    int opcion = 0;
    while (opcion != 5) {
        cout << "Menú de opciones:" << endl;
        cout << "-----------------" << endl;
        cout << "1. Ordenar los registros por fecha y hora" << endl;
        cout << "2. Ordenar los registros por IP, fecha y hora" << endl;
        cout << "3. Obtener los registros dentro de un rango de IPs (ordenados)" << endl;
        cout << "4. Obtener el recuento de IPs por año y mes" << endl;
        cout << "5. Salir" << endl;
        cout << "-----------------" << endl;
        cout << "Ingrese una opción: ";
        cin >> opcion;

        
        if (opcion == 1){
            // Ordenar los datos por fecha y hora usando Quicksort
            quicksortByDate(logs, 0, logs.size() - 1);
                
            // Escribir el resultado en el archivo de salida output602-1.out
            ofstream fileOut1("output602-1.out");
            for (const auto& log : logs) {
                fileOut1 << monthMapReverse[log.month] << " " << log.day << " " << log.year << " "
                        << log.hour << ":" << log.minute << ":" << log.second << " "
                        << log.ip << " " << log.message << endl;
            }
            fileOut1.close();
            }
        else if (opcion == 2){
            // Ordenar los datos por IP, fecha y hora usando Quicksort
            quicksortByIP(logs, 0, logs.size() - 1);
                
            // Escribir el resultado en el archivo de salida output602-2.out
            ofstream fileOut2("output602-2.out");
            for (const auto& log : logs) {
                fileOut2 << monthMapReverse[log.month] << " " << log.day << " " << log.year << " "<< log.hour << ":" << log.minute << ":" << log.second << " "<< log.ip << " " << log.message << endl;
            }
            fileOut2.close();
        }       
        else if (opcion == 3){
            // Pedir al usuario un rango de IPs
            string startIP, endIP;
            cout << "Ingrese la IP de inicio del rango: ";
            cin >> startIP;
            cout << "Ingrese la IP de fin del rango: ";
            cin >> endIP;

            // Formatear las IPs para comparación y almacenamiento
            string startFormattedIP = formatearIP(startIP);
            string endFormattedIP = formatearIP(endIP);

            // Iterar a través de los registros y comparar las IPs formateadas
            DoublyLinkedList ipRangeList;
            for (const auto& log : logs) {
                string logIP = formatearIP(log.ip);
                if (logIP >= startFormattedIP && logIP <= endFormattedIP) {
                    ipRangeList.insertLog(log);
                }
            }

            // Ordenar los registros dentro del rango en orden ascendente y guardarlos en un archivo de salida
            ipRangeList.sortAscending();
            ofstream fileOutAsc("iprange602-a.out");
            Node* current = ipRangeList.getHead();
            while (current != nullptr) {
                fileOutAsc << monthMapReverse[current->data.month] << " " << current->data.day << " "<< current->data.year << " " << current->data.hour << ":"<< current->data.minute << ":" << current->data.second << " "<< current->data.ip << " " << current->data.message << endl;
                current = current->next;
            }
            fileOutAsc.close();

            // Ordenar los registros dentro del rango en orden descendente y guardarlos en un archivo de salida
            ipRangeList.sortDescending();
            ofstream fileOutDesc("iprange602-d.out");
            current = ipRangeList.getHead();
            while (current != nullptr) {
                fileOutDesc << monthMapReverse[current->data.month] << " " << current->data.day << " "<< current->data.year << " " << current->data.hour << ":"<< current->data.minute << ":" << current->data.second << " "<< current->data.ip << " " << current->data.message << endl;
                current = current->next;
            }
            fileOutDesc.close();
        }
        else if (opcion == 4){

            for (const auto& entry : ipCountByYearMonth) {
            int year = entry.first.first;
            int month = entry.first.second;
            int count = entry.second;
                
            // Obtener el nombre del mes a partir del mapa 'monthMapReverse' que proporcionaste anteriormente
            string monthName = monthMapReverse[month];

            // Imprimir el recuento de IPs por año y mes
            cout << monthName << " " << year << ": " << count << " ips" << endl;
            }
        }
        else if (opcion == 5){
            cout << "Saliendo..." << endl;
        }
    }
}
   

