#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

//_____________________________________________________________________________________
// Класс DynamicArray
class DynamicArray {
private:
    string* data = nullptr;
    size_t size = 0;
    size_t capacity = 1;

    void increase_capacity();

public:
    DynamicArray();
    ~DynamicArray();

    void push_back(const string& value);
    void insert(const string& value, int index);
    void pop_back();
    void remove_at(int index);
    int search(const string& value) const;
    string get(int index) const;
    void set(int index, const string& value);
    void print() const;
    void load_from_file(const string& filename);
    void save_to_file(const string& filename) const;
};

//_____________________________________________________________________________________
// Класс HashTable
class HashTable {
private:
    struct Node {
        string key;
        string value;
        Node* next;
    };

    static const int TABLE_SIZE = 256;
    Node* table[TABLE_SIZE];

    int hash_function(const string& key) const;

public:
    HashTable();
    ~HashTable();

    void insert(const string& key, const string& value);
    string search(const string& value) const;
    void remove(const string& key);
    void print() const;
    void clear();
    void load_from_file(const string& filename);
    void save_to_file(const string& filename) const;
};

//_____________________________________________________________________________________
// Класс LinkedList
class LinkedList {
public:
    struct Node {
        string data;
        Node* next;
    };

    Node* head;

public:
    LinkedList();
    ~LinkedList();

    void add_to_head(const string& value);
    void add_to_tail(const string& value);
    void remove_from_head();
    void remove_from_tail();
    void remove_by_value(const string& value);
    Node* search(const string& value, int& index) const;
    void print() const;
    void free();
    void load_from_file(const string& filename);
    void upload_to_file(const string& filename) const;
};

//_____________________________________________________________________________________
// Класс DoublyLinkedList
class DoublyLinkedList {
public:
    struct Node {
        string data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList();
    ~DoublyLinkedList();

    void add_to_head(const string& value);
    void add_to_tail(const string& value);
    void remove_from_head();
    void remove_from_tail();
    void remove_by_value(const string& value);
    Node* search(const string& value, int& index) const;
    void print() const;
    void free();
    void load_from_file(const string& filename);
    void upload_to_file(const string& filename) const;
};

//_____________________________________________________________________________________
// Класс Queue
class Queue {
private:
    struct Node {
        string data;
        Node* next;
    };

    Node* head;
    Node* tail;

public:
    Queue();
    ~Queue();

    bool is_empty() const;
    void push(const string& value);
    string pop();
    void print() const;
    void clear();
    void load_from_file(const string& filename);
    void save_to_file(const string& filename) const;
};

//_____________________________________________________________________________________
// Класс Stack
class Stack {
private:
    struct Node {
        string data;
        Node* next;

        Node(const string& data) : data(data), next(nullptr) {}
    };

    Node* head;

public:
    Stack();
    ~Stack();

    void push(const string& value);
    string pop();
    void print() const;
    void clear();
    void load_from_file(const string& filename);
    void save_to_file(const string& filename) const;

    bool is_empty() const {
        return head == nullptr;
    }
};

//_____________________________________________________________________________________
// Класс BinaryTree
class treeNode {
public:
    int value;
    treeNode* left;
    treeNode* right;

    treeNode(int val) : value(val), left(nullptr), right(nullptr) {}
};

class QueueT {
private:
    struct NodeQT {
        treeNode* data;
        NodeQT* next;
    };

    NodeQT* head;
    NodeQT* tail;

public:
    QueueT();
    ~QueueT();

    bool is_empty() const;
    void push(treeNode* value);
    treeNode* pop();
};

class BinaryTree {
private:
    treeNode* root;

    int count_of_nodes_tree(treeNode* node) const;
    int height_tree(treeNode* node) const;
    void clear_tree(treeNode*& node);
    void print_lvl(treeNode* node, int level) const;
    void push_tree(treeNode*& node, int value);
    bool search_tree(treeNode* node, int val) const;

public:
    BinaryTree() : root(nullptr) {}  // Конструктор по умолчанию
    ~BinaryTree();

    bool is_complete() const;
    bool is_full() const;
    void print() const;
    void push(int value);
    bool search(int val) const;
    void load_from_file(const string& filename);
    void upload_to_file(const string& filename) const;
    void clear();
};

#endif