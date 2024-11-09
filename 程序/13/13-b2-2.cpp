/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

// ѧ���ṹ��
struct Student {
    int no;          // ѧ��
    char name[9]; // ����
    int score;       // �ɼ�
    int rank;        // ����
};

// ���ݳɼ������ѡ��������
void select_by_score(Student* students, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int maxIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (students[j].score > students[maxIndex].score)
                maxIndex = j;
        }
        // ����
        Student temp = students[i];
        students[i] = students[maxIndex];
        students[maxIndex] = temp;
    }
}

// ��������
void my_rank(Student* students, int n)
{
    for (int i = 0; i < n; i++)
    {
        students[i].rank = i + 1; // Ĭ������
        if (i > 0 && students[i].score == students[i - 1].score)
            students[i].rank = students[i - 1].rank; // ��ͬ�ɼ���������
    }
}

// ����ѧ�������ѡ��������
void my_sort(Student* students, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        // �趨��ǰ��С����
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (students[j].no < students[minIndex].no)
            {
                minIndex = j;
            }
        }
        // ����ҵ���С��Ԫ�أ����н���
        if (minIndex != i)
        {
            Student temp = students[i];
            students[i] = students[minIndex];
            students[minIndex] = temp;
        }
    }
}

int main()
{
    ifstream fin;
    fin.open("student.txt", ios::in);
    if (!fin.is_open())
    {
        cerr << "���ļ�student.txtʧ��." << endl;
        return -1;
    }

    int n = 0;

    // ��ȡѧ������
    fin >> n;

    // ��̬����ѧ������
    Student* students = new Student[n];

    // ���ļ��ж�ȡѧ����Ϣ
    for (int i = 0; i < n; i++)
        fin >> students[i].no >> students[i].name >> students[i].score;

    fin.close();

    // ���ɼ�����
    select_by_score(students, n);
    // ��������
    my_rank(students, n);
    // �������κ�ѧ������
    my_sort(students, n);
    // ������
    for (int i = 0; i < n; i++)
        cout << students[i].no << " " << students[i].name << " " << students[i].score << " " << students[i].rank << endl;

    // �ͷŶ�̬������ڴ�
    delete[] students;

    return 0;
}
