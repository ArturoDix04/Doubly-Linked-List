#pragma once
#include <string>
#include "formato.h"


using namespace std;

// Definición de una estructura para representar registros de log.
struct Log {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    string ip;
    string message;

    // Constructor predeterminado de la estructura Log.
    Log();
    // Constructor de la estructura Log con parámetros.
    Log(int year, int month, int day, int hour, int minute, int second, const string& ip, const string& message);
    // Sobrecarga del operador < para comparar registros de log.
    bool operator<(const Log& other) const;
    bool operator==(const Log& other) const;
    bool operator>(const Log& other) const;
};

// Implementación del constructor de Log.
Log::Log(int year, int month, int day, int hour, int minute, int second, const string& ip, const string& message) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->hour = hour;
    this->minute = minute;
    this->second = second;
    this->ip = ip;
    this->message = message;
}

// Implementación de la sobrecarga del operador <.
bool Log::operator<(const Log& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    if (day != other.day) return day < other.day;
    if (hour != other.hour) return hour < other.hour;
    if (minute != other.minute) return minute < other.minute;
    return second < other.second;
}

// Implementación de la sobrecarga del operador ==.
bool Log::operator==(const Log& other) const{
    if (year != other.year) return false;
    if (month != other.month) return false;
    if (day != other.day) return false;
    if (hour != other.hour) return false;
    if (minute != other.minute) return false;
    return true;
} 

// Implementación de la sobrecarga del operador >.
bool Log::operator>(const Log& other) const {
    if (year != other.year) return year > other.year;
    if (month != other.month) return month > other.month;
    if (day != other.day) return day > other.day;
    if (hour != other.hour) return hour > other.hour;
    if (minute != other.minute) return minute > other.minute;
    return second > other.second;
}