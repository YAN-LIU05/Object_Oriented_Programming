/* 2352018 ������ ���� */
#include <iostream>
#include <cmath>
using namespace std;

/* �Ӵ˴�������滻��֮�䣬����������Ķ��弰ʵ��
	1����������ȫ�ֱ���������const��#define��
	2���������������ϵͳͷ�ļ�
*/
//�Զ����ַ������ƺ���
int tj_strcpy(char s1[], const char s2[])
{
	int i = 0; // ��ʼ����������i
	// ����s2��s1��ֱ���������ַ�
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	// ��s1��ĩβ��ӿ��ַ�
	s1[i] = '\0';
	return 0; 
}
//�˴�����������Ķ��弰ʵ��
class integral {
protected:
	double min, max;
	int    num;
	char   name[128];
public:
	virtual double value();
	friend istream& operator >>(istream& in, integral& _integral);
};
class integral_sin : public integral{
public:
	integral_sin();
	virtual double value();
};
class integral_cos : public integral {
public:
	integral_cos();
	virtual double value();
};
class integral_exp : public integral {
public:
	integral_exp();
	virtual double value();
};
//��������
integral_sin::integral_sin()
{
	tj_strcpy(name, "sinxdx");
}
integral_cos::integral_cos()
{
	tj_strcpy(name, "cosxdx");
}
integral_exp::integral_exp()
{
	tj_strcpy(name, "e^xdx");
}
//���ּ��㺯��
double integral::value() 
{
	return 0;
}
double integral_sin::value()
{
	double result = 0;
	double width = (max - min) / num;
	for (int i = 1; i <= num; i++)
		result += sin(min + i * width) * width;
	cout << name << "[" << min << "~" << max << "/n=" << num << "] : " << result << endl;
	return result;
}
double integral_cos::value()
{
	double result = 0;
	double width = (max - min) / num;
	for (int i = 1; i <= num; i++)
		result += cos(min + i * width) * width;
	cout << name << "[" << min << "~" << max << "/n=" << num << "] : " << result << endl;
	return result;
}
double integral_exp::value()
{
	double result = 0;
	double width = (max - min) / num;
	for (int i = 1; i <= num; i++)
		result += exp(min + i * width) * width;
	cout << name << "[" << min << "~" << max << "/n=" << num << "] : " << result << endl;
	return result;
}
//�����������أ������ʾ��
istream& operator >>(istream& in, integral& _integral)
{
	while (1)
	{
		cout << "������" << _integral.name << "�����ޡ����޼����仮������" << endl;
		in >> _integral.min >> _integral.max >> _integral.num;
		if (in.good() && _integral.min <= _integral.max && _integral.num > 0)
			break;
		cout << "���������������������" << endl;
		in.clear();
		in.ignore(65536, '\n');
	}
	return in;
}
/* -- �滻����� -- ���в�Ҫ���κθĶ� -- ���в�Ҫɾ�� -- �ڱ��е����治Ҫ�����κ��Լ�����䣬��ҵ�ύ��ӱ��п�ʼ�ᱻ�滻 -- �滻����� -- */

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����fun_integral��׼����˼��һ�£�integralӦ��ζ���
***************************************************************************/
void fun_integral(integral& fRef)
{
	cin >> fRef;	//���������ޡ�������
	cout << fRef.value() << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼��
***************************************************************************/
int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;

	fun_integral(s1); //����sinxdx��ֵ
	fun_integral(s2); //����cosxdx��ֵ
	fun_integral(s3); //����expxdx��ֵ

	return 0;
}

//ע�����μ���ȡ��ֵ�����Ϊ����double��ʽ