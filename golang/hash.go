package hash

import (
	"fmt"
	"os"
	"strings"
)

// Размер хэш-таблицы
const TableSize = 10

// Структура для узла хэш-таблицы
type Node struct {
	Key   string
	Value string
	Next  *Node
}

// Структура для хэш-таблицы
type HashTable struct {
	Table [TableSize]*Node // Приватная таблица
}

// Хэш-функция для вычисления индекса
func (ht *HashTable) hashFunction(Key string) int {
	hash := 0
	for i := 0; i < len(Key); i++ {
		hash = (hash * 31) + int(Key[i])
	}
	return hash % TableSize
}

// Public методы:

// Insert - добавление элемента в хэш-таблицу
func (ht *HashTable) Insert(Key, Value string) {
	index := ht.hashFunction(Key)
	newNode := &Node{Key: Key, Value: Value}

	if ht.Table[index] == nil {
		ht.Table[index] = newNode
	} else {
		current := ht.Table[index]
		for current.Next != nil {
			if current.Key == Key {
				current.Value = Value // Обновляем значение, если ключ уже существует
				return
			}
			current = current.Next
		}
		current.Next = newNode
	}
}

// Search - поиск элемента по ключу
func (ht *HashTable) Search(Key string) string {
	index := ht.hashFunction(Key)
	current := ht.Table[index]
	for current != nil {
		if current.Key == Key {
			return current.Value
		}
		current = current.Next
	}
	return "" // Если ключ не найден
}

// Remove - удаление элемента по ключу
func (ht *HashTable) Remove(Key string) error {
	index := ht.hashFunction(Key)
	current := ht.Table[index]
	var prev *Node

	for current != nil {
		if current.Key == Key {
			if prev == nil {
				ht.Table[index] = current.Next
			} else {
				prev.Next = current.Next
			}
			return nil
		}
		prev = current
		current = current.Next
	}
	return fmt.Errorf("key not found")
}

// Print - вывод хэш-таблицы
func (ht *HashTable) Print() {
	for i := 0; i < TableSize; i++ {
		current := ht.Table[i]
		if current != nil {
			fmt.Printf("Table[%d]: ", i)
			for current != nil {
				fmt.Printf("{%s: %s}", current.Key, current.Value)
				current = current.Next
			}
			fmt.Println() // Здесь мы делаем перенос строки только после полного вывода связанного списка
		}
	}
}

// Clear - очистка хэш-таблицы
func (ht *HashTable) Clear() {
	for i := 0; i < TableSize; i++ {
		ht.Table[i] = nil
	}
}

// LoadFromFile - загрузка данных из файла
func (ht *HashTable) LoadFromFile(filename string) error {
	data, err := os.ReadFile(filename)
	if err != nil {
		return fmt.Errorf("file %s not found: %v", filename, err)
	}
	ht.Clear()

	lines := strings.Split(string(data), "\n")
	for _, line := range lines {
		parts := strings.Split(line, " ")
		if len(parts) == 2 {
			ht.Insert(parts[0], parts[1])
		}
	}

	return nil
}

// SaveToFile - сохранение данных в файл
func (ht *HashTable) SaveToFile(filename string) {
	var builder strings.Builder
	for i := 0; i < TableSize; i++ {
		current := ht.Table[i]
		for current != nil {
			builder.WriteString(fmt.Sprintf("%s %s\n", current.Key, current.Value))
			current = current.Next
		}
	}

	err := os.WriteFile(filename, []byte(builder.String()), 0644)
	if err != nil {
		fmt.Println("Error saving file:", err)
	}
}
