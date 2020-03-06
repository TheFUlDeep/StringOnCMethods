#define _CRT_SECURE_NO_WARNINGS //потому что strcpy небезопасный метод как и остальные методы
//strlen возвращает size_t, и я везде принудительно преобразовываю его в unsigned int
#include "MyString.h"
#include <cmath>

using namespace MyString;

//TODO убрать все вычитания на единицу
//TODO при преобразовании в число преобразовывать символ 'е' (степень)

void MyString::string::ClearMem() {if (ptr != nullptr) free(ptr); }

void MyString::string::AllocMem(UINT strlen)
{
	ClearMem();
	ptr = (char*)malloc(sizeof(char)*(strlen+1));
	len = strlen;
}

void MyString::string::IntervalException(UINT& start, UINT& end)const
{
	//if (start < 0) start = len - start + 1;
	//if (end < 0) end = len - start + 1;
	if (start == 0) start = 1;
	if (end == 0) end = len;
	if (start > end) { int tmp = end; end = start; start = tmp; }
	if (start < 1 || start > len || end < 1 || end > len || (end - start + 1) > len || end < start) throw std::exception("wrong interval args");
}

int MyString::string::CharToInt(const char c)const { return (int)c;}

short MyString::string::CharToNumber(const char symbol)const
{
	short res = symbol - '0';
	if (res > 9 || res < 0) throw std::exception("cant get number");
	return res;
}

char MyString::string::CharUpper(const char symbol) const
{
	int intsym = int(symbol);
	if (intsym >= 97 && intsym <= 122) return (char)(intsym - 32);
	else return symbol;
}

char MyString::string::CharLower(const char symbol) const
{
	int intsym = int(symbol);
	if (intsym >= 65 && intsym <= 90) return (char)(intsym + 32);
	else return symbol;
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

bool MyString::string::operator==(const char symbol)const {return len == 1 && ptr != nullptr && ptr[0] == symbol;}

bool MyString::string::operator==(const char *str)const {return strcmp(ptr,str) == 0;}

bool MyString::string::operator==(const string &str)const { return (len == str.len && (ptr == str.ptr || strcmp(ptr, str.ptr) == 0)); }

bool MyString::string::operator!=(const char symbol)const {return operator==(symbol) == false;}

bool MyString::string::operator!=(const char *str)const {return operator==(str) == false; }

bool MyString::string::operator!=(const string &str)const { return operator==(str) == false; }

bool MyString::string::operator>(const char symbol)const
{
//	char *tmpstr = (char*)malloc(sizeof(char)*2);//чет не подумал, что могу просто написать char tmpstr[2];. Оставлю этот вариант на память
	char tmpstr[2];
	tmpstr[0] = symbol;
	tmpstr[1] = '\0';
	auto res = strcmp(ptr, tmpstr);//auto, потому что я хз какой точно тип возвращает strcmp, мне просто достаточно знать, что оно может быть >0 и <0
//	free(tmpstr);
	return res > 0;
}

bool MyString::string::operator>(const char *str)const {return strcmp(ptr, str) > 0;}

bool MyString::string::operator>(const string &str)const {return operator>(str.ptr);}

bool MyString::string::operator<(const char symbol)const {return (operator!=(symbol) == true && operator>(symbol) == false);}

bool MyString::string::operator<(const char *str)const { return strcmp(ptr,str); }

bool MyString::string::operator<(const string &str)const { return operator<(str.ptr); }

bool MyString::string::operator>=(const char symbol)const { return operator<(symbol) == false; }

bool MyString::string::operator>=(const char *str)const { return operator<(str) == false;}

bool MyString::string::operator>=(const string &str)const { return operator<(str) == false;}

bool MyString::string::operator<=(const char symbol)const { return operator>(symbol) == false;}

bool MyString::string::operator<=(const char *str)const { return operator>(str) == false;}

bool MyString::string::operator<=(const string &str)const { return operator>(str) == false;}

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

char & MyString::string::operator[](const UINT index)const {
	if (index < 1 || index > len) throw std::exception("wrong index");
	return ptr[index-1]; 
}

MyString::string MyString::string::operator-()const { MyString::string tmpstr = *this; tmpstr.Reverse(); return tmpstr; }

char MyString::string::Char(const UINT index)const {
	if (index < 1 || index > len) throw std::exception("wrong index");
	return ptr[index - 1]; 
}

int MyString::string::Int(const UINT index)const
{
	if (index < 1 || index > len) throw std::exception("wrong index");
	return (int)Char(index);
}

MyString::string MyString::string::SubString(const UINT start1, const UINT end1)const
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

	//если отрезки пересекаются
	for (UINT i = tmpstart1; i <= tmpend1; i++)for (UINT j = tmpstart2; j <= tmpend2; j++)if (i == j) return;

	//делаю так, чтобы tmpstart1 -- tmpend1 всегда был левым
	if (tmpstart1 > tmpstart2)
	{
		UINT tmp;
		tmp = tmpstart1;
		tmpstart1 = tmpstart2;
		tmpstart2 = tmp;

		tmp = tmpend1;
		tmpend1 = tmpend2;
		tmpend2 = tmp;
	}

	//сделал так, чтобы можно было свапать даже разные интервалы
	string newstr;
	if ((tmpstart1 - 1) > 0) newstr = this->SubString(0, tmpstart1 - 1);
	newstr += this->SubString(tmpstart2, tmpend2);
	if ((tmpstart2 - tmpend1) > 1) newstr += this->SubString(tmpend1+1, tmpstart2-1);
	newstr += this->SubString(tmpstart1, tmpend1);
	if (tmpend2 < len) newstr += this->SubString(tmpend2 + 1);
	*this = newstr;
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

MyString::string::operator int()const
{
	UINT point = Find('.');
	if (point == 0) point = len + 1;

	bool firstminus = false;
	UINT startpos = 1;
	if (operator[](1) == '-') { firstminus = true; startpos = 2; }

	//пытаюсь перевести каждый символ после точки в число (таким образом выясняю, есть ли там символы кроме цифр). Если там есть другой символ, вылетит исключение
	if (point < len) for (UINT i = point+1; i <= len; i++) { auto a = CharToNumber(operator[](i)); }

	int res = 0;
	for (UINT i = startpos; i < point; i++) res += (CharToNumber(operator[](i)) * ((UINT)pow(10, point - 1 - i)));
	if (firstminus) res = -res;
	return res;
}

MyString::string::operator double()const
{
	UINT point = Find('.');
	if (point == 0) point = len+1;

	//если в строке несколько точек, то это не дабл
	//else if (point != len && Find('.', point + 1) != 0) throw std::exception("its not double");//это все-таки не нужно, так как CharToNumber пройдет по всеми символам и выкинет исключение в случае если там есть не цифра

	bool firstminus = false;
	UINT startpos = 1;
	if (operator[](1) == '-') { firstminus = true; startpos = 2; }

	double res = 0;
	for (UINT i = startpos; i <= len; i++)
	{
		if (i < point)
		{
			res += (CharToNumber(operator[](i)) * (pow(10, (int)(point - i - 1))));
		}
		else if (i > point)
		{
			res += (CharToNumber(operator[](i)) * (pow(10, (int)(point - i))));
		}
	}
	if (firstminus) res = -res;
	return res;
}

UINT MyString::string::Len()const {return len;}

const char * MyString::string::CString()const {return ptr;}

string MyString::string::Lower() const
{
	string tmpstr = *this;
	for (UINT i = 1; i <= tmpstr.len; i++)
	{
		tmpstr.ptr[i - 1] = CharLower(tmpstr.ptr[i - 1]);
	}
	return tmpstr;
}

string MyString::string::Upper() const
{
	string tmpstr = *this;
	for (UINT i = 1; i <= tmpstr.len; i++)
	{
		tmpstr.ptr[i - 1] = CharUpper(tmpstr.ptr[i - 1]);
	}
	return tmpstr;
}

char * MyString::string::begin() const {return &ptr[0];}

char * MyString::string::end() const { return &ptr[len+1]; }

const char * MyString::string::cbegin() const { return &ptr[0]; }

const char * MyString::string::cend() const { return &ptr[len + 1]; }

char * MyString::string::rbegin() const { return &ptr[len]; }

char * MyString::string::rend() const { return &ptr[-1]; }

const char * MyString::string::crbegin() const { return &ptr[len]; }

const char * MyString::string::crend() const { return &ptr[-1]; }

//возвращает индекс или 0 если ничего не найдено
UINT MyString::string::Find(const char symbol, const UINT start1, const UINT end1)const
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
UINT MyString::string::Find(const char *str, const UINT start1, const UINT end1)const
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

UINT MyString::string::Find(const string &str, const UINT start, const UINT end)const {return Find(str.ptr,start,end);}

void MyString::string::InsertAfter(const UINT index, const char symbol)
{
	if (index > len) return;
	string newstr;
	newstr.AllocMem(len + 1);
	strncpy(newstr.ptr, ptr, index);
	newstr[index+1] = symbol;
	strcpy(&newstr.ptr[index + 1], &ptr[index]);
	*this = newstr;
}

void MyString::string::InsertAfter(const UINT index, const char *str)
{
	if (index > len) return;
	UINT strl = (UINT)strlen(str);
	string newstr;
	newstr.AllocMem(len + strl);
	strncpy(newstr.ptr, ptr, index);
	strcpy(&newstr.ptr[index], str);
	strcpy(&newstr.ptr[index+strl], &ptr[index]);
	*this = newstr;
}

void MyString::string::InsertAfter(const UINT index, const string &str) {InsertAfter(index, str.ptr);}

MyString::string MyString::string::operator+(const char symbol)const
{
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

MyString::string MyString::string::operator+(const char *str)const
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

MyString::string MyString::string::operator+(const string &str)const
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

bool MyString::operator==(const char left , const string &right) {return right.operator==(left);}

bool MyString::operator==(const char *left, const string &right) {return right.operator==(left);}

bool MyString::operator!=(const char left, const string &right) {return right.operator!=(left);}

bool MyString::operator!=(const char *left, const string &right) { return right.operator!=(left); }

bool MyString::operator>(const char left, const string &right) {return right.operator<(left);}

bool MyString::operator>(const char *left, const string &right) { return right.operator<(left); }

bool MyString::operator<(const char left, const string &right) { return right.operator>(left); }

bool MyString::operator<(const char *left, const string &right) { return right.operator>(left); }

bool MyString::operator>=(const char left, const string &right) { return right.operator<=(left); }

bool MyString::operator>=(const char *left, const string &right) { return right.operator<=(left); }

bool MyString::operator<=(const char left, const string &right) { return right.operator>=(left); }

bool MyString::operator<=(const char *left, const string &right) { return right.operator>=(left); }

string MyString::operator+(const char left, const string &right)
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

string MyString::operator+(const char *left, const string &right)
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