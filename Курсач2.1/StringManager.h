#pragma once
#pragma warning(disable : 4716)
#include "IdClass.h"
#include "BiteClass.h"
#include "MyString.h"
#include <cstring>

/*
Файл отвечает за работу со строками
*/
 

class StringManager
{


public:
 	StringManager() = delete;

	static bool setSize(const std::string &number)
	{
		if (!isNumber(number))
		{
			return false;
		}
		int num = std::stoi(number);
		if (num < 4 || num > 10)
		{
			return false;
		}
		maxSize = num;
		return true;
	}

	static bool setCurrentString(int num)//Выбираем текущую строку
	{
		if (num < 0 || num > strings.size())
		{
			return false;
		}
		currentString = strings[num];
		return true;
	}
    static bool setCurrentString(const std::string &number)//Выбираем текущую строку
	{
		if (!isNumber(number))
		{
			return false;
		}
		int num = std::stoi(number);
		if ( num < 0 || num > strings.size())
		{
			return false;
		}
		currentString = strings[num];
		return true;
	}



	static bool  createString(const string &str)
	{
		if (str.empty())
		{
			errorMessage = "Введена пустая строка";
			return false;
	    }
		if (strings.size() >= maxSize)
		{
			errorMessage = "Лимит превышен";
			return false;
		}
		strings.push_back(new MyString(str.c_str()));
		return true;
	}

	static bool  createIdString(const string& str)
	{
		if (str.empty())
		{
			errorMessage = "Введена пустая строка";
			return false;
		}
		if (strings.size() >= maxSize)
		{
			errorMessage = "Лимит превышен";
			return false;
		}
		MyString* temp = new stringid(str.c_str());
		if (temp->str == nullptr)
		{
			errorMessage = "Некорректная строка, удалите введенные данные и попробуйте снова";
			delete temp;
			return false;
		}
		strings.push_back(new stringid(str.c_str()));
		return true;
		
	}

	static  std::vector<MyString*>  getStrings()
	{
		return strings;
	}


	static bool  createBiteString(const string& str)
	{
		if (str.empty())
		{
			errorMessage = "Введена пустая строка";
			return false;
		}
		if (strings.size() >= maxSize)
		{
			errorMessage = "Вы превысили лимит";
			return false;
		}
		MyString* temp = new Bite(str.c_str());
		if (temp->str == nullptr)
		{
			errorMessage = "Некорректная строка, удалите введенные данные и попробуйте снова";
			delete  temp;
			return false;
		}
		strings.push_back(temp);
		return true;
	}


	static std::string getUperrCase()
	{
		if (!currentString)
		{
			return "Строка не введена";
		}
		stringid*  uperCaseBuffer = dynamic_cast<stringid*> (currentString);
		uperCaseBuffer->upercase();
		return uperCaseBuffer->str;
	}

	static std::string getIdAdding()
	{
		if (currentString == nullptr || supString == nullptr)
		{
			return "Какая то или обе строки пусты";
		}
		if (currentString->type() != IDTYPE || supString->type() != IDTYPE)
		{
			return "Строки не корректны";
		}
		stringid* str1 = dynamic_cast<stringid*> (currentString);
		stringid* str2 = dynamic_cast<stringid*> (supString);
		stringid result = *str1 + *str2;
		*currentString = result;
		return result.str;
	}

	static std::string ChangeString()
	{
		if (currentString == nullptr || supString == nullptr)
		{
			return "Какая то или обе строки пусты";
		}
		if (currentString->type() != STRINGTYPE || supString->type() != STRINGTYPE)
		{
			return "Строки не корректны";
		}
		*currentString = *supString;
		return  currentString->str;
	}


	static std::string getBiteCompare()
	{
		if (currentString == nullptr || supString == nullptr)
		{
			return "Какая то или обе строки пусты";
		}
		if (currentString->type() != BITETYPE || supString->type() != BITETYPE)
		{
			return "Строки не корректны";
		}
		Bite* str1 = dynamic_cast<Bite*> (currentString);
		Bite* str2 = dynamic_cast<Bite*> (supString);
		if (*str1 == *str2)
		{
			return "Строки одинаковые";
		}
		return "Строки не одинаковы";
	}

	static std::string getBiteAdding()
	{
		if (currentString == nullptr || supString == nullptr)
		{
			return "Какая то или обе строки пусты";
		}
		if (currentString->type() != BITETYPE || supString->type() != BITETYPE)
		{
			return "Строки не корректны";
		}
		
		Bite* str1 = dynamic_cast<Bite*> (currentString);
		Bite* str2 = dynamic_cast<Bite*> (supString);
		Bite result = *str1 + *str2;
		*currentString = result;
		return std::string(str1->str) + "+" + str2->str + "=" + result.str;
	}


	static std::string getError()
	{
		return errorMessage;
	}

	static std::string getLength() // На примере этой функции делать, понял, дебил?! 
	{
		if (!currentString)
		{
			return "Строка пустая";
		}
		return std::to_string(currentString->Getlength());
	}

template<class T>
	static bool setSupString(const string& str)
	{
		if (str.empty())
		{
			errorMessage = "Введена пустая строка";
			return false;
		}
		if (supString)
		{
			delete supString;
		}
		supString = new T(str.c_str());
		if (supString->str == nullptr)
		{
			errorMessage = "Некорректная строка, удалите введенные данные и попробуйте снова";
			delete supString;
			return false;
		}
		return true;
	}

   static std::string getMessage()
	{
		return message;
	}

private:
	static int maxSize;
	static std::string message;
	static std::vector<MyString*> strings;
	static MyString* currentString;
	static std::string errorMessage;
	static MyString* supString;

	static bool isNumber(const string& str)
	{
		if (str.empty())
		{
			return false;
		}
		for (char c : str)//Провекра на то, ввели ли число
		{
			if (!std::isdigit(c))
			{
				return false;
			}
		}
		return true;
	}
};
std::string StringManager::errorMessage;
int StringManager::maxSize = 0;
std::string  StringManager::message;
std::vector < MyString*> StringManager::strings;
MyString* StringManager::currentString = nullptr;
MyString* StringManager::supString = nullptr;


