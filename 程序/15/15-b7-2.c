/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#if defined(_MSC_VER) || defined(__MINGW32__) 
#include <conio.h>
#endif
//������Ҫ�ɼ�������ͷ�ļ�


// ����һ�� 64 �ֽڵĽṹ�壬��Ա���������
#pragma pack(push, 1)
typedef struct {
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
} GameData;
#pragma pack(pop)

/* �˴�����������������������
   1�����������ĺ����������������µ� FILE* �����д�/��/д/�رյȲ���
   2����������ͬ��������main����
*/

// �жϲ��޸� char ������ֵ
void judge_and_change_char(GameData* data, char* value, const char attribute[15], int num, char max_border, char min_border) {
    while (1) {
        printf("%s����ǰֵ=%d����Χ[%d..%d]��������: ", attribute, (int)*value, (int)min_border, (int)max_border);
        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n');  // ������뻺����
            continue;
        }
        if (num > max_border || num < min_border) {
            printf("�Ƿ���%sֵ��%d\n", attribute, num);
            continue;
        }
        else {
            *value = (char)num;
            break;
        }
    }
}

// �жϲ��޸� short ������ֵ
void judge_and_change_short(GameData* data, short* value, const char attribute[15], short num, short max_border, short min_border) {
    while (1) {
        printf("%s����ǰֵ=%d����Χ[%d..%d]��������: ", attribute, *value, min_border, max_border);
        if (scanf("%hd", &num) != 1) {
            while (getchar() != '\n');  // ������뻺����
            continue;
        }
        if (num > max_border || num < min_border) {
            printf("�Ƿ���%sֵ��%d\n", attribute, num);
            continue;
        }
        else {
            *value = num;
            break;
        }
    }
}

// �жϲ��޸� int ������ֵ
void judge_and_change_int(GameData* data, int* value, const char attribute[15], int num, int max_border, int min_border) {
    while (1) {
        printf("%s����ǰֵ=%d����Χ[%d..%d]��������: ", attribute, *value, min_border, max_border);
        if (scanf("%d", &num) != 1) {
            while (getchar() != '\n');  // ������뻺����
            continue;
        }
        if (num > max_border || num < min_border) {
            printf("�Ƿ���%sֵ��%d\n", attribute, num);
            continue;
        }
        else {
            *value = num;
            break;
        }
    }
}

// �жϲ��޸� long long ������ֵ
void judge_and_change_long_long(GameData* data, long long* value, const char attribute[15], long long num, long long max_border, long long min_border) {
    while (1) {
        printf("%s����ǰֵ=%lld����Χ[%lld..%lld]��������: ", attribute, *value, min_border, max_border);
        if (scanf("%lld", &num) != 1) {
            while (getchar() != '\n');  // ������뻺����
            continue;
        }
        if (num > max_border || num < min_border) {
            printf("�Ƿ���%sֵ��%lld\n", attribute, num);
            continue;
        }
        else {
            *value = num;
            break;
        }
    }
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��fopen��һ��fread����Ϊ����������������fclose��
***************************************************************************/
int read()
{
    const char attributes[][22] = {
    "����ǳƣ�", "����ֵ��", "����ֵ��", "����ֵ��", "����ֵ��", "��Ǯֵ��",
    "����ֵ��", "����ֵ��", "��Ϸ�ۼ�ʱ��(us)ֵ��", "�ƶ��ٶ�ֵ��", "�����ٶ�ֵ��",
    "������Χֵ��", "������ֵ��", "������ֵ��", "���ݶ�ֵ��", "����ֵ��",
    "����ֵ��", "�ȼ�ֵ��", "ħ��ֵ��", "����ħ��ֵ��", "ħ���˺���ֵ��",
    "ħ��������ֵ��", "ħ��������ֵ��", "������ֵ��", "����ֵ��"
    };
    FILE* fp = fopen("game.dat", "rb");
    if (!fp) 
    {
        fprintf(stderr, "�޷����ļ� game.dat\n");
        return -1;
    }

    GameData data;
    if (fread(&data, 1, sizeof(GameData), fp) != sizeof(GameData)) 
    {
        fprintf(stderr, "��ȡ�ļ�ʧ��\n");
        fclose(fp);
        return -1;
    }
    

    int length = strlen("��Ϸ�ۼ�ʱ��(us)ֵ��");
    printf("%*s%s\n", length, attributes[0], data.nickname);
    printf("%*s%d\n", length, attributes[1], data.hp);
    printf("%*s%d\n", length, attributes[2], data.strength);
    printf("%*s%d\n", length, attributes[3], data.constitution);
    printf("%*s%d\n", length, attributes[4], data.agility);
    printf("%*s%d\n", length, attributes[5], data.money);
    printf("%*s%d\n", length, attributes[6], data.reputation);
    printf("%*s%d\n", length, attributes[7], data.charm);
    printf("%*s%lld\n", length, attributes[8], data.playTime);
    printf("%*s%d\n", length, attributes[9], (int)data.moveSpeed);
    printf("%*s%d\n", length, attributes[10], (int)data.attackSpeed);
    printf("%*s%d\n", length, attributes[11], (int)data.attackRange);
    printf("%*s%d\n", length, attributes[12], data.attackPower);
    printf("%*s%d\n", length, attributes[13], data.defense);
    printf("%*s%d\n", length, attributes[14], (int)data.dexterity);
    printf("%*s%d\n", length, attributes[15], (int)data.intelligence);
    printf("%*s%d\n", length, attributes[16], (int)data.experience);
    printf("%*s%d\n", length, attributes[17], (int)data.level);
    printf("%*s%d\n", length, attributes[18], data.mana);
    printf("%*s%d\n", length, attributes[19], (int)data.manaCost);
    printf("%*s%d\n", length, attributes[20], (int)data.magicDamage);
    printf("%*s%d\n", length, attributes[21], (int)data.hitRate);
    printf("%*s%d\n", length, attributes[22], (int)data.magicDefense);
    printf("%*s%d\n", length, attributes[23], (int)data.criticalRate);
    printf("%*s%d\n", length, attributes[24], (int)data.stamina);

    fclose(fp);
    return 0;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ��������������ֻ�������һ��open��һ��read��һ��write����Ϊ����������������fclose��
***************************************************************************/
int modify()
{
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
        "ħ��������", "ħ��������", "������", "����"
    };

    FILE* gfile = fopen("game.dat", "rb+");
    if (!gfile) {
        perror("�޷����ļ� game.dat");
        return -1;
    }

    GameData data;
    if (fread(&data, sizeof(GameData), 1, gfile) != 1) {
        perror("��ȡ�ļ�ʧ��");
        fclose(gfile);
        return -1;
    }

    char choice;
    do {
        printf("--------------------------------------\n");
        printf("  ��Ϸ�浵�ļ��޸Ĺ���\n");
        printf("--------------------------------------\n");
        printf("  %s(%s)\n", attributes[0], data.nickname);
        printf("  %s(%d)\n", attributes[1], data.hp);
        printf("  %s(%d)\n", attributes[2], data.strength);
        printf("  %s(%d)\n", attributes[3], data.constitution);
        printf("  %s(%d)\n", attributes[4], data.agility);
        printf("  %s(%d)\n", attributes[5], data.money);
        printf("  %s(%d)\n", attributes[6], data.reputation);
        printf("  %s(%d)\n", attributes[7], data.charm);
        printf("  %s(%lld)\n", attributes[8], data.playTime);
        printf("  %s(%d)\n", attributes[9], (int)data.moveSpeed);
        printf("  %s(%d)\n", attributes[10], (int)data.attackSpeed);
        printf("  %s(%d)\n", attributes[11], (int)data.attackRange);
        printf("  %s(%d)\n", attributes[12], data.attackPower);
        printf("  %s(%d)\n", attributes[13], data.defense);
        printf("  %s(%d)\n", attributes[14], (int)data.dexterity);
        printf("  %s(%d)\n", attributes[15], (int)data.intelligence);
        printf("  %s(%d)\n", attributes[16], (int)data.experience);
        printf("  %s(%d)\n", attributes[17], (int)data.level);
        printf("  %s(%d)\n", attributes[18], data.mana);
        printf("  %s(%d)\n", attributes[19], (int)data.manaCost);
        printf("  %s(%d)\n", attributes[20], (int)data.magicDamage);
        printf("  %s(%d)\n", attributes[21], (int)data.hitRate);
        printf("  %s(%d)\n", attributes[22], (int)data.magicDefense);
        printf("  %s(%d)\n", attributes[23], (int)data.criticalRate);
        printf("  %s(%d)\n", attributes[24], (int)data.stamina);
        printf("--------------------------------------\n");
        printf("  0.�����޸�\n");
        printf("  1.�����˳�\n");
        printf("--------------------------------------\n");
        printf("��ѡ��[a..y, 0..1]: ");
#if defined(_MSC_VER) || defined(__MINGW32__) 
        choice = _getch();
#elif defined(__linux__)
        choice = getchar();
#endif
#if defined(_MSC_VER) || defined(__MINGW32__) 
        printf("%c\n", choice);
#endif
        printf("\n");
        short num_short = 0;
        int num_int = 0;
        long long num_long_long = 0LL;
        switch (choice) 
        {
            case 'a':
                printf("����ǳƣ���ǰֵ=%s��������: ", data.nickname);
#if defined(__linux__)
                while (getchar() != '\n' && getchar() != EOF);
#endif
                if (fgets(data.nickname, sizeof(data.nickname), stdin))
                    data.nickname[strcspn(data.nickname, "\n")] = '\0'; // ȥ�����з�
                if (strcspn(data.nickname, "\n") == sizeof(data.nickname) - 1) {
                    char ch;
                    while ((ch = getchar()) != '\n' && ch != EOF);  // ��ȡ������ֱ�����з�
                }
                break;
            case 'b':
                judge_and_change_short(&data, &data.hp, attribute[1], num_short, 10000, 0);
                break;
            case 'c':
                judge_and_change_short(&data, &data.strength, attribute[2], num_short, 10000, 0);
                break;
            case 'd':
                judge_and_change_short(&data, &data.constitution, attribute[3], num_short, 8192, 0);
                break;
            case 'e':
                judge_and_change_short(&data, &data.agility, attribute[4], num_short, 1024, 0);
                break;
            case 'f':
                judge_and_change_int(&data, &data.money, attribute[5], num_int, 100000000, 0);
                break;
            case 'g':
                judge_and_change_int(&data, &data.reputation, attribute[6], num_int, 1000000, 0);
                break;
            case 'h':
                judge_and_change_int(&data, &data.charm, attribute[7], num_int, 1000000, 0);
                break;
            case 'i':
                judge_and_change_long_long(&data, &data.playTime, attribute[8], num_long_long, 10000000000000000LL, 0);
                break;
            case 'j':
                judge_and_change_char(&data, &data.moveSpeed, attribute[9], num_int, 127, 0);
                break;
            case 'k':
                judge_and_change_char(&data, &data.attackSpeed, attribute[10], num_int, 127, 0);
                break;
            case 'l':
                judge_and_change_char(&data, &data.attackRange, attribute[11], num_int, 127, 0);
                break;
            case 'm':
                judge_and_change_short(&data, &data.attackPower, attribute[12], num_short, 2000, 0);
                break;
            case 'n':
                judge_and_change_short(&data, &data.defense, attribute[13], num_short, 2000, 0);
                break;
            case 'o':
                judge_and_change_char(&data, &data.dexterity, attribute[14], num_int, 100, 0);
                break;
            case 'p':
                judge_and_change_char(&data, &data.intelligence, attribute[15], num_int, 100, 0);
                break;
            case 'q':
                judge_and_change_char(&data, &data.experience, attribute[16], num_int, 100, 0);
                break;
            case 'r':
                judge_and_change_char(&data, &data.level, attribute[17], num_int, 100, 0);
                break;
            case 's':
                judge_and_change_short(&data, &data.mana, attribute[18], num_short, 10000, 0);
                break;
            case 't':
                judge_and_change_char(&data, &data.manaCost, attribute[19], num_int, 100, 0);
                break;
            case 'u':
                judge_and_change_char(&data, &data.magicDamage, attribute[20], num_int, 100, 0);
                break;
            case 'v':
                judge_and_change_char(&data, &data.hitRate, attribute[21], num_int, 100, 0);
                break;
            case 'w':
                judge_and_change_char(&data, &data.magicDefense, attribute[22], num_int, 100, 0);
                break;
            case 'x':
                judge_and_change_char(&data, &data.criticalRate, attribute[23], num_int, 100, 0);
                break;
            case 'y':
                judge_and_change_char(&data, &data.stamina, attribute[24], num_int, 100, 0);
                break;
            case '0':
                fclose(gfile);
                return 0;
            case '1':
                fseek(gfile, 0, SEEK_SET);
                if (fwrite(&data, sizeof(GameData), 1, gfile) != 1) {
                    perror("�ļ�д��ʧ��");
                    fclose(gfile);
                    return -1;
                }
                fclose(gfile);
                return 0;
            default:
                continue;
        }
    } while (1);

    fclose(gfile);
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
    if (argc < 2) {
        fprintf(stderr, "usage : 15-b7-2 --modify | --read\n");
        return -1;
    }

    if (strcmp(argv[1], "--read") == 0) 
        read();
    else if (strcmp(argv[1], "--modify") == 0) 
        modify();
    else {
        fprintf(stderr, "usage: program --modify | --read\n");
        return -1;
    }

    return 0;
}