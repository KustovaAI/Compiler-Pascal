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
	string val;		//значение
	string type;		//значение

	int check;	//0 - строка свободна, 1 - строка занята, 2 - строка была удалена, 3 - строка была удалена с возможностью отмены
	TNote() {}
	TNote(TKey _key, string _val, string _type)
	{
		key = _key;
		val = _val;
		type = _type;
		check = 0;
	}
};
class  THash1Table 
{
	TNote *Data;	//память для записей таблицы
	int size_buf;	//максимально возможное к-во записей
	int step;		//шаг вторичного перемешивания
	int Curpos;		//номер текущей записи		
	int length;         // количество записей в таблице
private:
	int GetNextPos(int pos) { return (pos + step) % size_buf; }		//генератор новой позиции
	int HashFunc(const TKey key);									//хэш-функция
public:
	THash1Table();
	~THash1Table();

	TNote * Search(const TKey& key);								// поиск по ключу, возвращет запись в таблице	
	void Insert(const TNote& note);								    // вставка записи в таблицу
	void ReadFile(string filename);									//чтение файла	
	void Delete(const TKey& key);								   // удаление по ключу без отмены
	void Set_Val(const TKey& key, string _val);						//установить значение
	void Set_Type(const TKey& key, string _type);					//установить тип переменной
	void Print();													//вывод на экран
};