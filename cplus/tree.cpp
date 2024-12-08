#include <iostream>
#include <fstream>
#include <cmath>
#include "header.h"

using namespace std;

QueueT::QueueT() : head(nullptr), tail(nullptr) {}

QueueT::~QueueT() {
    while (head) {
        NodeQT* temp = head;
        head = head->next;
        delete temp;
    }
}

bool QueueT::is_empty() const {
    return head == nullptr;
}

void QueueT::push(treeNode* value) {
    NodeQT* newNode = new NodeQT;
    if (!newNode) {
        cout << "Memory allocation failed!" << endl;
        return;
    }

    newNode->data = value;
    newNode->next = nullptr;

    if (!tail) { // Если очередь пустая
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode; // Добавляем новый узел в конец
        tail = newNode; // Обновляем указатель на хвост
    }
}

treeNode* QueueT::pop() {
    if (!head) {
        cout << "Queue is empty!" << endl;
        return nullptr;
    }

    NodeQT* temp = head;
    treeNode* value = temp->data;
    head = head->next;

    if (!head) { // Если очередь стала пустой
        tail = nullptr;
    }

    delete temp;
    return value;
}

BinaryTree::~BinaryTree() {
    clear();
}

int BinaryTree::count_of_nodes_tree(treeNode* node) const {
    if (node == nullptr)
        return 0;
    return 1 + count_of_nodes_tree(node->left) + count_of_nodes_tree(node->right);
}

int BinaryTree::height_tree(treeNode* node) const {
    if (node == nullptr) {
        return 0;
    }
    return max(height_tree(node->left), height_tree(node->right)) + 1;
}

bool BinaryTree::is_complete() const {
    if (!root) return true;

    QueueT queue;
    queue.push(root);
    bool mustBeLeaf = false;

    while (!queue.is_empty()) {
        treeNode* current = queue.pop();

        if (current->left) {
            if (mustBeLeaf) return false;
            queue.push(current->left);
        } else {
            mustBeLeaf = true;
        }

        if (current->right) {
            if (mustBeLeaf) return false;
            queue.push(current->right);
        } else {
            mustBeLeaf = true;
        }
    }
    return true;
}

bool BinaryTree::is_full() const {
    int height = height_tree(root);
    int countIfComplete = pow(2, height) - 1;
    return count_of_nodes_tree(root) == countIfComplete;
}

void BinaryTree::print_lvl(treeNode* node, int level) const {
    if (node == nullptr) {
        return;
    }

    int width = pow(2, height_tree(node)) - 1;
    int spacesCnt = width / 2;
    string spacesBefore(spacesCnt, ' ');
    string spacesAfter(spacesCnt + 1, ' ');

    if (level == 1) {
        cout << spacesBefore << node->value << spacesAfter;
    } else {
        print_lvl(node->left, level - 1);
        print_lvl(node->right, level - 1);
    }
}

void BinaryTree::print() const {
    int height = height_tree(root);
    for (int i = 1; i <= height; i++) {
        print_lvl(root, i);
        cout << endl;
    }
}

bool BinaryTree::search_tree(treeNode* node, int val) const {
    if (node == nullptr) {
        return false;
    }
    if (node->value == val) {
        return true;
    }
    return search_tree(node->left, val) || search_tree(node->right, val);
}

bool BinaryTree::search(int val) const {
    return search_tree(root, val);
}

void BinaryTree::push_tree(treeNode*& node, int value) {
    if (node == nullptr) {
        node = new treeNode(value);
        return;
    }

    QueueT queue;
    queue.push(node);

    while (!queue.is_empty()) {
        treeNode* current = queue.pop();

        if (current->left == nullptr) {
            current->left = new treeNode(value);
            return;
        } else {
            queue.push(current->left);
        }

        if (current->right == nullptr) {
            current->right = new treeNode(value);
            return;
        } else {
            queue.push(current->right);
        }
    }
}

void BinaryTree::push(int value) {
        push_tree(root, value);  // Добавляем элемент в дерево, начиная с корня
    }

void BinaryTree::clear_tree(treeNode*& node) {
    if (node == nullptr) return;

    clear_tree(node->left);
    clear_tree(node->right);

    delete node;
    node = nullptr;
}

void BinaryTree::clear() {
    clear_tree(root);
}

void BinaryTree::load_from_file(const string& filename) {
    clear();
    ifstream load(filename);
    if (!load.is_open()) {
        cout << "Failed to open file.\n";
        return;
    }

    int value;
    while (load >> value) {
        push_tree(root, value);
    }
    load.close();
}

void BinaryTree::upload_to_file(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "File is not found" << endl;
        return;
    }

    if (!root) {
        file << "Tree is empty" << endl;
    } else {
        QueueT queue;
        queue.push(root);

        while (!queue.is_empty()) {
            treeNode* current = queue.pop();
            file << current->value << endl;

            if (current->left != nullptr) {
                queue.push(current->left);
            }
            if (current->right != nullptr) {
                queue.push(current->right);
            }
        }
    }
    file.close();
}