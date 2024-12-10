package hash

import (
	"bytes"
	"fmt"
	"os"
	"strings"
	"testing"
)

// Тест для метода Insert
func TestInsert(t *testing.T) {
	ht := &HashTable{}
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

func TestInsertCollisions(t *testing.T) {
	ht := &HashTable{}

	// Вставляем элементы с одинаковым индексом хэширования
	ht.Insert("name", "Alice")   // Первый элемент
	ht.Insert("eman", "Bob")     // Коллизия (предположим, хэширует в тот же индекс)
	ht.Insert("name", "Updated") // Обновление существующего ключа

	// Проверяем значения
	if result := ht.Search("name"); result != "Updated" {
		t.Errorf("Expected 'Updated', got '%s'", result)
	}
	if result := ht.Search("eman"); result != "Bob" {
		t.Errorf("Expected 'Bob', got '%s'", result)
	}
}

// Тест для метода Search
func TestSearch(t *testing.T) {
	ht := &HashTable{}
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
	ht := &HashTable{}
	ht.Insert("name", "Alice")
	ht.Remove("name")

	// Проверяем, что элемент удален
	result := ht.Search("name")
	if result != "" {
		t.Errorf("Expected '', got '%s'", result)
	}
}

// Тест для метода Print
func TestPrint(t *testing.T) {
	ht := &HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Перенаправляем вывод в буфер
	var buffer bytes.Buffer
	originalStdout := os.Stdout
	r, w, _ := os.Pipe()
	os.Stdout = w

	// Вызываем Print, чтобы его вывод пошел в Pipe
	go func() {
		ht.Print()
		w.Close()
	}()

	// Читаем вывод из Pipe
	buffer.ReadFrom(r)
	os.Stdout = originalStdout

	// Ожидаемый результат
	expectedOutput := "Table[1]: {age: 30}\nTable[7]: {name: Alice}\n"
	if buffer.String() != expectedOutput {
		t.Errorf("Expected output: '%s', got '%s'", expectedOutput, buffer.String())
	}
}

// Тест для метода LoadFromFile
func TestLoadFromFile(t *testing.T) {
	ht := &HashTable{}
	ht.Clear()

	err := ht.LoadFromFile("nonexistent_file.txt")
	if err != nil {
		fmt.Println("Error loading file:", err)
	}
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
	ht := &HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Сохраняем данные в файл
	ht.SaveToFile("test_data.txt")

	// Проверяем, что файл был сохранен корректно
	data, err := os.ReadFile("test_data.txt")
	if err != nil {
		t.Fatalf("Failed to read file: %v", err)
	}

	// Проверяем содержимое файла
	content := string(data)
	if !strings.Contains(content, "name Alice") || !strings.Contains(content, "age 30") {
		t.Errorf("File content is incorrect: %s", content)
	}
}
