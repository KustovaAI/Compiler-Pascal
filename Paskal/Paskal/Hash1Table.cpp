#include "Hash1Table.h"
#include <string>
#include <iostream>

THash1Table::THash1Table()
{
	size_buf = 25;
	step = 7;
	Data = new TNote[size_buf];				//создание массива
	for (int i = 0; i < size_buf; i++)		//сделать статус всех записей - строка свободна
	{
		Data[i].check = 0;
	}
}
THash1Table :: ~THash1Table()
{
	delete[] Data;
	size_buf = 0;
}

int THash1Table::HashFunc(const TKey h)		//хэш-функция
{
	long long int res = 0;
	int t;
	string s;
	for (int i = 0; i < h.length(); i++)
	{
		t = 1;
		s = to_string(h[i] - '0');
		//s = To_Str();			//s - номер буквы в таблице символов
		for (int i = 0; i < s.length(); i++)
		{
			t = t * 10;
		}
		res = res * t + h[i] - '0';		//res - подряд идущие номера символов key из таблицы символов
	}
	int k = sqrt(res * 3.14);
	return k;
}


TNote * THash1Table::Search(const TKey & key)	// поиск по ключу, возвращет запись в таблице
{
	Curpos = HashFunc(key) % size_buf;			//установка текущую позицию строки
	for (int i = 0; i < size_buf; i++)
	{
		if (Data[Curpos].check == 0) break;		//если строка всегда была и есть пуста
		else if ((Data[Curpos].key == key) && (Data[Curpos].check == 1))	//если ключи совпадают и строка занята	
			return &Data[Curpos];
		Curpos = GetNextPos(Curpos);			//установить новую текущую позицию
	}
	return nullptr;
}

void THash1Table::Insert(const TNote & note)	//вставка
{
	if (Search(note.key) != nullptr) throw ("A polinom whith such key already exist");	//если полином с таким ключом существует - исключение
	if (length == size_buf) cout << "В таблице нет места";
	else
	{
		Curpos = HashFunc(note.key) % size_buf;		//установление текущей позиции
		for (int i = 0; i < size_buf; i++)
		{
			if (Data[Curpos].check == 0)		//если строка пустая
			{
				Data[Curpos] = note;			//вставка записи
				Data[Curpos].check = 1;			//исзменение параметра строки - занята
				length++;		//изменение к-ва строк
				break;							//выход из цикла
			}
			else Curpos = GetNextPos(Curpos);	//установление новой текущей позиции
		}

	}
}

void THash1Table::Print()									//вывод таблицы на экран
{
	if (length == 0) cout << "Таблица Hash1Table пуста" << endl;
	else
	{
		cout << "Таблица Hash1Table: " << endl;
		for (int i = 0; i < size_buf; i++)
			if (Data[i].check == 1)								//если строка занята - вывод на экран
				cout << "Key: " << Data[i].key << "	Val: " << Data[i].val << endl;
	}
}

void THash1Table::ReadFile(string filename)			//чтение файла
{
	int size = 0;
	ifstream is;
	is.open(filename);								// открытие файла
	string name, str;
	
	is >> size;										//чтение к-ва записей
	for (int i = 0; i < size; i++)
	{
		is >> name >> str;							//чтение содержимого 
		//cout << name << " " << str << endl;			//вывод содержимого на экран
		TNote s1(name, str, "");
		//THash1Table();								
		Insert(s1);									//вставка записи в таблицу
	}
	is.close();										//закрытие файла
}


void THash1Table::Delete(const TKey & key)		//Удаление без возможности отмены
{
	if (length == 0) throw ("negative");					//если к-во записей = 0 - исключение
	TNote * s = Search(key);									//поиск записи
	if (s == nullptr) throw ("There is no note whith such key");//если запись не найдена - исключение
	s->check = 2;												//помечаем запись как удалённую
	length--;									//уменьшаем к-во записей
}

void THash1Table::Set_Val(const TKey & key, string _val)		//установка значения переменной
{
	TNote * s = Search(key);
	if (s == nullptr) throw ("There is no note whith such key");		//если не нашли по ключу
	s->val = _val;
	
}

void THash1Table::Set_Type(const TKey & key, string _type)		//установка типа переменной
{
	TNote * s = Search(key);
	if (s == nullptr) throw ("There is no note whith such key");		//если не нашли по ключу
	s->type = _type;
}