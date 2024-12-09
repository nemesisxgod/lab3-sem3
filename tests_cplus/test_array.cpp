#define BOOST_TEST_MODULE DynamicArrayTests
#include <boost/test/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(dynamic_array_tests)

BOOST_AUTO_TEST_CASE(test_increase_capacity) {
    DynamicArray arr;
    for (int i = 0; i < 10; ++i) {
        arr.push_back("element" + to_string(i));
    }

    arr.push_back("new_element");
    BOOST_CHECK_EQUAL(arr.get(10), "new_element");
}

BOOST_AUTO_TEST_CASE(test_push_back) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("two");
    BOOST_CHECK_EQUAL(arr.get(0), "one");
    BOOST_CHECK_EQUAL(arr.get(1), "two");
    BOOST_CHECK_EQUAL(arr.search("two"), 1);
}

BOOST_AUTO_TEST_CASE(test_insert) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("three");
    arr.insert("two", 1);
    BOOST_CHECK_EQUAL(arr.get(1), "two");
    BOOST_CHECK_EQUAL(arr.get(2), "three");
}

BOOST_AUTO_TEST_CASE(test_pop_back) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("two");
    arr.pop_back();
    BOOST_CHECK_EQUAL(arr.get(0), "one");
}

BOOST_AUTO_TEST_CASE(test_print) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("two");
    arr.push_back("three");

    ostringstream output;
    streambuf* originalBuf = cout.rdbuf(output.rdbuf());  // Переадресовываем cout в ostringstream

    arr.print(); 

    cout.rdbuf(originalBuf);  // Восстанавливаем cout

    BOOST_CHECK_EQUAL(output.str(), "one two three \n");
}

BOOST_AUTO_TEST_CASE(test_remove_at) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("two");
    arr.push_back("three");
    arr.remove_at(1);
    BOOST_CHECK_EQUAL(arr.get(1), "three");
    BOOST_CHECK_EQUAL(arr.search("two"), -1);
}

BOOST_AUTO_TEST_CASE(test_search) {
    DynamicArray arr;
    arr.push_back("one");
    arr.push_back("two");
    BOOST_CHECK_EQUAL(arr.search("two"), 1);
    BOOST_CHECK_EQUAL(arr.search("three"), -1);
}

BOOST_AUTO_TEST_CASE(test_get_set) {
    DynamicArray arr;
    arr.push_back("one");
    arr.set(0, "new_one");
    BOOST_CHECK_EQUAL(arr.get(0), "new_one");
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    DynamicArray arr;
    ofstream file("test_array.txt");
    file << "line1\nline2\nline3";
    file.close();

    arr.load_from_file("test_array.txt");
    BOOST_CHECK_EQUAL(arr.get(0), "line1");
    BOOST_CHECK_EQUAL(arr.get(1), "line2");
    BOOST_CHECK_EQUAL(arr.get(2), "line3");
}

BOOST_AUTO_TEST_CASE(test_save_to_file) {
    DynamicArray arr;
    arr.push_back("line1");
    arr.push_back("line2");
    arr.push_back("line3");
    arr.save_to_file("output_array.txt");

    ifstream file("output_array.txt");
    string content;
    string expected[] = {"line1", "line2", "line3"};
    int i = 0;
    while (getline(file, content)) {
        BOOST_CHECK_EQUAL(content, expected[i++]);
    }
    file.close();
}

BOOST_AUTO_TEST_CASE(test_pop_back_exception) {
    DynamicArray arr;
    
    BOOST_CHECK_THROW(arr.pop_back(), out_of_range);
}

BOOST_AUTO_TEST_CASE(test_remove_at_exception) {
    DynamicArray arr;
    arr.push_back("one");
    
    BOOST_CHECK_THROW(arr.remove_at(-1), out_of_range);  
    BOOST_CHECK_THROW(arr.remove_at(1), out_of_range);   
}

BOOST_AUTO_TEST_CASE(test_get_exception) {
    DynamicArray arr;
    arr.push_back("one");

    // Проверка, что исключение выбрасывается при неверном индексе
    BOOST_CHECK_THROW(arr.get(-1), out_of_range);
    BOOST_CHECK_THROW(arr.get(1), out_of_range); 
}

BOOST_AUTO_TEST_CASE(test_set_exception) {
    DynamicArray arr;
    arr.push_back("one");

    BOOST_CHECK_THROW(arr.set(-1, "invalid"), out_of_range);
    BOOST_CHECK_THROW(arr.set(1, "invalid"), out_of_range);
}


BOOST_AUTO_TEST_SUITE_END()