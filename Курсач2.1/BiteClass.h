#pragma once
#pragma warning(disable : 4996)
#include "MyString.h"
#define BITETYPE 2

/*
Битовый класс
*/

class Bite : public MyString
{
protected:
	static int counter;

	int Check_Bite() //функци¤ идентификации
	{
		cout << "Функция проверки на битность" << endl; //печать сообщени¤
		if (str == nullptr)
			return 0;
		if (str[0] != '1' && str[0] != '0')
			return 0;
		if (strlen(str) == 2) // исключени¤ чисел в виде -2 -1 0 1 (10, 11, 00, 01)
			return 1;
		if (str[0] == '0' && str[1] == '0')
			return 0;
		if (str[0] == '1' && str[1] == '1')
			return 0;
		for (int i = 2; str[i]; i++)
		{
			if (str[i] != '0' && str[i] != '1')
				return 0;
		}
		return 1;
	}


public:


	virtual int type()
	{
		return BITETYPE;
	}

	Bite()
	{
		//	cout << "конструктор без параметров" << endl;
		this->str = nullptr;
		length = 0;
	};

	Bite(const char* other) : MyString(other) //конструктор принимающий в качетве параметра си-строку
	{
		if (!(Check_Bite())) {
			cout << "Строка не валидна" << endl;
			length = 0;
			if (str != nullptr)
			{
				delete[] str;
				str = nullptr;
			}
		}
	};


	Bite(const Bite& other) //констурктор копи
	{
		cout << "Конструктор копирования" << endl; //печать сообщени¤
		cout << "Был вызван " << ++counter << " раз" << endl;
		length = strlen(other.str);
		this->str = new char[length + 1];
		strcpy(this->str, other.str);
	}

	~Bite()
	{
		cout << "Деструктор бита" << endl;
	};

	bool operator == (const Bite& other)
	{
		if (this->str != nullptr && other.str != nullptr)
		{
			return !strcmp(this->str, other.str);
		}
		else
		{
			cout << "Строки пусты" << endl;
		}
	}


	Bite& operator = (const Bite& other) //оператор присваивани¤
	{
		cout << "Перегрузка операции присваивания" << endl; //печать сообщени¤;
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

	void revers()
	{
		if (str == nullptr)
			return;
		int i = 0;
		for (i = 0; str[i]; i++)
		{
			if (str[i] == '1')
				str[i] = '0';
			else
				str[i] = '1';
		}
		//Надо выкинуть лишние нули или единицы при инвертировании (создать новую строку)
		*this = *this + Bite("01");
	}

	Bite operator + (const Bite& other)
	{
		if (str == nullptr)
		{
			if (other.str == nullptr)
				return Bite();
			else
				return Bite(other.str);
		}
		else if (other.str == nullptr)
			return Bite(str);
		int i;
		char m;
		char* temp;
		char* minstr;
		char* maxstr;

		int maxleng = max(length, other.length);
		int minleng = min(length, other.length);
		if (length < other.length)
		{
			minleng = length;
			maxleng = other.length;
			minstr = str;
			maxstr = other.str;
		}
		else
		{
			maxleng = length;
			minleng = other.length;
			maxstr = str;
			minstr = other.str;
		}
		temp = new char[maxleng + 2];
		temp[maxleng + 1] = '\0';
		m = 0;
		int tempindex = maxleng, minindex = minleng - 1, maxindex = maxleng - 1;
		for (; minindex > 0; minindex--)
		{
			temp[tempindex] = minstr[minindex] - 48 + maxstr[maxindex] + m;
			m = 0;
			if (temp[tempindex] == '2')
			{
				temp[tempindex] = '0';
				m = 1;
			}
			else if (temp[tempindex] == '3')
			{
				temp[tempindex] = '1';
				m = 1;
			}
			tempindex--;
			maxindex--;

		}//елси minleng < maxleng, то все оставшиес¤ элементы пока maxindex>0, сложить с остатком. после проверить, осталс¤ ли остаток и занести его в нулевой элемент
		int mink = minstr[0] - '0';
		for (; maxindex > 0; maxindex--)
		{
			temp[tempindex] = maxstr[maxindex] - 48 + m + mink;
			m = 0;
			if (temp[tempindex] == '2')
			{
				temp[tempindex] = '0';
				m = 1;
			}
			else if (temp[tempindex] == '3')
			{
				temp[tempindex] = '1';
				m = 1;
			}
			tempindex--;
		}

		if (str[0] == '0' && other.str[0] == '0')
		{
			if (m == 1)
			{
				temp[tempindex--] = '1';//увеличиваем размер, если осталс¤ остаток					
			}
			temp[tempindex] = '0'; // в результате сложени¤ получили положительное
		}


		if (str[0] == '1' && other.str[0] == '1')
		{
			if (m == 0)
			{
				temp[tempindex--] = '0';//увеличиваем размер, если не осталось остаток					
			}
			temp[tempindex] = '1'; // в результате сложени¤ получили отрицательное
		}

		if (str[0] == '1' && other.str[0] == '0' || str[0] == '0' && other.str[0] == '1')
		{
			temp[tempindex] = '0' + m; // если m = 0, то знак +, иначе -				
		}
		char* finalstr;
		finalstr = new char[maxleng + 2];
		i = 1;
		finalstr[0] = temp[tempindex];
		tempindex++;
		for (; temp[tempindex]; tempindex++)
		{
			if (temp[tempindex] != finalstr[0])
				break;
		}
		for (; temp[tempindex]; tempindex++)
		{
			finalstr[i++] = temp[tempindex];
		}
		if (i == 1)
		{
			finalstr[i++] = finalstr[0];
		}
		finalstr[i] = '\0';

		/*≈сли складываем положительные, то ничего не мен¤етс¤, если по¤вл¤етс¤ перенос, то увеличиваетс¤ размер (знак 0)
		  ≈сли складываем отрицательные, то если по¤влис¤ перенос, то длина не мен¤етс¤, иначе добавл¤ем 0 (знак 1)
		  ≈сли слкадываем +-, то если по¤вилс¤ перенос, то результат положительный, иначе отрицательный
		  ≈сли числа разной длины, то отрицательным дописываютс¤ единицы, положительным нули
		  Ќадо выбросить лишние нули или единицы , смотр¤ что по¤витс¤ (јккуратно с -2 и 0 (они исключени¤))*/

		delete[] temp;

		Bite final(finalstr);
		delete[] finalstr;
		return  final;
	}
};

int Bite::counter = 0;


