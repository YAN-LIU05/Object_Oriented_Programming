/* 2352018 ������ ���� */

/* ���������Ҫ��ͷ�ļ����궨��� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <cstring>
#include "16-b6.h"
using namespace std;

/* ���� enum class week ������г�Ա����������ʵ�� */
ostream& operator<<(ostream& os, const week& w) 
{
    switch (w) 
    {
        case week::sun: 
            os << "������"; break;
        case week::mon: 
            os << "����һ"; break;
        case week::tue: 
            os << "���ڶ�"; break;
        case week::wed: 
            os << "������"; break;
        case week::thu: 
            os << "������"; break;
        case week::fri: 
            os << "������"; break;
        case week::sat: 
            os << "������"; break;
        default: 
            os << "����"; break;
    }
    return os;
}

istream& operator>>(istream& is, week& w) 
{
    char input[1024];  // ���������ַ����ĳ��Ȳ��ᳬ�� 1024 ���ַ�
    is >> input;

    // ������ת��ΪСд��ĸ���бȽ�
    for (int i = 0; input[i] != '\0'; ++i) 
        input[i] = my_tolower(input[i]);

    if (strcmp(input, "sun") == 0) 
        w = week::sun;
    else if (strcmp(input, "mon") == 0) 
        w = week::mon;
    else if (strcmp(input, "tue") == 0) 
        w = week::tue;
    else if (strcmp(input, "wed") == 0) 
        w = week::wed;
    else if (strcmp(input, "thu") == 0) 
        w = week::thu;
    else if (strcmp(input, "fri") == 0) 
        w = week::fri;
    else if (strcmp(input, "sat") == 0) 
        w = week::sat;
    else 
        w = static_cast<week>(10); //һ������ֵ

    return is;
}

week& operator++(week& w) 
{
    w = static_cast<week>((static_cast<int>(w) + 1) % 7);
    return w;
}

week operator++(week& w, int) 
{
    week old = w;
    ++w;
    return old;
}

week& operator--(week& w) 
{
    w = static_cast<week>((static_cast<int>(w) + 6) % 7);
    return w;
}

week operator--(week& w, int) 
{
    week old = w;
    --w;
    return old;
}

week operator+(week w, int n) 
{
    int new_day = (static_cast<int>(w) + n) % 7;
    if (new_day < 0) 
        new_day += 7;  // �����������ȷ���ڷ�Χ��
    return static_cast<week>(new_day);
}

week operator-(week w, int n) 
{
    int new_day = (static_cast<int>(w) - n) % 7;
    if (new_day < 0) 
        new_day += 7;  // �����������ȷ���ڷ�Χ��
    return static_cast<week>(new_day);
}

week& operator+=(week& w, int n) 
{
    w = w + n;
    return w;
}

week& operator-=(week& w, int n)
{
    w = w - n;
    return w;
}

char my_tolower(char c) 
{
    if (c >= 'A' && c <= 'Z') 
        return c + ('a' - 'A');
    return c;
}