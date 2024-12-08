#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

DoublyLinkedList::DoublyLinkedList() : head(nullptr), tail(nullptr) {}

DoublyLinkedList::~DoublyLinkedList() {
    free();
}

void DoublyLinkedList::add_to_head(const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    newNode->prev = nullptr;
    
    if (head) {
        head->prev = newNode;
    } else {
        tail = newNode;
    }
    head = newNode;
}

void DoublyLinkedList::add_to_tail(const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;
    
    if (!head) {
        newNode->prev = nullptr;
        head = newNode;
        tail = newNode;
    } else {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
    }
}

void DoublyLinkedList::remove_from_head() {
    if (!head) {
        return;
    }
    Node* temp = head;
    head = head->next;
    
    if (head) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    
    delete temp;
}

void DoublyLinkedList::remove_from_tail() {
    if (!tail) {
        return;
    }

    if (head == tail) {
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
    }

    Node* temp = tail;
    tail = tail->prev;
    tail->next = nullptr;

    delete temp;
}

void DoublyLinkedList::remove_by_value(const string& value) {
    if (!head) {
        return;  // Если список пуст, ничего не делаем
    }

    // Если удаляем первый элемент
    if (head->data == value) {
        remove_from_head();
        return;
    }

    Node* current = head;

    // Ищем элемент с данным значением
    while (current && current->data != value) {
        current = current->next;
    }

    // Если элемент найден
    if (current) {
        if (!current->next) {
            remove_from_tail();  // Если элемент последний
        } else {
            current->next->prev = current->prev;  // Обновляем ссылку на следующий элемент
        }
        
        if (current->prev) {
            current->prev->next = current->next;  // Обновляем ссылку на предыдущий элемент
        }
        
        delete current;  // Удаляем текущий элемент
    }
}

DoublyLinkedList::Node* DoublyLinkedList::search(const string& value, int& index) const {
    Node* current = head;
    index = 0;
    while (current) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
        index++;
    }
    return nullptr;
}

void DoublyLinkedList::print() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void DoublyLinkedList::free() {
    while (head) {
        remove_from_head();
    }
}

void DoublyLinkedList::load_from_file(const string& filename) {
    free();
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        add_to_tail(line);
    }

    file.close();
}

void DoublyLinkedList::upload_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    Node* current = head;
    while (current) {
        file << current->data << endl;
        current = current->next;
    }

    file.close();
}