#define BOOST_TEST_MODULE StackTest

#include <boost/test/included/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(stack_tests)

BOOST_AUTO_TEST_CASE(test_push_pop) {
    Stack stack;

    stack.push("first");
    stack.push("second");
    stack.push("third");

    BOOST_CHECK_EQUAL(stack.pop(), "third");
    BOOST_CHECK_EQUAL(stack.pop(), "second");
    BOOST_CHECK_EQUAL(stack.pop(), "first");
    BOOST_CHECK(stack.pop().empty()); // Проверяем на пустом стеке
}

BOOST_AUTO_TEST_CASE(test_is_empty_after_clear) {
    Stack stack;

    stack.push("data");
    BOOST_CHECK(!stack.is_empty());
    stack.clear();
    BOOST_CHECK(stack.is_empty());
}

BOOST_AUTO_TEST_CASE(test_print_empty_stack) {
    Stack stack;

    std::ostringstream oss;
    std::streambuf* original_cout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    stack.print();
    BOOST_CHECK_EQUAL(oss.str(), "Stack is empty\n");

    std::cout.rdbuf(original_cout); // Восстановим стандартный поток
}

BOOST_AUTO_TEST_CASE(test_print_non_empty_stack) {
    Stack stack;

    stack.push("first");
    stack.push("second");
    stack.push("third");

    std::ostringstream oss;
    std::streambuf* original_cout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    stack.print();
    BOOST_CHECK_EQUAL(oss.str(), "third second first \n");

    std::cout.rdbuf(original_cout);
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    Stack stack;

    const std::string filename = "data.txt";
    std::ofstream file(filename);
    file << "line3\nline2\nline1\n";
    file.close();

    stack.load_from_file(filename);
    BOOST_CHECK(!stack.is_empty());
    BOOST_CHECK_EQUAL(stack.pop(), "line3");
    BOOST_CHECK_EQUAL(stack.pop(), "line2");
    BOOST_CHECK_EQUAL(stack.pop(), "line1");
    BOOST_CHECK(stack.is_empty());

    std::remove(filename.c_str()); // Удаляем временный файл
}

BOOST_AUTO_TEST_CASE(test_save_to_file) {
    Stack stack;
    stack.push("line1");
    stack.push("line2");
    stack.push("line3");

    const std::string filename = "output_data.txt";
    stack.save_to_file(filename);

    std::ifstream file(filename);
    BOOST_REQUIRE(file.is_open());

    std::string line;
    std::vector<std::string> lines;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    file.close();

    BOOST_CHECK_EQUAL(lines.size(), 3);
    BOOST_CHECK_EQUAL(lines[0], "line3");
    BOOST_CHECK_EQUAL(lines[1], "line2");
    BOOST_CHECK_EQUAL(lines[2], "line1");

    std::remove(filename.c_str()); // Удаляем временный файл
}

BOOST_AUTO_TEST_CASE(test_clear) {
    Stack stack;

    stack.push("first");
    stack.push("second");
    BOOST_CHECK(!stack.is_empty());
    stack.clear();
    BOOST_CHECK(stack.is_empty());
    BOOST_CHECK(stack.pop().empty());
}

BOOST_AUTO_TEST_CASE(test_load_nonexistent_file) {
    Stack stack;

    std::ostringstream oss;
    std::streambuf* original_cout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    stack.load_from_file("nonexistent_file.txt");
    BOOST_CHECK_EQUAL(oss.str(), "File not found\n");

    std::cout.rdbuf(original_cout);
}

BOOST_AUTO_TEST_CASE(test_save_to_invalid_path) {
    Stack stack;
    stack.push("data");

    std::ostringstream oss;
    std::streambuf* original_cout = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    stack.save_to_file("/invalid/path/output.txt");
    BOOST_CHECK_EQUAL(oss.str(), "File not found\n");

    std::cout.rdbuf(original_cout);
}

BOOST_AUTO_TEST_SUITE_END()