#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    free();
}

void LinkedList::add_to_head(const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = head;
    head = newNode;
}

void LinkedList::add_to_tail(const string& value) {
    Node* newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;  // Инициализируем поле next
    
    if (!head) {  // Если список пуст
        head = newNode;
        return;
    }
    Node* current = head;
    while (current->next) {  // Идем до последнего узла
        current = current->next;
    }
    current->next = newNode;
}

void LinkedList::remove_from_head() {
    if (!head) {
        return;
    }
    Node* temp = head;
    head = head->next;
    delete temp;
}

void LinkedList::remove_from_tail() {
    if (!head) {
        return;
    }

    if (!head->next) {
        delete head;
        head = nullptr;
        return;
    }

    Node* current = head;
    while (current->next && current->next->next) {  // Находим предпоследний элемент
        current = current->next;
    }
    delete current->next;  // Удаляем последний узел
    current->next = nullptr;
}

void LinkedList::remove_by_value(const string& value) {
    if (!head) {
        return;  // Если список пуст
    }

    if (head->data == value) {  // Если нужно удалить первый элемент
        remove_from_head();
        return;
    }

    Node* current = head;
    while (current->next && current->next->data != value) {
        current = current->next;
    }

    if (current->next) {  // Если элемент найден
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
    }
}

LinkedList::Node* LinkedList::search(const string& value, int& index) const {
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

void LinkedList::print() const {
    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void LinkedList::free() {
    while (head) {
        remove_from_head();
    }
}

void LinkedList::load_from_file(const string& filename) {
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

void LinkedList::upload_to_file(const string& filename) const {
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