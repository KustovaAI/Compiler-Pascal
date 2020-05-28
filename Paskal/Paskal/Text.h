#pragma once

#include <iostream>
#include <string>
#include <cstdlib>
#include<locale>
#include "Hierarchy_List.h"
#include "Hash1Table.h"
using namespace std;

class TText
{
private:
	THierarchy_List<string> list;	//иерархический список строк
	THash1Table variables;			//таблица с переменными
	THash1Table keywords;			//таблица с ключевыми словами
	int count_line;					//число строк
	int count_begin;				//число слов begin	
	
public:
	TText();
	void Read_and_out_file(string filename);			//чтение файла и вывод строк на экран
	void Enter_line_to_list(string filename, int n);	//занесение строк в список
	void Line_processing();								//обработка строк
	void Check_End_Line(string line);					//проверка на наличие ;
	string Delete_space_before_and_after_keywords(string line);		//удаление пробелов до и после ключевых слов
	string Get_the_beginning_of_the_word(string str, int &j);		//получение ключевого слова в начале строки или саму строку при его отсутствии
	void Enter_Programm();											//ввод программы
	string Read_before_symbol(string str, int &j, char symbol);		//чтение строки до определённого симола

};