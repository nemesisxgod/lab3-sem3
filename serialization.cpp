#include "cplus/header.h"
#include "serialization.h"

using namespace std;

int main() {
    // Тест DynamicArray
    DynamicArray arr;
    arr.push_back("Apple");
    arr.push_back("Banana");
    arr.push_back("Cherry");
    save_to_binary_array(arr, "dynamic_array.bin");

    DynamicArray loaded_arr;

    load_from_binary_array(loaded_arr, "dynamic_array.bin");

    cout << "DynamicArray:" << endl;
    loaded_arr.print();

    // Тест HashTable
    HashTable hashTable;
    hashTable.insert("key1", "value1");
    hashTable.insert("key2", "value2");
    save_to_binary_hash(hashTable, "hash_table.bin");

    HashTable loaded_hashTable;
    load_from_binary_hash(loaded_hashTable, "hash_table.bin");
    cout << "\nHashTable:" << endl;
    loaded_hashTable.print();

    // Тест LinkedList
    LinkedList list;
    list.add_to_tail("Node1");
    list.add_to_tail("Node2");
    save_to_binary_list(list, "linked_list.bin");

    LinkedList loaded_list;
    load_from_binary_list(loaded_list, "linked_list.bin");
    cout << "\nLinkedList:" << endl;
    loaded_list.print();

    // Тест DoublyLinkedList
    DoublyLinkedList dlist;
    dlist.add_to_tail("Node1");
    dlist.add_to_tail("Node2");
    save_to_binary_dlist(dlist, "doubly_linked_list.bin");

    DoublyLinkedList loaded_dlist;
    load_from_binary_dlist(loaded_dlist, "doubly_linked_list.bin");
    cout << "\nDoublyLinkedList:" << endl;
    loaded_dlist.print();

    // Тест Queue
    Queue queue;
    queue.push("First");
    queue.push("Second");
    save_to_binary_queue(queue, "queue.bin");

    Queue loaded_queue;
    load_from_binary_queue(loaded_queue, "queue.bin");
    cout << "\nQueue:" << endl;
    loaded_queue.print();

    // Тест Stack
    Stack stack;
    stack.push("Top1");
    stack.push("Top2");
    save_to_binary_stack(stack, "stack.bin");

    Stack loaded_stack;
    load_from_binary_stack(loaded_stack, "stack.bin");
    cout << "\nStack:" << endl;
    loaded_stack.print();

    // Тест BinaryTree
    BinaryTree tree;
    tree.push(5);
    tree.push(3);
    tree.push(8);
    save_to_binary_tree(tree, "binary_tree.bin");

    BinaryTree loaded_tree;
    load_from_binary_tree(loaded_tree, "binary_tree.bin");
    cout << "\nBinaryTree:" << endl;
    loaded_tree.print();

    return 0;
}