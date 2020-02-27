#include "MyString.h"
#include <iostream>//это только шобы cout был и system
//писал и проверял на VisualStudio17

using namespace std;

//демонстрация работы методов моего класса String
int main() {
	setlocale(LC_ALL, "Rus");

	cout << "демонстрация работы методов моего класса String" << endl << endl;
	cout << "Конструктор по умолчанию:";
	MyString::string a;
	cout << " Объект имеет адрес: " << &a << ", его массив чаров - nullptr (пишу словами, потому что нельзя вывести через cout nullptr)" << endl << endl;

	cout << "Конструктор с аргументом - символом:";
	MyString::string b('a');
	cout << " Объект имеет адрес: " << &b << ", его первый элемент: " << b.GetChar(1) << endl << "Тут же я продемонстрировал работу метода GetChar" << endl << endl;

	cout << "Конструктор с аргументом - массив чаров:";
	MyString::string c("asd");
	cout << " Объект имеет адрес: " << &c << ", его третий элемент: " << c[3] << endl << "Тут же я продемонстрировал перегруженный оператор []" << endl << endl;

	cout << "Конструктор копирования:";
	MyString::string d(c);
	cout << " Объект имеет адрес: " << &d << ", его третий элемент: " << d[3] << endl << "Проверка оператора ==: " << (b==d) << endl << "Тут же я продемонстрировал перегруженный оператор == для двух стрингов" << endl << endl;

	cout << "Присваивание чара: было: " << c;
	c = 'a';
	cout << " стало: " << c << endl << "Тут же я продемонстрировал потоковый вывод" << endl << endl;

	cout << "Присваивание массива чаров: было: " << d;
	d = "qwerty";
	cout << " стало: " << d << endl;
	cout << "Заодно провека оператора== для массива чаров: "<< (d == "qwerty") << endl << endl;

	cout << "Присваивание стринга: было: " << d;
	d = b;
	cout << " стало: " << d << endl;
	cout << "Заодно провека оператора== для символа: " << (d == 'a') << endl << endl;

	cout << "!= сделано через отрицание равенства, поэтому не вижу смысла показывать" << endl << endl;

	cout << "остальные неравенства демонстрировать долго и неинтересно" << endl << endl;

	cout << "Конкатинация стринга и чара: " << d+'j' << endl;
	cout << "Конкатинация стринга и массива чаров: " << d + "zxc" << endl;
	cout << "Конкатинация стринга и стринга: " << d + c << endl << endl;

	d = "abcdefgh";
	cout << "Получение сабстринга " << d.SubString(4,6) << endl << endl;

	cout << "Поиск массиа чаров в стринге " << d.Find("def") << endl << endl;

	cout << "Поиск символа в стринге " << d.Find('a') << endl << endl;

	cout << "Поиск стринга в стринге " << d.Find(MyString::string("def")) << endl << endl;

	d.SwapIntervals(1, 3, 4, 6);
	cout << "Свап двух кусков " << d << endl << endl;

	d = "йцукен";
	d.Reverse(4);
	cout << "Реверс стринга " << d << endl << endl;


	a = "qwerty";
	b = "asdf";
	c = "zxc";
	d = a + "jkl" + b + 'p' + c;
	cout << d << endl;
	cout << -d << endl;

	cout << ('a' != a) << endl;

	MyString::string number = "-12345";
	cout << (int)number << "\n";

	number = "-.1234";
	cout << (double)number << "\n";

	//cout << d << endl; //и это ввод. Закомментил просто потомушта
	//cin >> d;
	//cout << d << endl;

	cout << endl;
	system("pause");
	return 0;
}