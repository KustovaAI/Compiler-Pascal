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
	void ToPostfix( THash1Table * table);			//привести к постфиксному виду
	void Delete_Space();							//удаление пробелов	
	int Check_Parentheses(const string& c)const;	//счёт скобок
	int Check_Str();								//проверка строки на правильность
	string Is_Unary_operation(int &i);				//проверка на унарную операцию в инфиксе
	string Is_Unary_operation2(int &i);				//проверка на унарную операцию в постфиксе
	bool Is_Operator(char c);						//является ли символ оператором	
	int Priority(string c);							//получить приоритет оператора	
	string Is_mod_or_div(int &i);					//является ли строка mod или div
	double Calculate(THash1Table* table, string _type); // вычисление по постфиксной форме
};


