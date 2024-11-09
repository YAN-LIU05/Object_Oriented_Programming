/* 2352018 ������ ���� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>

// ����definite_integration���������ڼ��㶨����
double definite_integration(double (*func)(double), double low, double high, int n) 
{
    double width = (high - low) / n; // ÿ��С���εĿ��
    double integral = 0.0;
    for (int i = 0; i < n; i++) 
    {
        double x = low + i * width + width; // ȡ�Ҷ˵��ֵ
        integral += func(x) * width;
    }
    return integral;
}

int main() 
{
    int n;
    double low, high, value;

    // ����sin(x)dx�Ļ���
    printf("������sinxdx�����ޡ����޼����仮������\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(sin, low, high, n);
    printf("sinxdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    // ����cos(x)dx�Ļ���
    printf("������cosxdx�����ޡ����޼����仮������\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(cos, low, high, n);
    printf("cosxdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    // ����e^(x)dx�Ļ���
    printf("������e^xdx�����ޡ����޼����仮������\n");
    scanf("%lf %lf %d", &low, &high, &n);
    value = definite_integration(exp, low, high, n);
    printf("e^xdx[%g~%g/n=%d] : %g\n", low, high, n, value);

    return 0;
}