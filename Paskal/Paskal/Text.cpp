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

//деструктор//

void TText::Read_and_out_file(string filename)		//чтение и вовод на экран содержимого файла
{
	string line;	
	ifstream is;
	int count = 0;
	is.open(filename);						//открытие файла	
	cout << "Текст программы: " << endl;
	while (getline(is, line))
	{		
		cout << line << endl;
		count++;
	}
	is.close();								//закрытие файла
	cout << "Результат обработки: " << endl;
	Enter_line_to_list(filename,count);
}
void TText::Enter_Programm()
{
	string line = "";	
	int count = 0;			
	ofstream os;												//открытие файла
	os.open("Tmp.txt", ios_base::trunc);							//удаление записей из файла
	os.close();													//закрытие файла
	os.open("Tmp.txt", ios_base::app);							//запись в файл
	cout << "Введите текст программы, для окончания ввода введите -1 " << endl;	
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
	os.close();													//закрытие файла
	cout << "Результат обработки: " << endl;
	Enter_line_to_list("Tmp.txt", count);						//занесение строк в список
}


void TText::Check_End_Line(string line)							//проверка строки на ;
{
	if (line != "")
	{
		string tmp;
		int j = line.length() - 1;
		while ((tmp == "") && (j > 0))
		{
			if ((line[j] != ' ') && (line[j] != '\t'))tmp += line[j];			//если символ не пробел и не табуляция
			j--;
		}
		if (tmp != ";") throw ("Error of end line");
	}
}

string TText::Delete_space_before_and_after_keywords(string line)				//удаление пробелов до и после ключевых слов
{
	string tmp = "";
	for (int i = 0; i < line.length(); i++)
	{
		if ((line[i] != ' ') && (line[i] != '\t')) tmp += line[i];				//если символ не пробел и не табуляция 
	}
	return tmp;
}

string TText::Get_the_beginning_of_the_word(string str, int & j)				//получение ключевого слова из начала строки и всю строку при его отсутствии
{
	string tmp = "";
	while ((keywords.Search(tmp) == nullptr) && (j < str.length()))
	{
		if ((str[j] != ' ') && (str[j] != '\t'))	tmp += str[j];				//если символ - не пробел и не табуляция
		j++;
	}
	return tmp;
}

void TText::Enter_line_to_list(string filename, int n)			//ввод строк в список
{		
	int c = 1;		
	int count_end = 0;
	bool Down_one_line = false;			//если = true, то следующая строка записывается на уровень ниже
	bool Dont_read_next_line = false;	//если true, то не читается следующая строка
	string str;			//текущая строка
	ifstream is;
	is.open(filename);						//открытие файла	
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
		if (Delete_space_before_and_after_keywords(tmp) == "") continue;	//если пустая строчка - пропускаем
		//Program
		if ((list.Is_Empty()) && (tmp != "program")) throw ("In the first line no program");	//если "program" не на своём месте		
		else if ((list.Is_Empty()) && (tmp == "program"))
		{
			Check_End_Line(str);		//проверка на ;
			list.InsertFirst(str);		//вставка в список
			count_line++;		
			continue;
		}
		//const & var
		if (((tmp == "const") || (tmp == "var")) && (count_begin > 0)) throw ("'const'/'var' after begin");
		else if ((tmp == "const") || (tmp == "var"))
		{			
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after const/var");		//если после слов const, var что-нибудь написано
			list.Insert_Next_Line(Delete_space_before_and_after_keywords(str));		//вставка	
			count_line++;		
			getline(is,str);		//читаем первую строку после var/const
			tmp = "";
			i++;			
			j = 0;			
			tmp = Get_the_beginning_of_the_word(str, j);		//получаем ключевое слово в начале строки или саму строку
			if (j != str.length())  throw ("Error const/var"); //если посде const/var идёт ключевое слово
			else
			{
				Check_End_Line(str);			//проверка на ;
				list.Insert_Down_Line(str);		//вставка на уровень ниже
				count_line++;
			}
			//читаем следующие строки после объявления переменных const/var и если это тоже объявления переменных вставляем Next_Line
			while (1)
			{	
				tmp = "";
				getline(is,str);		//читаем новую строку
				i++;
				j = 0;
				tmp = Get_the_beginning_of_the_word(str, j);				//получаем ключевое слово в начале строки или саму строку
				if ((tmp == "begin") || (tmp == "var") || (tmp == "const"))//если после const/var идёт ключевое слово
				{
					Dont_read_next_line = true;		//не читаем следующую строку
					break;
				}
						
				else if (j  != str.length())  throw ("Error const/var");				//если идёт какая-то другая команда из списка ключевых слов
				else
				{
					Check_End_Line(str);			//проверка на ;
					list.Insert_Next_Line(str);		//втавка следующей строки		
					count_line++;
				}				
			}
			list.Go_Parent();		//возвращаемся на уровень const	/var	
			continue;
		}		

		//begin		
		if (tmp == "begin")
		{
			if (list.Get_Current_Line() == "begin")  throw ("After begin goes begin");
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after begin");
			if ((Down_one_line == false) && (count_begin != 0))throw ("Error begin");		//если begin не начинает цикл и стоит не в начале программы
			list.Insert_Next_Line(Delete_space_before_and_after_keywords(str));		//вставляем строку
			count_begin++;
			count_line++;					
			Down_one_line = true;		//следующую строку нужно будет вставить на уровень ниже	
			continue;
		}
		//end
		if (tmp == "end")
		{
			if (list.Get_Current_Line() == "begin") throw ("After begin goes end");
			list.Go_Parent();		//переходим к родителю
			string tmp1 = Delete_space_before_and_after_keywords(str);
			if ((tmp1 != "end") && (tmp1 != "end.")) throw ("Error end");			
			list.Insert_Next_Line(tmp1);		//вставляем следующей строкой
			count_end++;
			count_line++;		
			continue;
		}
		//if/else
		if ((tmp == "else") || (tmp == "if"))
		{
			if (Down_one_line == true)		//если строку нужно вставить на уровень ниже
			{
				if (tmp == "else") throw ("Error else");		//если после if сразу идёт else
				else	
				{
					list.Insert_Down_Line(str);					//вставка строки на уровень ниже
					Down_one_line = true;						//следующую строку нужно будет вставить на уровень ниже
					count_line++;
					list.Set_check(c);							//устанавливаем check
					c++;										//увеличиваем номер для следующего check
				}
				continue;
			}
			else
			{
				list.Insert_Next_Line(str);						//вставляем следующую строку
				count_line++;
				Down_one_line = true;							//следующую строку нужно будет вставить на уровень ниже
				if (tmp == "if")
				{
					list.Set_check(c);							//устанавливаем check
					c++;										//увеличиваем номер для следующего check
				}
				else				
					list.Set_check(list.Get_check_prev_if());			//если это else - в check ставим ей номер соответствующего if	
				continue;
			}
		}				
		else
		{
			Check_End_Line(str);							//проверка на ;
			if (Down_one_line == true)						//если строку нужно вставить на уровень ниже
			{
				if (list.Get_Current_Line() != "begin")		//если после условного оператора стоит одна строка
				{
					list.Insert_Down_Line(str);				//вставка строки на уровень ниже
					count_line++;
					Down_one_line = false;					//следующую строку нужно вставлять на том же уровне
					list.Go_Parent();						//возвращение к родителю
				}
				else
				{
					list.Insert_Down_Line(str);				//вставка строки на уровень ниже
					count_line++;
					Down_one_line = false;					//следующую строку нужно вставлять на том же уровне
				}
			}
			else
			{
				list.Insert_Next_Line(str);					//вставка строки на том же уровне
				count_line++;
			}
		}
	}
	if (count_begin != count_end) throw("Different count of begin and end");
	is.close();			//закрытие файла
}

string TText::Read_before_symbol(string str, int & j, char symbol)
{
	string tmp = "";
	while ((str[j] != symbol) && (j < str.length()))		//чтаем объявление до :
	{
		if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
		j++;
	}
	return tmp;
}

void TText::Line_processing()				//обработка строк
{
	list.ReSetCur();						//возвращаемся к началу списка
	const string comparison = "<>=";	
	string tmp = "";
	int j = 0;
	int arr[20];		//на против номера check каждого if, который будет являться индексом массива, ставится 1, если условие выполнилось и 0 - если не выполнилось
	//первая строчка
	string str = list.Get_Current_Line();		//читаем строку	
	tmp = Get_the_beginning_of_the_word(str, j);	//получаем ключевое слово в начале строки или всю строку	
	if ((str[j] != ' ') && (str[j] != '\t')) throw ("Error: There is no space after 'program'");
	j++;
	string tmp1 = "";
	tmp1 = Read_before_symbol(str, j, ';');	//читаем имя program	
	if (tmp1 == "") throw ("Error: There is no program name");
	list.Go();		//переходим на строку ниже
	
	//------------------------------------------
	for (int i = 0; i < count_line; i++)
	{
		tmp = "";
		j = 0;
		str = list.Get_Current_Line();		//читаем строку	
		while ((keywords.Search(tmp) == nullptr) && (j < str.length())) //читаем символы
		{
			if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
			j++;
		}
		if (keywords.Search(tmp) == nullptr) //если не нашли слово в ключевых
		{
			tmp = "";
			j = 0;
			while ((variables.Search(tmp) == nullptr) && (j < str.length())) //читаем символы
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
				j++;
			}
		}
		//const--------------------
		if (tmp == "const")
		{
			string tmp1 = "";			
			list.Go();		//переходим к следующей строчке
			str = list.Get_Current_Line();
			while (1)
			{	
				tmp = "";				
				string name;
				string _type;
				j = 0;
				//чтение имени
				tmp = Read_before_symbol(str, j, ':');	//читаем объявление до :				
				if (j == str.length()) throw ("Error of variable declaration");		//если нет :
				if (variables.Search(tmp) != nullptr) throw ("Error: reclaim variables");		//если повторное объявление переменной
				name = tmp;	
				j++;
				//чтение типа
				tmp = "";
				tmp = Read_before_symbol(str, j, '=');		//читаем до =				
				if (j == str.length()) throw ("Error of variable declaration");
				if (tmp == "integer") _type = "const integer";
				else if (tmp == "double") _type = "const double";
				else throw ("Error: wrong type of constant");
				//чтение значения
				tmp = "";
				j++;
				tmp = Read_before_symbol(str, j, ';');		//читаем до ;				
				if (tmp == "") throw ("Error of variable declaration");
				double f;				//перевод в double
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
				if ((_type == "const integer") && (x != 0)) throw ("не соответствие типов");			//если есть дробная часть	
				//вставка переменной в таблицу
				TNote s(name, tmp, _type);
				variables.Insert(s);
				list.Go();		//переход к следующей строке
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
			str = list.Get_Current_Line();		//получить текущее значение
			while (1)
			{					
				stack<string> ar;
				string _type;
				j = 0;
				while ((str[j] != ':') && (j < str.length()))			//читаем до :
				{
					tmp = "";
					while (((str[j] != ',') && (str[j] != ':')) && (j < str.length()))		//читаем до двоеточия, либо до запятой
					{
						if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
						j++;
					}
					if (j == str.length()) throw ("Error of variable declaration");
					if (variables.Search(tmp) != nullptr) throw ("Error: reclaim variables");		//повторное объявление переменной
					ar.push(tmp);			//ладём переменную в стек
					if (str[j] == ':')		//если ввод переменных закончен
					{
						j++;
						break;
					}
					else j++;
				}
				tmp = "";
				tmp = Read_before_symbol(str, j, ';');	//чтение до ;							
				if (tmp == "integer") _type = "integer";
				else if (tmp == "double") _type = "double";
				else throw ("Error: wrong type of variable");
				//вставка переменной в таблицу
				while (!ar.empty())
				{
					TNote s(ar.top(), "", _type);					
					variables.Insert(s);					
					ar.pop();
				}				
				list.Go();	//переход к следующей строке
				str = list.Get_Current_Line();
				if ((str == "var") || (str == "const") || (str == "begin")) break;
			}
			continue;
		}
		//---------------------
		if (tmp == "begin")
		{				
			list.GoDown();		//переход на подуровень
			continue;
		}
		//---------------------------
		//end
		if (tmp == "end")
		{
			if (str == "end.") break;
			list.Go();			//переход на следующую строку
			continue;
		}
		//---------------------------
		//операции с переменными
		if (variables.Search(tmp) != nullptr)	
		{
			if ((variables.Search(tmp)->type == "const integer") || (variables.Search(tmp)->type == "const double"))
				throw ("Error: operation with constants");		//если попытка присваивания константной переменной
			string tmp1 = "";
			tmp1 = Read_before_symbol(str, j, '=');		//чтение до =			
			if (j == str.length()) throw ("Error of assignment operation");
			tmp1 += str[j];
			j++;
			if (tmp1 != ":=") throw ("Error of assignment operation");
			tmp1 = "";
			tmp1 = Read_before_symbol(str, j, ';');		//чтение до ;			
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
			tmp1 = Read_before_symbol(str, j, '(');		//чтение до (	
			if (j == str.length()) throw ("Error of Write");
			tmp1 += str[j];
			if ((tmp1.length() != 1) || (tmp1[0] != '(')) throw ("Error Write");			
			j++;
			while ((str[j] != ')') && (j < str.length()))		//читаем до )
			{
				tmp = "";				
				while (((str[j] != ',') && (str[j] != ')')) && (j < str.length()))		//читаем до , или до )
				{
					if (tmp == "")
					{
						if ((str[j] != ' ') && (str[j] != '\t')) tmp += str[j];
					}
					else tmp += str[j];					
					j++;
				}
				//удаление пробелов после tmp
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
				if ((tmp[0] == '"') && (tmp[tmp.length() - 1] == '"'))		//если вывод фразы в ковычках
				{
					if (tmp.length() < 3) throw("Error Write");		//если пустые кавычки
					for (int k = 1; k < tmp.length() - 1; k++)
						cout << tmp[k];				//вывод содержимого					
				}
				else
				{				//если вывод переменной
					if (variables.Search(tmp) == nullptr) throw ("Error: Write");		//если не нашли выводимую переменную
					cout << variables.Search(tmp)->val;				//вывод значения переменной
				}				
				if (str[j] == ')')		//если вывод закончен
				{
					j++;
					break;
				}
				else j++;
			}
			tmp = "";
			tmp = Read_before_symbol(str, j, ';');			//чтение до ;			
			if (tmp != "") throw ("Error Write");						
			list.Go();		//переход к следующей строке
			continue;
		}
		//----------------------
		//Read
		if (tmp == "Read")
		{
			string tmp1 = "";
			string text = "";
			tmp1 = Read_before_symbol(str, j, '(');		//читаем символы до (
			tmp1 += str[j];
			if (tmp1 != "(") throw ("Error Read");
			int t = j + 1;
			j = str.length() - 1;
			tmp1 = "";
			//считаем до какого символа читать
			while ((str[j] != ')') && (j > t))
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j--;
			}
			if (j == t) throw ("Error Read");			//если в скобках пусто			
			tmp1 = "";
			for (int k = t; k < j; k++)		//читаем переменную
			{
				tmp1 += str[k];
			}
			if (variables.Search(tmp1) == nullptr) throw ("Error Read");	//если переменная не объявлена
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
			if ((variables.Search(tmp1)->type == "integer") && (x != 0)) throw ("не соответствие типов");			
			variables.Set_Val(tmp1, text);		//устанавливаем значение переменной
			list.Go();		//переход к следующей строке
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
			while ((tmp1 != "(") && (j < str.length()))		//читаем до скобки
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (j == str.length()) throw ("Error of conditional operation");		//если нет открывающей скобки
			tmp1 = "";
			while ((comparison.find(str[j]) == string::npos) && (j < str.length()))		//пока не найдём знак сравнения
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (j == str.length()) throw ("Error of conditional operation");		//если отсутствует знак сравнения
			left_op = tmp1;		//записываем левый операнд
			sign = str[j];		//записываем знак сравнения
			j++;
			tmp1 = "";
			tmp1 = Read_before_symbol(str, j, ')');			//чтение до )			
			if (j == str.length()) throw ("Error of conditional operation");
			j++;
			right_op = tmp1;	//записываем правый операнд
			tmp1 = "";
			while (j < str.length())		//читаем оставшуюся часть
			{
				if ((str[j] != ' ') && (str[j] != '\t')) tmp1 += str[j];
				j++;
			}
			if (tmp1 != "then") throw ("Absence of 'then'");
			//вычисление
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
				arr[list.Get_check()] = 1;		//устанавливаем соответствующему if значение - 1 - условие выполнилось
				list.Go();						//переходим к следующему
				continue;
			}
			else
			{
				
				arr[list.Get_check()] = 2;		//устанавливаем соответствующему if значение - 2 - условие не выполнилось
				list.Go_throw_down();			//обходим подуровень
				continue;
			}
		}
		//------------------------------
		//else
		if (tmp == "else")
		{
			if (tmp != Delete_space_before_and_after_keywords(str)) throw ("There are words after else");
			if (arr[list.Get_check()] == 1)		//если у соответствующего if выполнилось условие
			{
				list.Go_throw_down();			//обходим подуровень	
				continue;
			}
			else if (arr[list.Get_check()] == 0) throw ("Error else");		//если у соответствующего if не выполнилось условие
			else
			{				
				list.Go();		//переходим к следующему
				continue;
			}
		}
		else throw("Unknown line");
	}
}
	