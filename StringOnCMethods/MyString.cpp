#define _CRT_SECURE_NO_WARNINGS //потому что strcpy небезопасный метод как и остальные методы
//strlen возвращает size_t, и я везде принудительно преобразовываю его в unsigned int
#include "MyString.h"

using namespace MyString;

//TODO убрать все вычитания на единицу

void MyString::string::ClearMem() {if (ptr != nullptr) free(ptr); }

void MyString::string::AllocMem(UINT strlen)
{
	ClearMem();
	ptr = (char*)malloc(sizeof(char)*(strlen+1));
	len = strlen;
}

void MyString::string::IntervalException(UINT& start, UINT& end)
{
	//if (start < 0) start = len - start + 1;
	//if (end < 0) end = len - start + 1;
	if (start == 0) start = 1;
	if (end == 0) end = len;
	if (start > end) { int tmp = end; end = start; start = tmp; }
	if (start < 1 || start > len || end < 1 || end > len || (end - start + 1) > len || end < start) throw std::exception("wrong interval args");
}

MyString::string::string() = default;

MyString::string::string(const char symbol)
{
	AllocMem(1);
	ptr[0] = symbol;
	ptr[1] = '\0';
}

MyString::string::string(const char *str)
{
	AllocMem((UINT)strlen(str));
	strcpy(ptr, str);
}

MyString::string::string(const string &str)
{
	AllocMem(str.len);
	strcpy(ptr, str.ptr);
}

MyString::string::~string() { ClearMem(); }

MyString::string & MyString::string::operator=(const char symbol)
{
	AllocMem(1);
	ptr[0] = symbol;
	return *this;
}

MyString::string & MyString::string::operator=(const char *str)
{
	AllocMem((UINT)strlen(str));
	strcpy(ptr, str);
	return *this;
}

MyString::string & MyString::string::operator=(const string& str)
{
	if (ptr == str.ptr) { return *this; }
	AllocMem(str.len);
	strcpy(ptr, str.ptr);
	return *this;
}

bool MyString::string::operator==(const char symbol){return len == 1 && ptr != nullptr && ptr[0] == symbol;}

bool MyString::string::operator==(const char *str){return strcmp(ptr,str) == 0;}

bool MyString::string::operator==(const string &str) { return (len == str.len && ptr == str.ptr) || strcmp(ptr, str.ptr) == 0; }

bool MyString::string::operator!=(const char symbol){return operator==(symbol) == false;}

bool MyString::string::operator!=(const char *str) {return operator==(str) == false; }

bool MyString::string::operator!=(const string &str) { return operator==(str) == false; }

bool MyString::string::operator>(const char symbol)
{
//	char *tmpstr = (char*)malloc(sizeof(char)*2);//чет не подумал, что могу просто написать char tmpstr[2];. Оставлю этот вариант на память
	char tmpstr[2];
	tmpstr[0] = symbol;
	tmpstr[1] = '\0';
	auto res = strcmp(ptr, tmpstr);//auto, потому что я хз какой точно тип возвращает strcmp, мне просто достаточно знать, что оно может быть >0 и <0
//	free(tmpstr);
	return res > 0;
}

bool MyString::string::operator>(const char *str){return strcmp(ptr, str) > 0;}

bool MyString::string::operator>(const string &str){return strcmp(ptr, str.ptr) > 0;}

//следующие ДЕВЯТЬ(9(nine)) методов можно сделать через strcmp, что потребует меньше действий от программы, но я сделаю через уже готовые операторы
bool MyString::string::operator<(const char symbol){return (operator!=(symbol) == true && operator>(symbol) == false);}

bool MyString::string::operator<(const char *str) { return (operator!=(str) == true && operator>(str) == false); }

bool MyString::string::operator<(const string &str) { return (operator!=(str) == true && operator>(str) == false); }

bool MyString::string::operator>=(const char symbol) { return operator<(symbol) == false; }

bool MyString::string::operator>=(const char *str) { return operator<(str) == false;}

bool MyString::string::operator>=(const string &str) { return operator<(str) == false;}

bool MyString::string::operator<=(const char symbol) { return operator>(symbol) == false;}

bool MyString::string::operator<=(const char *str) { return operator>(str) == false;}

bool MyString::string::operator<=(const string &str) { return operator>(str) == false;}

std::ostream &MyString::operator<<(std::ostream &out, const string &str) { out << str.ptr; return out; }//если ptr будет nullptr, то выбросится исключение

//сделал как показали в примере на практике
std::istream & MyString::operator>>(std::istream & in, string &str)
{
	char buf[255];
	in.getline(buf, 255);
	str = buf;
	return in;
}

//std::istream & MyString::operator>>(std::istream in&, string &str) {in >> ptr*  return in; }

char & MyString::string::operator[](const UINT index) {
	if (index < 1 || index > len) throw std::exception("wrong index");
	return ptr[index-1]; 
}

MyString::string& MyString::string::operator-() { Reverse(); return *this; }

char MyString::string::GetChar(const UINT index) { 
	if (index < 1 || index > len) throw std::exception("wrong index");
	return ptr[index - 1]; 
}

int MyString::string::GetInt(const UINT index)
{
	if (index < 1 || index > len) throw std::exception("wrong index");
	return (int)GetChar(index);
}

MyString::string MyString::string::SubString(const UINT start1, const UINT end1)
{
	UINT start = start1;
	UINT end = end1;
	IntervalException(start, end);
	UINT newlen = end - start + 1;
	string str;
	str.AllocMem(newlen);
	start = (UINT)start;
	end = (UINT)end;
	UINT c = 0;
	for (UINT i = start; i <= end; i++) {
		str.ptr[c] = ptr[i-1];
		c++;
	}
	str.ptr[c] = '\0';
	return str;
}

void MyString::string::SwapSymbols(const UINT a, const UINT b)
{
	if (a < 1 || a > len || b < 1 || b > len) throw std::exception("wrong index");
	char tmp = ptr[a - 1];
	ptr[a - 1] = ptr[b - 1];
	ptr[b - 1] = tmp;
}

void MyString::string::SwapIntervals(const UINT start1, const UINT end1, const UINT start2, const UINT end2)
{
	UINT tmpstart1 = start1; UINT tmpstart2 = start2; UINT tmpend1 = end1; UINT tmpend2 = end2;
	IntervalException(tmpstart1, tmpend1);
	IntervalException(tmpstart2, tmpend2);
	if ((tmpend1 - tmpstart1 + 1) != (tmpend2 - tmpstart2 + 1)) return;//если длины разные  //можно еще сделать свап даже для разных длин, но тогда придется сдвигать, а мне лень писать это

	//если отрезки пересекаются
	for (UINT i = tmpstart1; i <= tmpend1; i++)for (UINT j = tmpstart2; j <= tmpend2; j++)if (i == j) return;

	UINT iter = 0;
	for (UINT i = tmpstart1; i <= tmpend1; i++) {
		SwapSymbols(i, tmpstart2 + iter);
		iter++;
	}
}

void MyString::string::Fill(const char symbol, const UINT start1, const UINT end1, const UINT maxfills1)
{
	UINT start = start1;
	UINT end = end1;
	UINT maxfills = maxfills1;
	IntervalException(start, end);
	if (maxfills == 0) maxfills = end - start + 1;
	for (UINT i = start; i <= end; i++) {
		if (maxfills == 0) return;
		(*this)[i] = symbol;
		maxfills--;
	}
}

void MyString::string::Reverse(const UINT start1, const UINT end1)
{
	UINT start = start1;
	UINT end = end1;
	IntervalException(start, end);
	UINT intervallen = end - start + 1;
	UINT halflen = start + (intervallen / 2);//не знаю, как я это придумал, но это поиск индекса центрального элемента из отрезка. Сначала ищу длину от начала отрезка до его середины, а потом прибавляю расстояние от начала стринга
	UINT iter = 0;
	for (UINT i = start; i < halflen; i++) {
		SwapSymbols(i, UINT(end - iter));
		iter++;
	}
}

UINT MyString::string::GetLen(){return len;}

//возвращает индекс или 0 если ничего не найдено
UINT MyString::string::Find(const char symbol, const UINT start1, const UINT end1)
{
	UINT start = start1;
	UINT end = end1;
	IntervalException(start, end);
	for (UINT i = start; i <= end; i++) {
		if (ptr[i - 1] == symbol) return i;
	}
	return 0;
}

//возвращает индекс начала найденного паттерна или 0, если ничего не найдено
UINT MyString::string::Find(const char *str, const UINT start1, const UINT end1)
{
	UINT start = start1;
	UINT end = end1;
	IntervalException(start, end);
	UINT tmpstrlen = (UINT)strlen(str);
	UINT intervallen = end - start + 1;
	if (intervallen < tmpstrlen) return 0;//вместо этого можно выбросить исключение, но я хз как лучше
	for (UINT i = start; i <= (end - tmpstrlen + 1); i++) if (strncmp(&ptr[i - 1], str, tmpstrlen) == 0) return i;
	return 0;
}

UINT MyString::string::Find(const string &str, const UINT start, const UINT end){return Find(str.ptr,start,end);}

MyString::string MyString::string::operator+(const char symbol){
	if (len == 0) {
		return string(symbol);
	}
	else {
		string tmpstring;
		tmpstring.AllocMem(len + 1);
		strcpy(tmpstring.ptr, ptr);
		tmpstring.ptr[tmpstring.len - 1] = symbol;
		tmpstring.ptr[tmpstring.len] = '\0';
		return tmpstring;
	}
}

MyString::string MyString::string::operator+(const char *str)
{
	if (len == 0) {
		return string(str);
	}
	else {
		UINT strl = (UINT)strlen(str);
		string tmpstring;
		tmpstring.AllocMem(len + strl);
		UINT curi = 0;
		//посимвольно копирую
		for (UINT i = 1; i <= len; i++) {
			tmpstring.ptr[curi] = ptr[i - 1];
			curi++;
		}
		for (UINT i = 1; i <= strl; i++) {
			tmpstring.ptr[curi] = str[i - 1];
			curi++;
		}
		tmpstring.ptr[curi] = '\0';
		return tmpstring;
	}
}

MyString::string MyString::string::operator+(const string &str)
{
	if (str.len != 0) {
		UINT newlen = len + str.len;
		//создаю временный стринг, в котором буду хранить новую строку
		string tmpstring;
		tmpstring.AllocMem(newlen);
		//посимвольно копирую (можно было исопльзовать strcpy)
		UINT curi = 0;
		for (UINT i = 1; i <= len; i++) {
			tmpstring.ptr[curi] = ptr[i - 1];
			curi++;
		}
		for (UINT i = 1; i <= str.len; i++) {
			tmpstring.ptr[curi] = str.ptr[i - 1];
			curi++;
		}
		tmpstring.ptr[curi] = '\0';
		//временный tmpstring умрет и очистит за собой память, чего я не хочу
		//но если я изменю его деструктор, то он вообще никогда не очистит память
		//решение - использовать конструктор копирования
		return tmpstring;
	}
	else {
		return string(*this);
	}
}


//следующие три метода можно сделать чуть оптимизированнее, но я сделал так, чтобы меньше писать кода
MyString::string& MyString::string::operator+=(const char symbol) { *this = *this + symbol; return *this; }

MyString::string& MyString::string::operator+=(const char *str) { *this = *this + str; return *this;}

MyString::string& MyString::string::operator+=(const string &str) { *this = *this + str; return *this;}

bool MyString::operator==(const char left , string &right) {return right.operator==(left);}

bool MyString::operator==(const char *left, string &right) {return right.operator==(left);}

bool MyString::operator!=(const char left, string &right) {return right.operator!=(left);}

bool MyString::operator!=(const char *left, string &right) { return right.operator!=(left); }

bool MyString::operator>(const char left, string &right) {return right.operator<(left);}

bool MyString::operator>(const char *left, string &right) { return right.operator<(left); }

bool MyString::operator<(const char left, string &right) { return right.operator>(left); }

bool MyString::operator<(const char *left, string &right) { return right.operator>(left); }

bool MyString::operator>=(const char left, string &right) { return right.operator<=(left); }

bool MyString::operator>=(const char *left, string &right) { return right.operator<=(left); }

bool MyString::operator<=(const char left, string &right) { return right.operator>=(left); }

bool MyString::operator<=(const char *left, string &right) { return right.operator>=(left); }

string MyString::operator+(const char left, string &right)
{
	string tmpstr;
	tmpstr.AllocMem(right.len + 1);
	tmpstr[1] = left;
	//можно было через strcpy, но я решил так, так как у меня есть удобный operator[]
	//то есть вот так strcpy(&tpmstr.ptr[1], right.ptr)
	for (UINT i = 1; i <= right.len; i++) tmpstr[i + 1] = right[i];
	tmpstr.ptr[tmpstr.len] = '\0';
	return tmpstr;
}

string MyString::operator+(const char *left, string &right)
{
	string tmpstr;
	UINT charlen = (UINT)strlen(left);
	tmpstr.AllocMem(right.len + charlen);

	//копирую левую часть
	strcpy(tmpstr.ptr, left);

	//копирую правую часть
	strcpy(&tmpstr.ptr[charlen], right.ptr);

	return tmpstr;
}
