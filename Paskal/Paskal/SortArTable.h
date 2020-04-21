#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

typedef string TKey;

struct TNote             // запись о переменной
{
	TKey key;		//имя переменной
	string val ;		//значение
	
//	int check;	//0 - строка свободна, 1 - строка занята, 2 - строка была удалена, 3 - строка была удалена с возможностью отмены
	TNote() {}
	TNote(TKey _key, string _val)
	{
		key = _key;
		val = _val;		
		//check = 0;
	}
};
// добавление/удаление происходит без нарушения упорядоченности
// записи при необходимости перепаковываются
// таким образом в любой момент времени таблица упорядочена
// порядок возрастающий
// используется бинарный поиск так как записи упорядочены
class  TSortArTable 
{
	TNote *Data;	// данные
	int size_buf;	// размер буфера
	unsigned int length;         // количество записей в таблице

public:
	TSortArTable();
	~TSortArTable();

	TNote * Search(const TKey& key);					// поиск по ключу, возвращет запись в таблице	
	void Insert(const TNote& note);						// вставка записи в таблицу	
	void Delete(const TKey& key);      // удаление по ключу 	
	void Print();										//вывод записей на экран
	void ReadFile(string filename);
};
