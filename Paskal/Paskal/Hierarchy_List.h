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
		T data;			//данные
		int check;		//используется для if и else - номера if и соответствующие else
		link *pNext;	//указатель на следующий элемент
		link *pDown;	//указатель на следующий подуровень
		link *pParent;	//указатель на уровень из которого вышел этот подуровень
		link(T _data = {}, link *_pNext = nullptr, link *_pDown = nullptr, link *_pParent = nullptr)
		{
			check = 0;
			data = _data;
			pNext = _pNext;
			pDown = _pDown;
			pParent = _pParent;			
		}
	};
	link<T> *pFirst;		//– указатель на первое звено списка;	
	link<T>*pCurrLink;		 //– указатель на текущее звено списка;	
	int ListLen;			//-количество звеньев в списке;

public:
	THierarchy_List()
	{
		pFirst = nullptr;
		pCurrLink = nullptr;	
		link<T> *p = new link<T>;		
		ListLen = 0;
	}


	bool Is_Empty();						//проверка на пустоту
	void Set_check(int _c);					//установка check
	int Get_check();						//получение check;
	int Get_check_prev_if();				//возвращает номер для else соответствующего if
	void InsertFirst(const T val);			//вставка первого звена
	void Insert_Next_Line(const T val);		//вставить в текущий раздел
	void Insert_Down_Line(const T val);		//вставить в строки в следующей подуровень
	void ReSetCur();						 //сделать текущее звено-первым
	void Go_Parent();						//сделать текущее звено уровнем выше		
	T Get_Current_Line();					//возвращает текущую строку			
	void GoDown();							//переход на подуровень
	void Go();								//переход на строку ниже
	void Go_throw_down();					//переход на строку нужную при невыполнении условного оператора
	
};

template<class T>
void THierarchy_List<T>::Set_check(int _c)		//установка check
{
	if (Is_Empty()) throw("List is empty");
	pCurrLink->check = _c;
}

template<class T>
int THierarchy_List<T>::Get_check()				//получение check
{
	if (Is_Empty()) throw("List is empty");
	return pCurrLink->check;
}

template<class T>
void THierarchy_List<T>::ReSetCur()		//сделать текущее звено-первым
{
	if (Is_Empty()) throw("List is empty");	
	pCurrLink = pFirst;
}
template<class T>
void THierarchy_List<T>::GoDown()		//переход на подуровень
{
	if (Is_Empty()) throw("List is empty");
	if ((pCurrLink == nullptr) || (pCurrLink->pDown == nullptr)) throw ("negative");
	pCurrLink = pCurrLink->pDown;
}

template<class T>
bool THierarchy_List<T>::Is_Empty()		//проверка на пумтоту
{
	if (ListLen == 0)
		return true;
	else return false;
}

template<class T>
void THierarchy_List<T>::Go_Parent()		//переход к родителю
{
	if (Is_Empty()) throw ("negative");
	if (pCurrLink == nullptr) throw("pCurrLink = nullptr");
	if (pCurrLink->pParent == nullptr) throw("pCurrLink->pParent = nullptr");

	pCurrLink = pCurrLink->pParent;	
}

template<class T>
int THierarchy_List<T>::Get_check_prev_if()		//получение номера соответствующего if
{
	if (Is_Empty()) throw ("negative");
	int c;
	link<T> *pCur = pCurrLink;		//запоминаем текущую позицию
	pCurrLink = pFirst;
	//переход на строчку выше
	while (pCurrLink->pNext != pCur)
	{
		Go();
	}
	link<T> *p = pCurrLink;
	if (pCurrLink->data != "end")	//если предыдущая строка не end, значит строка перед ней - соответствующее if - берём его номер
		c = pCurrLink->check;
	else	
	{		//пропускаем строки end и begin и берём номер соответствующего if
		pCurrLink = pFirst;
		while (pCurrLink->pNext != p)
			Go();
		p = pCurrLink;
		pCurrLink = pFirst;
		while (pCurrLink->pNext != p)
			Go();
		c = pCurrLink->check;
	}
	if (c == 0) throw("Error else");	//если else стоит в запрещённом месте
	pCurrLink = pCur;	//возвращаем текущий указатель
	return c;
}

template<class T>
void THierarchy_List<T>::Go()		//переход на строку ниже
{
	if (Is_Empty()) throw ("List is empty");	
	if (pCurrLink->pDown != nullptr)	//если есть подуровень - спускаемся
		pCurrLink = pCurrLink->pDown;
	else if (pCurrLink->pNext != nullptr)		//иначе, если есть следующий элемент - переходим к нему
		pCurrLink = pCurrLink->pNext;
	else
	{	//возвращаемся к родителю, у которого есть следующий элемент
		while(pCurrLink->pNext == nullptr)
		{
			Go_Parent();
		}
		pCurrLink = pCurrLink->pNext;		
	}
}
template<class T>
void THierarchy_List<T>::Go_throw_down()		//переход через строки при не выполнении условного оператора
{
	Go();										//переходим на следующую строку
	if (pCurrLink->data == "begin")
		pCurrLink = pCurrLink->pNext;
	else
	{		//если после условного оператора стоит в условии одна строка 
		Go_Parent();							//возвращаемся к условному оператору
		while (pCurrLink->pNext == nullptr)		//возвращаемся к родителю, у которого есть следующий элемент
		{
			Go_Parent();
		}
		pCurrLink = pCurrLink->pNext;
	}
}

template<class T>
void THierarchy_List<T>::InsertFirst(const T val)		//вставка первого элемента
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
void THierarchy_List<T>::Insert_Next_Line(const T val)		//вставка следующей строки
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
void THierarchy_List<T>::Insert_Down_Line(const T val)		//вставка следующего подуровня
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
T THierarchy_List<T>::Get_Current_Line()			//получить текущую строку
{
	if (Is_Empty()) throw "negative";
	return pCurrLink->data;
}
