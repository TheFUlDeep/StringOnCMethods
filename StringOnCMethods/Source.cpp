#include "MyString.h"
#include <iostream>//��� ������ ���� cout ��� � system
//����� � �������� �� VisualStudio17

using namespace std;

//������������ ������ ������� ����� ������ String
int main() {
	setlocale(LC_ALL, "Rus");

	cout << "������������ ������ ������� ����� ������ String" << endl << endl;
	cout << "����������� �� ���������:";
	MyString::string a;
	cout << " ������ ����� �����: " << &a << ", ��� ������ ����� - nullptr (���� �������, ������ ��� ������ ������� ����� cout nullptr)" << endl << endl;

	cout << "����������� � ���������� - ��������:";
	MyString::string b('a');
	cout << " ������ ����� �����: " << &b << ", ��� ������ �������: " << b.GetChar(1) << endl << "��� �� � ����������������� ������ ������ GetChar" << endl << endl;

	cout << "����������� � ���������� - ������ �����:";
	MyString::string c("asd");
	cout << " ������ ����� �����: " << &c << ", ��� ������ �������: " << c[3] << endl << "��� �� � ����������������� ������������� �������� []" << endl << endl;

	cout << "����������� �����������:";
	MyString::string d(c);
	cout << " ������ ����� �����: " << &d << ", ��� ������ �������: " << d[3] << endl << "�������� ��������� ==: " << (b==d) << endl << "��� �� � ����������������� ������������� �������� == ��� ���� ��������" << endl << endl;

	cout << "������������ ����: ����: " << c;
	c = 'a';
	cout << " �����: " << c << endl << "��� �� � ����������������� ��������� �����" << endl << endl;

	cout << "������������ ������� �����: ����: " << d;
	d = "qwerty";
	cout << " �����: " << d << endl;
	cout << "������ ������� ���������== ��� ������� �����: "<< (d == "qwerty") << endl << endl;

	cout << "������������ �������: ����: " << d;
	d = b;
	cout << " �����: " << d << endl;
	cout << "������ ������� ���������== ��� �������: " << (d == 'a') << endl << endl;

	cout << "!= ������� ����� ��������� ���������, ������� �� ���� ������ ����������" << endl << endl;

	cout << "��������� ����������� ��������������� ����� � �����������" << endl << endl;

	cout << "������������ ������� � ����: " << d+'j' << endl;
	cout << "������������ ������� � ������� �����: " << d + "zxc" << endl;
	cout << "������������ ������� � �������: " << d + c << endl << endl;

	d = "abcdefgh";
	cout << "��������� ���������� " << d.SubString(4,6) << endl << endl;

	cout << "����� ������ ����� � ������� " << d.Find("def") << endl << endl;

	cout << "����� ������� � ������� " << d.Find('a') << endl << endl;

	cout << "����� ������� � ������� " << d.Find(MyString::string("def")) << endl << endl;

	d.SwapIntervals(1, 3, 4, 6);
	cout << "���� ���� ������ " << d << endl << endl;

	d = "������";
	d.Reverse(4);
	cout << "������ ������� " << d << endl << endl;


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

	//cout << d << endl; //� ��� ����. ����������� ������ ���������
	//cin >> d;
	//cout << d << endl;

	cout << endl;
	system("pause");
	return 0;
}