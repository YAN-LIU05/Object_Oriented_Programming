/* 2352018 ������ ���� */
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <time.h>
/* �������Ҫ���˴��������ͷ�ļ� */
	
using namespace std;

/* �����峣����/�궨�壬����������ȫ�ֱ��� */
#define TOTAL_CARDS 54 // ������
#define CARDS_PER_PLAYER 17 // ÿ�˷�������
#define NUMBER_OF_PLAYERS 3 // �������
#define REMAINING_CARDS 3 // ʣ�������
#if defined(__linux__) 
#define CHOICE 0
#else
#define CHOICE 1
#endif

/* ��������Լ���Ҫ�ĺ��� */

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡĳ����ҵ�������Ϣ������ǵ���������ӱ��
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int print(const char* prompt, const bool landlord, const unsigned long long player)
{
	/* ֻ�����岻���������������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
    int count = 0;

    cout << prompt;

    for (int i = 0; i < TOTAL_CARDS; ++i)
        if (player & (1ULL << i))
        {
            // ��ӡ��ɫ�͵���
            if (i == 52)
                cout << "BJ "; // С��
            else if (i == 53)
                cout << "RJ "; // ����
            else
            {
                char suit;
                int rank = i / 4 + 3; // ��3��ʼ

                if (CHOICE)   //�жϱ�����
                {
                    switch (i % 4)
                    {
                        case 0: suit = '\5'; // ÷��
                            break; 
                        case 1: suit = '\4'; // ����
                            break; 
                        case 2: suit = '\3'; // ����
                            break; 
                        case 3: suit = '\6'; // ����
                            break; 
                    }
                }
                else
                {
                    switch (i % 4)
                    {
                        case 0: suit = 'C'; // ÷��
                            break; 
                        case 1: suit = 'D'; // ����
                            break; 
                        case 2: suit = 'H'; // ����
                            break; 
                        case 3: suit = 'S'; // ����
                            break; 
                    }
                }

                // ���⴦�����
                switch (rank)
                {
                    case 10:
                        cout << suit << "T ";  // 10
                        break;
                    case 11:
                        cout << suit << "J ";  // J
                        break;
                    case 12:
                        cout << suit << "Q "; // Q
                        break;
                    case 13:
                        cout << suit << "K "; // K
                        break;
                    case 14:
                        cout << suit << "A ";  // A
                        break;
                    case 15:
                        cout << suit << "2 ";  // 2
                        break;
                    default:
                        if (rank >= 3 && rank <= 9)
                            cout << suit << rank << " "; // 3-9
                        break;
                }
            }
            count++;
        }

    if (landlord)
        cout << "(����)";
    cout << endl;
    return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����ƣ����������������
  ���������
  �� �� ֵ��
  ˵    ����
 ***************************************************************************/
int deal(unsigned long long* player)
{
	/* ֻ�����岻����ʮ���������͵ļ򵥱��������ܶ�������������ṹ�塢string�� */
    srand(static_cast<unsigned int>(time(nullptr)));
    long long card = (1ULL << 54) - 1;
    int landlord = 0;

    for (int i = 0; i < CARDS_PER_PLAYER; i++) // �����ִ�
    { 
        for (int j = 0; j < NUMBER_OF_PLAYERS; j++) // һ��Ϊ��λ��ҷ���
        { 
            int num = rand() % TOTAL_CARDS; // ����0-53��Χ�ڵ������
            if (card & ((long long)1 << num)) // ��鵱ǰλ���Ƿ�δ������
            { 
                card &= ~(1LL << num); // ���Ϊ�ѷ���
                *(player + j) |= ((unsigned long long) 1 << num);   // ���Ʒ������
            }
            else  // ��ǰλ���ѱ�����
                --j;
        }
        cout << "��" << i + 1 << "�ֽ�����" << endl;
        print("�׵��ƣ�", 0, *player);
        print("�ҵ��ƣ�", 0, *(player + 1));
        print("�����ƣ�", 0, *(player + 2));
    }
    cout << endl;

    // ֱ��������ʵ�������߼�
    cout << "��ѡ��һ������[0-2]��" << endl;
    while (1) 
    {
        cin >> landlord;
        if (!cin) 
        {
            cin.clear();
            cin.ignore(65536, '\n');
        }
        else if (landlord >= 0 && landlord <= 2) 
            break;
        cout << "��ѡ��һ������[0-2]��" << endl;
    }

    for (int i = 0; i < TOTAL_CARDS; i++)  // ����ʣ���ƶѣ���ʣ����Ʒ�������
    {
        if (card & ((long long)1 << i))  // ��鵱ǰλ���Ƿ�δ������
        {
            card &= ~(1LL << i); // ���Ϊ�ѷ���
            *(player + landlord) |= ((unsigned long long) 1 << i);   // ���Ʒ�������
        }
    }
    return landlord;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main��������׼�޸�
 ***************************************************************************/
int main()
{
	unsigned long long player[3] = { 0 }; //���������ҵķ�����Ϣ
	int landlord; //����0-2��ʾ�ĸ�����ǵ���

	cout << "���س�����ʼ����";
	while (getchar() != '\n')
		;

	landlord = deal(player);
	print("�׵��ƣ�", (landlord == 0), player[0]);
	print("�ҵ��ƣ�", (landlord == 1), player[1]);
	print("�����ƣ�", (landlord == 2), player[2]);

	return 0;
}