/* 2352018 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* Date������� */
class Date {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */
	int year;
	int month;
	int day;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	Date();                                      // Ĭ�Ϲ��캯��
	Date(const int y, const int m, const int d); // ���ι��캯��
	Date(int total_days); // ת�����캯����int->Date
	void set(const int y = 2000, const int m = 1, const int d = 1); // set��Ա����
	void get(int& y, int& m, int& d);
	void show();

	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	bool operator<(const Date& date);
	bool operator>(const Date& date);
	bool operator==(const Date& date);
	operator int() const;  // ����ת����������Date����ת��Ϊint���͵�����
	/* ���������Ԫ����������б�Ҫ�� */
	friend Date operator+(const Date& date, const int a);
	friend Date operator+(const int a, const Date& date);
	friend Date operator-(const Date& date, const int a);
	friend int operator-(const Date& date1, const Date& date2);
	friend ostream& operator<<(ostream& out, const Date& date);
	friend istream& operator>>(istream& in, Date& date);
	friend bool operator!=(const Date& date1, const Date& date2);
	friend bool operator>=(const Date& date1, const Date& date2);
	friend bool operator<=(const Date& date1, const Date& date2);
};