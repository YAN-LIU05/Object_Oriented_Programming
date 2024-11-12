/* 2352018 ������ ���� */
/* 2354040 �� 2351753 �Ʊ��� 2350488 ������ 2351044 ������ 2252036 �ջ� 2152131 ����� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��ӡ�����÷�
void printUsage()
{
    printf("Usage : 15-b5 --infile hex��ʽ�ļ� --outfile bin��ʽ�ļ�\n");
    printf("        15-b5 --infile a.hex --outfile a.bin\n");
}

// �ж�һ���ַ����Ƿ�����Ч��ʮ���������������ַ���
int valid_hex(const char* hexStr)
{
    if (hexStr == NULL || strlen(hexStr) != 2)
        return 0;  // ʮ�������ֽڱ����������ַ�

    // ���ÿ���ַ��Ƿ�����Ч��ʮ�������ַ�
    for (int i = 0; i < 2; i++)
    {
        if (!((hexStr[i] >= '0' && hexStr[i] <= '9') ||
            (hexStr[i] >= 'a' && hexStr[i] <= 'f') ||
            (hexStr[i] >= 'A' && hexStr[i] <= 'F')))
        {
            return 0;  // ����ַ����ǺϷ���ʮ�������ַ�������0
        }
    }
    return 1;  // ��������ַ�����ʮ�������ַ����򷵻�1
}

// ��ʮ�������ļ�ת��Ϊ�������ļ�
void hexToBinary(const char* infile, const char* outfile)
{
    FILE* inFile = fopen(infile, "r");
    if (!inFile)
    {
        fprintf(stderr, "�����ļ� %s ��ʧ��!\n", infile);
        return;
    }

    FILE* outFile = fopen(outfile, "wb");
    if (!outFile)
    {
        fprintf(stderr, "����ļ� %s ��ʧ��!\n", outfile);
        fclose(inFile);
        return;
    }

    const int MAX_FILENAME_LENGTH = 1024;
    char* line = (char*)malloc(MAX_FILENAME_LENGTH * sizeof(char));  // ��̬�����ڴ�����ȡÿһ��
    while (fgets(line, MAX_FILENAME_LENGTH, inFile))
    {
        char* hexByte = strtok(line, " \n");  // ��ȡÿһ�еĵ�һ��ʮ�������ֽ�
        while (hexByte != NULL)
        {
            // ���� "-" ����
            if (strcmp(hexByte, "-") == 0)
            {
                hexByte = strtok(NULL, " \n");
                continue;
            }

            // ֻ������Ч��ʮ�������ֽ�
            if (valid_hex(hexByte))
            {
                unsigned char byte = (unsigned char)strtol(hexByte, NULL, 16);
                fputc(byte, outFile);
            }

            hexByte = strtok(NULL, " \n");  // ����������һ��ʮ�������ֽ�
        }
    }

    free(line);  // �ͷ��ڴ�
    fclose(inFile);
    fclose(outFile);
}

// ���������в���
int main(int argc, char* argv[])
{
    char* infile = NULL;
    char* outfile = NULL;
    int hasInfile = 0, hasOutfile = 0;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--infile") == 0 && i + 1 < argc)
        {
            infile = (char*)malloc(strlen(argv[++i]) + 1);
            strcpy(infile, argv[i]);
            hasInfile = 1;
        }
        else if (strcmp(argv[i], "--outfile") == 0 && i + 1 < argc)
        {
            outfile = (char*)malloc(strlen(argv[++i]) + 1);
            strcpy(outfile, argv[i]);
            hasOutfile = 1;
        }
        else
        {
            printUsage();
            return 1;
        }
    }

    if (!hasInfile)
    {
        printUsage();
        return 1;
    }

    if (!hasOutfile)
    {
        printUsage();
        return 1;
    }

    hexToBinary(infile, outfile);

    free(infile);
    free(outfile);

    return 0;
}
