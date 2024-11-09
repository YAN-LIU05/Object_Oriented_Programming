/* 2352018 ������ ���� */
#include <iostream>
#include <cstring>

using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char* const procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl << endl;
	cout << "e.g. : " << procname << " 2159999 2159998 all       80 screen" << endl;
	cout << "       " << procname << " 2159999 all     14-b1.cpp 75 result.txt" << endl;
	cout << "       " << procname << " all     all     14-b2.cpp 80 check.dat" << endl;
	cout << "       " << procname << " all     all     all       85 screen" << endl;

	return 0;
}

// ѧ�ż�麯��
bool check_student_id_num(const char* id, const char* error_message) 
{
    if (strlen(id) != 7) 
    {
        cout << error_message << endl;
        return false;
    }
    for (int i = 0; i < 7; i++) 
    {
        if (id[i] < '0' || id[i] > '9') 
        {
            cout << error_message << endl;
            return false;
        }
    }
    return true;
}

// ����ѧ�ŵ��߼�
bool check_student_id_all(int argc, char* argv[]) 
{
    // �����ѧ����ѧ��
    bool flag_of_id = (strcmp(argv[1], "all") == 0);

    if (!flag_of_id) 
    {
        if (!check_student_id_num(argv[1], "Ҫ����ѧ�Ų���7λ����")) 
        {
            return false;
        }
    }

    // ���ƥ��ѧ����ѧ��
    bool match_id = (strcmp(argv[2], "all") == 0);

    if (!flag_of_id && strcmp(argv[1], argv[2]) == 0) 
    {
        cout << "ƥ��ѧ����Ҫ���ѧ����ͬ" << endl;
        return false;
    }

    if (!match_id) 
        if (!check_student_id_num(argv[2], "ƥ��ѧ�Ų���7λ����")) 
            return false;


    if (flag_of_id && !match_id) 
    {
        cout << "���ѧ����all��ƥ��ѧ�ű�����all" << endl;
        return false;
    }

    // ���м��ͨ��
    return true;
}

// ����ļ����ĳ���
bool check_filename_length(const char* filename, const char* error_message) 
{
    if (strlen(filename) > 32) 
    {
        cout << error_message << endl;
        return false;
    }
    return true;
}

// ���������ĺ���
void display_check_results(char* argv[])
{
    cout << "�������ͨ��" << endl;
    cout << "���ѧ�ţ�" << argv[1] << endl;
    cout << "ƥ��ѧ�ţ�" << argv[2] << endl;

    // Դ�ļ������
    cout << "Դ�ļ�����" << (strcmp(argv[3], "all") == 0 ? "all" : argv[3]) << endl;
}


// ���ƶȼ�麯��
void check_similarity(const char* similarity_set) 
{
    int num = 80; // Ĭ����ֵ

    if (similarity_set[0] >= '6' && similarity_set[0] <= '9') 
    {
        if (similarity_set[1] >= '0' && similarity_set[1] <= '9')       
            num = (similarity_set[0] - '0') * 10 + (similarity_set[1] - '0');  // ���ַ�ת��Ϊ����
    }
    else if (similarity_set[0] == '1' && similarity_set[1] == '0' && similarity_set[2] == '0') 
        num = 100; // ֱ������Ϊ100

    cout << "ƥ����ֵ��" << num << endl;
}

// �����ʽ��麯��
void check_output_target(const char* outfile) 
{
    if (strcmp(outfile, "screen") == 0) 
        cout << "���Ŀ�꣺screen" << endl;
    else
        cout << "���Ŀ�꣺" << outfile << endl;
}

int main(int argc, char* argv[])
{
	if (argc < 6)
	{
		usage(argv[0]);
		return 0;
	}

    // ���ѧ��
    if (!check_student_id_all(argc, argv)) 
        return 0; // �������ʧ��


    // ���Դ�����ļ����ĳ���
    if (!check_filename_length(argv[3], "Դ�����ļ���������32�ֽ�")) 
        return 0;

    // ����������ļ����ĳ���
    if (!check_filename_length(argv[5], "�������ļ���������32�ֽ�")) 
        return 0;

    // ��������
    display_check_results(argv);

    // ���ƶȼ��
    check_similarity(argv[4]);

    // �����ʽ���
    check_output_target(argv[5]);

    return 0;
}