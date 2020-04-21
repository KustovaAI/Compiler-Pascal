#include "Hash1Table.h"
#include <string>
#include <iostream>

THash1Table::THash1Table()
{
	size_buf = 25;
	step = 7;
	Data = new TNote[size_buf];				//�������� �������
	for (int i = 0; i < size_buf; i++)		//������� ������ ���� ������� - ������ ��������
	{
		Data[i].check = 0;
	}
}
THash1Table :: ~THash1Table()
{
	delete[] Data;
	size_buf = 0;
}

int THash1Table::HashFunc(const TKey h)		//���-�������
{
	long long int res = 0;
	int t;
	string s;
	for (int i = 0; i < h.length(); i++)
	{
		t = 1;
		s = to_string(h[i] - '0');
		//s = To_Str();			//s - ����� ����� � ������� ��������
		for (int i = 0; i < s.length(); i++)
		{
			t = t * 10;
		}
		res = res * t + h[i] - '0';		//res - ������ ������ ������ �������� key �� ������� ��������
	}
	int k = sqrt(res * 3.14);
	return k;
}


TNote * THash1Table::Search(const TKey & key)	// ����� �� �����, ��������� ������ � �������
{
	Curpos = HashFunc(key) % size_buf;			//��������� ������� ������� ������
	for (int i = 0; i < size_buf; i++)
	{
		if (Data[Curpos].check == 0) break;		//���� ������ ������ ���� � ���� �����
		else if ((Data[Curpos].key == key) && (Data[Curpos].check == 1))	//���� ����� ��������� � ������ ������	
			return &Data[Curpos];
		Curpos = GetNextPos(Curpos);			//���������� ����� ������� �������
	}
	return nullptr;
}

void THash1Table::Insert(const TNote & note)	//�������
{
	if (Search(note.key) != nullptr) throw ("A polinom whith such key already exist");	//���� ������� � ����� ������ ���������� - ����������
	if (length == size_buf) cout << "� ������� ��� �����";
	else
	{
		Curpos = HashFunc(note.key) % size_buf;		//������������ ������� �������
		for (int i = 0; i < size_buf; i++)
		{
			if (Data[Curpos].check == 0)		//���� ������ ������
			{
				Data[Curpos] = note;			//������� ������
				Data[Curpos].check = 1;			//���������� ��������� ������ - ������
				length++;		//��������� �-�� �����
				break;							//����� �� �����
			}
			else Curpos = GetNextPos(Curpos);	//������������ ����� ������� �������
		}

	}
}

void THash1Table::Print()									//����� ������� �� �����
{
	if (length == 0) cout << "������� Hash1Table �����" << endl;
	else
	{
		cout << "������� Hash1Table: " << endl;
		for (int i = 0; i < size_buf; i++)
			if (Data[i].check == 1)								//���� ������ ������ - ����� �� �����
				cout << "Key: " << Data[i].key << "	Val: " << Data[i].val << endl;
	}
}

void THash1Table::ReadFile(string filename)			//������ �����
{
	int size = 0;
	ifstream is;
	is.open(filename);								// �������� �����
	string name, str;
	
	is >> size;										//������ �-�� �������
	for (int i = 0; i < size; i++)
	{
		is >> name >> str;							//������ ����������� 
		//cout << name << " " << str << endl;			//����� ����������� �� �����
		TNote s1(name, str, "");
		//THash1Table();								
		Insert(s1);									//������� ������ � �������
	}
	is.close();										//�������� �����
}


void THash1Table::Delete(const TKey & key)		//�������� ��� ����������� ������
{
	if (length == 0) throw ("negative");					//���� �-�� ������� = 0 - ����������
	TNote * s = Search(key);									//����� ������
	if (s == nullptr) throw ("There is no note whith such key");//���� ������ �� ������� - ����������
	s->check = 2;												//�������� ������ ��� ��������
	length--;									//��������� �-�� �������
}

void THash1Table::Set_Val(const TKey & key, string _val)		//��������� �������� ����������
{
	TNote * s = Search(key);
	if (s == nullptr) throw ("There is no note whith such key");		//���� �� ����� �� �����
	s->val = _val;
	
}

void THash1Table::Set_Type(const TKey & key, string _type)		//��������� ���� ����������
{
	TNote * s = Search(key);
	if (s == nullptr) throw ("There is no note whith such key");		//���� �� ����� �� �����
	s->type = _type;
}