/* 2352018 ������ ���� */
#pragma once

#include <iostream>
using namespace std;

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */

/* Time������� */
class Time {
protected:
	/* �����������⣬�������ٶ����κ����ݳ�Ա */
	int hour;
	int minute;
	int second;
public:
	/* ������Ҫ�ĳ�Ա��������Ԫ���������� */
	Time();
	Time(int h, int m, int s);
	Time(int total_seconds);
	void set(const int h = 0, const int m = 0, const int s = 0);
	void get(int& h, int& m, int& s);
	void show();
	operator int() const;

	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	/* ���������Ԫ����������б�Ҫ�� */
	friend Time operator+(const Time& time, const int s);
	friend Time operator+(const int s, const Time& time);
	friend int operator-(const Time& time1, const Time& time2);
	friend Time operator-(const Time& time, const int s);
	friend ostream& operator<<(ostream& out, const Time& time);
	friend istream& operator>>(istream& in, Time& time);
	friend bool operator<(const Time& time1, const Time& time2);
	friend bool operator>(const Time& time1, const Time& time2);
	friend bool operator==(const Time& time1, const Time& time2);
	friend bool operator!=(const Time& time1, const Time& time2);
	friend bool operator>=(const Time& time1, const Time& time2);
	friend bool operator<=(const Time& time1, const Time& time2);
};