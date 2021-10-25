#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#define STRINGTYPE 0

/*
Класс обычной строки 
*/

using namespace std;

class MyString
{
	static int counter1; // количетсво вызовов констркутора копирования
protected:
	
public:
	char* str; // указатель на	
	int length; //длина строки в байтах

	MyString()
	{
		//	cout << "конструктор без параметров" << endl;
		this->str = nullptr;
		length = 0;
	}

	virtual int type()
	{
		return STRINGTYPE;
	}

	MyString(const char* str) //конструктор, принимающий в качестве параметра Си-строку
	{
		cout << "Конструктор си сторки" << endl;
		length = strlen(str);
		this->str = new char[length + 1];
		strcpy(this->str, str);
	}

	MyString(char sym) //конструктор, принимающий в качестве параметра Симивол char
	{
		cout << "Конструктор символа" << endl;
		length = 1;
		this->str = new char[length + 1];
		str[0] = sym;
		str[1] = '\0';
	}

	MyString(const MyString& other) //конструктор копирования
	{
		cout << "Конструктор копирования" << ++counter1 << " раз" << endl; //печать количества его вызовов
		length = strlen(other.str);
		this->str = new char[length + 1];
		strcpy(this->str, other.str);
	}



	~MyString()
	{
		cout << "Деструктор" << endl;
		if (str != nullptr)
			delete[] str;
	}

	MyString& operator = (const MyString& other) //оператор присваивания
	{
		cout << "Перегрузка операции присваивания" << endl; //печать сообщения;
		if (this->str != nullptr)
		{
			delete[] str;
		}
		if (other.str == nullptr)
		{
			length = 0;
			this->str = nullptr;
			return *this;
		}
		length = strlen(other.str);
		this->str = new char[length + 1];
		strcpy(this->str, other.str);
		return *this;
	}

	int Getlength()
	{
		cout << "Функция длины строки" << endl;
		return this->length;
	}
};


int MyString::counter1 = 0;

