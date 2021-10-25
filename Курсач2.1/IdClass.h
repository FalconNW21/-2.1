#pragma once
#pragma warning(disable : 4996)
#include "MyString.h"
#define IDTYPE 1

/*
Класс идентификаторов
*/

class stringid :public MyString // производный класс
{
	static int counter; // счетчик вызвова конструктора копирования



	int Check_Identifier() //функция идентификации
	{
		cout << "Функция идентификации" << endl; //печать сообщения
		if (str == nullptr)
			return 0;
		int i, flag = 1;
		for (i = 0; i < length; i++)
			if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] == '_' || str[i] >= '0' && str[i] <= '9'))
			{
				return 0; //создается пустая «Строка-идентификатор»
				flag = 0;
				break;
			}
		if (flag == 1)
			if (str[0] <= '9' && str[0] >= '0')
				return 0; //создается пустая «Строка-идентификатор»
			else
				return 1;
	}

public:

	virtual int type()
	{
		return IDTYPE;
	}

	stringid()
	{
			cout << "конструктор без параметров" << endl;
		this->str = nullptr;
		length = 0;
	}



	stringid(const char* other) : MyString(other) //конструктор принимающий в качетве параметра си-строку
	{

		if (!(Check_Identifier())) {
			length = 0;
			if (str != nullptr)
			{
				delete[] str;
				str = nullptr;
			}
		}
	}

	stringid(const stringid& other) //констурктор копи
	{
		cout << "Конструктор копирования" << endl; //печать сообщения
		cout << "Он был вызван " << ++counter << " раз" << endl;
		length = strlen(other.str);
		this->str = new char[length + 1];
		strcpy(this->str, other.str);

	}

	~stringid()
	{
		cout << "Деструктор идентификатора" << endl;
	}

	/*char String_char(int other) //функция получения символа строки по индексу
	{
		cout << "Функция получения символа строки" << endl; //печать сообщения
		return str[other];
	}*/

	/*int Search() //поиск первого вхождения символа в строку
	{
		cout << "Поиск первого вхождения символа в строку" << endl; //печать сообщения
		int i, flag = 0;
		for (i = 0; i < length; i++)
			if (!(str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] == '_'))
				flag++;
		return flag;
	}*/


    void upercase()
	{
		if (str == nullptr)
			return;
		int i = 0;
		while (str[i])
		{
			str[i] = towupper(str[i]);
			i++;
		}
	}

	stringid operator + (const stringid& other)
	{
		if (str == nullptr)
		{
			if (other.str == nullptr)
				return stringid();
			else
				return stringid(other.str);
		}
		else if (other.str == nullptr)
			return stringid(str);
		char* temp;
		temp = new char[length + other.length + 1];
		strcpy(temp, str);
		strcat(temp, other.str);
		return  stringid(temp);
	}
};

int stringid::counter = 0;

