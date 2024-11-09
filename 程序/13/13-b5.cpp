#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

const int MAX_NAME_LENGTH = 15; // ѧ����������󳤶�
const int MAX_SCHOOL_LENGTH = 10; // ѧУ���Ƶ���󳤶�
const int MAX_ID_LENGTH = 15; // �����ŵ���󳤶�

struct Student {
    char id[MAX_ID_LENGTH];
    char name[MAX_NAME_LENGTH];
    char school[MAX_SCHOOL_LENGTH];
};

bool my_select(int* have_selected, int count, int index) 
{
    for (int i = 0; i < count; ++i) 
    {
        if (have_selected[i] == index) 
            return true; // �����Ѵ���
    }
    return false; // ����������
}

int main() 
{
    cout << "��ȡ����ǩ����...";

    ifstream fin;
    fin.open("stulist.txt", ios::in);
    if (!fin.is_open()) 
    {
        cerr << "���ļ�stulist.txtʧ��." << endl;
        return -1;
    }

    int N, M;
    fin >> N >> M; // ��ȡN��M
    fin.ignore();   // ������ĩ�Ļ��з�

    // ��̬����ѧ������
    Student* students = new Student[M]; // ����M��ѧ����Ϣ���ڴ�

    // ��ȡѧ����Ϣ
    for (int i = 0; i < M; ++i) 
    {
        fin >> students[i].id;
        fin >> students[i].name;
        fin.ignore(); // ������������Ŀո�
        fin >> students[i].school;
    }

    fin.close();
    cout << "���" << endl;
    // �������������
    srand(static_cast<unsigned>(time(0)));

    cout << "���ڳ�ǩ...";

    // �洢��ѡ�е�����
    int* have_selected = new int[N]; // ����N���������ڴ�
    int count = 0;

    while (count < N) 
    {
        int randIndex = rand() % M; // ���ѡ������
        if (!my_select(have_selected, count, randIndex)) 
        {
            have_selected[count] = randIndex; // ���������
            count++;
        }
    }

    // ѡ������д���ļ�
    ofstream fout;
    fout.open("result.txt", ios::out);
    if (!fout.is_open()) 
    {
        cerr << "�޷������ļ� result.txt" << endl;
        delete[] students; // �ͷ��ڴ�
        delete[] have_selected; // �ͷ��ڴ�
        return -1;
    }

    for (int i = 0; i < N; ++i) 
    {
        const Student& selected = students[have_selected[i]];
        fout << selected.id << " " << selected.name << " " << selected.school << endl;
    }

    fout.close();
    cout << "���" << endl;

    // �ͷŶ�̬������ڴ�
    delete[] students; // �ͷ�ѧ����Ϣ�ڴ�
    delete[] have_selected; // �ͷ������ڴ�

    return 0;
}
