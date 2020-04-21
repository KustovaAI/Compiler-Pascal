#include "SortArTable.h"

TSortArTable::TSortArTable()
{
	length = 0;
	size_buf = 10;
	Data = new TNote[size_buf];
}

TSortArTable::~TSortArTable()
{
	delete[] Data;
}

void TSortArTable::ReadFile(string filename)
{
	int size = 0;
	string _key, _val;
	cout << "SortArTable: " << endl;
	ifstream is;
	is.open(filename);						//открытие файла
	is >> size;								//чтение к-ва записей
	delete[] Data;
	Data = new TNote[size_buf];				//создание массива
	length = size;
	for (int i = 0; i < size; i++)			//запись содержимого файла в массив
	{
		is >>_key >> _val;	
		TNote s(_key, _val);
		Insert(s);		
	}
	for (int i = 0; i < size; i++)			//запись содержимого файла в массив
	{
		cout << Data[i].key << endl;
	}
	is.close();								//закрытие файла
}

TNote * TSortArTable::Search(const TKey & key)
{
	int l, r, cur;
	l = 0; r = length - 1; cur = (l + r) / 2;
	while (l <= r)
	{
		if (Data[cur].key == key)
		{
			return &Data[cur];
		}
		else if (Data[cur].key < key)
		{
			l = cur + 1;

		}
		else
		{
			r = cur - 1;
		}
		cur = (l + r) / 2;
	}
	// не найдено
	return nullptr;
}

void TSortArTable::Insert(const TNote & note)
{
	// вставить нужно с учетом упор€доченности при сдвинув все что правее
	// дл€ поиска правильного места используетс€ тот же бинарный поиск
	int l, r, cur;
	l = 0; r = length - 1; cur = (l + r) / 2;
	while (l <= r)
	{
		if (Data[cur].key == note.key)
		{
			throw ("A polinom whith such key already exist");
		}
		else if (Data[cur].key < note.key)
		{
			l = cur + 1;

		}
		else
		{
			r = cur - 1;
		}
		cur = (l + r) / 2;
	}
	// нашли место оно = большему из l и r
	cur = l > r ? l : r;
	length++;
	if (length > size_buf) // проверка на необходимость увеличени€ буфера
	{
		size_buf *= 2;
		TNote* tmp = new TNote[size_buf];
		int i = 0;
		while (i < cur)
		{
			tmp[i] = Data[i];
			i++;
		}
		tmp[i] = note;
		
		i++;
		while (i < length - 1)
		{
			tmp[i] = Data[i - 1];
			i++;
		}
		delete[] Data;
		Data = tmp;
		return;
	}
	// места в буфере хватает - необходимо сдивнуть на 1 вправо большие записи
	for (int i = length - 1; i > cur; i--)
	{
		Data[i] = Data[i - 1];
	}
	Data[cur] = note;	
	return;
}

void TSortArTable::Delete(const TKey & key)
{
	TNote* n = Search(key);
	if (n == nullptr)
		throw "There is no element whith such key";
	int i = n - Data;   // нашли индекс записи в буфере
	for (; i < length - 1; i++)
	{
		Data[i] = Data[i + 1];
	}	
	length--;
}

void TSortArTable::Print()
{
	if (length == 0) cout << "“аблица LinArTable пуста" << endl;
	else
	{
		cout << "“аблица LinArArr: " << endl;
		for (int i = 0; i < length; i++)			
				cout << "Key: " << Data[i].key << "	Val: " << Data[i].val << endl;
	}
}



