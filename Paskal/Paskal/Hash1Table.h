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
	string val;		//��������
	string type;		//��������

	int check;	//0 - ������ ��������, 1 - ������ ������, 2 - ������ ���� �������, 3 - ������ ���� ������� � ������������ ������
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
	TNote *Data;	//������ ��� ������� �������
	int size_buf;	//����������� ��������� �-�� �������
	int step;		//��� ���������� �������������
	int Curpos;		//����� ������� ������		
	int length;         // ���������� ������� � �������
private:
	int GetNextPos(int pos) { return (pos + step) % size_buf; }		//��������� ����� �������
	int HashFunc(const TKey key);									//���-�������
public:
	THash1Table();
	~THash1Table();

	TNote * Search(const TKey& key);								// ����� �� �����, ��������� ������ � �������	
	void Insert(const TNote& note);								    // ������� ������ � �������
	void ReadFile(string filename);									//������ �����	
	void Delete(const TKey& key);								   // �������� �� ����� ��� ������
	void Set_Val(const TKey& key, string _val);						//���������� ��������
	void Set_Type(const TKey& key, string _type);					//���������� ��� ����������
	void Print();													//����� �� �����
};