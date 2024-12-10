package main

import (
	"fmt"
	hash "lab3-sem3/golang"
	"log"
)

func main() {
	// Создаем хэш-таблицу и добавляем элементы
	ht := &hash.HashTable{}
	ht.Insert("name", "Alice")
	ht.Insert("age", "30")

	// Сериализация в текстовый файл
	err := ht.SaveToTextFile("hash_table.txt")
	if err != nil {
		log.Fatalf("Error saving to text file: %v", err)
	}

	// Создаем новую хэш-таблицу
	loadedHTText := &hash.HashTable{}

	// Загружаем данные из текстового файла
	err = loadedHTText.LoadFromTextFile("hash_table.txt")
	if err != nil {
		log.Fatalf("Error loading from text file: %v", err)
	}

	// Печатаем загруженную хэш-таблицу
	fmt.Print("TXT\n")
	loadedHTText.Print()

	// Сериализация в бинарный файл
	err = ht.SaveToBinaryFile("hash_table.bin")
	if err != nil {
		log.Fatalf("Error saving to binary file: %v", err)
	}

	// Создаем новую хэш-таблицу
	loadedHTBinary := &hash.HashTable{}

	// Загружаем данные из бинарного файла
	err = loadedHTBinary.LoadFromBinaryFile("hash_table.bin")
	if err != nil {
		log.Fatalf("Error loading from binary file: %v", err)
	}

	// Печатаем загруженную хэш-таблицу
	fmt.Print("Bin\n")
	loadedHTBinary.Print()
}
