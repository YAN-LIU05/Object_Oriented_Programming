/* 2352018 ������ ���� */

#pragma once

#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
private:
	char* content;
	int   len;
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
	void copy_strings(char* dest, const char* src1, int len1, const char* src2, int len2);
	void append_to_content(const char* appendStr, int appendLen);
public:
	/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */

	/* ���캯�� */
	TString();                                                           // Ĭ�Ϲ��캯��
	~TString();                                                          // ��������
	TString(const char* str);                                            // һ�ι��캯��
	TString(const TString& other);                                       // һ�ι��캯��
	char* c_str() const;                                                 // ���ƹ��캯��
	
	/* ��������� */
	TString& operator= (const TString& other);                           // ����=
	
	friend ostream& operator<< (ostream& out, const TString& str);       // ����<<
	friend istream& operator>> (istream& in, TString& str);              // ����>>
	
	friend const TString operator+(const TString& str1, const TString& str2);// ��һ���ӷ���������أ�TString + TString
	friend const TString operator+(const TString& str1, const char* str2);   // �ڶ����ӷ���������أ�TString + const char*
    friend const TString operator+(const char c, const TString& str);      // �������ӷ���������أ�char + TString
	friend const TString operator+(const TString& str, const char c);      // ���ĸ��ӷ���������أ�TString + char

	TString& operator+=(const TString& other);                         // ��һ���Ӹ�ֵ��������أ�TString
	TString& operator+=(const char* str);                                // �ڶ����Ӹ�ֵ��������أ�const char* 
	TString& operator+=(const char c);                                 // �������Ӹ�ֵ��������أ�char  
	 
	friend TString operator-(const TString& str1, const TString& str2);    // ��һ��������������أ�TString - TString
	friend TString operator-(const TString& str1, const char c);         // �ڶ���������������أ�TString - char

	TString& operator-=(const TString& str);                             // ��һ������ֵ��������أ�TString
	TString& operator-=(const char c);                                 // �ڶ�������ֵ��������أ�char  

	TString operator*(int n) const;                                    // ����*  

	TString& operator*=(const int n);                                  // ����*=

	TString operator!();                                               // ����!

	friend bool operator<(const TString& str1, const TString& str2);       // ����<
	friend bool operator>(const TString& str1, const TString& str2);       // ����>
	friend bool operator<=(const TString& str1, const TString& str2);      // ����<=
	friend bool operator>=(const TString& str1, const TString& str2);      // ����>=
	friend bool operator==(const TString& str1, const TString& str2);      // ����==
	friend bool operator!=(const TString& str1, const TString& str2);      // ����!=

	char& operator[](const int n);                                     // ����[]

	/* �������� */
	void append(const TString& other);
	TString& append(const char c);
	TString& append(const char* str);
	int length();
	friend int TStringLen(const TString& str);
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
void my_exit(char*& content);                                                //�ڴ�����⺯��
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
