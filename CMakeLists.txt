cmake_minimum_required(VERSION 3.10)
project(ProjectName)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
# Найти Boost
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Указать include-директории
include_directories(${CMAKE_SOURCE_DIR}/cplus)

# Тесты для Stack
add_executable(test_stack tests_cplus/test_stack.cpp cplus/stack.cpp)
target_link_libraries(test_stack Boost::unit_test_framework)

# Тесты для Queue
add_executable(test_queue tests_cplus/test_queue.cpp cplus/queue.cpp)
target_link_libraries(test_queue Boost::unit_test_framework)

# Тесты для Array
add_executable(test_array tests_cplus/test_array.cpp cplus/array.cpp)
target_link_libraries(test_array Boost::unit_test_framework)

# Тесты для Hasht
add_executable(test_hashtable tests_cplus/test_hashtable.cpp cplus/hashtable.cpp)
target_link_libraries(test_hashtable Boost::unit_test_framework)

# Тесты для Tree
add_executable(test_tree tests_cplus/test_tree.cpp cplus/tree.cpp)
target_link_libraries(test_tree Boost::unit_test_framework)

# Тесты для List
add_executable(test_list tests_cplus/test_list.cpp cplus/list.cpp)
target_link_libraries(test_list Boost::unit_test_framework)

# Тесты для DList
add_executable(test_dlist tests_cplus/test_dlist.cpp cplus/dlist.cpp)
target_link_libraries(test_dlist Boost::unit_test_framework)

# Добавить тесты для ctest
enable_testing()
add_test(NAME StackTests COMMAND test_stack)
add_test(NAME QueueTests COMMAND test_queue)
add_test(NAME DynamicArrayTests COMMAND test_array)
add_test(NAME HashTableTests COMMAND test_hashtable)
add_test(NAME BinaryTreeTests COMMAND test_tree)
add_test(NAME LinkedListTests COMMAND test_list)
add_test(NAME DoublyLinkedListTests COMMAND test_dlist)