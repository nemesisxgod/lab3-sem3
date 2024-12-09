package tests_golang

import (
	"io/ioutil"
	hash "lab3-sem3/golang" // Импортируем ваш пакет с хэш-таблицей
	"strings"
	"testing"
)

// Тест для метода Insert
func TestInsert(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Проверяем правильность вставки
	if result := ht.Search("name"); result != "Alice" {
		t.Errorf("Expected 'Alice', got '%s'", result)
	}
	if result := ht.Search("age"); result != "30" {
		t.Errorf("Expected '30', got '%s'", result)
	}
}

// Тест для метода Search
func TestSearch(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")

	// Проверяем корректность поиска
	result := ht.Search("name")
	if result != "Alice" {
		t.Errorf("Expected 'Alice', got '%s'", result)
	}

	// Проверяем несуществующий ключ
	result = ht.Search("nonexistent")
	if result != "" {
		t.Errorf("Expected '', got '%s'", result)
	}
}

// Тест для метода Remove
func TestRemove(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")
	ht.Remove("name")

	// Проверяем, что элемент удален
	result := ht.Search("name")
	if result != "" {
		t.Errorf("Expected '', got '%s'", result)
	}
}

// Тест для метода Print (проверка вывода, можно сравнивать с ожиданием)
func TestPrint(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Захватываем вывод в буфер
	var builder strings.Builder
	// Направляем вывод хэш-таблицы в builder
	builder.WriteString(ht.String())

	// Ожидаемый вывод
	expectedOutput := "Table[1]: {age: 30} \nTable[7]: {name: Alice} \n"
	// Проверяем, соответствует ли вывод ожидаемому
	if builder.String() != expectedOutput {
		t.Errorf("Expected output: '%s', got '%s'", expectedOutput, builder.String())
	}
}

// Тест для метода LoadFromFile
func TestLoadFromFile(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Clear()

	// Загружаем данные из файла
	ht.LoadFromFile("test_data.txt")

	// Проверяем, что данные были загружены
	if result := ht.Search("name"); result != "Alice" {
		t.Errorf("Expected 'Alice', got '%s'", result)
	}
	if result := ht.Search("age"); result != "30" {
		t.Errorf("Expected '30', got '%s'", result)
	}
}

// Тест для метода SaveToFile
func TestSaveToFile(t *testing.T) {
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Сохраняем данные в файл
	ht.SaveToFile("test_data.txt")

	// Проверяем, что файл был сохранен корректно
	data, err := ioutil.ReadFile("test_data.txt")
	if err != nil {
		t.Fatalf("Failed to read file: %v", err)
	}

	// Проверяем содержимое файла
	content := string(data)
	if !strings.Contains(content, "name Alice") || !strings.Contains(content, "age 30") {
		t.Errorf("File content is incorrect: %s", content)
	}
}
