/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAX_SIZE = 4096;

// ����ļ���ʽ��������Ӧ�ĸ�ʽ����
const char* check_file_format(const char* file_path) 
{
    ifstream file(file_path, ios::binary);
    if (!file.is_open()) 
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    bool has_crlf = false; // �Ƿ���� \r\n
    bool has_lf = false;   // �Ƿ���� \n

    // �����ļ����ݣ���黻�з�
    while (file.read(buffer, MAX_SIZE)) 
    {
        for (int i = 0; i < file.gcount(); ++i) 
        {
            if (buffer[i] == '\r' && i + 1 < file.gcount() && buffer[i + 1] == '\n') 
            {
                has_crlf = true;
                i++; // ���� '\n'
            }
            else if (buffer[i] == '\n') 
                has_lf = true;
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
    ifstream infile(file_in, ios::binary);
    if (!infile.is_open()) 
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    bool is_windows = false;

    // ����Ƿ���Windows��ʽ
    while (infile.read(buffer, MAX_SIZE)) 
    {
        for (int i = 0; i < infile.gcount(); ++i)
        {
            if (buffer[i] == '\r' && i + 1 < infile.gcount() && buffer[i + 1] == '\n') 
            {
                is_windows = true;
                break;
            }
        }
        if (is_windows) 
            break;
    }

    if (!is_windows) 
        return "�ļ���ʽ�޷�ʶ��";

    // ������ļ�
    ofstream outfile(file_out, ios::binary);
    if (!outfile.is_open()) 
        return "�ļ�д��ʧ��";

    infile.clear();
    infile.seekg(0, ios::beg);

    // �� \r\n ת��Ϊ \n ��д��Ŀ���ļ�
    while (infile.read(buffer, MAX_SIZE)) 
    {
        for (int i = 0; i < infile.gcount(); ++i) 
        {
            if (buffer[i] == '\r' && i + 1 < infile.gcount() && buffer[i + 1] == '\n') 
            {
                outfile.put('\n');
                i++; // ���� '\n'
            }
            else 
                outfile.put(buffer[i]);
        }
    }

    return NULL;
}

// ��Linux��ʽ�ļ�ת��ΪWindows��ʽ
const char* convert_ltow(const char* file_in, const char* file_out) 
{
    ifstream infile(file_in, ios::binary);
    if (!infile.is_open()) 
        return "�ļ���ʧ��";

    char buffer[MAX_SIZE];
    bool is_linux = false;

    // ����Ƿ���Linux��ʽ
    while (infile.read(buffer, MAX_SIZE))
    {
        for (int i = 0; i < infile.gcount(); ++i) 
        {
            if (buffer[i] == '\n') 
            {
                if (i > 0 && buffer[i - 1] != '\r')
                {
                    is_linux = true;
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
    ofstream outfile(file_out, ios::binary);
    if (!outfile.is_open()) 
        return "�ļ�д��ʧ��";

    infile.clear();
    infile.seekg(0, ios::beg);

    // �� \n ת��Ϊ \r\n ��д��Ŀ���ļ�
    while (infile.read(buffer, MAX_SIZE)) 
    {
        for (int i = 0; i < infile.gcount(); ++i) 
        {
            if (buffer[i] == '\n') 
            {
                outfile.put('\r');
                outfile.put('\n');
            }
            else 
                outfile.put(buffer[i]);
        }
    }

    return NULL;
}

void printUsage()
{
    cout << "Usage : 15-b3 --check �ļ��� | --convert { wtol|ltow } Դ�ļ��� Ŀ���ļ���" << endl;
    cout << "        15-b3 --check a.txt" << endl;
    cout << "        15-b3 --convert wtol a.win.txt a.linux.txt" << endl;
    cout << "        15-b3 --convert ltow a.linux.txt a.win.txt" << endl;
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
        cout << check_file_format(file_path) << endl;

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
            cout << convert_wtol(source_file, target_file) << endl;
        else if (strcmp(conversion_type, "ltow") == 0) 
            cout << convert_ltow(source_file, target_file) << endl;
        else 
            printUsage();

    }
    else 
        printUsage();

    return 0;
}
