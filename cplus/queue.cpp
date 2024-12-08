#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

Queue::Queue() : head(nullptr), tail(nullptr) {}

Queue::~Queue() {
    clear();  // Очистка очереди при уничтожении объекта
}

bool Queue::is_empty() const {
    return head == nullptr;  // Проверка на пустоту
}

void Queue::push(const string& value) {
    Node* newNode = new Node{value, nullptr};

    if (!tail) { // Если очередь пуста
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode; // Добавляем новый узел в конец
        tail = newNode;       // Обновляем указатель на хвост
    }
}

std::string Queue::pop() {
    if (is_empty()) {
        cout << "Queue is empty!" << endl;
        return "";
    }

    Node* temp = head;
    string value = head->data;
    head = head->next; // Убираем элемент с головы

    if (!head) { // Если очередь стала пустой
        tail = nullptr;
    }

    delete temp; // Освобождаем память
    return value; // Возвращаем значение удалённого элемента
}

void Queue::print() const {
    if (is_empty()) {
        cout << "Queue is empty!" << endl;
        return;
    }

    Node* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void Queue::clear() {
    while (head) {
        pop();
    }
}

void Queue::load_from_file(const string& filename) {
    clear(); // Очищаем очередь перед загрузкой

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    string value;
    while (getline(file, value)) {
        push(value); // Загружаем значения в очередь
    }

    file.close();
}

void Queue::save_to_file(const string& filename) const {
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