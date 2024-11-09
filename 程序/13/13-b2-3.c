/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ѧ���ṹ��
struct Student {
    int no;      // ѧ��
    char name[9]; // ����
    int score;        // �ɼ�
    int rank;         // ����
};

// ���ݳɼ������ѡ��������
void select_by_score(struct Student* students, int n)
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
        struct Student temp = students[i];
        students[i] = students[maxIndex];
        students[maxIndex] = temp;
    }
}

// ��������
void my_rank(struct Student* students, int n)
{
    for (int i = 0; i < n; i++)
    {
        students[i].rank = i + 1; // Ĭ������
        if (i > 0 && students[i].score == students[i - 1].score)
        {
            students[i].rank = students[i - 1].rank; // ��ͬ�ɼ���������
        }
    }
}

// ����ѧ�������ѡ��������
void my_sort(struct Student* students, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (students[j].rank == students[i].rank && students[j].no < students[i].no)
            {
                // ���������ͬ����ѧ�Ŵ�С��������
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
}

int main()
{
    FILE* file = fopen("student.txt", "r");
    if (file == NULL)
    {
        fprintf(stderr, "���ļ�student.txtʧ��.\n");
        return -1;
    }

    int n = 0;

    // ��ȡѧ������
    fscanf(file, "%d", &n);

    // ��̬����ѧ������
    struct Student* students = (struct Student*)malloc(n * sizeof(struct Student));

    // ���ļ��ж�ȡѧ����Ϣ
    for (int i = 0; i < n; i++)
        fscanf(file, "%d %s %d", &students[i].no, students[i].name, &students[i].score);
    fclose(file);

    // ���ɼ�����
    select_by_score(students, n);
    // ��������
    my_rank(students, n);
    // �������κ�ѧ������
    my_sort(students, n);
    // ������
    for (int i = 0; i < n; i++)
        printf("%d %s %d %d\n", students[i].no, students[i].name, students[i].score, students[i].rank);

    // �ͷŶ�̬������ڴ�
    free(students);

    return 0;
}