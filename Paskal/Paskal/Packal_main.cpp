#include <iostream>
#include <string>
//#include <Windows.h>
#include <cstdlib>
#include <locale>
#include "Text.h"

using namespace std;

int main()
{
	//SetConsoleCP(1251); //����� ���������� Windows.h
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	TText t;
	string name;
	cout << "			������� �����:" << endl;
	cout << "	1)�� ����� ������� ��������� ���� ��������." << endl;
	cout << "	2)������� ����� ����� �������� ����� �������." << endl;
	cout << "	3)� ������ var ������������ �������� �� �����������." << endl;
	cout << "	4)�������� ��������� �������� ��� �����������:" << endl;
	cout << "+, -, *, / (��� �������), mod (��� �����), div (��� �����), sin, cos, tg, ctg, ln" << endl;
	cout << "	5)���� � if ���������� ������ �������� �������� ���������� if � else," << endl;
	cout << " �� �� ����������� � begin-end." << endl;
	cout << "	6)� Write ������� ����� �� �����������." << endl;
	cout << "	7) ����������� �������������� � �������� ������� Read, Write, " << endl;
	cout << "��������� �������� ���������: if, else, �� ������� ���������: <, >, =;" << endl; 
	cout << "���������� �������� ���������� � �������� ��� ����." << endl << endl;
	try
	{
		cout << "��������: " << endl;
		cout << "1 - ��������� ��������� �� ����� " << endl;
		cout << "2 - ������ � �������" << endl;		
		cin >> name;
		if (name == "1") t.Read_and_out_file("Paskal.txt");
		else if (name == "2") t.Enter_Programm();
		else throw ("Error of enter");
		t.Line_processing();
	}
	catch (const char* s)
	{
		cout << s << endl;		
	}
	getchar();
	getchar();
	return 0;
}