/* 2352018 ������ ���� */
#include <stdio.h>

int main()
{
    /* ��������������໥λ�ÿɻ���������Ŀǰ#if���������VS2022�������Ȼ�ΪLinux��*/
#if defined(_MSC_VER)
    printf("VS2022\n");
#elif defined(__MINGW32__) 
    printf("Dev\n");
#elif defined(__linux__) 
    printf("Linux\n");
#endif

    return 0;
}