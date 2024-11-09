/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct student {
    int no;
    char* name; // ��̬������ַ�ָ��
    int* score; // ��̬���������ָ��
    struct student* next;
};

int main() 
{
    FILE* infile = fopen("list.txt", "r");
    if (infile == NULL) 
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
            fprintf(stderr, "�ڴ����ʧ��.\n");
            return -1; // �ڴ����ʧ��
        }

        fscanf(infile, "%d", &new_student->no);
        if (new_student->no == 9999999) 
        {
            free(new_student); // �ͷ��ڴ�
            break;
        }

        // ��ȡ���ֲ�����ʵ�ʳ��ȷ����ڴ�
        char temp_name[9]; 
        fscanf(infile, "%8s", temp_name);
        temp_name[8] = '\0'; // ȷ���ַ�����ֹ��

        // �������ֵ�ʵ�ʳ��ȷ����ڴ�
        new_student->name = (char*)malloc((strlen(temp_name) + 1) * sizeof(char)); 
        if (!new_student->name)
        {
            fprintf(stderr, "�ڴ����ʧ��.\n");
            free(new_student);
            return -1; // �ڴ����ʧ��
        }
        strcpy(new_student->name, temp_name); // ��������

        new_student->score = (int*)malloc(sizeof(int));
        if (!new_student->score) 
        {
            fprintf(stderr, "�ڴ����ʧ��.\n");
            free(new_student->name);
            free(new_student);
            return -1; // �ڴ����ʧ��
        }

        fscanf(infile, "%d", new_student->score);
        new_student->next = NULL;

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

    fclose(infile);

    // ��������ӡ����
    struct student* current = head;
    while (current)
    {
        printf("%d %s %d\n", current->no, current->name, *(current->score));
        current = current->next;
    }

    // �ͷ�����
    current = head;
    while (current) 
    {
        struct student* temp = current;
        current = current->next;
        free(temp->name);  // �ͷ�name
        free(temp->score); // �ͷ�score
        free(temp);        // �ͷ�student
    }

    return 0;
}