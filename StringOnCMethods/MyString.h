#pragma once
#include <stdlib.h>
#include <string.h>
#include <iostream>//это только шобы ostream был

//использую malloc и free, потому что на первой лекции так сказали. Переписать на new и delete элементарно

//ВАЖНО. Индексы строки начинаются с 1 и кончаются длиной строки (это для юзера). А так массив с нуля и до \0

namespace MyString {

	typedef unsigned int UINT;

	class string {
	private:
		UINT len = 0;
		char* ptr = nullptr;
		void ClearMem();
		void AllocMem(UINT);
		void IntervalException(UINT&, UINT&);//функция для конвертации отрезков. Например исопльзуется в SubString
	public:
		//конструкторы
		string();

		string(const char);//символ

		string(const char*);//строка

		string(const string&);//конструктор копирования

		//деструктор
		~string();

		//присваивание
		string& operator=(const char);

		string& operator=(const char*);

		string& operator=(const string&);

		//равенство
		bool operator==(const char);

		bool operator==(const char*);

		bool operator==(const string&);

		//неравенство
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

		//конкатинация
		string operator+(const char);

		string operator+(const char*);

		string operator+(const string&);

		//конкатинаци с присваиванием
		//сделал их войдовыми, но не сложно поменять возвращаемое значение
		void operator+=(const char);

		void operator+=(const char*);

		void operator+=(const string&);

		//получение ссылки символа по номеру
		char& operator[](const UINT);

		//получение символа по номеру
		char GetChar(const UINT);


		int GetInt(const UINT);

		//получение строки по отрезку
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		string SubString(const UINT = 0, const UINT = 0);

		//TODO получение строки по замене паттерна на паттерн в указанном отрезке
		//аргументы - что искать, на что заменять, максимальное количество замен (если 0, то неограничено), начало отрезка (в котором искать), конец отрезка (в котором искать)
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		string& GSub(const char*, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char*, const string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char*, const char, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const string&, const char, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const char*, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const string&, const UINT = 0, const UINT = 0, const UINT = 0);

		string& GSub(const char, const char, const UINT = 0, const UINT = 0, const UINT = 0);


		//поиск. возвращает начало найденного паттерна или 0;
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		UINT Find(const char, const UINT = 0, const UINT = 0);

		UINT Find(const char*, const UINT = 0, const UINT = 0);

		UINT Find(const string&, const UINT = 0, const UINT = 0);

		//TODO вставка
		void InsertAfter(const UINT, char);

		void InsertAfter(const UINT, char*);

		void InsertAfter(const UINT, string&);

		//TODO вставка с другой стороны
		void InsertBefore(const UINT, char);

		void InsertBefore(const UINT, char*);

		void InsertBefore(const UINT, string&);

		//свап твух символов по индексам
		void SwapSymbols(const UINT, const UINT);

		//свап двух отрезков
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		void SwapIntervals(const UINT = 0, const UINT = 0, const UINT = 0, const UINT = 0);

		//заполнение отрезка строки символом
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		void Fill(const char, const UINT = 0, const UINT = 0, const UINT = 0);

		//вывод
		friend std::ostream& operator<<(std::ostream&, const string&);

		//ввод
		friend std::istream& operator>>(std::istream &in, string &);

		//переворачивание отрезка
		//если начало отрезка 0 - искать с начала
		//если конец отрезка 0 - искать до конца
		void Reverse(const UINT = 0, const UINT = 0);

		UINT GetLen();
	};
}