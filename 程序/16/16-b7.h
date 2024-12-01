/* 2352018 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

enum week { sun, mon, tue, wed, thu, fri, sat };

/* ���������Ӧ�ĺ������� */
ostream& operator<<(ostream& os, const week& w);
istream& operator>>(istream& is, week& w);
week& operator++(week& w);
week operator++(week& w, int);
week& operator--(week& w);
week operator--(week& w, int);
week operator+(week w, int n);
week operator-(week w, int n);
week& operator+=(week& w, int n);
week& operator-=(week& w, int n);
char my_tolower(char c);