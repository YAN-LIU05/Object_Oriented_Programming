/* 2352018 ������ ���� */
#include <iostream>
#include <iomanip>
#include "17-b2-date.h"
using namespace std;

/* --- ����Date��ĳ�Ա����������ʵ��(����Ԫ��������Ҫ�Ĺ�������)  --- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ����캯��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
Date::Date()
{
	year = 1900;
	month = 1;
	day = 1;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ι��캯��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
Date::Date(const int y, const int m, const int d)
{
    this->set(y, m, d);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�int���캯��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
Date::Date(int total_days)
{
	while (total_days < 0)
		total_days += 73049;
	total_days %= 73049;
	total_days++;
	set(1900, 1, 1);
	int days_per_month[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
	while (total_days > 365) 
	{
		if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		{
			if (total_days > 366)
				total_days -= 366;
			else
				break;
		}
		else
			total_days -= 365;
		++year;
	}
	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
		++days_per_month[2];
	while (total_days > days_per_month[month])
	{
		total_days -= days_per_month[month];
		++month;
	}
	day = total_days;
}

/***************************************************************************
  �������ƣ�set
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void Date::set(const int y, const int m, const int d) 
{
    // Ĭ������
    year = 1900;
    month = 1;
    day = 1;

    // �������Ƿ�Ϸ�
    if (y < 1900 || y > 2099) 
        return;

    // ����·��Ƿ�Ϸ�
    if (m < 1 || m > 12) 
        return;

    // ��������Ƿ�Ϸ�
    int days_per_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        days_per_month[2] = 29; // ���������������

    if (d < 1 || d > days_per_month[m]) 
        return;

    // ������м��ͨ������������
    year = y;
    month = m;
    day = d;
}

/***************************************************************************
  �������ƣ�get
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void Date::get(int& y, int& m, int& d)
{
    y = year;
    m = month;
    d = day;
}

/***************************************************************************
  �������ƣ�show
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void Date::show()
{
    cout << year << '-';
    cout << setfill('0') << setw(2) << month << '-';
    cout << setfill('0') << setw(2) << day;
    cout << endl;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ת������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
Date::operator int() const
{
    int totalday = 0;
    int month_day[13] = { 0,31,28,31,30,31,30,31,31,30,31,30,31 };
    for (int i = 1900; i < year; i++)
    {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0))
            totalday += 366;
        else
            totalday += 365;
    }
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        ++month_day[2];
    for (int i = 1; i < month; i++)
    {
        totalday += month_day[i];
    }
    totalday += day;
    totalday--; // ���㱾��Ҫ��
    return totalday;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������Ϊ���������
***************************************************************************/
Date operator+(const Date& date, const int a)
{
    int total_days = (int)date + a; // �ȵ�������ת��������dataת��Ϊint
    total_days %= 73049;
    return Date(total_days);
}
Date operator+(const int a, const Date& date)
{
    return date + a;
}

Date operator-(const Date& date, const int a)
{
    int total_days = (int)date - a;
    while (total_days < 0)
        total_days += 73049;
    total_days %= 73049;
    return Date(total_days);
}
int operator-(const Date& date1, const Date& date2)
{
    return (int)date1 - (int)date2;
}

ostream& operator<<(ostream& out, const Date& date)
{
    out << date.year << '-';
    out << setfill('0') << setw(2) << date.month << '-';
    out << setfill('0') << setw(2) << date.day;
    return out;
}
istream& operator>>(istream& in, Date& date)
{
    int y, m, d;
    in >> y >> m >> d;
    date.set(y, m, d);
    return in;
}

Date& Date::operator++()
{
    int total_days = (int)*this;
    total_days++;
    total_days %= 73049;
    *this = Date(total_days);
    return *this;
}
Date Date::operator++(int)
{
    Date temp(this->year, this->month, this->day);
    int total_days = (int)*this;
    total_days++;
    total_days %= 73049;
    *this = Date(total_days);
    return temp;
}

Date& Date::operator--()
{
    int total_days = (int)*this;
    total_days--;
    while (total_days < 0)
        total_days += 73049;
    total_days %= 73049;
    *this = Date(total_days);
    return *this;
}
Date Date::operator--(int)
{
    Date temp(this->year, this->month, this->day);
    int total_days = (int)*this;
    total_days--;
    while (total_days < 0)
        total_days += 73049;
    total_days %= 73049;
    *this = Date(total_days);
    return temp;
}

bool Date::operator <(const Date& date)
{
    return (int)(*this) < (int)date;
}
bool Date::operator >(const Date& date)
{
    return (int)(*this) > (int)date;
}
bool Date::operator == (const Date& date)
{
    return (int)(*this) == (int)date;
}
bool operator !=(const Date& date1, const Date& date2)
{
    return (int)date1 != (int)date2;
}
bool operator >=(const Date& date1, const Date& date2)
{
    return (int)date1 >= (int)date2;
}
bool operator <=(const Date& date1, const Date& date2)
{
    return (int)date1 <= (int)date2;
}