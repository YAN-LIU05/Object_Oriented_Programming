/* 2352018 ������ ���� */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 4096

// ����ļ���ʽ��������Ӧ�ĸ�ʽ����
const char* check_file_format(const char* file_path)
{
    FILE* file = fopen(file_path, "rb");
    if (!file)
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    int has_crlf = 0; // �Ƿ���� \r\n
    int has_lf = 0;   // �Ƿ���� \n

    // �����ļ����ݣ���黻�з�
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, MAX_SIZE, file)) > 0)
    {
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\r' && i + 1 < bytesRead && buffer[i + 1] == '\n')
            {
                has_crlf = 1;
                i++; // ���� '\n'
            }
            else if (buffer[i] == '\n')
                has_lf = 1;
        }
    }

    // �ж��ļ���ʽ
    if (has_crlf && has_lf)
        return "�ļ���ʽ�޷�ʶ��";
    if (has_crlf)
        return "Windows��ʽ";
    if (has_lf)
        return "Linux��ʽ";

    return "�ļ���ʽ�޷�ʶ��"; // ����ļ�����Ϊ�ջ��޷�ʶ��
}

// ��Windows��ʽ�ļ�ת��ΪLinux��ʽ
const char* convert_wtol(const char* file_in, const char* file_out)
{
    FILE* infile = fopen(file_in, "rb");
    if (!infile)
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    int is_windows = 0;
    int removed_cr_count = 0;  // ��¼ȥ����0x0D����

    // ����Ƿ���Windows��ʽ
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, MAX_SIZE, infile)) > 0)
    {
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\r' && i + 1 < bytesRead && buffer[i + 1] == '\n')
            {
                is_windows = 1;
                break;
            }
        }
        if (is_windows)
            break;
    }

    if (!is_windows)
        return "�ļ���ʽ�޷�ʶ��";

    // ������ļ�
    FILE* outfile = fopen(file_out, "wb");
    if (!outfile)
        return "�ļ�д��ʧ��";

    // �� \r\n ת��Ϊ \n ��д��Ŀ���ļ�
    fseek(infile, 0, SEEK_SET); // �����ļ�ָ��
    while ((bytesRead = fread(buffer, 1, MAX_SIZE, infile)) > 0)
    {
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\r' && i + 1 < bytesRead && buffer[i + 1] == '\n')
            {
                fputc('\n', outfile);
                i++; // ���� '\n'
                removed_cr_count++; // ��¼ȥ����0x0D����
            }
            else
                fputc(buffer[i], outfile);
        }
    }

    fclose(infile);
    fclose(outfile);

    // ���ת����Ϣ
    printf("ת����ɣ�ȥ��%d��0x0D\n", removed_cr_count);

    return NULL; // ����NULLʱ�����κβ���
}

// ��Linux��ʽ�ļ�ת��ΪWindows��ʽ
const char* convert_ltow(const char* file_in, const char* file_out)
{
    FILE* infile = fopen(file_in, "rb");
    if (!infile)
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    int is_linux = 0;
    int added_cr_count = 0;  // ��¼��ӵ�0x0D����

    // ����Ƿ���Linux��ʽ
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, MAX_SIZE, infile)) > 0)
    {
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
            {
                if (i > 0 && buffer[i - 1] != '\r')
                {
                    is_linux = 1;
                    break;
                }
            }
        }
        if (is_linux)
            break;
    }

    if (!is_linux)
        return "�ļ���ʽ�޷�ʶ��";

    // ������ļ�
    FILE* outfile = fopen(file_out, "wb");
    if (!outfile)
        return "�ļ�д��ʧ��";

    // �� \n ת��Ϊ \r\n ��д��Ŀ���ļ�
    fseek(infile, 0, SEEK_SET); // �����ļ�ָ��
    while ((bytesRead = fread(buffer, 1, MAX_SIZE, infile)) > 0)
    {
        for (size_t i = 0; i < bytesRead; ++i)
        {
            if (buffer[i] == '\n')
            {
                fputc('\r', outfile);
                fputc('\n', outfile);
                added_cr_count++; // ��¼��ӵ�0x0D����
            }
            else
                fputc(buffer[i], outfile);
        }
    }

    fclose(infile);
    fclose(outfile);

    // ���ת����Ϣ
    printf("ת����ɣ�����%d��0x0D\n", added_cr_count);

    return NULL; // ����NULLʱ�����κβ���
}

void printUsage()
{
    printf("Usage : 15-b6 --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���\n");
    printf("        15-b6 --check a.txt\n");
    printf("        15-b6 --convert wtol a.win.txt a.linux.txt\n");
    printf("        15-b6 --convert ltow a.linux.txt a.win.txt\n");
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        printUsage();
        return 1;
    }

    const char* command = argv[1];

    if (strcmp(command, "--check") == 0)
    {
        if (argc != 3)
        {
            printUsage();
            return 1;
        }
        const char* file_path = argv[2];
        printf("%s\n", check_file_format(file_path));
    }
    else if (strcmp(command, "--convert") == 0)
    {
        if (argc != 5)
        {
            printUsage();
            return 1;
        }
        const char* conversion_type = argv[2];
        const char* source_file = argv[3];
        const char* target_file = argv[4];

        if (strcmp(conversion_type, "wtol") == 0)
        {
            const char* result = convert_wtol(source_file, target_file);
            if (result != NULL)
                printf("%s\n", result);
        }
        else if (strcmp(conversion_type, "ltow") == 0)
        {
            const char* result = convert_ltow(source_file, target_file);
            if (result != NULL)
                printf("%s\n", result);
        }
        else
            printUsage();
    }
    else
    {
        printUsage();
    }

    return 0;
}
