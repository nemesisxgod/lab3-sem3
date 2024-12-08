#define BOOST_TEST_MODULE BinaryTreeTests
#include <boost/test/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(binary_tree_tests)

BOOST_AUTO_TEST_CASE(test_push_and_search) {
    BinaryTree tree;
    tree.push(10);
    tree.push(20);
    tree.push(30);

    BOOST_CHECK(tree.search(10));
    BOOST_CHECK(tree.search(20));
    BOOST_CHECK(tree.search(30));
    BOOST_CHECK(!tree.search(40)); // Несуществующее значение
}

BOOST_AUTO_TEST_CASE(test_tree_structure) {
    BinaryTree tree;
    tree.push(10);
    tree.push(20);
    tree.push(30);
    tree.push(40);

    BOOST_CHECK(tree.is_complete());
    BOOST_CHECK(!tree.is_full()); // Дерево не полностью заполнено
}

BOOST_AUTO_TEST_CASE(test_clear) {
    BinaryTree tree;
    tree.push(10);
    tree.push(20);
    tree.push(30);

    tree.clear();

    BOOST_CHECK(!tree.search(10));
    BOOST_CHECK(!tree.search(20));
    BOOST_CHECK(!tree.search(30));
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    BinaryTree tree;

    std::ofstream file("test_binary_tree.txt");
    file << "10\n20\n30\n40\n50";
    file.close();

    tree.load_from_file("test_binary_tree.txt");

    BOOST_CHECK(tree.search(10));
    BOOST_CHECK(tree.search(20));
    BOOST_CHECK(tree.search(30));
    BOOST_CHECK(tree.search(40));
    BOOST_CHECK(tree.search(50));
}

BOOST_AUTO_TEST_CASE(test_upload_to_file) {
    BinaryTree tree;
    tree.push(10);
    tree.push(20);
    tree.push(30);

    tree.upload_to_file("output_binary_tree.txt");

    std::ifstream file("output_binary_tree.txt");
    std::vector<int> values;
    int value;
    while (file >> value) {
        values.push_back(value);
    }
    file.close();

    std::vector<int> expected = {10, 20, 30};
    BOOST_CHECK_EQUAL_COLLECTIONS(values.begin(), values.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(test_is_complete_and_is_full) {
    BinaryTree tree;
    tree.push(10);
    tree.push(20);
    tree.push(30);

    BOOST_CHECK(tree.is_complete()); // Дерево должно быть полным
    BOOST_CHECK(tree.is_full());     // Дерево полностью заполнено

    tree.push(40); // Добавление нарушает полноту
    BOOST_CHECK(tree.is_complete());
    BOOST_CHECK(!tree.is_full());
}

BOOST_AUTO_TEST_SUITE_END()