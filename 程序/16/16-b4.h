/* 2352018 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
private:
	int year;
	int month;
	int day;
	/* ������������ݳ�Ա */
    static bool is_leap_year(int year);
    static int days_in_month(int year, int month);
    void normalize();
public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
    Date();
    Date(int days);
    Date(int y, int m, int d);
    void set(int y);
    void set(int y, int m);
    void set(int y, int m, int d);
    void get(int& y, int& m, int& d) const;
    void show() const;
    
    operator int() const;
    Date& operator=(int days);

    Date& operator++();    // ǰ��++
    Date operator++(int);  // ����++
    Date& operator--();    // ǰ��--
    Date operator--(int);  // ����--

    friend Date operator+(const Date& date, int days);
    friend Date operator+(int days, const Date& date);
    friend Date operator-(const Date& date, int days);
    friend int operator-(const Date& lhs, const Date& rhs);

    friend bool operator==(const Date& lhs, const Date& rhs);
    friend bool operator!=(const Date& lhs, const Date& rhs);
    friend bool operator<(const Date& lhs, const Date& rhs);
    friend bool operator<=(const Date& lhs, const Date& rhs);
    friend bool operator>(const Date& lhs, const Date& rhs);
    friend bool operator>=(const Date& lhs, const Date& rhs);

    friend ostream& operator<<(ostream& os, const Date& date);
    friend istream& operator>>(istream& is, Date& date);
};

