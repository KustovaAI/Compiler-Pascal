#include "Postfix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <locale>
#include <algorithm>
#include <vector>
#include <stack>
TPostfix::TPostfix(string _c)
{
	infix = _c;
}
TPostfix::TPostfix()
{
	infix = "";
}
bool TPostfix::Is_Operator(char c)
{
	const string operators = "+-*/()";
	if (operators.find(c) == string::npos)
		return 0;
	return 1;
}

int TPostfix::Priority(string c)		//����������� �����������
{
	int res = -1;
	if (c == "(")
		res = 1;
	if ((c == "-") || (c == "+"))
		res = 2;
	if ((c == "*") || (c == "/") || (c == "mod") || (c == "div"))
		res = 3;
	if ((c == "sin") || (c == "cos") || (c == "tg") || (c == "ctg") || (c == "ln"))
		res = 4;
	return res;
}

void TPostfix::Delete_Space()	//�������� ��������
{
	string c1 = "";
	for (int i = 0; i < infix.length(); i++)
	{
		if (infix[i] != ' ')
			c1 += infix[i];
	}
	infix = c1;
}

int TPostfix::Check_Parentheses(const string & c) const		//��������� �-�� ������
{
	int open = 0;
	int close = 0;
	for (int i = 0; i < c.length();i++)
	{
		if (c[i] == '(')
			open++;
		if (c[i] == ')')
			close++;
	}
	if (open != close) return 0;
	else return 1;

}

int TPostfix::Check_Str()		//��������� �������� ������ �� ������������ �� ������ ��������
{
	if (infix.length() == 0)
		return 0;
	TPostfix p;
	if ((infix.length() == 1) && (p.Is_Operator(infix[0])))
		return 0;
	if ((infix[0] == '*') || (infix[0] == '/'))
		return 0;
	if ((infix[infix.length() - 1] == '*') || (infix[infix.length() - 1] == '/') || (infix[infix.length() - 1] == '-') || (infix[infix.length() - 1] == '+'))
		return 0;

	for (int i = 0; i < infix.length() - 1; i++)
	{
		int j = i + 1;
		if (Is_Unary_operation(i) != "")
		{
			if ((i + 1 == infix.length()) || (infix[i + 1] == ')') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || (infix[i + 1] == '+') || (infix[i + 1] == '-'))
				return 0;
			continue;
		}
		if ((infix[i] == '(') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '*') || (infix[i + 1] == '/') || (infix[i + 1] == '-')))
			return 0;

		if ((infix[i + 1] == ')') && ((infix[i] == '-') || (infix[i] == '+') || (infix[i] == '*') || (infix[i] == '/')))
			return 0;

		if ((infix[i] == '(') && (infix[i + 1] == ')'))
			return 0;

		if ((infix[i] == '+') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '-') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '*') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
		if ((infix[i] == '/') && (Is_Unary_operation(j) == "") && ((infix[i + 1] == '+') || (infix[i + 1] == '-') || (infix[i + 1] == '/') || (infix[i + 1] == ')') || (infix[i + 1] == '*')))
			return 0;
	}
	return 1;
}
string TPostfix::Is_Unary_operation(int &i)		//�������� �� ������� ��������
{
	string tmp = "";
	if ((i < infix.length() - 1) && (((infix[i] == 's') && (infix[i + 1] == 'i') && (infix[i + 2] == 'n'))
		|| ((infix[i] == 'c') && (infix[i + 1] == 'o') && (infix[i + 2] == 's'))
		|| ((infix[i] == 'c') && (infix[i + 1] == 't') && (infix[i + 2] == 'g'))))
	{
		tmp += infix[i];
		tmp += infix[i + 1];
		tmp += infix[i + 2];
		i += 2;
	}
	else if ((i < infix.length() - 2) && (((infix[i] == 't') && (infix[i + 1] == 'g'))
		|| ((infix[i] == 'l') && (infix[i + 1] == 'n'))
		|| ((infix[i] == '+') && (infix[i + 1] == '+'))
		|| ((infix[i] == '-') && (infix[i + 1] == '-'))))
	{
		tmp += infix[i];
		tmp += infix[i + 1];
		i += 1;
	}
	return tmp;
}
string TPostfix::Is_mod_or_div(int & i)		//�������� �� mod � div
{
	string tmp = "";
	if ((i < infix.length() - 1) && (((infix[i] == 'm') && (infix[i + 1] == 'o') && (infix[i + 2] == 'd'))
		|| ((infix[i] == 'd') && (infix[i + 1] == 'i') && (infix[i + 2] == 'v'))))		
	{
		tmp += infix[i];
		tmp += infix[i + 1];
		tmp += infix[i + 2];
		i += 2;
	}
	return tmp;
}
void TPostfix::ToPostfix(THash1Table * table)		//��������� ������ � ����������� �����
{
	if (infix.length() == 0) throw "negative";
	Delete_Space();
	//To_normal();
	if ((Check_Str() == 0) || (Check_Parentheses(infix) == 0)) throw "negative";
	const string operand = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
	const string numbers = "0123456789.";
	stack<string> op;
	stack<string> res;
	string tmp;
	int j;
	string Invert_res_Str = "";
	int len = infix.length();
	for (int i = 0; i < len; i++)
	{

		tmp = "";
		j = i;
		while (((numbers.find(infix[j]) != string::npos)) && (j < infix.length()))		//���� ������ - �����
		{
			tmp += infix[j];
			j++;
		}
		if (tmp.length() > 0)
		{
			res.push(tmp);		//�������� � ����
			i = j - 1;
			continue;
		}
		//----------------
		tmp = Is_Unary_operation(i);
		if (tmp.length() > 0)		//���� ������� ��������
		{
			if ((!op.empty()) && (Priority(tmp) <= Priority(op.top())))
				while ((!op.empty()) && (Priority(tmp) <= Priority(op.top())))
				{
					res.push(op.top());		//�������������� � ����� ���������� � ���� ����������
					op.pop();
				}
			op.push(tmp);		//�������� � ���� ����������
			continue;
		}
		//mod, div
		tmp = Is_mod_or_div(i);
		if (tmp.length() > 0)
		{
			if ((!op.empty()) && (Priority(tmp) <= Priority(op.top())))
				while ((!op.empty()) && (Priority(tmp) <= Priority(op.top())))
				{
					res.push(op.top());		//�������������� � ����� ���������� � ���� ����������
					op.pop();
				}
			op.push(tmp);		//�������� � ���� ����������
			continue;
		}
		
		tmp = "";
		bool ok = false;
		j = i;
		while (((operand.find(infix[j]) != string::npos)) && (j < infix.length()))	//���� ������� - �����	//���� ������� - �����
		{
			tmp += infix[j];
			j++;
			if (table->Search(tmp) != nullptr)
			{
				ok = true;
				break;
			}
		}
		if (tmp.length() > 0)
		{
			if (ok == false) throw ("negative");		//���� �� ��������� ����
			res.push(tmp);
			i = j - 1;
			continue;
		}
		
		string str = "";
		str += infix[i];
		if ((Is_Operator(infix[i])) && (infix[i] != ')'))		//���� ������ - ��������
		{

			if ((!op.empty()) && (Priority(str) <= Priority(op.top())) && (infix[i] != '('))
				while ((!op.empty()) && (Priority(str) <= Priority(op.top())))
				{
					res.push(op.top());	//����� � ���� ���������� �������� �� ����� ��������
					op.pop();
				}
			op.push(str);	//����� �������� � ���� ��������
		}
		

		else if (str == ")")		//���� ����������� ������
		{
			string r = "";
			while ((!op.empty()) && (r != "("))		//����� � ���� ���������� �������� �� ����� ��������, ���� �� ����� �� ����������� ������
			{
				r = op.top();
				op.pop();
				res.push(r);
			}
			if (r == "(")
				res.pop();
		}
		else throw ("negative");
	}

	while (!op.empty())
	{
		res.push(op.top());
		op.pop();
	}
		
	while (!res.empty())
	{
		string s;
		s = res.top();
		res.pop();
		Invert_res_Str += ' ';
		for (int i = s.length() - 1; i >= 0; i--)
			Invert_res_Str += s[i];

	}
	for (int j = Invert_res_Str.length() - 1; j > 0; j--)
	{
		postfix += Invert_res_Str[j];
	}
	
}

double TPostfix::Calculate(THash1Table * table, string _type)
{
	if (postfix == "")
		throw "String is empy";	
	stack <double> res;
	stack <string> res_type;
	string tmp = "";
	const string numbers = "0123456789.";
	const string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	int j;
	int f = 0;	
	double left_op;
	double right_op;
	string left_op_type;
	string right_op_type;	
	int arr2_count = 0;
	string str1 = "";
	for (int i = 0; i < postfix.length(); i++)
	{
		tmp = "";
		j = i;
		while ((postfix[j] != ' ') && (j < postfix.length()))	//�������� ������������
		{
			tmp += postfix[j];
			j++;
		}
		if (numbers.find(tmp[0]) != string::npos)		//���� ��� �����
		{
			double res1 = atof(tmp.c_str());
			res.push(res1);			
			double *x1 = &res1;
			double x = modf(res1, x1);
			//����� � � ����
			if (x != 0) res_type.push("double");	//���� ���� ������� �����
			else res_type.push("integer");
			i = j;
			continue;
		}
		else if (Is_Unary_operation(i) != "")		//���� ������� ��������
		{
			right_op = res.top();		//���� ������ �������
			res.pop();
			right_op_type = res_type.top();		//���� ��� ������� ��������
			res_type.pop();
			if (tmp == "sin")
			{
				res.push(sin(right_op));		//����� ����������� ��������� � ����
				res_type.push("double");		//����� ��� ������������ ���������� � ����
			}
			if (tmp == "cos")
			{
				res.push(cos(right_op));		//����� ����������� ��������� � ����
				res_type.push("double");		//����� ��� ������������ ���������� � ����
			}
			if (tmp == "tg")
			{
				res.push(tan(right_op));		//����� ����������� ��������� � ����
				res_type.push("double");		//����� ��� ������������ ���������� � ����
			}
			if (tmp == "ctg")
			{
				res.push(1 / tan(right_op));	//����� ����������� ��������� � ����
				res_type.push("double");		//����� ��� ������������ ���������� � ����
			}
			if (tmp == "ln")
			{
				if (right_op <= 0) throw "negative";
				res.push(log(right_op));		//����� ����������� ��������� � ����
				res_type.push("double");		//����� ��� ������������ ���������� � ����
			}			
			i = j;

			continue;
		}
		else  if ((alphabet.find(tmp[0]) != string::npos) && (tmp != "mod") && (tmp != "div"))			//���� ��� �������� ����������
		{
			if (table->Search(tmp) == nullptr) throw ("Undeclaring variable");	//���� �� ����� �� �����
			if (table->Search(tmp)->val == "") throw ("uninitialized variable");			//���� �� ��������� ��������		
			res.push(atof((table->Search(tmp)->val).c_str()));				//����� ����������� ����
			if ((table->Search(tmp)->type == "integer") || (table->Search(tmp)->type == "const integer"))
				res_type.push("integer");		//����� ��� ���������� � ����
			else
				res_type.push("double");
			i = i + tmp.length();
			continue;
		}
		right_op = res.top();		//���� ������ �������
		res.pop();
		right_op_type = res_type.top();	//���� ��� ������� ��������
		res_type.pop();
		if ((res.empty()) && (tmp == "-"))	//���� ��������� ��������
		{
			res.push(-right_op);
			res_type.push(right_op_type);
			i++;
			continue;
		}

		left_op = res.top();		//��� ����� �������
		left_op_type = res_type.top();		//���� ��� ������ ��������
		res.pop();
		res_type.pop();
		if (tmp == "div")
		{
			if (right_op == 0) throw ("Divizion by 0");
			if ((right_op_type == "integer") && (left_op_type == "integer"))
			{
				int c = left_op / right_op;
				res.push(c);				//����� ��������� � ����
				res_type.push("integer");	//����� ��� ���������� � ����
			}
			else throw ("Error div");			//���� �������� ������������ ��� �������� �������
		}
		if (tmp == "mod")
		{
			if (right_op == 0) throw ("Divizion by 0");
			if ((right_op_type == "integer") && (left_op_type == "integer"))
			{
				int c = (int)left_op % (int)right_op;
				res.push(c);					//����� ��������� � ����
				res_type.push("integer");		//����� ��� ���������� � ����
			}
			else throw ("Error mod");		//���� �������� ������������ ��� �������� �������
		}
		if (tmp == "+")
		{
			res.push(left_op + right_op);		//����� ��������� � ����
			if ((left_op_type == "double") || (right_op_type == "double"))
				res_type.push("double");		//����� ��� ���������� � ����
			else res_type.push("integer");
		}
		if (tmp == "-")
		{
			res.push(left_op - right_op);		//����� ��������� � ����
			if ((left_op_type == "double") || (right_op_type == "double"))
				res_type.push("double");		//����� ��� ���������� � ����
			else res_type.push("integer");
		}
		if (tmp == "*")
		{
			res.push(left_op * right_op);		//����� ��������� � ����
			if ((left_op_type == "double") || (right_op_type == "double"))
				res_type.push("double");		//����� ��� ���������� � ����
			else res_type.push("integer");
		}		
		if (tmp == "/")
		{
			if (right_op == 0) throw ("Divizion by 0");			
			res.push(left_op / right_op);		//����� ��������� � ����
			res_type.push("double");		//����� ��� ���������� � ����
		}
		i = i + tmp.length();

	}
	double res1 = res.top();
	double *x1 = &res1;
	double x = modf(res1, x1);
	if ((_type == "integer") && (x != 0)) throw ("variable is not integer");	//���� ����� ���������� ����������� ������� ��������
	return res.top();
}
