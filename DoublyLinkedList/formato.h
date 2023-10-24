#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

// Función para formatear una IP con ceros a la izquierda y que se ordenen de manera correcta.

string formatearIP(const string& ip) {
    vector<int> segmentos;
    stringstream ss(ip);
    string segmento;
    while (getline(ss, segmento, '.')) {
        int num = stoi(segmento);
        segmentos.push_back(num);
    }

    // Asegurar que haya 4 segmentos en la IP, si no, rellenar con 0
    while (segmentos.size() < 4) {
        segmentos.push_back(0);
    }

    // Formatear cada segmento con ceros a la izquierda y unirlos con puntos
    stringstream formattedIP;
    formattedIP << setw(3) << setfill('0') << segmentos[0] << ".";
    formattedIP << setw(3) << setfill('0') << segmentos[1] << ".";
    formattedIP << setw(3) << setfill('0') << segmentos[2] << ".";
    formattedIP << setw(3) << setfill('0') << segmentos[3];

    return formattedIP.str();
}