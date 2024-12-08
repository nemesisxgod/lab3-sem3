#include <iostream>
#include <fstream>
#include <sstream>
#include "header.h"

using namespace std;

void processQuery(const string& query, DynamicArray& arr, Stack& stack, Queue& queue, LinkedList& singlyList, DoublyLinkedList& doublyList, HashTable& hashTable, BinaryTree& tree) {
    vector<string> tokens;
    stringstream ss(query);
    string token;

    while (getline(ss, token, ' ')) {
        tokens.push_back(token);
    }

    // Массив (DynamicArray)
    if (tokens[0] == "APUSHBACK") {
        if (tokens.size() == 2) {
            arr.push_back(tokens[1]);
        } else {
            cout << "Error: APUSHBACK command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "APUSHIN") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            arr.insert(tokens[2], index);
        } else {
            cout << "Error: APUSHIN command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "APOPBACK") {
        if (tokens.size() == 1) {
            arr.pop_back();
        } else {
            cout << "Error: APOPBACK command requires no argument." << endl;
        }
    } else if (tokens[0] == "ASEARCH") {
        if (tokens.size() == 2) {
            arr.search(tokens[1]);
        } else {
            cout << "Error: ASEARCH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "ASET") {
        if (tokens.size() == 3) {
            int index = stoi(tokens[1]);
            arr.set(index, tokens[2]);
        } else {
            cout << "Error: ASET command requires 2 arguments." << endl;
        }
    }

    // Стек (Stack)
    else if (tokens[0] == "SPUSH") {
        if (tokens.size() == 2) {
            stack.push(tokens[1]);
        } else {
            cout << "Error: SPUSH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "SPOP") {
        stack.pop();
    }

    // Очередь (Queue)
    else if (tokens[0] == "QPUSH") {
        if (tokens.size() == 2) {
            queue.push(tokens[1]);
        } else {
            cout << "Error: QPUSH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "QPOP") {
        queue.pop();
    }

    // Односвязный список (LinkedList)
    else if (tokens[0] == "LSADDHEAD") {
        if (tokens.size() == 2) {
            singlyList.add_to_head(tokens[1]);
        } else {
            cout << "Error: LSADDHEAD requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LSADDTAIL") {
        if (tokens.size() == 2) {
            singlyList.add_to_tail(tokens[1]);
        } else {
            cout << "Error: LSADDTAIL requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LSDELHEAD") {
        singlyList.remove_from_head();
    } else if (tokens[0] == "LSDELTAIL") {
        singlyList.remove_from_tail();
    }

    // Двусвязный список (DoublyLinkedList)
    else if (tokens[0] == "LDADDHEAD") {
        if (tokens.size() == 2) {
            doublyList.add_to_head(tokens[1]);
        } else {
            cout << "Error: LDADDHEAD requires 1 argument." << endl;
        }
    } else if (tokens[0] == "LDADDTAIL") {
        if (tokens.size() == 2) {
            doublyList.add_to_tail(tokens[1]);
        } else {
            cout << "Error: LDADDTAIL requires 1 argument." << endl;
        }
    }

    // Хэш-таблица (HashTable)
    else if (tokens[0] == "HPUSH") {
        if (tokens.size() == 3) {
            hashTable.insert(tokens[1], tokens[2]);
        } else {
            cout << "Error: HPUSH command requires 2 arguments." << endl;
        }
    } else if (tokens[0] == "HSEARCH") {
        if (tokens.size() == 2) {
            hashTable.search(tokens[1]);
        } else {
            cout << "Error: HSEARCH command requires 1 argument." << endl;
        }
    }

    else if (tokens[0] == "TPUSH") {
        if (tokens.size() == 2) {
            int value = stoi(tokens[1]);
            tree.push(value);
        } else {
            cout << "Error: TPUSH command requires 1 argument." << endl;
        }
    } else if (tokens[0] == "TISCBT") {
        if (tree.is_complete()) {
            cout << "The tree is a complete binary tree." << endl;
        } else {
            cout << "The tree is not a complete binary tree." << endl;
        }
    } else if (tokens[0] == "TFIND") {
        if (tokens.size() == 2) {
            int value = stoi(tokens[1]);
            if (tree.search(value)) {
                cout << "Value " << value << " found in the tree." << endl;
            } else {
                cout << "Value " << value << " not found in the tree." << endl;
            }
        } else {
            cout << "Error: TFIND command requires 1 argument." << endl;
        }
    }

    // Общая операция PRINT для всех структур данных
    else if (tokens[0] == "PRINT") {
        cout << "The structure is deduced." << endl;
    } else {
        cout << "Unknown command: " << tokens[0] << endl;
    }
}

int main(int argc, char* argv[]) {
    string query;
    string filename;

    DynamicArray arr;
    Stack stack;
    Queue queue;
    LinkedList singlyList;
    DoublyLinkedList doublyList;
    HashTable hashTable;
    BinaryTree tree;

    // Чтение аргументов командной строки
    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "--file" && i + 1 < argc) {
            filename = argv[++i];
        }
        if (arg == "--query" && i + 1 < argc) {
            query = argv[++i];
        }
    }

    // Загрузка данных из файла для конкретной структуры данных
    if (!filename.empty()) {
        stringstream ss(query);
        string command;
        ss >> command;

        if (command[0] == 'A') {
            arr.load_from_file(filename);
        } else if (command[0] == 'S') {
            stack.load_from_file(filename);
        } else if (command[0] == 'Q') {
            queue.load_from_file(filename);
        } else if (command[0] == 'L' && command[1] == 'S') {
            singlyList.load_from_file(filename);
        } else if (command[0] == 'L' && command[1] == 'D') {
            doublyList.load_from_file(filename);
        } else if (command[0] == 'H') {
            hashTable.load_from_file(filename);
        } else if (command[0] == 'T') {
            tree.load_from_file(filename);
        } else if (command == "PRINT") {
            ifstream file(filename);
            if (!file.is_open()) {
                cerr << "Error: could not open file " << filename << endl;
                return 1;
            }
            string line;
            while (getline(file, line)) {
                cout << line << endl;
            }
            file.close();
        } else {
            cout << "Error: unrecognized command type." << endl;
            return 1;
        }
    }

    // Обработка запроса
    if (!query.empty()) {
        processQuery(query, arr, stack, queue, singlyList, doublyList, hashTable, tree);
    } else {
        cout << "Error: query not specified." << endl;
        return 1;
    }

    // Сохранение данных в файл для конкретной структуры данных
    if (!filename.empty()) {
        stringstream ss(query);
        string command;
        ss >> command;

        if (command[0] == 'A') {
            arr.save_to_file(filename);
        } else if (command[0] == 'S') {
            stack.save_to_file(filename);
        } else if (command[0] == 'Q') {
            queue.save_to_file(filename);
        } else if (command[0] == 'L' && command[1] == 'S') {
            singlyList.upload_to_file(filename);
        } else if (command[0] == 'L' && command[1] == 'D') {
            doublyList.upload_to_file(filename);
        } else if (command[0] == 'H') {
            hashTable.save_to_file(filename);
        } else if (command[0] == 'T') {
            tree.upload_to_file(filename);
        }
    }

    return 0;
}