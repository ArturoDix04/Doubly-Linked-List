#pragma once
#include "Log.h"
#include <iostream>
#include <string>
#include "formato.h"

using namespace std;

// Definición de la estructura de un nodo de la lista doblemente enlazada.
struct Node {
    Log data;
    Node* prev;
    Node* next;
    Node(const Log& log) : data(log), prev(nullptr), next(nullptr) {}
};

// Definición de la clase DoublyLinkedList.
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    void insert(const Log& log);
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    void sortAscending();
    void sortDescending();
    void insertLog(const Log& log);
};

// Implementación del constructor de la clase DoublyLinkedList.
DoublyLinkedList::DoublyLinkedList() {
    head = nullptr;
    tail = nullptr;
}

// Implementación del método insert 
void DoublyLinkedList::insert(const Log& log) {
    Node* newNode = new Node(log);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Implementación del método sortAscending para el archivo de salida iprange602-a.out.
void DoublyLinkedList::sortAscending() {
    if (head == nullptr || head->next == nullptr) {
        // La lista está vacía o tiene un solo elemento, no es necesario ordenarla.
        return;
    }

    bool swapped;
    Node* current;
    Node* last = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != last) {
            if (formatearIP(current->data.ip) > formatearIP(current->next->data.ip)) {
                // Intercambiar los datos de los nodos.
                Log temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Implementación del método sortDescending para el archivo de salida iprange602-d.out.
void DoublyLinkedList::sortDescending() {
    if (head == nullptr || head->next == nullptr) {
        // La lista está vacía o tiene un solo elemento, no es necesario ordenarla.
        return;
    }

    bool swapped;
    Node* current;
    Node* last = nullptr;

    do {
        swapped = false;
        current = head;

        while (current->next != last) {
            if (formatearIP(current->data.ip) < formatearIP(current->next->data.ip)) {
                // Intercambiar los datos de los nodos.
                Log temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

// Implementación del método insertLog para el archivo de salida iprange602-a.out y iprange602-d.out.

void DoublyLinkedList::insertLog(const Log& log) {
    Node* newNode = new Node(log);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}