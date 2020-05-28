#pragma once

#include<iostream>
#include<cstdlib>
#include<iterator>
#include <string>
const int MAXSIZE = 1000;
using namespace std;
template <class T>
class THierarchy_List
{
private:
	template <class T>
	struct link
	{
		T data;			//������
		int check;		//������������ ��� if � else - ������ if � ��������������� else
		link *pNext;	//��������� �� ��������� �������
		link *pDown;	//��������� �� ��������� ����������
		link *pParent;	//��������� �� ������� �� �������� ����� ���� ����������
		link(T _data = {}, link *_pNext = nullptr, link *_pDown = nullptr, link *_pParent = nullptr)
		{
			check = 0;
			data = _data;
			pNext = _pNext;
			pDown = _pDown;
			pParent = _pParent;			
		}
	};
	link<T> *pFirst;		//� ��������� �� ������ ����� ������;	
	link<T>*pCurrLink;		 //� ��������� �� ������� ����� ������;	
	int ListLen;			//-���������� ������� � ������;

public:
	THierarchy_List()
	{
		pFirst = nullptr;
		pCurrLink = nullptr;	
		link<T> *p = new link<T>;		
		ListLen = 0;
	}


	bool Is_Empty();						//�������� �� �������
	void Set_check(int _c);					//��������� check
	int Get_check();						//��������� check;
	int Get_check_prev_if();				//���������� ����� ��� else ���������������� if
	void InsertFirst(const T val);			//������� ������� �����
	void Insert_Next_Line(const T val);		//�������� � ������� ������
	void Insert_Down_Line(const T val);		//�������� � ������ � ��������� ����������
	void ReSetCur();						 //������� ������� �����-������
	void Go_Parent();						//������� ������� ����� ������� ����		
	T Get_Current_Line();					//���������� ������� ������			
	void GoDown();							//������� �� ����������
	void Go();								//������� �� ������ ����
	void Go_throw_down();					//������� �� ������ ������ ��� ������������ ��������� ���������
	
};

template<class T>
void THierarchy_List<T>::Set_check(int _c)		//��������� check
{
	if (Is_Empty()) throw("List is empty");
	pCurrLink->check = _c;
}

template<class T>
int THierarchy_List<T>::Get_check()				//��������� check
{
	if (Is_Empty()) throw("List is empty");
	return pCurrLink->check;
}

template<class T>
void THierarchy_List<T>::ReSetCur()		//������� ������� �����-������
{
	if (Is_Empty()) throw("List is empty");	
	pCurrLink = pFirst;
}
template<class T>
void THierarchy_List<T>::GoDown()		//������� �� ����������
{
	if (Is_Empty()) throw("List is empty");
	if ((pCurrLink == nullptr) || (pCurrLink->pDown == nullptr)) throw ("negative");
	pCurrLink = pCurrLink->pDown;
}

template<class T>
bool THierarchy_List<T>::Is_Empty()		//�������� �� �������
{
	if (ListLen == 0)
		return true;
	else return false;
}

template<class T>
void THierarchy_List<T>::Go_Parent()		//������� � ��������
{
	if (Is_Empty()) throw ("negative");
	if (pCurrLink == nullptr) throw("pCurrLink = nullptr");
	if (pCurrLink->pParent == nullptr) throw("pCurrLink->pParent = nullptr");

	pCurrLink = pCurrLink->pParent;	
}

template<class T>
int THierarchy_List<T>::Get_check_prev_if()		//��������� ������ ���������������� if
{
	if (Is_Empty()) throw ("negative");
	int c;
	link<T> *pCur = pCurrLink;		//���������� ������� �������
	pCurrLink = pFirst;
	//������� �� ������� ����
	while (pCurrLink->pNext != pCur)
	{
		Go();
	}
	link<T> *p = pCurrLink;
	if (pCurrLink->data != "end")	//���� ���������� ������ �� end, ������ ������ ����� ��� - ��������������� if - ���� ��� �����
		c = pCurrLink->check;
	else	
	{		//���������� ������ end � begin � ���� ����� ���������������� if
		pCurrLink = pFirst;
		while (pCurrLink->pNext != p)
			Go();
		p = pCurrLink;
		pCurrLink = pFirst;
		while (pCurrLink->pNext != p)
			Go();
		c = pCurrLink->check;
	}
	if (c == 0) throw("Error else");	//���� else ����� � ����������� �����
	pCurrLink = pCur;	//���������� ������� ���������
	return c;
}

template<class T>
void THierarchy_List<T>::Go()		//������� �� ������ ����
{
	if (Is_Empty()) throw ("List is empty");	
	if (pCurrLink->pDown != nullptr)	//���� ���� ���������� - ����������
		pCurrLink = pCurrLink->pDown;
	else if (pCurrLink->pNext != nullptr)		//�����, ���� ���� ��������� ������� - ��������� � ����
		pCurrLink = pCurrLink->pNext;
	else
	{	//������������ � ��������, � �������� ���� ��������� �������
		while(pCurrLink->pNext == nullptr)
		{
			Go_Parent();
		}
		pCurrLink = pCurrLink->pNext;		
	}
}
template<class T>
void THierarchy_List<T>::Go_throw_down()		//������� ����� ������ ��� �� ���������� ��������� ���������
{
	Go();										//��������� �� ��������� ������
	if (pCurrLink->data == "begin")
		pCurrLink = pCurrLink->pNext;
	else
	{		//���� ����� ��������� ��������� ����� � ������� ���� ������ 
		Go_Parent();							//������������ � ��������� ���������
		while (pCurrLink->pNext == nullptr)		//������������ � ��������, � �������� ���� ��������� �������
		{
			Go_Parent();
		}
		pCurrLink = pCurrLink->pNext;
	}
}

template<class T>
void THierarchy_List<T>::InsertFirst(const T val)		//������� ������� ��������
{
	link<T> *p = new link<T>;
	p->data = val;
	p->pNext = nullptr;
	p->pDown = nullptr;
	pFirst = p;
	pCurrLink = pFirst;
	p->pParent = pCurrLink;			
	ListLen++;
}

template<class T>
void THierarchy_List<T>::Insert_Next_Line(const T val)		//������� ��������� ������
{
	if (Is_Empty())		InsertFirst(val);
	else
	{
		if (ListLen == MAXSIZE) throw "negative";
		link<T> *tmp = new link<T>;
		tmp->data = val;
		pCurrLink->pNext = tmp;		
		tmp->pNext = nullptr;
		tmp->pDown = nullptr;
		tmp->pParent = pCurrLink->pParent;	
		pCurrLink = tmp;
		ListLen++;
	}
}

template<class T>
void THierarchy_List<T>::Insert_Down_Line(const T val)		//������� ���������� ���������
{	
	if (ListLen == MAXSIZE) throw "negative";
	link<T> *tmp = new link<T>;
	tmp->data = val;	
	tmp->pParent = pCurrLink;
	pCurrLink->pDown = tmp;
	tmp->pNext = nullptr;
	tmp->pDown = nullptr;	
	pCurrLink = tmp;
	ListLen++;	
}

template<class T>
T THierarchy_List<T>::Get_Current_Line()			//�������� ������� ������
{
	if (Is_Empty()) throw "negative";
	return pCurrLink->data;
}
