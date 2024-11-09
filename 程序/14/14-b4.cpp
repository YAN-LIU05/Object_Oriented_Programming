/* 2352018 ������ ���� */
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

#define PING_NUM  3
#define MAX_LEN1  5
#define MAX_LEN2  9
#define MAX_LEN3  12
#define MAX_LEN4  6
#define MAX_SIZE  64000
#define MIN_SIZE  32
#define DEFAULT_SIZE  64
#define MAX_AMOUNT  1024
#define MIN_AMOUNT  1
#define DEFAULT_AMOUNT  4

class ping 
{
    public:
        const char* name;        // ��������
        const char* description; // ����������
        int count;              // ���Ӳ����ĸ���
        int origin;             // Ĭ��ֵ
        int value;              // ��ǰֵ
        int minimum;            // �������Сֵ
        int maximum;            // ��������ֵ

        // ���캯�������ڳ�ʼ����Ա����
        ping(const char* n, const char* desc, int c, int o, int min, int max)
        {
            name = n;          // ���ò�������
            description = desc; // ���ò�������
            count = c;        // ���ø��Ӳ�������
            origin = o;       // ����Ĭ��ֵ
            value = o;        // ��ǰֵ��ʼ��ΪĬ��ֵ
            minimum = min;    // ������Сֵ
            maximum = max;    // �������ֵ
        }

        int int_bit_num(int value) const
        {
            if (value == 0) // 0 �� 1 λ
                return 1;
            int cnt = 0;
            while (value > 0)
            {
                cnt++;
                value /= 10; // ÿ�ν�ֵ���� 10
            }
            return cnt; // ����λ��
        }

        static int my_max(int a, int b)
        {
            return (a > b) ? a : b; // ���ؽϴ��ֵ
        }

        static void calculate_max_lengths(const ping para_menu[], int max_length[], int temp_length[])
        {
            for (int j = 0; j < PING_NUM; j++)
            {
                temp_length[0] = my_max(int(strlen(para_menu[j].name)), temp_length[0]);
                temp_length[1] = my_max(para_menu[j].count, temp_length[1]);
                temp_length[2] = my_max(para_menu[j].int_bit_num(para_menu[j].minimum) +
                    para_menu[j].int_bit_num(para_menu[j].maximum) + 4,
                    temp_length[2]);
                temp_length[3] = my_max(para_menu[j].int_bit_num(para_menu[j].origin), temp_length[3]);
            }

            // ���� max_length ����
            for (int i = 0; i < 4; i++) {
                max_length[i] = my_max(max_length[i], temp_length[i] + 1);
            }
        }
};

// ��֤ IP ��
bool check_ip_segment(const char* segment_start, int length)
{
    if (length == 0) return false; // ��Ϊ�գ�������Ч

    int segment_value = 0; // ��ǰ�ε���ֵ

    // ����ת��Ϊ����
    for (int j = 0; j < length; ++j)
    {
        if (segment_start[j] < '0' || segment_start[j] > '9')
        {
            return false; // �������֣����Ϊ��Ч
        }
        segment_value = segment_value * 10 + (segment_start[j] - '0'); // ������ֵ
    }

    // ���ε���Ч��
    if (segment_value < 0 || segment_value > 255)
        return false; // ֵ������Χ
    if (length > 1 && segment_start[0] == '0')
        return false; // ǰ���㲻�Ϸ�

    return true; // ����Ч
}

// ��֤ ipv4 ����
bool check_ipv4(const char* ip_str)
{
    int segments[4] = { 0 }; // ���ڴ洢ÿ���εĳ���
    int segment_count = 0;   // �μ���
    const char* segment_start = ip_str; // ��ǰ�ε���ʼλ��

    // ���� IP �ַ��������ҷָ��� '.'
    for (const char* p = ip_str; *p; ++p)
    {
        if (*p == '.')
        {
            if (segment_count >= 4)
                return false; // �������� 4������ false
            segments[segment_count++] = p - segment_start; // ��¼�εĳ���
            segment_start = p + 1; // ������һ���ε���ʼλ��
        }
    }

    // �������һ����
    int last_segment_length = strlen(segment_start);
    if (segment_count != 3 || last_segment_length == 0)
        return false; // ������ 4 ���������һ�β���Ϊ��

    // ��֤ÿ����
    segment_start = ip_str; // ���öε���ʼλ��
    for (int i = 0; i < 4; ++i)
    {
        if (i < 3)
        {
            if (!check_ip_segment(segment_start, segments[i]))
                return false; // �������Ч������ false
            segment_start += segments[i] + 1; // ������һ���ε���ʼλ��
        }
        else
        {
            // ������һ�ε���Ч��
            if (!check_ip_segment(segment_start, last_segment_length))
                return false; // ������һ����Ч������ false
        }
    }

    return true; // ���жξ���Ч
}


int usage(const char* const procname, const ping para_menu[]) 
{
    cout << "Usage: " << procname << " ";
    for (int i = 0; i < PING_NUM; i++) 
    {
        cout << "[" << para_menu[i].name;
        if (para_menu[i].description != nullptr)
            cout << " " << para_menu[i].description;
        cout << "] ";
    }
    cout << "IP��ַ" << endl;

    // ������󳤶�
    int max_length[4] = { MAX_LEN1, MAX_LEN2, MAX_LEN3, MAX_LEN4 };
    int temp_length[4] = { 0 };

    ping::calculate_max_lengths(para_menu, max_length, temp_length);

    // ��ӡ�ָ���
    cout << "       " << "=";
    for (int i = 0; i < 4; i++)
        cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
    cout << "=" << endl;

    // ��ӡ����
    cout << "        ";
    cout << setiosflags(ios::left) << setw(max_length[0]) << setfill(' ') << "����";
    cout << setiosflags(ios::left) << setw(max_length[1]) << setfill(' ') << "���Ӳ���";
    cout << setiosflags(ios::left) << setw(max_length[2]) << setfill(' ') << "��Χ";
    cout << setiosflags(ios::left) << setw(max_length[3]) << setfill(' ') << "Ĭ��ֵ";
    cout << endl;

    // ��ӡ�ָ���
    cout << "       =";
    for (int i = 0; i < 4; i++)
        cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
    cout << "=" << endl;

    // ��ӡ������Ϣ
    for (int i = 0; i < PING_NUM; i++) {
        int tem_len = max_length[2] - 3 - para_menu[i].int_bit_num(para_menu[i].minimum) - para_menu[i].int_bit_num(para_menu[i].maximum);
        cout << setw(8) << setfill(' ') << " ";
        cout << setiosflags(ios::left) << setw(max_length[0]) << setfill(' ') << para_menu[i].name;
        cout << setiosflags(ios::left) << setw(max_length[1]) << setfill(' ') << para_menu[i].count;
        cout << "[" << para_menu[i].minimum << ".." << para_menu[i].maximum << setw(tem_len) << setfill(' ') << "] ";
        cout << para_menu[i].origin << endl;
    }

    // ��ӡ�ָ���
    cout << "       " << "=";
    for (int i = 0; i < 4; i++)
        cout << setiosflags(ios::left) << setw(max_length[i]) << setfill('=') << '=';
    cout << "=" << endl;

    return 0;
}

int main(int argc, char* argv[])
{
    // ��ʼ�������˵�
    ping para_menu[PING_NUM] = 
    {
        ping("-l", "��С", 1, DEFAULT_SIZE, MIN_SIZE, MAX_SIZE),
        ping("-n", "����", 1, DEFAULT_AMOUNT, MIN_AMOUNT, MAX_AMOUNT),
        ping("-t", "��������", 0, 0, 0, 1)
    };

    // ��������в�������
    if (argc < 2)
    {
        usage(argv[0], para_menu); // ��ʾʹ��˵��
        return 0;
    }

    // ��֤���һ�������Ƿ�Ϊ�Ϸ��� IP ��ַ
    if (!check_ipv4(argv[argc - 1]))
    {
        cout << "IP��ַ����" << endl; // ��ʾ IP ��ַ����
        return 0;
    }

    // ���������в���
    for (int i = 1; i < argc - 1; ++i)
    {
        if (argv[i][0] != '-') // ȷ�������� '-' ��ͷ
        {
            cout << "����" << argv[i] << "������-��ͷ�ĺϷ�����" << endl;
            return 0; // ��ʾ������ʽ����
        }
        int param_id = -1;
        for (int j = 0; j < PING_NUM; ++j)
        {
            if (strcmp(argv[i], para_menu[j].name) == 0)
            {
                param_id = j; // �ҵ����� ID
                break;
            }
        }
        if (param_id == -1)
        {
            cout << "����" << argv[i] << "������" << endl; // ��ʾ����������
            return 0;
        }

        // ������и��Ӳ�����ѡ��
        if (para_menu[param_id].count == 0)     //��"-t"���е�����      
        {
            para_menu[param_id].value = 1;          
            continue;
        }
        if (para_menu[param_id].count > 0)
        {
            if (i + 1 >= argc || argv[i + 1][0] == '-')
            {
                cout << "����" << argv[i] << "û�к�������" << endl; // ��ʾȱ�ٲ���ֵ
                return 0;
            }

            bool valid = true; // ��ǲ���ֵ�Ƿ���Ч
            int param_value = 0; // ��ʼ������ֵ
            int sign = 1; // ��ʼ������Ϊ��
            const char* param_arg = argv[i + 1]; // ��ȡ����ֵ
            int length = strlen(param_arg); // ��ȡ����ֵ�ĳ���

            // ת������ֵΪ����
            for (int j = 0; j < length; ++j)
            {
                if (j == 0 && param_arg[j] == '-')
                {
                    sign = -1; // ������
                    continue;
                }
                if (param_arg[j] < '0' || param_arg[j] > '9')
                {
                    valid = false; // �������ַ����Ϊ��Ч
                    break;
                }
                param_value = param_value * 10 + (param_arg[j] - '0'); // �������ֵ
            }
            param_value *= sign; // Ӧ�÷���

            // ������ֵ�ķ�Χ
            if (valid && param_value >= para_menu[param_id].minimum && param_value <= para_menu[param_id].maximum)
                para_menu[param_id].value = param_value; // ������Чֵ
            else
                para_menu[param_id].value = para_menu[param_id].origin; // ʹ��Ĭ��ֵ
            ++i; // �����Ѵ���Ĳ���
        }
    }

    // ������������
    cout << "�������ͨ��" << endl;
    for (int i = 0; i < PING_NUM; ++i)
        cout << para_menu[i].name << " ������" << para_menu[i].value << endl; // ��ӡÿ��������ֵ
    cout << "IP��ַ��" << argv[argc - 1] << endl; // ��ӡ IP ��ַ

    return 0;
}