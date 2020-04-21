#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

typedef string TKey;

struct TNote             // ������ � ����������
{
	TKey key;		//��� ����������
	string val ;		//��������
	
//	int check;	//0 - ������ ��������, 1 - ������ ������, 2 - ������ ���� �������, 3 - ������ ���� ������� � ������������ ������
	TNote() {}
	TNote(TKey _key, string _val)
	{
		key = _key;
		val = _val;		
		//check = 0;
	}
};
// ����������/�������� ���������� ��� ��������� ���������������
// ������ ��� ������������� ����������������
// ����� ������� � ����� ������ ������� ������� �����������
// ������� ������������
// ������������ �������� ����� ��� ��� ������ �����������
class  TSortArTable 
{
	TNote *Data;	// ������
	int size_buf;	// ������ ������
	unsigned int length;         // ���������� ������� � �������

public:
	TSortArTable();
	~TSortArTable();

	TNote * Search(const TKey& key);					// ����� �� �����, ��������� ������ � �������	
	void Insert(const TNote& note);						// ������� ������ � �������	
	void Delete(const TKey& key);      // �������� �� ����� 	
	void Print();										//����� ������� �� �����
	void ReadFile(string filename);
};
