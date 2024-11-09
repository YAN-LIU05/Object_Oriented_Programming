/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <iomanip>
#include <climits>

using namespace std;

void print_switches(short state)
{
    const char labels[] = "ABCDEFGHIJ";
    for (int i = 0; i < 11; i++)
        cout << labels[i] << "   ";
    cout << endl;
    // �����������״̬
    for (int i = 0; i < 10; ++i) 
        cout << ((state & (1 << i)) ? "ON  " : "OFF ");
    cout << endl;
}

char change_to_capital(char c) 
{
    if (c >= 'a' && c <= 'z') return c - ('a' - 'A');
    return c;
}

int main() 
{
    short state = 0x0000;
    cout << "��ʼ״̬��0x" << hex << setw(4) << setfill('0') << state << endl;
    print_switches(state);
    cout << endl;

    while (1) 
    {
        char input[CHAR_MAX];  
        cout << "����(\"A ON / J OFF\"��ʽ���룬����\"Q on/off\"�˳�): " << endl;
        cin.getline(input, sizeof(input));

        if (input[0] == 'Q' || input[0] == 'q') 
            break;

        char switch_label;
        char on_off[4];  // �洢 "ON" �� "OFF"

        // �ֶ���������
        switch_label = change_to_capital(input[0]);

        // ���ҿո����ȡ����
        int num = 2; 
        int on_off_num = 0;  // ���� on_off ������

        // �������ܵĿո�
        while (input[num] == ' ') 
            num++;

        // ��ȡ
        while (input[num] != '\0' && input[num] != ' ' && on_off_num < 3)
            on_off[on_off_num++] = change_to_capital(input[num++]);  // �������ַ�ת��Ϊ��д
        on_off[on_off_num] = '\0';  // �����ַ���

        // ����������
        if (switch_label < 'A' || switch_label > 'J' || (strcmp(on_off, "ON") != 0 && strcmp(on_off, "OFF") != 0)) 
            continue;

        int index = switch_label - 'A';
        if (strcmp(on_off, "ON") == 0) 
            state |= (1 << index);  // ���ö�Ӧ��bitΪ1
        else 
            state &= ~(1 << index);  // ���ö�Ӧ��bitΪ0

        cout << "��ǰ״̬��0x" << hex << setw(4) << setfill('0') << state << endl;  // �����ǰ״̬��ʮ������
        print_switches(state);
        cout << endl;
    }

    return 0;
}
