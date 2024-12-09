#define BOOST_TEST_MODULE DoublyLinkedListTests
#include <boost/test/unit_test.hpp>
#include <sstream>
#include <fstream>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(doubly_linked_list_tests)

BOOST_AUTO_TEST_CASE(test_add_to_head) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "C B A \n");
}

BOOST_AUTO_TEST_CASE(test_add_to_tail) {
    DoublyLinkedList list;
    list.add_to_tail("A");
    list.add_to_tail("B");
    list.add_to_tail("C");

    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "A B C \n");
}

BOOST_AUTO_TEST_CASE(test_remove_from_head) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.remove_from_head();
    
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "B A \n");
}

BOOST_AUTO_TEST_CASE(test_remove_from_tail) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_tail("B");
    list.add_to_tail("C");

    list.remove_from_tail();
    
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "A B \n");
}

BOOST_AUTO_TEST_CASE(test_remove_from_tail_single_element) {
    DoublyLinkedList list;

    list.add_to_head("10");

    list.remove_from_tail();

    BOOST_CHECK(list.head == nullptr); 
    BOOST_CHECK(list.tail == nullptr); 
}

BOOST_AUTO_TEST_CASE(test_remove_by_value) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.remove_by_value("B");

    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "C A \n");
}

BOOST_AUTO_TEST_CASE(test_load_from_file_with_content) {
    DoublyLinkedList list;

    ofstream file("test_file.txt");
    file << "line1\n";
    file << "line2\n";
    file << "line3\n";
    file.close();

    // Загружаем данные из файла
    list.load_from_file("test_file.txt");

    // Проверяем содержимое списка
    BOOST_CHECK_EQUAL(list.head->data, "line1");
    BOOST_CHECK_EQUAL(list.head->next->data, "line2");
    BOOST_CHECK_EQUAL(list.tail->data, "line3");
    BOOST_CHECK(list.tail->next == nullptr);

    remove("test_file.txt");
}

BOOST_AUTO_TEST_CASE(test_search) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    int index = 0;
    DoublyLinkedList::Node* node = list.search("B", index);
    BOOST_CHECK(node != nullptr);
    BOOST_CHECK_EQUAL(index, 1);

    node = list.search("Z", index);
    BOOST_CHECK(node == nullptr);
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    DoublyLinkedList list;
    list.load_from_file("test_file.txt");

    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "\n");
}

BOOST_AUTO_TEST_CASE(test_upload_to_file) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.upload_to_file("test_output.txt");

    ifstream file("test_output.txt");
    string line;
    getline(file, line);
    BOOST_CHECK_EQUAL(line, "C");
    getline(file, line);
    BOOST_CHECK_EQUAL(line, "B");
    getline(file, line);
    BOOST_CHECK_EQUAL(line, "A");
}

BOOST_AUTO_TEST_CASE(test_free) {
    DoublyLinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.free();
    
    ostringstream output;
    streambuf* old_buf = cout.rdbuf(output.rdbuf()); 
    list.print(); 
    cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "\n");
}

BOOST_AUTO_TEST_SUITE_END()