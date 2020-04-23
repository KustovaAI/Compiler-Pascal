#include <iostream>
#include <string>
//#include <Windows.h>
#include <cstdlib>
#include <locale>
#include "Text.h"

using namespace std;

int main()
{
	//SetConsoleCP(1251); //нужна библиотека Windows.h
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");
	TText t;
	string name;
	cout << "			Правила ввода:" << endl;
	cout << "	1)На одной строчке находится одна операция." << endl;
	cout << "	2)Дробная часть числа вводится через запятую." << endl;
	cout << "	3)В секции var присваивание значений не допускается." << endl;
	cout << "	4)Доступны следующие операции над переменными:" << endl;
	cout << "+, -, *, / (для дробных), mod (для целых), div (для целых), sin, cos, tg, ctg, ln" << endl;
	cout << "	5)Если в if содержится только условный оператор содержащий if и else," << endl;
	cout << " то он заключается в begin-end." << endl;
	cout << "	6)В Write русский текст не считывается." << endl;
	cout << "	7) Реализованы чувствительные к регистру функции Read, Write, " << endl;
	cout << "вложенные условные операторы: if, else, со знаками сравнения: <, >, =;" << endl; 
	cout << "присвоение значений переменным и операции над ними." << endl << endl;
	try
	{
		cout << "Выберите: " << endl;
		cout << "1 - Загрузить программу из файла " << endl;
		cout << "2 - Ввести в консоль" << endl;		
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