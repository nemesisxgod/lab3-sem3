package hash

import (
	"encoding/gob"
	"fmt"
	"os"
	"strings"
)

func (ht *HashTable) SaveToTextFile(filename string) error {
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
		return fmt.Errorf("error saving to text file: %v", err)
	}
	return nil
}

// LoadFromTextFile - загрузка данных из текстового файла
func (ht *HashTable) LoadFromTextFile(filename string) error {
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

func (ht *HashTable) SaveToBinaryFile(filename string) error {
	// Создаем временную структуру для хранения только непустых ячеек
	var nonEmptyNodes []*Node
	for i := 0; i < TableSize; i++ {
		current := ht.Table[i]
		// Добавляем в срез только непустые узлы
		for current != nil {
			nonEmptyNodes = append(nonEmptyNodes, current)
			current = current.Next
		}
	}

	// Создание бинарного файла
	file, err := os.Create(filename)
	if err != nil {
		return fmt.Errorf("error creating binary file: %v", err)
	}
	defer file.Close()

	// Сериализация в бинарный формат
	encoder := gob.NewEncoder(file)
	err = encoder.Encode(nonEmptyNodes) // Сохраняем только непустые узлы
	if err != nil {
		return fmt.Errorf("error encoding to binary: %v", err)
	}

	return nil
}

// LoadFromBinaryFile - загрузка данных из бинарного файла с использованием gob
func (ht *HashTable) LoadFromBinaryFile(filename string) error {
	file, err := os.Open(filename)
	if err != nil {
		return fmt.Errorf("error opening binary file: %v", err)
	}
	defer file.Close()

	decoder := gob.NewDecoder(file)
	var nonEmptyNodes []*Node
	err = decoder.Decode(&nonEmptyNodes)
	if err != nil {
		return fmt.Errorf("error decoding binary data: %v", err)
	}

	// Восстанавливаем только непустые элементы
	ht.Clear()
	for _, node := range nonEmptyNodes {
		ht.Insert(node.Key, node.Value)
	}

	return nil
}
