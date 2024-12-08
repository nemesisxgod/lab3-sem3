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
    BOOST_CHECK_THROW(table.search("key4"), std::out_of_range);
}

// BOOST_AUTO_TEST_CASE(test_remove_exception) {
//     HashTable ht;
//     ht.insert("key1", "value1");

//     // Проверка удаления существующего ключа
//     ht.remove("key1");
//     BOOST_CHECK_THROW(ht.search("key1"), std::out_of_range);

//     // Проверка на удаление несуществующего ключа
//     std::stringstream output;
//     std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());  // Перенаправляем вывод в строку

//     ht.remove("key2");  // Ключ "key2" не существует
//     BOOST_CHECK_THROW(ht.remove("key2"), std::out_of_range);  // Проверяем, что напечатано сообщение об ошибке

//     std::cout.rdbuf(old_cout);  // Восстанавливаем стандартный вывод
// }

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
    BOOST_CHECK_THROW(table.search("key1"), std::out_of_range);
    BOOST_CHECK_EQUAL(table.search("key2"), "value2"); // Остальные ключи остаются

    table.remove("key2");
    BOOST_CHECK_THROW(table.search("key2"), std::out_of_range);
}

// BOOST_AUTO_TEST_CASE(test_print) {
//     HashTable ht;
//     ht.insert("key1", "value1");
//     ht.insert("key2", "value2");
    
//     std::stringstream output;
//     std::streambuf* old_cout = std::cout.rdbuf(output.rdbuf());  // Перенаправляем вывод в строку
    
//     ht.print();  // Вызываем метод print
    
//     std::string expected_output = "Table[0]: nullptr\nTable[1]: {key2: value2} -> nullptr\nTable[2]: nullptr\n";  // Пример, ожидаемый вывод
//     BOOST_CHECK_EQUAL(output.str(), expected_output);  // Проверка
    
//     std::cout.rdbuf(old_cout);  // Восстанавливаем стандартный вывод
// }

BOOST_AUTO_TEST_CASE(test_clear) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key2", "value2");
    table.clear();

    BOOST_CHECK_THROW(table.search("key1"), std::out_of_range);
    BOOST_CHECK_THROW(table.search("key2"), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(test_load_from_file) {
    HashTable table;
    std::ofstream file("test_hash_table.txt");
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

    std::ifstream file("output_hash_table.txt");
    std::string key, value;
    std::map<std::string, std::string> result;

    while (file >> key >> value) {
        result[key] = value;
    }
    file.close();

    BOOST_CHECK_EQUAL(result["key1"], "value1");
    BOOST_CHECK_EQUAL(result["key2"], "value2");
    BOOST_CHECK_EQUAL(result["key3"], "value3");
}

BOOST_AUTO_TEST_CASE(test_collision_handling) {
    HashTable table;
    table.insert("key1", "value1");
    table.insert("key1_collision", "collision_value"); // Проверка обработки коллизий

    BOOST_CHECK_EQUAL(table.search("key1"), "value1");
    BOOST_CHECK_EQUAL(table.search("key1_collision"), "collision_value");
}

BOOST_AUTO_TEST_SUITE_END()