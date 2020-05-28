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
	THierarchy_List<string> list;	//������������� ������ �����
	THash1Table variables;			//������� � �����������
	THash1Table keywords;			//������� � ��������� �������
	int count_line;					//����� �����
	int count_begin;				//����� ���� begin	
	
public:
	TText();
	void Read_and_out_file(string filename);			//������ ����� � ����� ����� �� �����
	void Enter_line_to_list(string filename, int n);	//��������� ����� � ������
	void Line_processing();								//��������� �����
	void Check_End_Line(string line);					//�������� �� ������� ;
	string Delete_space_before_and_after_keywords(string line);		//�������� �������� �� � ����� �������� ����
	string Get_the_beginning_of_the_word(string str, int &j);		//��������� ��������� ����� � ������ ������ ��� ���� ������ ��� ��� ����������
	void Enter_Programm();											//���� ���������
	string Read_before_symbol(string str, int &j, char symbol);		//������ ������ �� ������������ ������

};