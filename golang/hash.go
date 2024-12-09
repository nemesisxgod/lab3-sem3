package hash

import (
	"fmt"
	"io/ioutil"
	"strings"
)

// Размер хэш-таблицы
const TableSize = 10

// Структура для узла хэш-таблицы
type Node struct {
	key   string
	value string
	next  *Node
}

// Структура для хэш-таблицы
type HashTable struct {
	table [TableSize]*Node // Приватная таблица
}

// Хэш-функция для вычисления индекса
func (ht *HashTable) hashFunction(key string) int {
	hash := 0
	for i := 0; i < len(key); i++ {
		hash = (hash * 31) + int(key[i])
	}
	return hash % TableSize
}

// Public методы:

// Insert - добавление элемента в хэш-таблицу
func (ht *HashTable) Insert(key, value string) {
	index := ht.hashFunction(key)
	newNode := &Node{key: key, value: value}

	if ht.table[index] == nil {
		ht.table[index] = newNode
	} else {
		current := ht.table[index]
		for current.next != nil {
			if current.key == key {
				current.value = value // Обновляем значение, если ключ уже существует
				return
			}
			current = current.next
		}
		current.next = newNode
	}
}

// Search - поиск элемента по ключу
func (ht *HashTable) Search(key string) string {
	index := ht.hashFunction(key)
	current := ht.table[index]
	for current != nil {
		if current.key == key {
			return current.value
		}
		current = current.next
	}
	return "" // Если ключ не найден
}

// Remove - удаление элемента по ключу
func (ht *HashTable) Remove(key string) error {
	index := ht.hashFunction(key)
	current := ht.table[index]
	var prev *Node

	for current != nil {
		if current.key == key {
			if prev == nil {
				ht.table[index] = current.next
			} else {
				prev.next = current.next
			}
			return nil
		}
		prev = current
		current = current.next
	}
	return fmt.Errorf("key not found")
}

// Реализуем метод String для хэш-таблицы
func (ht *HashTable) String() string {
	var builder strings.Builder
	for i := 0; i < TableSize; i++ {
		current := ht.table[i]
		for current != nil {
			builder.WriteString(fmt.Sprintf("Table[%d]: {%s: %s} \n", i, current.key, current.value))
			current = current.next
		}
	}
	return builder.String()
}

// Print - вывод хэш-таблицы
func (ht *HashTable) Print() {
	for i := 0; i < TableSize; i++ {
		current := ht.table[i]
		if current != nil {
			fmt.Printf("Table[%d]: ", i)
			for current != nil {
				fmt.Printf("{%s: %s}", current.key, current.value)
				current = current.next
			}
			fmt.Println() // Здесь мы делаем перенос строки только после полного вывода связанного списка
		}
	}
}

// Clear - очистка хэш-таблицы
func (ht *HashTable) Clear() {
	for i := 0; i < TableSize; i++ {
		ht.table[i] = nil
	}
}

// LoadFromFile - загрузка данных из файла
func (ht *HashTable) LoadFromFile(filename string) {
	data, err := ioutil.ReadFile(filename)
	if err != nil {
		fmt.Println("File is not found")
		return
	}
	ht.Clear()

	lines := strings.Split(string(data), "\n")
	for _, line := range lines {
		line = strings.TrimSpace(line) // Убираем лишние пробелы по краям
		if line == "" {
			continue // Пропускаем пустые строки
		}
		parts := strings.Split(line, " ")
		if len(parts) == 2 {
			ht.Insert(parts[0], parts[1])
		}
	}
}

// SaveToFile - сохранение данных в файл
func (ht *HashTable) SaveToFile(filename string) {
	var builder strings.Builder
	for i := 0; i < TableSize; i++ {
		current := ht.table[i]
		for current != nil {
			builder.WriteString(fmt.Sprintf("%s %s\n", current.key, current.value))
			current = current.next
		}
	}

	err := ioutil.WriteFile(filename, []byte(builder.String()), 0644)
	if err != nil {
		fmt.Println("Error saving file:", err)
	}
}
