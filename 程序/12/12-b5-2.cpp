/* 2352018 ������ ���� */
#include <iostream>
#include <iomanip>
using namespace std;

const char* sp = "=====================================";

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����ÿ�����ֿ��Ϊ8���Ҷ���
***************************************************************************/
template <typename T, int ROWS, int COLS>
void matrix_print(const char* message, T(&matrix)[ROWS][COLS])
{
	cout << message << endl;
	for (int i = 0; i < ROWS; ++i) 
	{
		for (int j = 0; j < COLS; ++j) 
			cout << setw(8) << right << matrix[i][j]; // ÿ�����ֿ��Ϊ8���Ҷ���
		cout << endl;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<typename T1, typename T2, int ROWS, int COLS>
void matrix_addition(T1(&result)[ROWS][COLS], const T2(&matrix1)[ROWS][COLS], const T2(&matrix2)[ROWS][COLS]) {
	cout << "Դ����1 : ��=" << ROWS << " ��=" << COLS << " ռ�ÿռ�=" << sizeof(matrix1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << ROWS << " ��=" << COLS << " ռ�ÿռ�=" << sizeof(matrix2) << "�ֽ�" << endl;

	for (int i = 0; i < ROWS; ++i)
	{
		for (int j = 0; j < COLS; ++j) 
			result[i][j] = matrix1[i][j] + matrix2[i][j];
	}

	cout << "�;���  : ��=" << ROWS << " ��=" << COLS << " ռ�ÿռ�=" << sizeof(result) << "�ֽ�" << endl;
}



/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
template<typename T1, typename T2, typename T3, int ROWS, int COLS, int COLS_>
void matrix_multiplication(T1(&t_mul)[ROWS][COLS_], const T2(&t1)[ROWS][COLS], const T3(&t2)[COLS][COLS_]) 
{
	cout << "Դ����1 : ��=" << ROWS << " ��=" << COLS << " ռ�ÿռ�=" << sizeof(t1) << "�ֽ�" << endl;
	cout << "Դ����2 : ��=" << COLS << " ��=" << COLS_ << " ռ�ÿռ�=" << sizeof(t2) << "�ֽ�" << endl;

	for (int i = 0; i < ROWS; ++i) 
	{
		for (int j = 0; j < COLS_; ++j) 
		{
			t_mul[i][j] = 0; // ��ʼ��������ĵ�ǰԪ��
			for (int k = 0; k < COLS; ++k) 
				t_mul[i][j] += static_cast<T1>(t1[i][k] * t2[k][j]); // ʹ�� static_cast ��������ת��
		}
	}
	cout << "������  : ��=" << ROWS << " ��=" << COLS_ << " ռ�ÿռ�=" << sizeof(t_mul) << "�ֽ�" << endl;
}


/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main������׼����
***************************************************************************/
int main()
{
	int t1[3][4] = {
		{1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}
	};
	int t2[3][4] = {
		{12,11,10,9},
		{8,7,6,5},
		{4,3,2,1}
	};
	int t3[4][2] = {
		{1, 2},
		{3, 4},
		{5, 6},
		{7, 8}
	};
	int t_add[3][4], t_mul[3][2];

	cout << sp << endl;
	matrix_print("�ӷ����㣬Դ����1��", t1);
	matrix_print("�ӷ����㣬Դ����2��", t2);
	matrix_addition(t_add, t1, t2);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", t_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", t1);
	matrix_print("�˷����㣬Դ����2��", t3);
	matrix_multiplication(t_mul, t1, t3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", t_mul);
	cout << sp << endl;

	double d1[2][4] = {
		{1.1, 2.2, 3.3, 4.4},
		{5.5 ,6.6, 7.7, 8.8}
	};
	double d2[2][4] = {
		{8.8, 7.7, 6.6, 5.5},
		{4.4, 3.3, 2.2, 1.1}
	};
	double d_add[2][4];
	/* ��Ҫ��Ϊʲô����˷��������Ͳ�ͬ������� */
	float f3[4][3] = {
		{12.12f, 11.11f, 10.10f},
		{9.9f, 8.8f, 7.7f},
		{6.6f, 5.5f, 4.4f},
		{3.3f, 2.2f, 1.1f}
	};
	int i_mul[2][3];

	matrix_print("�ӷ����㣬Դ����1��", d1);
	matrix_print("�ӷ����㣬Դ����2��", d2);
	matrix_addition(d_add, d1, d2);	//��d1��d2�ĺͷ���d_add�У��˹���֤������������һ��
	matrix_print("�ӷ����㣬�;��� ��", d_add);
	cout << sp << endl;
	matrix_print("�˷����㣬Դ����1��", d1);
	matrix_print("�˷����㣬Դ����2��", f3);
	matrix_multiplication(i_mul, d1, f3);	//��t1��t2�ĺͷ���t_add�У��˹���֤������������һ��
	matrix_print("�˷����㣬������ ��", i_mul);
	cout << sp << endl;

	return 0;
}