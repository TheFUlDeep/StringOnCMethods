#pragma once
#include <stdlib.h>
#include <string.h>
#include <iostream>//��� ������ ���� ostream ���

//��������� malloc � free, ������ ��� �� ������ ������ ��� �������. ���������� �� new � delete �����������

//�����. ������� ������ ���������� � 1 � ��������� ������ ������ (��� ��� �����). � ��� ������ � ���� � �� \0

namespace MyString {

	typedef unsigned int UINT;

	class string {
	private:
		UINT len = 0;
		char* ptr = nullptr;
		void ClearMem();
		void AllocMem(UINT);
		void IntervalException(UINT&, UINT&);//������� ��� ����������� ��������. �������� ������������ � SubString
	public:
		//������������
		string();

		string(const char);//������

		string(const char*);//������

		string(const string&);//����������� �����������

		//����������
		~string();

		//������������
		string& operator=(const char);

		string& operator=(const char*);

		string& operator=(const string&);

		//���������
		bool operator==(const char);

		bool operator==(const char*);

		bool operator==(const string&);

		//�����������
		bool operator!=(const char);

		bool operator!=(const char*);

		bool operator!=(const string&);

		//>
		bool operator>(const char);

		bool operator>(const char*);

		bool operator>(const string&);

		//<
		bool operator<(const char);

		bool operator<(const char*);

		bool operator<(const string&);

		//>=
		bool operator>=(const char);

		bool operator>=(const char*);

		bool operator>=(const string&);

		//<=
		bool operator<=(const char);

		bool operator<=(const char*);

		bool operator<=(const string&);

		//������������
		string operator+(const char);

		string operator+(const char*);

		string operator+(const string&);

		//����������� � �������������
		//������ �� ���������, �� �� ������ �������� ������������ ��������
		void operator+=(const char);

		void operator+=(const char*);

		void operator+=(const string&);

		//��������� ������ ������� �� ������
		char& operator[](const UINT);

		//��������� ������� �� ������
		char GetChar(const UINT);


		int GetInt(const UINT);

		//��������� ������ �� �������
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		string SubString(const UINT = 0, const UINT = 0);

		//TODO ��������� ������ �� ������ �������� �� ������� � ��������� �������
		//��������� - ��� ������, �� ��� ��������, ������������ ���������� ����� (���� 0, �� ������������), ������ ������� (� ������� ������), ����� ������� (� ������� ������)
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		string& GSub(const char*, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char*, const string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char*, const char, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, const char, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const char, const UINT = 0, const UINT = 0, const UINT = 0);


		//�����. ���������� ������ ���������� �������� ��� 0;
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		UINT Find(const char, const UINT = 0, const UINT = 0);

		UINT Find(const char*, const UINT = 0, const UINT = 0);

		UINT Find(const string&, const UINT = 0, const UINT = 0);

		//TODO �������
		void InsertAfter(const UINT, char);

		void InsertAfter(const UINT, char*);

		void InsertAfter(const UINT, string&);

		//TODO ������� � ������ �������
		void InsertBefore(const UINT, char);

		void InsertBefore(const UINT, char*);

		void InsertBefore(const UINT, string&);

		//���� ���� �������� �� ��������
		void SwapSymbols(const UINT, const UINT);

		//���� ���� ��������
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		void SwapIntervals(const UINT = 0, const UINT = 0, const UINT = 0, const UINT = 0);

		//���������� ������� ������ ��������
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		void Fill(const char, const UINT = 0, const UINT = 0, const UINT = 0);

		//�����
		friend std::ostream& operator<<(std::ostream&, const string&);

		//����
		friend std::istream& operator>>(std::istream &in, string &);

		//��������������� �������
		//���� ������ ������� 0 - ������ � ������
		//���� ����� ������� 0 - ������ �� �����
		void Reverse(const UINT = 0, const UINT = 0);

		UINT GetLen();
	};
}