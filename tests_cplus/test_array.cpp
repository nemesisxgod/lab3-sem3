#define BOOST_TEST_MODULE DynamicArrayTests
#include <boost/test/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(dynamic_array_tests)

BOOST_AUTO_TEST_CASE(test_increase_capacity) {
    DynamicArray arr;
    // Заполняем массив до его полной вместимости
    for (int i = 0; i < 10; ++i) {
        arr.push_back("element" + std::to_string(i));
    }

    // Теперь добавим еще один элемент, чтобы проверить, что вместимость увеличилась
    arr.push_back("new_element");
    BOOST_CHECK_EQUAL(arr.get(10), "new_element");  // Убедимся, что новый элемент был добавлен
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

    std::ostringstream output;
    std::streambuf* originalBuf = std::cout.rdbuf(output.rdbuf());  // Переадресовываем std::cout в ostringstream

    try {
        arr.print();  // Вызываем печать
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << std::endl;  // Логируем исключения, если они есть
        BOOST_FAIL("Exception occurred during print");
    }

    std::cout.rdbuf(originalBuf);  // Восстанавливаем std::cout

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
    std::ofstream file("test_array.txt");
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

    std::ifstream file("output_array.txt");
    std::string content;
    std::string expected[] = {"line1", "line2", "line3"};
    int i = 0;
    while (getline(file, content)) {
        BOOST_CHECK_EQUAL(content, expected[i++]);
    }
    file.close();
}

BOOST_AUTO_TEST_CASE(test_pop_back_exception) {
    DynamicArray arr;
    
    BOOST_CHECK_THROW(arr.pop_back(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_remove_at_exception) {
    DynamicArray arr;
    arr.push_back("one");
    
    BOOST_CHECK_THROW(arr.remove_at(-1), std::out_of_range);  // Проверка, что выбрасывается исключение для неверного индекса
    BOOST_CHECK_THROW(arr.remove_at(1), std::out_of_range);   // Проверка, что выбрасывается исключение для неверного индекса
}

BOOST_AUTO_TEST_CASE(test_get_exception) {
    DynamicArray arr;
    arr.push_back("one");

    // Проверка, что исключение выбрасывается при неверном индексе
    BOOST_CHECK_THROW(arr.get(-1), std::out_of_range);
    BOOST_CHECK_THROW(arr.get(1), std::out_of_range);  // Индекс выходит за пределы массива
}

BOOST_AUTO_TEST_CASE(test_set_exception) {
    DynamicArray arr;
    arr.push_back("one");

    // Проверка, что исключение выбрасывается при неверном индексе
    BOOST_CHECK_THROW(arr.set(-1, "invalid"), std::out_of_range);
    BOOST_CHECK_THROW(arr.set(1, "invalid"), std::out_of_range);  // Индекс выходит за пределы массива
}


BOOST_AUTO_TEST_SUITE_END()