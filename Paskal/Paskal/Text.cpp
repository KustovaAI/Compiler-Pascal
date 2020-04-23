#include "Text.h"
#include "Hierarchy_List.h"
#include <stack>
#include "Postfix.h"
TText::TText()
{
	keywords.ReadFile("Keywords.txt");
	count_line = 0;
	count_begin = 0;
}

//����������//

void TText::Read_and_out_file(string filename)		//������ � ����� �� ����� ����������� �����
{
	string line;	
	ifstream is;
	int count = 0;
	is.open(filename);						//�������� �����	
	cout << "����� ���������: " << endl;
	while (getline(is, line))
	{		
		cout << line << endl;
		count++;
	}
	is.close();								//�������� �����
	cout << "��������� ���������: " << endl;
	Enter_line_to_list(filename,count);
}
void TText::Enter_Programm()
{
	string line = "";	
	int count = 0;			
	ofstream os;												//�������� �����
	os.open("Tmp.txt", ios_base::trunc);							//�������� ������� �� �����
	os.close();													//�������� �����
	os.open("Tmp.txt", ios_base::app);							//������ � ����
	cout << "������� ����� ���������, ��� ��������� ����� ������� -1 " << endl;	
	getline(cin, line);																			//?????????????????
	while (line != "-1")
	{
		getline(cin, line);
		if (line != "-1")
		{
			os << line << endl;
			count++;
		}
	}
	os.close();													//�������� �����
	cout << "��������� ���������: " << endl;
	Enter_line_to_list("Tmp.txt", count);						//��������� ����� � ������
}


void TText::Check_End_Line(string line)							//�������� ������ �� ;
{
	if (line != "")
	{
		string tmp;
		int j = line.length() - 1;
		while ((tmp == "") && (j > 0))
		{
			if ((line[j] != ' ') && (line[j] != '\t'))tmp += line[j];			//���� ������ �� ������ � �� ���������
			j--;
		}
		if (tmp != ";") throw ("Error of end line");
	}
}

string TText::Delete_space_before_and_after_keywords(string line)				//�������� �������� �� � ����� �������� ����
{
	string tmp = "";
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ' ') && (line[i] != '\t')) tmp += line[i];				//���� ������ �� ������ � �� ��������� 
	}
	return tmp;
}

string TText::Get_the_beginning_of_the_word(string str, int & j)				//��������� ��������� ����� �� ������ ������ � ��� ������ ��� ��� ����������
{
	string tmp = "";
	while ((keywords.Search(tmp) == nullptr) && (j < str.length()))
	{
		if ((str[j] != ' ') && (str[j] != '\t'))	tmp += str[j];				//���� ������ - �� ������ � �� ���������
		j++;
	}
	return tmp;
}

void TText::Enter_line_to_list(string filename, int n)			//���� ����� � ������
{		
	int c = 1;		
	int count_end = 0;
	bool Down_one_line = false;			//���� = true, �� ��������� ������ ������������ �� ������� ����
	bool Dont_read_next_line = false;	//���� true, �� �� �������� ��������� ������
	string str;			//������� ������
	ifstream is;
	is.open(filename);						//�������� �����	
	for (int i = 0; i < n; i++)
	{
		string tmp = "";
		int j = 0;
		if (Dont_read_next_line == false) getline(is,str);	
		else
		{
			Dont_read_next_line = false;
			i--;
		}
		tmp = Get_the_beginning_of_the_word(str, j);
		if (Delete_space_before_and_after_keywords(tmp) == "") continue;	//���� ������ ������� - ����������
		//Program
		if ((list.Is_Empty()) && (tmp != "program")) throw ("In the first line no program");	//���� "program" �� �� ���� �����		
		else if ((list.Is_Empty()) && (tmp == "program"))
		{
			Check_End_Line(str);		//�������� �� ;
			list.InsertFirst(str);		//������� � ������
			count_line++;		
			continue;
		}
		//const & var
		if (((tmp == "const") || (tmp == "var")) && (count_begin > 0)) throw ("'const'/'var' after begin");
		else if ((tmp == "const") || (tmp == "var"))
		{			
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after const/var");		//���� ����� ���� const, var ���-������ ��������
			list.Insert_Next_Line(Delete_space_before_and_after_keywords(str));		//�������	
			count_line++;		
			getline(is,str);		//������ ������ ������ ����� var/const
			tmp = "";
			i++;			
			j = 0;			
			tmp = Get_the_beginning_of_the_word(str, j);		//�������� �������� ����� � ������ ������ ��� ���� ������
			if (j != str.length())  throw ("Error const/var"); //���� ����� const/var ��� �������� �����
			else
			{
				Check_End_Line(str);			//�������� �� ;
				list.Insert_Down_Line(str);		//������� �� ������� ����
				count_line++;
			}
			//������ ��������� ������ ����� ���������� ���������� const/var � ���� ��� ���� ���������� ���������� ��������� Next_Line
			while (1)
			{	
				tmp = "";
				getline(is,str);		//������ ����� ������
				i++;
				j = 0;
				tmp = Get_the_beginning_of_the_word(str, j);				//�������� �������� ����� � ������ ������ ��� ���� ������
				if ((tmp == "begin") || (tmp == "var") || (tmp == "const"))//���� ����� const/var ��� �������� �����
				{
					Dont_read_next_line = true;		//�� ������ ��������� ������
					break;
				}
						
				else if (j  != str.length())  throw ("Error const/var");				//���� ��� �����-�� ������ ������� �� ������ �������� ����
				else
				{
					Check_End_Line(str);			//�������� �� ;
					list.Insert_Next_Line(str);		//������ ��������� ������		
					count_line++;
				}				
			}
			list.Go_Parent();		//������������ �� ������� const	/var	
			continue;
		}		

		//begin		
		if (tmp == "begin")
		{
			if (list.Get_Current_Line() == "begin")  throw ("After begin goes begin");
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after begin");
			if ((Down_one_line == false) && (count_begin != 0))throw ("Error begin");		//���� begin �� �������� ���� � ����� �� � ������ ���������
			list.Insert_Next_Line(Delete_space_before_and_after_keywords(str));		//��������� ������
			count_begin++;
			count_line++;					
			Down_one_line = true;		//��������� ������ ����� ����� �������� �� ������� ����	
			continue;
		}
		//end
		if (tmp == "end")
		{
			if (list.Get_Current_Line() == "begin") throw ("After begin goes end");
			list.Go_Parent();		//��������� � ��������
			string tmp1 = Delete_space_before_and_after_keywords(str);
			if ((tmp1 != "end") && (tmp1 != "end.")) throw ("Error end");			
			list.Insert_Next_Line(tmp1);		//��������� ��������� �������
			count_end++;
			count_line++;		
			continue;
		}
		//if/else
		if ((tmp == "else") || (tmp == "if"))
		{
			if (Down_one_line == true)		//���� ������ ����� �������� �� ������� ����
			{
				if (tmp == "else") throw ("Error else");		//���� ����� if ����� ��� else
				else	
				{
					list.Insert_Down_Line(str);					//������� ������ �� ������� ����
					Down_one_line = true;						//��������� ������ ����� ����� �������� �� ������� ����
					count_line++;
					list.Set_check(c);							//������������� check
					c++;										//����������� ����� ��� ���������� check
				}
				continue;
			}
			else
			{
				list.Insert_Next_Line(str);						//��������� ��������� ������
				count_line++;
				Down_one_line = true;							//��������� ������ ����� ����� �������� �� ������� ����
				if (tmp == "if")
				{
					list.Set_check(c);							//������������� check
					c++;										//����������� ����� ��� ���������� check
				}
				else				
					list.Set_check(list.Get_check_prev_if());			//���� ��� else - � check ������ �� ����� ���������������� if	
				continue;
			}
		}				
		else
		{
			Check_End_Line(str);							//�������� �� ;
			if (Down_one_line == true)						//���� ������ ����� �������� �� ������� ����
			{
				if (list.Get_Current_Line() != "begin")		//���� ����� ��������� ��������� ����� ���� ������
				{
					list.Insert_Down_Line(str);				//������� ������ �� ������� ����
					count_line++;
					Down_one_line = false;					//��������� ������ ����� ��������� �� ��� �� ������
					list.Go_Parent();						//����������� � ��������
				}
				else
				{
					list.Insert_Down_Line(str);				//������� ������ �� ������� ����
					count_line++;
					Down_one_line = false;					//��������� ������ ����� ��������� �� ��� �� ������
				}
			}
			else
			{
				list.Insert_Next_Line(str);					//������� ������ �� ��� �� ������
				count_line++;
			}
		}
	}
	if (count_begin != count_end) throw("Different count of begin and end");
	is.close();			//�������� �����
}

string TText::Read_before_symbol(string str, int & j, char symbol)
{
	string tmp = "";
	while ((str[j] != symbol) && (j < str.length()))		//����� ���������� �� :
	{
		if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
		j++;
	}
	return tmp;
}

void TText::Line_processing()				//��������� �����
{
	list.ReSetCur();						//������������ � ������ ������
	const string comparison = "<>=";	
	string tmp = "";
	int j = 0;
	int arr[20];		//�� ������ ������ check ������� if, ������� ����� �������� �������� �������, �������� 1, ���� ������� ����������� � 0 - ���� �� �����������
	//������ �������
	string str = list.Get_Current_Line();		//������ ������	
	tmp = Get_the_beginning_of_the_word(str, j);	//�������� �������� ����� � ������ ������ ��� ��� ������	
	if ((str[j] != ' ') && (str[j] != '\t')) throw ("Error: There is no space after 'program'");
	j++;
	string tmp1 = "";
	tmp1 = Read_before_symbol(str, j, ';');	//������ ��� program	
	if (tmp1 == "") throw ("Error: There is no program name");
	list.Go();		//��������� �� ������ ����
	
	//------------------------------------------
	for (int i = 0; i < count_line; i++)
	{
		tmp = "";
		j = 0;
		str = list.Get_Current_Line();		//������ ������	
		while ((keywords.Search(tmp) == nullptr) && (j < str.length())) //������ �������
		{
			if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
			j++;
		}
		if (keywords.Search(tmp) == nullptr) //���� �� ����� ����� � ��������
		{
			tmp = "";
			j = 0;
			while ((variables.Search(tmp) == nullptr) && (j < str.length())) //������ �������
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
				j++;
			}
		}
		//const--------------------
		if (tmp == "const")
		{
			string tmp1 = "";			
			list.Go();		//��������� � ��������� �������
			str = list.Get_Current_Line();
			while (1)
			{	
				tmp = "";				
				string name;
				string _type;
				j = 0;
				//������ �����
				tmp = Read_before_symbol(str, j, ':');	//������ ���������� �� :				
				if (j == str.length()) throw ("Error of variable declaration");		//���� ��� :
				if (variables.Search(tmp) != nullptr) throw ("Error: reclaim variables");		//���� ��������� ���������� ����������
				name = tmp;	
				j++;
				//������ ����
				tmp = "";
				tmp = Read_before_symbol(str, j, '=');		//������ �� =				
				if (j == str.length()) throw ("Error of variable declaration");
				if (tmp == "integer") _type = "const integer";
				else if (tmp == "double") _type = "const double";
				else throw ("Error: wrong type of constant");
				//������ ��������
				tmp = "";
				j++;
				tmp = Read_before_symbol(str, j, ';');		//������ �� ;				
				if (tmp == "") throw ("Error of variable declaration");
				double f;				//������� � double
				try
				{
					f = stod(tmp, 0);

				}
				catch (const char* s)
				{
					cout << "Error const";
				}				
				double *x1 = &f;
				double x = modf(f, x1);
				if ((_type == "const integer") && (x != 0)) throw ("�� ������������ �����");			//���� ���� ������� �����	
				//������� ���������� � �������
				TNote s(name, tmp, _type);
				variables.Insert(s);
				list.Go();		//������� � ��������� ������
				str = list.Get_Current_Line();				
				if ((str == "var") || (str == "const") || (str == "begin")) break;
			}		
			continue;
		}
		//------------------
		//var
		if (tmp == "var")
		{
			string tmp1 = "";			
			list.Go();
			str = list.Get_Current_Line();		//�������� ������� ��������
			while (1)
			{					
				stack<string> ar;
				string _type;
				j = 0;
				while ((str[j] != ':') && (j < str.length()))			//������ �� :
				{
					tmp = "";
					while (((str[j] != ',') && (str[j] != ':')) && (j < str.length()))		//������ �� ���������, ���� �� �������
					{
						if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
						j++;
					}
					if (j == str.length()) throw ("Error of variable declaration");
					if (variables.Search(tmp) != nullptr) throw ("Error: reclaim variables");		//��������� ���������� ����������
					ar.push(tmp);			//���� ���������� � ����
					if (str[j] == ':')		//���� ���� ���������� ��������
					{
						j++;
						break;
					}
					else j++;
				}
				tmp = "";
				tmp = Read_before_symbol(str, j, ';');	//������ �� ;							
				if (tmp == "integer") _type = "integer";
				else if (tmp == "double") _type = "double";
				else throw ("Error: wrong type of variable");
				//������� ���������� � �������
				while (!ar.empty())
				{
					TNote s(ar.top(), "", _type);					
					variables.Insert(s);					
					ar.pop();
				}				
				list.Go();	//������� � ��������� ������
				str = list.Get_Current_Line();
				if ((str == "var") || (str == "const") || (str == "begin")) break;
			}
			continue;
		}
		//---------------------
		if (tmp == "begin")
		{				
			list.GoDown();		//������� �� ����������
			continue;
		}
		//---------------------------
		//end
		if (tmp == "end")
		{
			if (str == "end.") break;
			list.Go();			//������� �� ��������� ������
			continue;
		}
		//---------------------------
		//�������� � �����������
		if (variables.Search(tmp) != nullptr)	
		{
			if ((variables.Search(tmp)->type == "const integer") || (variables.Search(tmp)->type == "const double"))
				throw ("Error: operation with constants");		//���� ������� ������������ ����������� ����������
			string tmp1 = "";
			tmp1 = Read_before_symbol(str, j, '=');		//������ �� =			
			if (j == str.length()) throw ("Error of assignment operation");
			tmp1 += str[j];
			j++;
			if (tmp1 != ":=") throw ("Error of assignment operation");
			tmp1 = "";
			tmp1 = Read_before_symbol(str, j, ';');		//������ �� ;			
			TPostfix p(tmp1);
			p.ToPostfix(&variables);
			double res = p.Calculate(&variables, variables.Search(tmp)->type);
			if (variables.Search(tmp)->type == "integer")
				variables.Set_Val(tmp, to_string((int)res));
			else
				variables.Set_Val(tmp, to_string(res));
			list.Go();
			continue;
		}
		///-------------------
		//Write
		if (tmp == "Write")
		{			
			string tmp1 = "";
			string text = "";
			tmp1 = Read_before_symbol(str, j, '(');		//������ �� (	
			if (j == str.length()) throw ("Error of Write");
			tmp1 += str[j];
			if ((tmp1.length() != 1) || (tmp1[0] != '(')) throw ("Error Write");			
			j++;
			while ((str[j] != ')') && (j < str.length()))		//������ �� )
			{
				tmp = "";				
				while (((str[j] != ',') && (str[j] != ')')) && (j < str.length()))		//������ �� , ��� �� )
				{
					if (tmp == "")
					{
						if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
					}
					else tmp += str[j];					
					j++;
				}
				//�������� �������� ����� tmp
				int k = tmp.length() - 1;
				string tmp1 = "";
				while ((tmp[k] == ' ') || (tmp[k] == '\t'))
				{
					k--;
				}
				for (int i = 0; i <= k; i++)
					tmp1 += tmp[i];
				tmp = tmp1;
				if (j == str.length()) throw ("Error of write");
				if ((tmp[0] == '"') && (tmp[tmp.length() - 1] == '"'))		//���� ����� ����� � ��������
				{
					if (tmp.length() < 3) throw("Error Write");		//���� ������ �������
					for (int k = 1; k < tmp.length() - 1; k++)
						cout << tmp[k];				//����� �����������					
				}
				else
				{				//���� ����� ����������
					if (variables.Search(tmp) == nullptr) throw ("Error: Write");		//���� �� ����� ��������� ����������
					cout << variables.Search(tmp)->val;				//����� �������� ����������
				}				
				if (str[j] == ')')		//���� ����� ��������
				{
					j++;
					break;
				}
				else j++;
			}
			tmp = "";
			tmp = Read_before_symbol(str, j, ';');			//������ �� ;			
			if (tmp != "") throw ("Error Write");						
			list.Go();		//������� � ��������� ������
			continue;
		}
		//----------------------
		//Read
		if (tmp == "Read")
		{
			string tmp1 = "";
			string text = "";
			tmp1 = Read_before_symbol(str, j, '(');		//������ ������� �� (
			tmp1 += str[j];
			if (tmp1 != "(") throw ("Error Read");
			int t = j + 1;
			j = str.length() - 1;
			tmp1 = "";
			//������� �� ������ ������� ������
			while ((str[j] != ')') && (j > t))
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j--;
			}
			if (j == t) throw ("Error Read");			//���� � ������� �����			
			tmp1 = "";
			for (int k = t; k < j; k++)		//������ ����������
			{
				tmp1 += str[k];
			}
			if (variables.Search(tmp1) == nullptr) throw ("Error Read");	//���� ���������� �� ���������
			cin >> text;			
			double s;
			try
			{
				s = stod(text, 0);				
				
			}
			catch (const char* s)
			{
				cout << "Error Read";
			}
			double *x1 = &s;
			double x = modf(s, x1);
			if ((variables.Search(tmp1)->type == "integer") && (x != 0)) throw ("�� ������������ �����");			
			variables.Set_Val(tmp1, text);		//������������� �������� ����������
			list.Go();		//������� � ��������� ������
			continue;
		}
		//---------------------------------------
		//if
		if (tmp == "if")
		{
			string left_op = "";
			string right_op = "";
			double left_res, right_res;
			bool res = false;
			string sign = "";
			string tmp1 = "";
			while ((tmp1 != "(") && (j < str.length()))		//������ �� ������
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (j == str.length()) throw ("Error of conditional operation");		//���� ��� ����������� ������
			tmp1 = "";
			while ((comparison.find(str[j]) == string::npos) && (j < str.length()))		//���� �� ����� ���� ���������
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (j == str.length()) throw ("Error of conditional operation");		//���� ����������� ���� ���������
			left_op = tmp1;		//���������� ����� �������
			sign = str[j];		//���������� ���� ���������
			j++;
			tmp1 = "";
			tmp1 = Read_before_symbol(str, j, ')');			//������ �� )			
			if (j == str.length()) throw ("Error of conditional operation");
			j++;
			right_op = tmp1;	//���������� ������ �������
			tmp1 = "";
			while (j < str.length())		//������ ���������� �����
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (tmp1 != "then") throw ("Absence of 'then'");
			//����������
			TPostfix p1(left_op), p2(right_op);
			p1.ToPostfix(&variables);
			p2.ToPostfix(&variables);
			left_res = p1.Calculate(&variables, "double");
			right_res = p2.Calculate(&variables, "double");
			if (sign == "=")
			{
				if (left_res == right_res) res = true;
				else res = false;
			}
			else if (sign == "<")
			{
				if (left_res < right_res) res = true;
				else res = false;
			}
			if (sign == ">")
			{
				if (left_res > right_res) res = true;
				else res = false;
			}
			if (res == true)
			{				
				arr[list.Get_check()] = 1;		//������������� ���������������� if �������� - 1 - ������� �����������
				list.Go();						//��������� � ����������
				continue;
			}
			else
			{
				
				arr[list.Get_check()] = 2;		//������������� ���������������� if �������� - 2 - ������� �� �����������
				list.Go_throw_down();			//������� ����������
				continue;
			}
		}
		//------------------------------
		//else
		if (tmp == "else")
		{
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after else");
			if (arr[list.Get_check()] == 1)		//���� � ���������������� if ����������� �������
			{
				list.Go_throw_down();			//������� ����������	
				continue;
			}
			else if (arr[list.Get_check()] == 0) throw ("Error else");		//���� � ���������������� if �� ����������� �������
			else
			{				
				list.Go();		//��������� � ����������
				continue;
			}
		}
		else throw("Unknown line");
	}
}
	