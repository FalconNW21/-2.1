/*
Этот файл отвечает за состояние окна, что будет выводится следующим
*/



#pragma once
#include "Menu.h"
#include "TextMessage.h"
#include "StringManager.h"
#include "InputField.h"
#include "StringChooseMenu.h"
#include <map>



class StateManager
{
public:

	StateManager()
	{
		states["NumInput"] = new InputField("Введите количество строк от 4 до 6: ", "MainMenu", StringManager::setSize); //ключ для ввода кол-во строк
		states["MainMenu"] = new Menu({ "Ввод строк",
									   "Тестирование обычной строки",
									   "Тестирование строки-идентификатора",
									   "Тестирование Битовой строки",
									   "Выход" },
			{ "StringsInput",
			 "StringsTest",
			 "IDStringsTest",
			 "BiteStringsTest",
			 "Exit" }); //Ключи (массив ключей) для главного меню

		
		//Меню ввода строк
		states["StringsInput"] = new Menu({ "Ввести обычную строку", "Ввести строку-индентификатор", "Ввести Битовую строку", "Выход в главное меню" }, { "OrigString", "IdString", "BiteString", "MainMenu" }); //Выбор ввода  строки какого вида
		//Ввод строк разных видов
		states["OrigString"] = new InputField("Введите строку: ", "StringsInput", StringManager::createString);
		states["IdString"] = new InputField("Введите строку: ", "StringsInput", StringManager::createIdString);//Ввод строк
		states["BiteString"] = new InputField("Введите строку: ", "StringsInput", StringManager::createBiteString);
		
		//Меню тестирования обычной строки
	    states["StringsTest"] = new Menu({ "Заменить строку", "Вывести длину строки", "Выйти в главное меню" }, { "ChooseString", "ChooseStringToGetLength", "MainMenu" });//Ключи для подменю строки
		//Пункт замены строки
		states["ChooseString"] = new StringChooseMenu(STRINGTYPE, "InputChangeString");
		states["InputChangeString"] = new InputField("Напишите строку для замены: ", "ChangedString", StringManager::setSupString<MyString>);
		states["ChangedString"] = new TextMessage("Измененная строка: ", "StringsTest", StringManager::ChangeString);
		//Вывод длины строки
		states["ChooseStringToGetLength"] = new StringChooseMenu(STRINGTYPE, "ShowLength");
		states["ShowLength"] = new TextMessage("Длина строки: ", "StringsTest", StringManager::getLength);//ключ, для подменю обычной строки после вывода результата
		
		//Меню тестирования строки-идентификатора
		states["IDStringsTest"] = new Menu({ "Сложить строки", "Перевести в верхний регистр", "Выйти в главное меню" }, { "ChooseStringToAdd", "ChooseUpperCase", "MainMenu" });//Ключи для подменю строки-идентификатора
		//Сложение строки (добавление к существующей строке новую)
		states["ChooseStringToAdd"] = new StringChooseMenu(IDTYPE, "InputAddId");
		states["InputAddId"] = new InputField("Напишите строку для сложения: ", "ResultIdstring", StringManager::setSupString<stringid>);
		states["ResultIdstring"] = new TextMessage("Результат: ", "IDStringsTest", StringManager::getIdAdding);
		//Перевод строки в верхний регистр
		states["ChooseUpperCase"] = new StringChooseMenu(IDTYPE, "ResultUpperCase");
		states["ResultUpperCase"] = new TextMessage("Строка в верхнем регистре: ", "IDStringsTest", StringManager::getUperrCase);
		
		//Меню тестирования битовой строки
		states["BiteStringsTest"] = new Menu({ "Сложить строки", "Сравнить строки", "Выйти в главное меню" }, { "ChooseBiteToAddTo", "ChooseBiteToCompareWith", "MainMenu" });
		//Математическое сложение битовой строки
		states["ChooseBiteToAddTo"] = new StringChooseMenu(BITETYPE, "InputAddBite");
		states["InputAddBite"] = new InputField("Введите строку для сложения: ", "ResultBite", StringManager::setSupString<Bite>);
		states["ResultBite"] = new TextMessage("Результат: ", "BiteStringsTest", StringManager::getBiteAdding);
		//Сравнение битовой строки
		states["ChooseBiteToCompareWith"] = new StringChooseMenu(BITETYPE, "InputCompareBite");
		states["InputCompareBite"] = new InputField("Введите строку для сравнения", "ResultCompareBite", StringManager::setSupString<Bite>);
		states["ResultCompareBite"] = new TextMessage("Результат сложения : ", "BiteStringsTest", StringManager::getBiteCompare);
       
		//Выход
		states["Exit"] = nullptr;
	}

	void exec(const std::string& startStateName)//отвечает за навигаюцию в меню
	{
		State* currState = states[startStateName];
		std::string prevStateName = "Exit";
		std::string currStateName = startStateName;
		while(currState != nullptr)
		{
			currState->setFrom(prevStateName);
			prevStateName = currStateName;
			currStateName = currState->exec();
			currState = states[currStateName];			
		}
		
	}

private:
	std::map< std::string, State*> states;


};



