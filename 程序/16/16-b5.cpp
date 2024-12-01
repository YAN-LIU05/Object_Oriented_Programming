/* 2352018 ������ ���� */

/* ���������Ҫ��ͷ�ļ����궨��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "16-b5.h"
using namespace std;

/* ���� TString ������г�Ա����������ʵ�� */
TString::TString()
{
    len = 0;  // ��ʼ������Ϊ0
    content = new(nothrow) char[len + 1];  // �����ڴ棬ʹ�� 'nothrow' ��ֹ�׳��쳣
    my_exit(content);
    content[0] = '\0';  // ����һ���ַ�����Ϊ '\0'����ʾ���ַ���
}

TString::TString(const char* str)
{
    len = (str == nullptr) ? 0 : strlen(str);  // �����ַ����ĳ��ȣ���� s Ϊ nullptr���򳤶�Ϊ 0

    // ʹ�� new �����ڴ棬���ڷ���ʧ��ʱ���� nullptr
    content = new(nothrow) char[len + 1];

    my_exit(content);

    if (str == nullptr)
        content[0] = '\0';  // ��� s Ϊ nullptr���� content ��ʼ��Ϊ���ַ���
    else
        strcpy(content, str);  // ���� s �����ݵ� content
}

TString::TString(const TString& other)
{
    len = other.len;  // ���Ƴ���
    content = new(nothrow) char[len + 1];  // ʹ�� 'new' �����ڴ�

    my_exit(content);

    strcpy(content, other.content);  // ��������
}

TString::~TString()
{
    len = 0;
    delete[]content;
}

char* TString::c_str() const
{
    return content;
}

TString& TString::operator= (const TString& other)
{
    if (this != &other)
    {
        delete[]content;
        len = other.len;
        content = new(nothrow) char[len + 1]; 

        my_exit(content);
        strcpy(content, other.content);
    }
    return *this;
}

ostream& operator<< (ostream& out, const TString& str) 
{
    if (str.len == 0)
        out << "<EMPTY>";
    else
        out << str.content;
    return out;
}

istream& operator>> (istream& in, TString& str)
{
    char temp[2048] = { '\0' };
    in >> temp;
    str.len = strlen(temp);
    delete[]str.content;
    str.content = new(nothrow) char[str.len + 1];

    my_exit(str.content);
    strcpy(str.content, temp);
    return in;
}

const TString operator+(const TString& str1, const TString& str2) 
{
    TString temp;
	temp.len = str1.len + str2.len;
    temp.content = new(nothrow) char[str1.len + str2.len + 1];
    my_exit(temp.content);

    temp.copy_strings(temp.content, str1.content, str1.len, str2.content, str2.len);
    return temp;
}

const TString operator+(const TString& str1, const char* str2) 
{
    TString temp;
    int str2_len = (str2 != nullptr) ? strlen(str2) : 0;
	temp.len = str1.len + str2_len;
    temp.content = new(nothrow) char[str1.len + str2_len + 1];
    my_exit(temp.content);
    temp.copy_strings(temp.content, str1.content, str1.len, str2, str2_len);
    return temp;
}

const TString operator+(const char c, const TString & str) 
{
    TString temp;
	temp.len = str.len + 1;
    temp.content = new(nothrow) char[str.len + 1 + 1];
    my_exit(temp.content);
    temp.content[0] = c;
    temp.copy_strings(temp.content + 1, str.content, str.len, "", 0);

    return temp;
}

const TString operator+(const TString& str, const char c)
{
    TString temp;
	temp.len = str.len + 1;
    temp.content = new(nothrow) char[str.len + 1 + 1];
    my_exit(temp.content);
	memcpy(temp.content, str.content, str.len * sizeof(char));
	temp.content[temp.len - 1] = c;
	temp.content[temp.len] = '\0';

    return temp;
}

TString& TString::operator+=(const TString& other) 
{
    append_to_content(other.content, other.len);
    return *this;
}

TString& TString::operator+=(const char* s) 
{
    if (s) 
        append_to_content(s, strlen(s));
    return *this;
}

TString& TString::operator+=(const char c) 
{
    char temp[2] = { c, '\0' };  // ����ʱ�ַ���
    append_to_content(temp, 1);
    return *this;
}

TString operator-(const TString& str1, const TString& str2) 
{
	// ���� str2 �� str1 �е�λ��
	int* tmp = new (std::nothrow) int[str2.len];
	if (tmp == nullptr)
	{
		cerr << "�ڴ����ʧ��" << endl;
		exit(-1); 
	}

	memset(tmp, 0, sizeof(int) * str2.len);

	// ���� tmp ����
	int i = 1, j = 0;
	while (i < str2.len)
	{
		if (str2.content[i] == str2.content[j])
			tmp[i++] = ++j;
		else
		{
			if (j != 0)
				j = tmp[j - 1];
			else
				tmp[i++] = 0;
		}
	}

	// ƥ�����
	i = 0, j = 0;
	int locate = -1;
	while (i < str1.len)
	{
		if (str1.content[i] == str2.content[j]) 
		{
			++i;
			++j;
		}
		if (j == str2.len) 
		{
			locate = i - j;  // �ҵ���ȫ��ͬ���Ӵ�����¼����ʼλ��
			break;
		}
		else if (i < str1.len && str1.content[i] != str2.content[j]) 
		{
			if (j != 0)
				j = tmp[j - 1];
			else
				++i;
		}
	}

	delete[] tmp;

	if (locate == -1)
		return str1;

	// �����µ� TString ���� temp
	TString temp;

	temp.len = str1.len - str2.len;
	temp.content = new char[str1.len - str2.len + 1];
	my_exit(temp.content);

	// ���� str1 ��ȥ���Ӵ�������ݵ� temp.content
	for (int i = 0; i < locate; i++) 
		temp.content[i] = str1.content[i];  // �� str1 �� locate ֮ǰ�����ݸ��Ƶ� temp ��

	for (int i = locate, j = locate + str2.len; j < str1.len; i++, j++) 
		temp.content[i] = str1.content[j];  // ����ȥ���Ӵ����ʣ������

	temp.content[str1.len - str2.len] = '\0';  // ��֤�ַ���������

	return temp;
}

TString operator-(const TString& str1, const char c) 
{
	char str2[2] = { c, '\0' };

	// �����ַ� c �� str1 �е�λ��
	int length = str1.len;

	int* tmp = new (std::nothrow) int[1];
	if (tmp == nullptr)
		exit(-1);  // �ڴ����ʧ�ܣ��˳�����

	// ��ʼ�� tmp ����
	tmp[0] = 0;

	int i = 0, j = 0;
	int locate = -1;
	while (i < length) 
	{
		if (str1.content[i] == str2[j]) 
		{
			++i;
			++j;
		}
		if (j == 1) 
		{
			locate = i - j;  // �ҵ��ַ���λ��
			break;
		}
		else if (i < length && str1.content[i] != str2[j]) 
		{
			if (j != 0)
				j = tmp[j - 1];
			else
				++i;
		}
	}

	delete[] tmp;

	if (locate == -1)
		return str1;

	// �����µ� TString ���� temp
	TString temp;
	temp.len = str1.len - 1;

	// �ֶ������ڴ�
	temp.content = new char[temp.len + 1];
	if (temp.content == nullptr)
		exit(-1);  // �ڴ����ʧ�ܣ��˳�����

	// ���� str1 ��ȥ���ַ�������ݵ� temp.content
	for (int i = 0; i < locate; i++)
		temp.content[i] = str1.content[i];

	for (int i = locate; str1.content[i + 1] != '\0'; i++)
		temp.content[i] = str1.content[i + 1];

	temp.content[temp.len] = '\0';  // ��֤�ַ���������

	return temp;
}

TString& TString::operator-=(const TString& str)
{
	if (str.len == 0 || len < str.len)
		return *this;

	// ��������ƥ���
	int* tmp = new (std::nothrow) int[str.len];
	if (tmp == nullptr)
	{
		std::cerr << "�ڴ����ʧ��" << std::endl;
		exit(-1);
	}
	memset(tmp, 0, sizeof(int) * str.len);

	int i = 1, j = 0;
	while (i < str.len) {
		if (str.content[i] == str.content[j]) 
			tmp[i++] = ++j;
		else if (j != 0) 
			j = tmp[j - 1];
		else 
			tmp[i++] = 0;
	}

	// �������ַ���
	i = 0, j = 0;
	int locate = -1; // �Ӵ�λ��
	while (i < len) {
		if (content[i] == str.content[j]) 
		{
			i++;
			j++;
		}
		if (j == str.len) 
		{
			locate = i - j; // �ҵ��Ӵ���ʼλ��
			break;
		}
		else if (i < len && content[i] != str.content[j]) 
		{
			if (j != 0) 
				j = tmp[j - 1];
			else 
				i++;
		}
	}
	delete[] tmp;

	// ���δ�ҵ�������ԭ�ַ���
	if (locate == -1)
		return *this;

	// ɾ���Ӵ�
	len -= str.len;
	char* temp = nullptr;
	temp = new(nothrow) char[len + 1];
	my_exit(temp);

	for (int k = 0; k < locate; k++)
		temp[k] = content[k];
	for (int k = locate; content[k + str.len] != '\0'; k++)
		temp[k] = content[k + str.len];

	delete[] content;
	content = temp;
	content[len] = '\0';
	return *this;
}

TString& TString::operator-=(const char c)
{
	char str2[2] = { c, '\0' };
	TString temp(str2);
	return (*this -= temp);
}

TString TString::operator*(int n) const 
{
	if (n <= 0) 
		return TString("");  // ���ؿ��ַ���

	TString temp;  // ����һ���յ��ַ���
	for (int i = 0; i < n; i++) 
		temp += *this;  // ��ԭ�ַ���׷�ӵ� temp ��
	return temp;
}

TString& TString::operator*=(const int n)
{
	if (n <= 0)	// ��� n <= 0��ֱ������ַ���
	{
		TString empty;
		*this = empty;
		return *this;
	}

	// �����µ��ڴ�ռ�
	char* new_content = new char[len * n + 1];

	// ��ԭ�ַ����ظ� n ����䵽 new_content
	for (int i = 0; i < n; ++i)
		strcpy(new_content + i * len, content);

	// �ͷ�ԭ���ڴ沢���� content �� len
	delete[] content;
	content = new_content;
	len = len * n;

	return *this;
}

TString TString::operator!() // �Լ�������ת�����Է�����ʱ����
{
	TString temp = *this;
	temp.content = new(nothrow) char[len + 1];
	my_exit(temp.content);
	for (int i = 0; i < len; i++)
		temp.content[i] = content[len - i - 1];
	temp.content[len] = '\0';
	return temp; // �Լ�������ת�����Է�����ʱ����
}

bool operator<(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") < 0;
}

bool operator>(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") > 0;
}

bool operator<=(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") <= 0;
}

bool operator>=(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") >= 0;
}

bool operator==(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") == 0;
}

bool operator!=(const TString& str1, const TString& str2) 
{
	return strcmp(str1.content ? str1.content : "", str2.content ? str2.content : "") != 0;
}

char& TString::operator[](const int n)
{
	return content[n];
}

void TString::append(const TString& other) 
{
	*this += other;
}

TString& TString::append(const char* str) 
{
	*this += str;
	return *this;
}

TString& TString::append(const char c) 
{
	*this += c;
	return *this;
}

int TString::length()
{
	return len;
}
int TStringLen(const TString& str)
{
	return str.len;
}

void TString::copy_strings(char* dest, const char* src1, int len1, const char* src2, int len2)
{
    // ʹ�� memcpy �ϲ������ַ���
    memcpy(dest, src1, len1 * sizeof(char));
    memcpy(dest + len1, src2, len2 * sizeof(char));
    dest[len1 + len2] = '\0';  // ȷ��Ŀ���ַ����� '\0' ��β
}

void TString::append_to_content(const char* append_str, int append_len) 
{
    int old_len = len;
    len += append_len;

    // �������ڴ�
    char* new_content = new (nothrow) char[len + 1];
    my_exit(new_content);

    // ���ƾ����ݺ�׷�ӵ�������
    if (content) 
    {
        memcpy(new_content, content, old_len * sizeof(char));
        delete[] content;
    }
    memcpy(new_content + old_len, append_str, append_len * sizeof(char));

    // ���� content
    content = new_content;
    content[len] = '\0';
}

/* �������Ҫ������ȫ�ֺ�����ʵ�֣�����д�ڴ˴� */
void my_exit(char* &content)
{
    if (!content)  // ����ڴ�����Ƿ�ɹ�
    {
        cerr << "�ڴ����ʧ��" << endl;
        exit(-1);  //������ֹ
    }
}

