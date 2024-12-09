#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

DynamicArray::DynamicArray() : size(0), capacity(1) {
    data = new string[capacity];
}

DynamicArray::~DynamicArray() {
    delete[] data;
}

void DynamicArray::increase_capacity() {
    size_t newCapacity = capacity * 2;
    string* newData = new string[newCapacity];

    for (size_t i = 0; i < size; i++) {
        newData[i] = data[i];
    }

    delete[] data;

    data = newData; // Переназначаем указатель на новый массив
    capacity = newCapacity;
}

void DynamicArray::push_back(const string& value) {
    if (size == capacity) {
        increase_capacity();
    }

    data[size] = value;
    size++;
}

void DynamicArray::insert(const string& value, int index) {
    if (index < 0 || index > static_cast<int>(size)) {
        cout << "Invalid index" << endl;
        return;
    }

    if (size == capacity) {
        increase_capacity();
    }

    for (size_t i = size; i > static_cast<size_t>(index); i--) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

void DynamicArray::pop_back() {
    if (size > 0) {
        size--;
    } else {
        throw out_of_range("Array is empty"); 
    }
}

// Удаление элемента по индексу
void DynamicArray::remove_at(int index) {
    if (index < 0 || index >= static_cast<int>(size)) {
        throw out_of_range("Invalid index");  
    }

    for (size_t i = index; i < size - 1; i++) {
        data[i] = data[i + 1];
    }
    size--;
}

int DynamicArray::search(const string& value) const {
    for (size_t i = 0; i < size; i++) {
        if (data[i] == value) {
            return static_cast<int>(i);
        }
    }
    return -1; // Элемент не найден
}

// Получение элемента по индексу
string DynamicArray::get(int index) const {
    if (index < 0 || index >= static_cast<int>(size)) {
        throw out_of_range("Invalid index"); 
    }
    return data[index];
}

// Установка значения элемента по индексу
void DynamicArray::set(int index, const string& value) {
    if (index < 0 || index >= static_cast<int>(size)) {
        throw out_of_range("Invalid index"); 
    }
    data[index] = value;
}

void DynamicArray::print() const {
    for (size_t i = 0; i < size; i++) {
        cout << data[i] << ' ';
    }
    cout << endl;
}

void DynamicArray::load_from_file(const string& filename) {
    delete[] data; // Удаляем существующий массив
    size = 0;
    capacity = 10; // Начальная емкость
    data = new string[capacity];

    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File is not found" << endl;
        return;
    }

    string stroka;
    while (getline(file, stroka)) {
        push_back(stroka);
    }

    file.close();
}

void DynamicArray::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    for (size_t i = 0; i < size; i++) {
        file << data[i] << endl;
    }

    file.close();
}