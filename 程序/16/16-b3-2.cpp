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
	//���в���������ӳ�Ա����������ʵ�֣���������������ݳ�Ա����Ԫ����
	Student& operator=(const Teacher& stu);
	operator Teacher() const;
};

/* ----����Student���Ա��������Ԫ����������ʵ�֣������޷��ڴ˴�ʵ�ֵĺ�������������ţ�---- */
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



/* Teacher ��Ķ���(Teacher���в�����������κ����ݳ�Ա����Ա��������Ԫ����Ա��������������ʵ��) */
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
	friend Student;
	//���в��ֲ���������κ�����
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
/* ----����Student���б�����Teacher��ʵ�ֵĳ�Ա����������ʵ��---- */
Student::operator Teacher() const 
{
	// ����һ�� Teacher ����
	Teacher te;

	// ѧ��ת���Ź��򣺹��� = 21 + ѧ�ź���λ
	te.num = 21000 + (num % 1000);

	// ����ת������ǰ��������ת��Ϊ"��ʦ"�������ַ�����
	strcpy(te.name, "��ʦ");
	strncat(te.name, this->name + 4, sizeof(te.name) - strlen(te.name) - 1); // ƴ�ӽ�ʦ�����ĺ�������

	// �Ա�ת������ԭ��ת��
	te.sex = sex;

	// ��ַת������ԭ��ַ���"����ѧԺ"
	strncpy(te.addr, this->addr, sizeof(te.addr) - 1);
	te.addr[sizeof(te.addr) - 1] = '\0';
	strncat(te.addr, "����ѧԺ", sizeof(te.addr) - strlen(te.addr) - 1);

	return te;
}

Student& Student::operator=(const Teacher& te)
{
	// ѧ��ת������ѧ�� = 2150 + ���ź���λ
	this->num = 2150000 + this->num % 1000;

	// ����ת������ǰ���������滻Ϊ "ѧ��"
	strcpy(this->name, "ѧ��");
	strncat(this->name, te.name + 4, 14 - strlen(this->name));

	// �Ա�ת������
	this->sex = this->sex;

	// ��ַת������ԭ��ַ��� "101��"
	strncpy(this->addr, te.addr, sizeof(this->addr) - 1);
	this->addr[sizeof(this->addr) - 1] = '\0';
	strncat(this->addr, "101��", sizeof(this->addr) - strlen(this->addr) - 1);

	return *this;
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