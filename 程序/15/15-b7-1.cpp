/* 2352018 ������ ���� */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#if defined(_MSC_VER) || defined(__MINGW32__) 
#include <conio.h>
#endif

using namespace std;

// ����һ�� 64 �ֽڵĽṹ�壬��Ա���������
#pragma pack(push, 1)
struct GameData {
    char nickname[16];    // 1-16 ����ǳ�
    short hp;             // 17-18 ����ֵ
    short strength;       // 19-20 ����ֵ
    short constitution;   // 21-22 ����
    short agility;        // 23-24 ����
    int money;            // 25-28 ��Ǯ
    int reputation;       // 29-32 ����ֵ
    int charm;            // 33-36 ����ֵ
    long long playTime;   // 37-44 �ۼ�ʱ��
    char moveSpeed;       // 45 �ƶ��ٶ�
    char attackSpeed;     // 46 �����ٶ�
    char attackRange;     // 47 ������Χ
    char empty;           // 48
    short attackPower;    // 49-50 ������
    short defense;        // 51-52 ������
    char dexterity;       // 53 ����
    char intelligence;    // 54 ����
    char experience;      // 55 ����
    char level;           // 56 �ȼ�
    short mana;           // 57-58 ħ��ֵ
    char manaCost;        // 59 ʹ��ħ������
    char magicDamage;     // 60 ħ���˺�
    char hitRate;         // 61 ������
    char magicDefense;    // 62 ħ������
    char criticalRate;    // 63 ������
    char stamina;         // 64 ����
};
#pragma pack(pop)

/* �˴�����������������������
   1�����������ĺ����������������µ� fstream / ifstream / ofstream �����󣬲����д�/��/д/�رյȲ���
   2�����������ĺ���������������C��ʽ�����ļ�����
   3��������������ͬ��������main����
*/

/***************************************************************************
  �������ƣ�judge_and_change
  ��    �ܣ��жϲ��޸���ֵ
  ���������
  �� �� ֵ��
  ˵    �����ĸ����غ���
***************************************************************************/
void judge_and_change(GameData& data, char& value, const char attribute[15], int num, char max_border = 100, char min_border = 0)
{
    while (1)
    {
        cout << attribute << "����ǰֵ=" << (int)value << "����Χ[" << (int)min_border << ".." << (int)max_border << "]�������� : ";
        cin.clear();
        cin >> num;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (num > max_border || num < min_border)
        {
            cout << "�Ƿ���" << attribute << "ֵ��" << (int)num << endl;
            continue;
        }
        else
        {
            value = num;
            break;
        }
    }
}

void judge_and_change(GameData& data, short& value, const char attribute[15], short num, short max_border, short min_border = 0)
{
    while (1)
    {
        cout << attribute << "����ǰֵ=" << value << "����Χ[" << min_border << ".." << max_border << "]�������� : ";
        cin.clear();
        cin >> num;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (num > max_border || num < min_border)
        {
            cout << "�Ƿ���" << attribute << "ֵ��" << num << endl;
            continue;
        }
        else
        {
            value = num;
            break;
        }
    }
}

void judge_and_change(GameData& data, int& value, const char attribute[15], int num, int max_border, int min_border = 0)
{
    while (1)
    {
        cout << attribute << "����ǰֵ=" << value << "����Χ[" << min_border << ".." << max_border << "]�������� : ";
        cin.clear();
        cin >> num;
        if (cin.fail()) 
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (num > max_border || num < min_border)
        {
            cout << "�Ƿ���" << attribute << "ֵ��" << num << endl;
            continue;
        }
        else
        {
            value = num;
            break;
        }
    }
}

void judge_and_change(GameData& data, long long& value, const char attribute[15], long long num, long long max_border = 10000000000000000, long long min_border = 0)
{
    while (1)
    {
        cout << attribute << "����ǰֵ=" << value << "����Χ[" << min_border << ".." << max_border << "]�������� : ";
        cin.clear();
        cin >> num;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(65536, '\n');
            continue;
        }
        if (num > max_border || num < min_border)
        {
            cout << "�Ƿ���" << attribute << "ֵ��" << num << endl;
            continue;
        }
        else
        {
            value = num;
            break;
        }
    }
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read����Ϊ����������������close��
***************************************************************************/
int read() 
{
    // ������������
    const char attributes[][22] = {
        "����ǳƣ�", "����ֵ��", "����ֵ��", "����ֵ��", "����ֵ��", "��Ǯֵ��",
        "����ֵ��", "����ֵ��", "��Ϸ�ۼ�ʱ��(us)ֵ��", "�ƶ��ٶ�ֵ��", "�����ٶ�ֵ��",
        "������Χֵ��", "������ֵ��", "������ֵ��", "���ݶ�ֵ��", "����ֵ��", 
        "����ֵ��", "�ȼ�ֵ��", "ħ��ֵ��", "����ħ��ֵ��", "ħ���˺���ֵ��", 
        "ħ��������ֵ��", "ħ��������ֵ��", "������ֵ��", "����ֵ��"
    };

    fstream gfile;

    // ���ļ�
    gfile.open("game.dat", ios::binary | ios::in);
    if (!gfile) 
    {
        cerr << "�޷����ļ� game.dat" << endl;
        return -1;
    }

    GameData data;

    // һ���Զ�ȡ 64 �ֽ�����
    char temp[sizeof(GameData)];
    gfile.read(temp, sizeof(GameData));
    if (!gfile) 
    {
        cerr << "��ȡ�ļ�ʧ��" << endl;
        gfile.close();
        return -1;
    }
    memcpy(&data, temp, sizeof(GameData));
    // ��ʾ�浵����
    int length = strlen("��Ϸ�ۼ�ʱ��(us)ֵ��");
    cout << setw(length) << right << attributes[0] << data.nickname << endl;
    cout << setw(length) << right << attributes[1] << data.hp << endl;
    cout << setw(length) << right << attributes[2] << data.strength << endl;
    cout << setw(length) << right << attributes[3] << data.constitution << endl;
    cout << setw(length) << right << attributes[4] << data.agility << endl;
    cout << setw(length) << right << attributes[5] << data.money << endl;
    cout << setw(length) << right << attributes[6] << data.reputation << endl;
    cout << setw(length) << right << attributes[7] << data.charm << endl;
    cout << setw(length) << right << attributes[8] << data.playTime << endl;
    cout << setw(length) << right << attributes[9] << static_cast<int>(data.moveSpeed) << endl;
    cout << setw(length) << right << attributes[10] << static_cast<int>(data.attackSpeed) << endl;
    cout << setw(length) << right << attributes[11] << static_cast<int>(data.attackRange) << endl;
    cout << setw(length) << right << attributes[12] << data.attackPower << endl;
    cout << setw(length) << right << attributes[13] << data.defense << endl;
    cout << setw(length) << right << attributes[14] << static_cast<int>(data.dexterity) << endl;
    cout << setw(length) << right << attributes[15] << static_cast<int>(data.intelligence) << endl;
    cout << setw(length) << right << attributes[16] << static_cast<int>(data.experience) << endl;
    cout << setw(length) << right << attributes[17] << static_cast<int>(data.level) << endl;
    cout << setw(length) << right << attributes[18] << data.mana << endl;
    cout << setw(length) << right << attributes[19] << static_cast<int>(data.manaCost) << endl;
    cout << setw(length) << right << attributes[20] << static_cast<int>(data.magicDamage) << endl;
    cout << setw(length) << right << attributes[21] << static_cast<int>(data.hitRate) << endl;
    cout << setw(length) << right << attributes[22] << static_cast<int>(data.magicDefense) << endl;
    cout << setw(length) << right << attributes[23] << static_cast<int>(data.criticalRate) << endl;
    cout << setw(length) << right << attributes[24] << static_cast<int>(data.stamina) << endl;

    gfile.close();
    return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read��һ��write����Ϊ����������������close��
***************************************************************************/
int modify() 
{
    // ������������
    const char attributes[][15] = {
        "a.����ǳ�    ", "b.����        ", "c.����        ", "d.����        ",
        "e.����        ", "f.��Ǯ        ", "g.����        ", "h.����        ",
        "i.��Ϸ�ۼ�ʱ��", "j.�ƶ��ٶ�    ", "k.�����ٶ�    ", "l.������Χ    ",
        "m.������      ", "n.������      ", "o.���ݶ�      ", "p.����        ",
        "q.����        ", "r.�ȼ�        ", "s.ħ��ֵ      ", "t.����ħ��ֵ  ",
        "u.ħ���˺���  ", "v.ħ��������  ", "w.ħ��������  ", "x.������      ",
        "y.����        "
    };
    const char attribute[][15] = {
    "����ǳ�", "����", "����", "����", "����", "��Ǯ", "����", "����",
    "��Ϸ�ۼ�ʱ��", "�ƶ��ٶ�", "�����ٶ�", "������Χ", "������", "������", 
    "���ݶ�", "����",  "����", "�ȼ�", "ħ��ֵ", "����ħ��ֵ", "ħ���˺���", 
    "ħ��������", "ħ��������", "������", "���� "
    };

    fstream gfile;
    
    gfile.open("game.dat", ios::binary | ios::in | ios::out);
    if (!gfile) 
    {
        cerr << "�޷����ļ� game.dat" << endl;
        return -1;
    }

    GameData data;
    char temp[sizeof(GameData)];
    gfile.read(temp, sizeof(GameData));

    if (!gfile)
    {
        cerr << "��ȡ�ļ�ʧ��" << endl;
        gfile.close();
        return -1;
    }
    memcpy(&data, temp, sizeof(GameData));
    char choice;
    do {
        cout << "--------------------------------------" << endl;
        cout << "  ��Ϸ�浵�ļ��޸Ĺ���" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  " << attributes[0] << "(" << data.nickname << ")" << endl;
        cout << "  " << attributes[1] << "(" << data.hp << ")" << endl;
        cout << "  " << attributes[2] << "(" << data.strength << ")" << endl;
        cout << "  " << attributes[3] << "(" << data.constitution << ")" << endl;
        cout << "  " << attributes[4] << "(" << data.agility << ")" << endl;
        cout << "  " << attributes[5] << "(" << data.money << ")" << endl;
        cout << "  " << attributes[6] << "(" << data.reputation << ")" << endl;
        cout << "  " << attributes[7] << "(" << data.charm << ")" << endl;
        cout << "  " << attributes[8] << "(" << data.playTime << ")" << endl;
        cout << "  " << attributes[9] << "(" << static_cast<int>(data.moveSpeed) << ")" << endl;
        cout << "  " << attributes[10] << "(" << static_cast<int>(data.attackSpeed) << ")" << endl;
        cout << "  " << attributes[11] << "(" << static_cast<int>(data.attackRange) << ")" << endl;
        cout << "  " << attributes[12] << "(" << data.attackPower << ")" << endl;
        cout << "  " << attributes[13] << "(" << data.defense << ")" << endl;
        cout << "  " << attributes[14] << "(" << static_cast<int>(data.dexterity) << ")" << endl;
        cout << "  " << attributes[15] << "(" << static_cast<int>(data.intelligence) << ")" << endl;
        cout << "  " << attributes[16] << "(" << static_cast<int>(data.experience) << ")" << endl;
        cout << "  " << attributes[17] << "(" << static_cast<int>(data.level) << ")" << endl;
        cout << "  " << attributes[18] << "(" << data.mana << ")" << endl;
        cout << "  " << attributes[19] << "(" << static_cast<int>(data.manaCost) << ")" << endl;
        cout << "  " << attributes[20] << "(" << static_cast<int>(data.magicDamage) << ")" << endl;
        cout << "  " << attributes[21] << "(" << static_cast<int>(data.hitRate) << ")" << endl;
        cout << "  " << attributes[22] << "(" << static_cast<int>(data.magicDefense) << ")" << endl;
        cout << "  " << attributes[23] << "(" << static_cast<int>(data.criticalRate) << ")" << endl;
        cout << "  " << attributes[24] << "(" << static_cast<int>(data.stamina) << ")" << endl;
        cout << "--------------------------------------" << endl;
        cout << "  0.�����޸�" << endl;
        cout << "  1.�����˳�" << endl;
        cout << "--------------------------------------" << endl;
        cout << "��ѡ��[a..y, 0..1] ";
#if defined(_MSC_VER) || defined(__MINGW32__) 
        choice = _getch();
#elif defined(__linux__)
        choice = getchar();
#endif
#if defined(_MSC_VER) || defined(__MINGW32__) 
        cout << choice << endl;
#endif
        cout << endl;
        short num_short = 0;
        int num_int = 0;
        long long num_long_long = 0LL;
        switch (choice) 
        {
            case 'a':
                cout << "����ǳƣ���ǰֵ=" << data.nickname << "��������: ";
                cin.clear();
#if defined(__linux__) 
                cin.ignore(65536, '\n');
#endif
                cin.getline(data.nickname, 16);
                if (cin.fail()) 
                {
                    cin.clear();
                    cin.ignore(65536, '\n'); 
                }
                data.nickname[15] = '\0';
                break;
            case 'b':
                judge_and_change(data, data.hp, attribute[1], num_short, 10000);
                break;
            case 'c':
                judge_and_change(data, data.strength, attribute[2], num_short, 10000);
                break;
            case 'd':
                judge_and_change(data, data.constitution, attribute[3], num_short, 8192);
                break;
            case 'e':
                judge_and_change(data, data.agility, attribute[4], num_short, 1024);
                break;
            case 'f':
                judge_and_change(data, data.money, attribute[5], num_int, 100000000);
                break;
            case 'g':
                judge_and_change(data, data.reputation, attribute[6], num_int, 1000000);
                break;
            case 'h':
                judge_and_change(data, data.charm, attribute[7], num_int, 1000000);
                break;
            case 'i':
                judge_and_change(data, data.playTime, attribute[8], num_long_long);
                break;
            case 'j':
                judge_and_change(data, data.moveSpeed, attribute[9], num_int);
                break;
            case 'k':
                judge_and_change(data, data.attackSpeed, attribute[10], num_int);
                break;
            case 'l':
                judge_and_change(data, data.attackRange, attribute[11], num_int);
                break;
            case 'm':
                judge_and_change(data, data.attackPower, attribute[12], num_short, 2000);
                break;
            case 'n':
                judge_and_change(data, data.defense, attribute[13], num_short, 2000);
                break;
            case 'o':
                judge_and_change(data, data.dexterity, attribute[14], num_int);
                break;
            case 'p':
                judge_and_change(data, data.intelligence, attribute[15], num_int);
                break;
            case 'q':
                judge_and_change(data, data.experience, attribute[16], num_int);
                break;
            case 'r':
                judge_and_change(data, data.level, attribute[17], num_int);
                break;
            case 's':
                judge_and_change(data, data.mana, attribute[18], num_short, 10000);
                break;
            case 't':
                judge_and_change(data, data.manaCost, attribute[19], num_int);
                break;
            case 'u':
                judge_and_change(data, data.magicDamage, attribute[20], num_int);
                break;
            case 'v':
                judge_and_change(data, data.hitRate, attribute[21], num_int);
                break;
            case 'w':
                judge_and_change(data, data.magicDefense, attribute[22], num_int);
                break;
            case 'x':
                judge_and_change(data, data.criticalRate, attribute[23], num_int);
                break;
            case 'y':
                judge_and_change(data, data.stamina, attribute[24], num_int);
                break;
            case '0':
                gfile.close();
                return 0;
            case '1':
                char temp0[sizeof(GameData)];
                memcpy(temp0, &data, sizeof(GameData));
                gfile.seekp(0);
                gfile.write(temp0, sizeof(GameData));
                if (!gfile) 
                {
                    cerr << "�ļ�д��ʧ��" << endl;
                    return -1;
                }
                gfile.close();
                return 0;
            default:
                continue;
        }
    } while (true);

    return 0;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main�������������������������ļ���д
***************************************************************************/
int main(int argc, char** argv) 
{
    if (argc < 2)
    {
        cerr << "usage : 15-b7-1 --modify | --read" << endl;
        return -1;
    }

    if (strcmp(argv[1], "--read") == 0) 
        return read();
    else if (strcmp(argv[1], "--modify") == 0) 
        return modify();
    else {
        cerr << "usage : 15-b7 --modify | --read" << endl;
        return -1;
    }
    return 0;
}

