/* 2352018 ������ ���� */
/* 2350995 ��ϲ�� 2354040 �� 2351044 ������ 2353581 ���� 2351753 �Ʊ��� 2353572 ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <sstream>

using namespace std;

void printUsage()
{
    cout << "Usage : 15-b2 --infile hex��ʽ�ļ� --outfile bin��ʽ�ļ�" << endl;
    cout << "        15-b2 --infile a.hex --outfile a.bin" << endl;
}

// �ж�һ���ַ����Ƿ�����Ч��ʮ���������������ַ���
bool valid_hex(const char* hexStr)
{
    if (hexStr == nullptr || strlen(hexStr) != 2)
        return false;  // ʮ�������ֽڱ����������ַ�

    // ���ÿ���ַ��Ƿ�����Ч��ʮ�������ַ�
    for (int i = 0; i < 2; i++)
    {
        if (!((hexStr[i] >= '0' && hexStr[i] <= '9') ||
            (hexStr[i] >= 'a' && hexStr[i] <= 'f') ||
            (hexStr[i] >= 'A' && hexStr[i] <= 'F')))
        {
            return false;  // ����ַ����ǺϷ���ʮ�������ַ�������false
        }
    }
    return true;  // ��������ַ�����ʮ�������ַ����򷵻�true
}

// ��ʮ�������ļ�ת��Ϊ�������ļ�
void hexToBinary(const char* infile, const char* outfile)
{
    ifstream inFile(infile);
    if (!inFile)
    {
        cerr << "�����ļ�" << infile << "��ʧ��!" << endl;
        return;
    }

    ofstream outFile(outfile, ios::binary);
    if (!outFile)
    {
        cerr << "����ļ�" << outfile << "��ʧ��!" << endl;
        return;
    }
    const int MAX_FILENAME_LENGTH = 1024;
    char* line = new char[MAX_FILENAME_LENGTH];  // ��̬�����ڴ�����ȡÿһ��
    while (inFile.getline(line, MAX_FILENAME_LENGTH))
    {
#ifdef _WIN32
        char* address = strtok(line, " ");
#else
        strtok(line, " ");
#endif
         

        char* hexByte = strtok(nullptr, " ");  // ��ȡ��һ��ʮ�������ֽ�
        while (hexByte != nullptr)
        {
            // ���� "-" ����
            if (strcmp(hexByte, "-") == 0)
            {
                hexByte = strtok(nullptr, " ");
                continue;
            }

            // ֻ������Ч��ʮ�������ֽ�
            if (valid_hex(hexByte))
            {
                unsigned char byte = static_cast<unsigned char>(strtol(hexByte, nullptr, 16));
                outFile.put(byte);
            }

            hexByte = strtok(nullptr, " ");  // ����������һ��ʮ�������ֽ�
        }
    }

    delete[] line;  
    inFile.close();
    outFile.close();
}

// ���������в���
int main(int argc, char* argv[])
{
    char* infile = nullptr;
    char* outfile = nullptr;
    bool hasInfile = false, hasOutfile = false;

    for (int i = 1; i < argc; ++i)
    {
        if (strcmp(argv[i], "--infile") == 0 && i + 1 < argc)
        {
            infile = new char[strlen(argv[++i]) + 1];
            strcpy(infile, argv[i]);
            hasInfile = true;
        }
        else if (strcmp(argv[i], "--outfile") == 0 && i + 1 < argc)
        {
            outfile = new char[strlen(argv[++i]) + 1];
            strcpy(outfile, argv[i]);
            hasOutfile = true;
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

    delete[] infile;
    delete[] outfile;

    return 0;
}
