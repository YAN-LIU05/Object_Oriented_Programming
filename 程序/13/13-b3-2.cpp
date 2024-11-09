/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct student {
    int no;
    char name[9];
    int score;
    struct student* next;
};

int main() {
    ifstream fin("list.txt");
    if (!fin.is_open()) 
    {
        cerr << "���ļ�list.txtʧ��." << endl;
        cerr << "������ʧ��." << endl;
        return -1;
    }

    student* head = nullptr;
    student* tail = nullptr;

    while (1) {
        student* new_student = new student;
        if (!new_student) 
        {
            cerr << "�ڴ�����ʧ��." << endl;
            return -1;  // �ڴ�����ʧ��
        }
        fin >> new_student->no;
        if (new_student->no == 9999999) {
            delete new_student; // �ͷ��ڴ�
            break;
        }
        fin >> new_student->name >> new_student->score;

        new_student->next = nullptr;

        if (!head) {
            head = new_student;
            tail = new_student;
        }
        else {
            tail->next = new_student;
            tail = new_student;
        }
    }

    fin.close();

    // ��������ӡ����
    student* current = head;
    while (current) {
        cout << current->no << " " << current->name << " " << current->score << endl;
        current = current->next;
    }

    // �ͷ�����
    current = head;
    while (current) {
        student* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}