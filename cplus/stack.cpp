#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

Stack::Stack() : head(nullptr) {}

Stack::~Stack() {
    clear();
}

void Stack::push(const string& data) {
    Node* newNode = new Node(data);
    newNode->next = head;
    head = newNode;
}

std::string Stack::pop() {
    if (head == nullptr) {
        cout << "Stack is empty" << endl;
        return "";
    }

    Node* temp = head;
    std::string poppedValue = head->data;
    head = head->next;
    delete temp;

    return poppedValue;
}

void Stack::print() const {
    if (head == nullptr) {
        cout << "Stack is empty" << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

void Stack::clear() {
    while (head) {
        pop();
    }
}

void Stack::load_from_file(const string& filename) {
    clear();  // Очищаем текущий стек

    ifstream file(filename); 
    if (!file.is_open()) { 
        cout << "File not found" << endl;
        return;
    }

    string stroka;
    Stack tempStack;  // временный стек для хранения данных

    // Загружаем данные в временный стек (элементы будут в порядке их прочтения)
    while (getline(file, stroka)) {
        tempStack.push(stroka);  // Добавляем элементы в обратном порядке
    }
    file.close();

    // Переносим элементы из временного стека в основной стек
    while (!tempStack.is_empty()) {
        push(tempStack.pop());  // Перемещаем элементы в основной стек
    }
}

void Stack::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
            cout << "File not found" << endl;
            return;
        }

    Node* current = head;;
    while (current!=nullptr) {
        file << current->data << endl;
        current = current->next;
    }

    file.close();
}