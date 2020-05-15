#pragma once

#include <string>
#include "Hash1Table.h"

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
public:
	TPostfix(string _c);
	TPostfix();
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	void ToPostfix( THash1Table * table);			//�������� � ������������ ����
	void Delete_Space();							//�������� ��������	
	int Check_Parentheses(const string& c)const;	//���� ������
	int Check_Str();								//�������� ������ �� ������������
	string Is_Unary_operation(int &i);				//�������� �� ������� �������� � �������
	string Is_Unary_operation2(int &i);				//�������� �� ������� �������� � ���������
	bool Is_Operator(char c);						//�������� �� ������ ����������	
	int Priority(string c);							//�������� ��������� ���������	
	string Is_mod_or_div(int &i);					//�������� �� ������ mod ��� div
	double Calculate(THash1Table* table, string _type); // ���������� �� ����������� �����
};


