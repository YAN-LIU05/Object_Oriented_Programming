/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int no;
    char name[9];
    int score;
    struct student* next;
};

int main() 
{
    FILE* file = fopen("list.txt", "r");
    if (file == NULL) 
    {
        fprintf(stderr, "���ļ�list.txtʧ��.\n");
        fprintf(stderr, "������ʧ��.\n");
        return -1;
    }

    struct student* head = NULL;
    struct student* tail = NULL;

    while (1) 
    {
        struct student* new_student = (struct student*)malloc(sizeof(struct student));
        if (!new_student) 
        {
            fprintf(stderr, "�ڴ�����ʧ��.\n");
            return -1;  // �ڴ�����ʧ��
        }

        fscanf(file, "%d", &new_student->no);
        if (new_student->no == 9999999) 
        {
            free(new_student);  // �ͷ�δʹ�õ��ڴ�
            break;  // ������ȡ
        }

        fscanf(file, "%s", new_student->name);
        fscanf(file, "%d", &new_student->score);
        new_student->next = NULL;

        // ����ѧ����ӵ������β��
        if (head == NULL) 
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

    fclose(file);

    // ����������ӡ��Ϣ
    struct student* current = head;
    while (current != NULL) 
    {
        printf("%d %s %d\n", current->no, current->name, current->score);
        current = current->next;
    }

    // �ͷ�����
    current = head;
    while (current != NULL)
    {
        struct student* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
