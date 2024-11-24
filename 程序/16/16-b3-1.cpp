/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* �˴�������ӱ���Ķ����������������ȫ�ֱ����� */
class Teacher;
/* Student ��Ķ��壨��Ա��������������ʵ�֣� */
class Student {
private:
	int num;	//ѧ��
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Student();
	Student(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Student& stu);
	friend Teacher;
	//���в��ֲ���������κ�����
};

/* ----����Student���Ա��������Ԫ����������ʵ��---- */
Student::Student() 
{
	num = 2150000;
	sex = 'M';
	strcpy(name, "<ѧ��S>");
	strcpy(addr, "��ƽ·1239��");
}

Student::Student(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	sex = sex1;
	strncpy(name, name1, 15);
	name[15] = '\0'; // ȷ���ַ����� '\0' ����
	strncpy(addr, addr1, 63);
	addr[63] = '\0';
}

ostream& operator<<(ostream& out, const Student& stu) 
{
	out << stu.num << " " << stu.name << " " << stu.sex << " " << stu.addr;
	return out;
}
/* Teacher ��Ķ��壨��Ա��������������ʵ�֣� */
class Teacher {
private:
	int num;	//����
	char name[16];	//����
	char sex;	//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Teacher();
	Teacher(const int num1, const char* name1, const char sex1, const char* addr1);
	friend ostream& operator<<(ostream& out, const Teacher& te);
	//���в���������ӳ�Ա����������ʵ�֣���������������ݳ�Ա����Ԫ����
	Teacher& operator=(const Student& stu);
	operator Student() const;
};

/* ----����Teacher���Ա��������Ԫ����������ʵ��---- */
Teacher::Teacher()
{
	num = 21000; 
	sex = 'M';
	strcpy(name, "<��ʦT>");
	strcpy(addr, "��ƽ·1239���Ժ�¥");
}

Teacher::Teacher(const int num1, const char* name1, const char sex1, const char* addr1)
{
	num = num1;
	sex = sex1;
	strncpy(name, name1, 15);
	name[15] = '\0';
	strncpy(addr, addr1, 63);
	addr[63] = '\0';
}

ostream& operator<<(ostream& out, const Teacher& te) 
{
	out << te.num << " " << te.name << " " << te.sex << " " << te.addr;
	return out;
}

Teacher& Teacher::operator=(const Student& stu)
{
	// ���Ź���
	this->num = 21 * 1000 + stu.num % 1000;

	// ��������
	strcpy(this->name, "��ʦ");
	strncat(this->name, stu.name + 4, 14 - strlen(this->name)); // ƴ��ѧ�������ӵ�3���ַ���ʼ

	// �Ա����
	this->sex = stu.sex;

	// ��ַ����
	strncpy(this->addr, stu.addr, sizeof(this->addr) - 1);
	this->addr[sizeof(this->addr) - 1] = '\0';
	strncat(this->addr, "����ѧԺ", sizeof(this->addr) - strlen(this->addr) - 1);

	return *this;
}

Teacher::operator Student() const
{
	Student stu;

	// ѧ��ת������ѧ�� = 2150 + ���ź���λ
	stu.num = 2150000 + this->num % 1000;

	// ����ת������ǰ���������滻Ϊ "ѧ��"
	strcpy(stu.name, "ѧ��");
	strncat(stu.name, this->name + 4, sizeof(stu.name) - strlen(stu.name) - 1); // ƴ�ӽ�ʦ�����ĺ�������

	// �Ա�ת������
	stu.sex = this->sex;

	// ��ַת������ԭ��ַ��� "101��"
	strncpy(stu.addr, this->addr, sizeof(stu.addr) - 1);
	stu.addr[sizeof(stu.addr) - 1] = '\0';
	strncat(stu.addr, "101��", sizeof(stu.addr) - strlen(stu.addr) - 1);

	return stu;
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
	Student s1;	//ȱʡֵ - ѧ�ţ�2150000 ������<ѧ��S> �Ա�M ��ַ����ƽ·1239��
	Student s2 = Student(2151234, "ѧ����", 'M', "�ܰ���·4800��");
	Teacher t1;	//ȱʡֵ - ���ţ�21000 ������<��ʦT> �Ա�M ��ַ����ƽ·1239���Ժ�¥
	Teacher t2 = Teacher(21123, "��ʦA", 'F', "�ܰ���·4800�����Ź�");

	/* ��ӡԭʼѧ����Ϣ */
	cout << "ѧ����Ϣ��" << s1 << endl;				//���������"ѧ����Ϣ��2150000 <ѧ��S> M ��ƽ·1239��"
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��2151234 ѧ���� M �ܰ���·4800��"
	cout << endl;

	/* ��ӡԭʼ��ʦ��Ϣ */
	cout << "��ʦ��Ϣ��" << t1 << endl;				//���������"��ʦ��Ϣ��21000 <��ʦT> M ��ƽ·1239���Ժ�¥"
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��21123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << endl;

	/* ѧ��ת��ʦ���ԣ�
		ѧ��ת���Ź��򣺹��� = 21 + ѧ�ź���λ
		����ת������ǰ��������ת��Ϊ"��ʦ"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"����ѧԺ"(�������ַ���Խ��)    */
	t1 = s2;
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��2151234 ѧ���� M �ܰ���·4800��"
	cout << "ת��Ϊ��ʦ����Ϣ��" << t1 << endl;		//���������"ת��Ϊ��ʦ����Ϣ��21234 ��ʦ�� M �ܰ���·4800�ŵ���ѧԺ"
	cout << endl;

	/* ��ʦתѧ�����ԣ�
		����תѧ�Ź���ѧ�� = 2150 + ���ź���λ
		����ת������ǰ��������ת��Ϊ"ѧ��"�������ַ�����
		�Ա�ת������ԭ��ת��
		��ַת������ԭ��ַ���"101��"(�������ַ���Խ��)    */
	s1 = t2;
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��21123 ��ʦA F �ܰ���·4800�����Ź�"
	cout << "ת��Ϊѧ������Ϣ��" << s1 << endl;		//���������"ת��Ϊѧ������Ϣ��2150123 ѧ��A F �ܰ���·4800�����Ź�101��"
	cout << endl;

	return 0;
}