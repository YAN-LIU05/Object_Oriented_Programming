/* 2352018 ������ ���� */
#include <iostream>
#include <cmath>
using namespace std;

class Shape {
protected:
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
    const double pai = 3.14159;
public:
    virtual void ShapeName() = 0; //�˾䲻׼��
    //������Ҫ������Ӧ�ĳ�Ա��Ҳ����Ϊ��
    virtual double area() = 0;
};

//�˴����������Ķ��弰ʵ��(��Ա������������ʵ����ʽ)
class Circle : public Shape {
protected:
    double r;
public:
    Circle(double _r);
    virtual void ShapeName();
    virtual double area();
};
class Square : public Shape {
protected:
    double a;
public:
    Square(double _a);
    virtual void ShapeName();
    virtual double area();
};
class Rectangle : public Shape {
protected:
    double a, b;
public:
    Rectangle(double _a, double _b);
    virtual void ShapeName();
    virtual double area();
};
class Trapezoid : public Shape {
protected:
    double a, b, h;
public:
    Trapezoid(double _a, double _b, double _h);
    virtual void ShapeName();
    virtual double area();
};
class Triangle : public Shape {
protected:
    double a, b, c;
public:
    Triangle(double _a, double _b, double _c);
    virtual void ShapeName();
    virtual double area();
};

//���캯��
Square::Square(double _a)
{
    a = _a;
}
Circle::Circle(double _r)
{
    r = _r;
}
Rectangle::Rectangle(double _a, double _b)
{
    a = _a;
    b = _b;
}
Trapezoid::Trapezoid(double _a, double _b, double _h)
{
    a = _a;
    b = _b;
    h = _h;
}
Triangle::Triangle(double _a, double _b, double _c)
{
    a = _a;
    b = _b;
    c = _c;
}
//ͼ������
void Circle::ShapeName()
{
    cout << "Circle" << endl;
}
void Square::ShapeName()
{
    cout << "Square" << endl;
}
void Rectangle::ShapeName()
{
    cout << "Rectangle" << endl;
}
void Trapezoid::ShapeName()
{
    cout << "Trapezoid" << endl;
}
void Triangle::ShapeName()
{
    cout << "Triangle" << endl;
}
//������㺯��
double Circle::area()
{
    if (r <= 0)
        return 0.0;
    else
        return pai * r * r;
}
double Square::area()
{
    if (a <= 0)
        return 0.0;
    else
        return a * a;
}
double Rectangle::area()
{
    if (a <= 0 || b <= 0)
        return 0.0;
    else
        return a * b;
}
double Trapezoid::area()
{
    if (a <= 0 || b <= 0 || h <= 0)
        return 0.0;
    else
        return (a + b) * h / 2;
}
double Triangle::area()
{
    if (a <= 0 || b <= 0 || c <= 0 || a + b <= c || a + c <= b || b + c <= a)
        return 0.0;
    double p = (a + b + c) / 2;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ������������main�����Ĵ��¿�ܣ��������΢����ı��ֵ
***************************************************************************/
int main()
{
    if (1) {
        Circle    c1(5.2);           //�뾶�����<=0�����Ϊ0��
        Square    s1(5.2);           //�߳������<=0�����Ϊ0��
        Rectangle r1(5.2, 3.7);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, 4.4, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, 5);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    if (1) {
        Circle    c1(-1);           //�뾶�����<=0�����Ϊ0��
        Square    s1(-1);           //�߳������<=0�����Ϊ0��
        Rectangle r1(5.2, -1);      //�����������һ<=0�����Ϊ0��
        Trapezoid t1(2.3, -1, 3.8); //�ϵס��µס��ߣ������һ<=0�����Ϊ0��
        Triangle  t2(3, 4, -1);       //���߳��ȣ������һ<=0�򲻹��������Σ����Ϊ0��
        Shape* s[5] = { &c1, &s1, &r1, &t1, &t2 };

        cout << "============" << endl;
        int   i;
        for (i = 0; i < 5; i++) {
            s[i]->ShapeName(); //�ֱ��ӡ��ͬ��״ͼ�ε����ƣ���ʽ�ο�demo��
            cout << s[i]->area() << endl; //�ֱ��ӡ��ͬ��״ͼ�ε��������ʽ�ο�demo��
            cout << endl;
        }
    }

    return 0;
}
