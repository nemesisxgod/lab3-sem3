#define BOOST_TEST_MODULE QueueTests
#include <boost/test/included/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(queue_tests)

BOOST_AUTO_TEST_CASE(test_is_empty) {
    Queue queue;
    BOOST_CHECK(queue.is_empty());

    queue.push("test");
    BOOST_CHECK(!queue.is_empty());
}

BOOST_AUTO_TEST_CASE(test_push_pop) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    queue.push("third");

    BOOST_CHECK_EQUAL(queue.pop(), "first");
    BOOST_CHECK_EQUAL(queue.pop(), "second");
    BOOST_CHECK_EQUAL(queue.pop(), "third");

    BOOST_CHECK(queue.is_empty());
}

BOOST_AUTO_TEST_CASE(test_pop_empty) {
    Queue queue;
    BOOST_CHECK_EQUAL(queue.pop(), "");
}

BOOST_AUTO_TEST_CASE(test_print_empty) {
    Queue queue;
    ostringstream output;
    streambuf* original_cout = cout.rdbuf(output.rdbuf());

    queue.print();

    cout.rdbuf(original_cout);
    BOOST_CHECK_EQUAL(output.str(), "Queue is empty!\n");
}

BOOST_AUTO_TEST_CASE(test_print_non_empty) {
    Queue queue;
    queue.push("first");
    queue.push("second");

    ostringstream output;
    streambuf* original_cout = cout.rdbuf(output.rdbuf());

    queue.print();

    cout.rdbuf(original_cout);
    BOOST_CHECK_EQUAL(output.str(), "first second \n");
}

BOOST_AUTO_TEST_CASE(test_clear) {
    Queue queue;
    queue.push("first");
    queue.push("second");
    queue.clear();

    BOOST_CHECK(queue.is_empty());
    BOOST_CHECK_EQUAL(queue.pop(), "");
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    Queue queue;

    ofstream test_file("test_queue.txt");
    test_file << "line1\nline2\nline3";
    test_file.close();

    queue.load_from_file("test_queue.txt");

    BOOST_CHECK_EQUAL(queue.pop(), "line1");
    BOOST_CHECK_EQUAL(queue.pop(), "line2");
    BOOST_CHECK_EQUAL(queue.pop(), "line3");
    BOOST_CHECK(queue.is_empty());
}

BOOST_AUTO_TEST_CASE(test_save_to_file) {
    Queue queue;
    queue.push("line1");
    queue.push("line2");
    queue.push("line3");

    queue.save_to_file("test_queue_save.txt");

    // Проверяем содержимое файла
    ifstream test_file("test_queue_save.txt");
    string line;
    BOOST_CHECK(getline(test_file, line) && line == "line1");
    BOOST_CHECK(getline(test_file, line) && line == "line2");
    BOOST_CHECK(getline(test_file, line) && line == "line3");
    BOOST_CHECK(!getline(test_file, line));
}

BOOST_AUTO_TEST_SUITE_END()