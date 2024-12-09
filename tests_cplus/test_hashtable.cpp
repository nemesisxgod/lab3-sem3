#define BOOST_TEST_MODULE HashTableTests
#include <boost/test/unit_test.hpp>
#include "../cplus/header.h"

BOOST_AUTO_TEST_SUITE(hash_table_tests)

BOOST_AUTO_TEST_CASE(test_insert_and_search) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3");

    BOOST_CHECK_EQUAL(table.search("key1"), "value1");
    BOOST_CHECK_EQUAL(table.search("key2"), "value2");
    BOOST_CHECK_EQUAL(table.search("key3"), "value3");
    BOOST_CHECK_THROW(table.search("key4"), out_of_range);
}

BOOST_AUTO_TEST_CASE(test_update_value) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key1", "value2"); // Обновление значения

    BOOST_CHECK_EQUAL(table.search("key1"), "value2");
}

BOOST_AUTO_TEST_CASE(test_remove) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");

    table.remove("key1");
    BOOST_CHECK_THROW(table.search("key1"), out_of_range);
    BOOST_CHECK_EQUAL(table.search("key2"), "value2"); // Остальные ключи остаются

    table.remove("key2");
    BOOST_CHECK_THROW(table.search("key2"), out_of_range);
}

BOOST_AUTO_TEST_CASE(test_print) {
    HashTable ht;
    ht.insert("key1", "value1");
    ht.insert("key2", "value2");

    stringstream output;
    streambuf* old_cout = cout.rdbuf(output.rdbuf());  // Перенаправляем вывод в строку

    ht.print();  // Вызываем метод print

    cout.rdbuf(old_cout);  // Восстанавливаем стандартный вывод

    string expected_output = 
        "Table[139]: {key1: value1} -> nullptr\nTable[170]: {key2: value2} -> nullptr\n";
    BOOST_CHECK_EQUAL(output.str(), expected_output);
}

BOOST_AUTO_TEST_CASE(test_clear) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.clear();

    BOOST_CHECK_THROW(table.search("key1"), out_of_range);
    BOOST_CHECK_THROW(table.search("key2"), out_of_range);
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    HashTable table;
    ofstream file("test_hash_table.txt");
    file << "key1 value1\nkey2 value2\nkey3 value3";
    file.close();

    table.load_from_file("test_hash_table.txt");

    BOOST_CHECK_EQUAL(table.search("key1"), "value1");
    BOOST_CHECK_EQUAL(table.search("key2"), "value2");
    BOOST_CHECK_EQUAL(table.search("key3"), "value3");
}

BOOST_AUTO_TEST_CASE(test_save_to_file) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.insert("key3", "value3");
    table.save_to_file("output_hash_table.txt");

    ifstream file("output_hash_table.txt");
    string key, value;
    map<string, string> result;

    while (file >> key >> value) {
        result[key] = value;
    }
    file.close();

    BOOST_CHECK_EQUAL(result["key1"], "value1");
    BOOST_CHECK_EQUAL(result["key2"], "value2");
    BOOST_CHECK_EQUAL(result["key3"], "value3");
}

BOOST_AUTO_TEST_CASE(test_load_from_file_exception) {
    HashTable ht;

    stringstream output;
    streambuf* old_cout = cout.rdbuf(output.rdbuf()); 

    ht.load_from_file("non_existent_file.txt");

    cout.rdbuf(old_cout); 

    BOOST_CHECK_EQUAL(output.str(), "File is not found\n");
}

BOOST_AUTO_TEST_CASE(test_save_to_file_exception) {
    HashTable ht;

    string restricted_file = "/restricted_dir/restricted_file.txt";

    stringstream output;
    streambuf* old_cout = cout.rdbuf(output.rdbuf()); 
    ht.save_to_file(restricted_file);

    cout.rdbuf(old_cout); 

    BOOST_CHECK_EQUAL(output.str(), "File not found\n");
}

BOOST_AUTO_TEST_CASE(test_collision_handling) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key1_collision", "collision_value"); // Проверка обработки коллизий

    BOOST_CHECK_EQUAL(table.search("key1"), "value1");
    BOOST_CHECK_EQUAL(table.search("key1_collision"), "collision_value");
}

BOOST_AUTO_TEST_SUITE_END()