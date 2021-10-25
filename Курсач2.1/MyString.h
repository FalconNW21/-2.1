#pragma once
#pragma warning(disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#define STRINGTYPE 0

/*
����� ������� ������ 
*/

using namespace std;

class MyString
{
	static int counter1; // ���������� ������� ������������ �����������
protected:
	
public:
	char* str; // ��������� ��	
	int length; //����� ������ � ������

	MyString()
	{
		//	cout << "����������� ��� ����������" << endl;
		this->str = nullptr;
		length = 0;
	}

	virtual int type()
	{
		return STRINGTYPE;
	}

	MyString(const char* str) //�����������, ����������� � �������� ��������� ��-������
	{
		cout << "����������� �� ������" << endl;
		length = strlen(str);
		this->str = new char[length + 1];
		strcpy(this->str, str);
	}

	MyString(char sym) //�����������, ����������� � �������� ��������� ������� char
	{
		cout << "����������� �������" << endl;
		length = 1;
		this->str = new char[length + 1];
		str[0] = sym;
		str[1] = '\0';
	}

	MyString(const MyString& other) //����������� �����������
	{
		cout << "����������� �����������" << ++counter1 << " ���" << endl; //������ ���������� ��� �������
		length = strlen(other.str);
		this->str = new char[length + 1];
		strcpy(this->str, other.str);
	}



	~MyString()
	{
		cout << "����������" << endl;
		if (str != nullptr)
			delete[] str;
	}

	MyString& operator = (const MyString& other) //�������� ������������
	{
		cout << "���������� �������� ������������" << endl; //������ ���������;
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
		cout << "������� ����� ������" << endl;
		return this->length;
	}
};


int MyString::counter1 = 0;

