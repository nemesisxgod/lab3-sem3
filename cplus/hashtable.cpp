#include <iostream>
#include <fstream>
#include "header.h"

using namespace std;

HashTable::HashTable() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table[i] = nullptr;
    }
}

HashTable::~HashTable() {
    clear();
}

int HashTable::hash_function(const string& key) const {
    size_t hash = 2566341;
    for (auto c : key) {
        hash += 31 * c;
    }
    return hash % TABLE_SIZE;
}

void HashTable::insert(const string& key, const string& value) {
    int index = hash_function(key);
    Node* newNode = new Node{key, value, nullptr};

    if (table[index] == nullptr) {
        table[index] = newNode;
        return;
    } 

    Node* temp = table[index];
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            temp->value = value;
            delete newNode; // Новый узел не нужен
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    // Вставляем новый узел в конец цепочки
    prev->next = newNode;
}

string HashTable::search(const string& key) const {
    int index = hash_function(key);
    Node* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            return temp->value;
        }
        temp = temp->next;
    }

    throw out_of_range("Key not found!");
}

void HashTable::remove(const string& key) {
    int index = hash_function(key);
    Node* temp = table[index];
    Node* prev = nullptr;

    while (temp != nullptr) {
        if (temp->key == key) {
            if (prev == nullptr) {
                table[index] = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next;
    }

    throw out_of_range("Key not found!");
}

void HashTable::print() const {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        if (table[i] != nullptr) {
            cout << "Table[" << i << "]: ";
            Node* temp = table[i];
            while (temp != nullptr) {
                cout << "{" << temp->key << ": " << temp->value << "} -> ";
                temp = temp->next;
            }
            cout << "nullptr\n";
        }
    }
}

void HashTable::clear() {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        table[i] = nullptr;
    }
}

void HashTable::load_from_file(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "File is not found" << endl;
        return;
    }

    clear();

    string key, value;
    while (file >> key >> value) {
        insert(key, value);
    }

    file.close();
}

void HashTable::save_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File not found" << endl;
        return;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Node* current = table[i];
        while (current) {
            file << current->key << " " << current->value << endl;
            current = current->next;
        }
    }

    file.close();
}