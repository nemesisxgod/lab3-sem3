#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include "cplus/header.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "nlohmann/json.hpp"

using namespace std;


// Сериализация в бинарный формат для DynamicArray
void save_to_binary_array(const DynamicArray& arr, const string& filename) {
    ofstream ofs(filename, ios::binary);
    size_t size = arr.size;
    ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        string value = arr.get(i);
        size_t len = value.size();
        ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
        ofs.write(value.c_str(), len);
    }
    ofs.close();
}

void load_from_binary_array(DynamicArray& arr, const string& filename) {
    ifstream ifs(filename, ios::binary);
    size_t size;
    ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
    for (size_t i = 0; i < size; ++i) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        string value(len, ' ');
        ifs.read(&value[0], len);
        arr.push_back(value);
    }
    ifs.close();
}

// Сериализация в бинарный формат для HashTable
void save_to_binary_hash(const HashTable& table, const string& filename) {
    ofstream ofs(filename, ios::binary);
    for (int i = 0; i < HashTable::TABLE_SIZE; ++i) {
        HashTable::Node* node = table.table[i];
        while (node) {
            size_t key_len = node->key.size();
            size_t value_len = node->value.size();
            ofs.write(reinterpret_cast<char*>(&key_len), sizeof(key_len));
            ofs.write(node->key.c_str(), key_len);
            ofs.write(reinterpret_cast<char*>(&value_len), sizeof(value_len));
            ofs.write(node->value.c_str(), value_len);
            node = node->next;
        }
    }
    ofs.close();
}

void load_from_binary_hash(HashTable& table, const string& filename) {
    ifstream ifs(filename, ios::binary);
    while (ifs.peek() != EOF) {
        size_t key_len;
        size_t value_len;
        ifs.read(reinterpret_cast<char*>(&key_len), sizeof(key_len));
        string key(key_len, ' ');
        ifs.read(&key[0], key_len);

        ifs.read(reinterpret_cast<char*>(&value_len), sizeof(value_len));
        string value(value_len, ' ');
        ifs.read(&value[0], value_len);

        table.insert(key, value);
    }
    ifs.close();
}

// Сериализация в бинарный формат для LinkedList
void save_to_binary_list(const LinkedList& list, const string& filename) {
    ofstream ofs(filename, ios::binary);
    LinkedList::Node* node = list.head;
    while (node) {
        size_t len = node->data.size();
        ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
        ofs.write(node->data.c_str(), len);
        node = node->next;
    }
    ofs.close();
}

void load_from_binary_list(LinkedList& list, const string& filename) {
    ifstream ifs(filename, ios::binary);
    while (ifs.peek() != EOF) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        string data(len, ' ');
        ifs.read(&data[0], len);
        list.add_to_tail(data);
    }
    ifs.close();
}

void save_to_binary_dlist(const DoublyLinkedList& list, const string& filename) {
    ofstream ofs(filename, ios::binary);
    DoublyLinkedList::Node* node = list.head;
    while (node) {
        size_t len = node->data.size();
        ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
        ofs.write(node->data.c_str(), len);
        node = node->next;
    }
    ofs.close();
}

void load_from_binary_dlist(DoublyLinkedList& list, const string& filename) {
    ifstream ifs(filename, ios::binary);
    list.free(); // Очищаем список перед загрузкой
    while (ifs.peek() != EOF) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        string data(len, ' ');
        ifs.read(&data[0], len);
        list.add_to_tail(data);
    }
    ifs.close();
}

void save_to_binary_queue(const Queue& queue, const string& filename) {
    ofstream ofs(filename, ios::binary);
    Queue::Node* node = queue.head;
    while (node) {
        size_t len = node->data.size();
        ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
        ofs.write(node->data.c_str(), len);
        node = node->next;
    }
    ofs.close();
}

void load_from_binary_queue(Queue& queue, const string& filename) {
    ifstream ifs(filename, ios::binary);
    queue.clear(); // Очищаем очередь перед загрузкой
    while (ifs.peek() != EOF) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        string data(len, ' ');
        ifs.read(&data[0], len);
        queue.push(data);
    }
    ifs.close();
}

void save_to_binary_stack(const Stack& stack, const string& filename) {
    ofstream ofs(filename, ios::binary);
    Stack::Node* node = stack.head;
    while (node) {
        size_t len = node->data.size();
        ofs.write(reinterpret_cast<char*>(&len), sizeof(len));
        ofs.write(node->data.c_str(), len);
        node = node->next;
    }
    ofs.close();
}

void load_from_binary_stack(Stack& stack, const string& filename) {
    ifstream ifs(filename, ios::binary);
    stack.clear(); // Очищаем стек перед загрузкой
    while (ifs.peek() != EOF) {
        size_t len;
        ifs.read(reinterpret_cast<char*>(&len), sizeof(len));
        string data(len, ' ');
        ifs.read(&data[0], len);
        stack.push(data);
    }
    ifs.close();
}

void save_to_binary_treenode(treeNode* node, ofstream& ofs) {
    if (node == nullptr) {
        int marker = -1; // Маркер пустого узла
        ofs.write(reinterpret_cast<char*>(&marker), sizeof(marker));
        return;
    }

    ofs.write(reinterpret_cast<char*>(&node->value), sizeof(node->value));
    save_to_binary_treenode(node->left, ofs);
    save_to_binary_treenode(node->right, ofs);
}

void save_to_binary_tree(const BinaryTree& tree, const string& filename) {
    ofstream ofs(filename, ios::binary);
    save_to_binary_treenode(tree.root, ofs);
    ofs.close();
}

treeNode* load_from_binary_treenode(ifstream& ifs) {
    int value;
    ifs.read(reinterpret_cast<char*>(&value), sizeof(value));
    if (value == -1) return nullptr; // Если маркер пустого узла, возвращаем nullptr

    treeNode* node = new treeNode(value);
    node->left = load_from_binary_treenode(ifs);
    node->right = load_from_binary_treenode(ifs);
    return node;
}

void load_from_binary_tree(BinaryTree& tree, const string& filename) {
    ifstream ifs(filename, ios::binary);
    tree.clear(); // Очищаем дерево перед загрузкой
    tree.root = load_from_binary_treenode(ifs);
    ifs.close();
};

#endif