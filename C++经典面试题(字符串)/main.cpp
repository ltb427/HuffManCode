#include<iostream>
#include<cassert>
#include<string>
#include<stdio.h>
#include<new>
#include<cstdio>
#include<cstdlib>
#include"huffman.h"
using namespace std;


/*在不使用itoa函数将数组转换为字符串*/
void itoa_me(void);
/*编写strcpy函数*/
char* strcpy_me(char* strDest, const char* strSrc);
/*字符移位*/
void LoopMove(char* pstr, int steps);
/*字符串翻转*/
void getback(void);
/*字符串查找*/
void find(void);
/*string 类*/
int strlen_me(const char* str);
/*gbktoutf8*/
//申请二维动态数组
template<typename T>
T** new_Array2D(const int row, const int col)
{
	int size = sizeof(T);
	int point_size = sizeof(T*);
	T** arr = (T**)malloc(point_size*row + size*row*col);
	if (arr != NULL)
	{
		T* head = (T*)((int)arr + point_size*row);
		for (int i = 0; i < row; ++i)
		{
			arr[i] = (T*)((int)head + i*col*size);
			for (int j = 0; j < col; ++j)
				new (&arr[i][j]) T;
		}
	}
	return (T**)arr;
}
//shifang
template<typename T>
void delete_Array2D(T** arr, const int row, const int col)
{
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
			arr[i][j].~T();
	}
	if (arr != NULL)
	{
		free((void**)arr);
	}
}

class string_me {
public:
	string_me(const char* str = NULL);//普通构造函数
	string_me(const string_me &other);//拷贝构造函数
	~string_me(void);
	string_me& operator=(const string_me &other);//赋值函数
private:
	char* m_data;
};

string_me::string_me(const char* str) {
	if (str == NULL) {
		m_data = new char[1];
		*m_data = '\0';
	}
	else {
		int length = strlen(str);
		m_data = new char[length + 1];
		strcpy(m_data, str);
	}
}

string_me::~string_me() {
	delete[] m_data;
}

string_me::string_me(const string_me &other) {
	int length = strlen(other.m_data);
	m_data = new char[length + 1];
	strcpy(m_data, other.m_data);
}

string_me& string_me::operator=(const string_me &other) {
	if (this == &other) {
		return *this; delete[] m_data;
	}
	int length = strlen(other.m_data) + 1;
	strcpy(m_data, other.m_data);
	return *this;
}



int main() {
	const char* str = "aba";
	Test(str);
	return 0;
}
void getback(void) {
	char str[] = "i come from beijing";
	char temp[256];
	int i = 0;
	int j = strlen(str);
	for (int index = j-1; index >= 0; --index) {
		temp[i] = str[index];
		++i;
	}
	temp[j] = 0;
	strcpy(str, temp);
	cout << "string:" << str << endl;
}

void itoa_me(void) {
	int  number=12345,i = 0, j = 0;
	char temp[7], str[7];
	while (number) {
		temp[i] = number % 10 + '0';
		++i;
		number = number / 10;
	}
	temp[i] = 0;
	cout << "temp: " << temp << endl;
	i = i - 1;
	while (i>=0){
		str[j++] = temp[i--];
	}
	str[j] = 0;
	cout << "string:" << str << endl;
}

char* strcpy_me(char* strDest, const char* strSrc) {
	assert(strDest != NULL && (strSrc != NULL));
	char* address = strDest;
	while ((*strDest++ = *strSrc++) != '\0')
	NULL;
	return address;
}

void LoopMove(char* pstr, int steps) {
	int n = strlen(pstr) - steps;
	char temp[256];
	strcpy(temp, pstr+n);
	strcpy(temp + steps, pstr);
	*(temp + strlen(pstr)) = '\0';
	strcpy(pstr, temp);
}

void find(void) {
	string str, tep;
	cout << "请输入字符串:";
	cin >> str;
	for (int i = str.length() - 1; i > 1; i--) {
		for (int j = 0; j < str.length(); j++) {
			size_t t = 0;
			size_t num = 0;
			tep = str.substr(j, i);
			t = str.find(tep);
			num = str.rfind(tep);
			if (t != num) {
				cout << tep << " " << t + 1 << endl;
			}
		}
	}
}
int strlen_me(const char* str) {
	char* substr = const_cast<char*>(str);
	unsigned int length = 0;
	if (str == NULL) {
		return 0;
	}
	else {
		while (*substr++ != '\0')
			length++;
	}
	return length;
}
