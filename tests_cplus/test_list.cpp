#define BOOST_TEST_MODULE LinkedListTests
#include <boost/test/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(LinkedListTests)

// Тест на добавление в начало списка
BOOST_AUTO_TEST_CASE(test_add_to_head) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);  

    BOOST_CHECK_EQUAL(output.str(), "C B A \n");
}

// Тест на добавление в конец списка
BOOST_AUTO_TEST_CASE(test_add_to_tail) {
    LinkedList list;
    list.add_to_tail("A");
    list.add_to_tail("B");
    list.add_to_tail("C");

    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "A B C \n");
}

// Тест на удаление с головы списка
BOOST_AUTO_TEST_CASE(test_remove_from_head) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.remove_from_head();
    
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "B A \n");
}

// Тест на удаление с хвоста списка
BOOST_AUTO_TEST_CASE(test_remove_from_tail) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_tail("B");
    list.add_to_tail("C");

    list.remove_from_tail();
    
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "A B \n");
}

// Тест на удаление по значению
BOOST_AUTO_TEST_CASE(test_remove_by_value) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.remove_by_value("B");

    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "C A \n");
}

// Тест на поиск элемента
BOOST_AUTO_TEST_CASE(test_search) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    int index = 0;
    LinkedList::Node* node = list.search("B", index);
    BOOST_CHECK(node != nullptr);
    BOOST_CHECK_EQUAL(index, 1);

    node = list.search("Z", index);
    BOOST_CHECK(node == nullptr);
}

// Тест на загрузку данных из файла
BOOST_AUTO_TEST_CASE(test_load_from_file) {
    LinkedList list;
    list.load_from_file("test_file.txt");

    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "\n");
}

// Тест на сохранение данных в файл
BOOST_AUTO_TEST_CASE(test_upload_to_file) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.upload_to_file("test_output.txt");

    std::ifstream file("test_output.txt");
    std::string line;
    std::getline(file, line);
    BOOST_CHECK_EQUAL(line, "C");
    std::getline(file, line);
    BOOST_CHECK_EQUAL(line, "B");
    std::getline(file, line);
    BOOST_CHECK_EQUAL(line, "A");
}

// Тест на очистку списка
BOOST_AUTO_TEST_CASE(test_free) {
    LinkedList list;
    list.add_to_head("A");
    list.add_to_head("B");
    list.add_to_head("C");

    list.free();
    
    std::ostringstream output;
    std::streambuf* old_buf = std::cout.rdbuf(output.rdbuf()); 
    list.print(); 
    std::cout.rdbuf(old_buf);
    BOOST_CHECK_EQUAL(output.str(), "\n");
}

BOOST_AUTO_TEST_SUITE_END()