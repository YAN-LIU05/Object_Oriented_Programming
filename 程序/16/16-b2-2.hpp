/* 2352018 ������ ���� */
#include <iostream>
#include <string>
using namespace std;

// ģ���� matrix
template <typename T, unsigned int ROW, unsigned int COL>
class matrix {
private:
    T value[ROW][COL]; // ���ڴ洢���������

public:
    // Ĭ�Ϲ��캯������ʼ��Ϊ T ��Ĭ��ֵ
    matrix() {
        for (unsigned int i = 0; i < ROW; ++i) {
            for (unsigned int j = 0; j < COL; ++j) {
                value[i][j] = T();
            }
        }
    }

    // ����ӷ�����������
    matrix operator+(const matrix& other) const {
        matrix result;
        for (unsigned int i = 0; i < ROW; ++i) {
            for (unsigned int j = 0; j < COL; ++j) {
                result.value[i][j] = value[i][j] + other.value[i][j];
            }
        }
        return result;
    }

    // ��ֵ����������
    matrix& operator=(const matrix& other) {
        if (this != &other) { // ��ֹ���Ҹ�ֵ
            for (unsigned int i = 0; i < ROW; ++i) {
                for (unsigned int j = 0; j < COL; ++j) {
                    value[i][j] = other.value[i][j];
                }
            }
        }
        return *this;
    }

    // �������������
    friend istream& operator>>(istream& in, matrix& m) {
        for (unsigned int i = 0; i < ROW; ++i) {
            for (unsigned int j = 0; j < COL; ++j) {
                in >> m.value[i][j];
            }
        }
        return in;
    }

    // ������������
    friend ostream& operator<<(ostream& out, const matrix& m) {
        for (unsigned int i = 0; i < ROW; ++i) {
            for (unsigned int j = 0; j < COL; ++j) {
                out << m.value[i][j] << " ";
            }
            out << endl;
        }
        return out;
    }
};
