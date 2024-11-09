/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct student {
    int no;
    char* name; // ��̬������ַ�ָ��
    int* score; // ��̬���������ָ��
    struct student* next;
};

char* tj_strcpy(char* s1, const char* s2)
{
    if (s1 == NULL)
        return s1;

    char* s = s1;

    if (s2 == NULL)
        *s = '\0';
    else
    {
        for (; *s2 != '\0'; s++, s2++)
            *s = *s2;
        *s = '\0';
    }
    return s1;
}

int main() 
{
    ifstream fin;
    fin.open("list.txt", ios::in);
    if (!fin.is_open()) 
    {
        cerr << "���ļ�list.txtʧ��." << endl;
        cerr << "������ʧ��." << endl;
        return -1;
    }

    student* head = nullptr;
    student* tail = nullptr;

    while (true) 
    {
        student* new_student = new student; // ����ѧ���ڵ�
        if (!new_student)
        {
            cerr << "�ڴ����ʧ��." << endl;
            return -1; // �ڴ����ʧ��
        }

        fin >> new_student->no;
        if (new_student->no == 9999999) 
        {
            delete new_student; // �ͷ��ڴ�
            break;
        }

        // ��ȡ���ֲ�����ʵ�ʳ��ȷ����ڴ�
        char temp_name[9]; // ������󳤶�Ϊ8������'\0'��
        fin >> temp_name;
        temp_name[8] = '\0'; // ȷ���ַ�����ֹ��

        // �������ֵ�ʵ�ʳ��ȷ����ڴ�
        new_student->name = new char[strlen(temp_name) + 1];
        if (!new_student->name) 
        {
            cerr << "�ڴ����ʧ��." << endl;
            delete new_student;
            return -1; // �ڴ����ʧ��
        }
        tj_strcpy(new_student->name, temp_name); // ��������

        new_student->score = new int; // ����ɼ��ڴ�
        if (!new_student->score) 
        {
            cerr << "�ڴ����ʧ��." << endl;
            delete[] new_student->name;
            delete new_student;
            return -1; // �ڴ����ʧ��
        }

        fin >> *(new_student->score); // ��ȡ�ɼ�
        new_student->next = nullptr;

        if (!head) 
        {
            head = new_student;
            tail = new_student;
        }
        else 
        {
            tail->next = new_student;
            tail = new_student;
        }
    }

    fin.close();

    // ��������ӡ����
    student* current = head;
    while (current) 
    {
        cout << current->no << " " << current->name << " " << *(current->score) << endl;
        current = current->next;
    }

    // �ͷ��������ﲻ�����ͷţ���Ҫ��ֻ�����������
    current = head;
    while (current) 
    {
        student* temp = current;
        current = current->next;
        delete[] temp->name;  // �ͷ�name
        delete temp->score;    // �ͷ�score
        delete temp;           // �ͷ�student
    }

    return 0;
}
