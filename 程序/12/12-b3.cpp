/* 2352018 ������ ���� */
#include <iostream>
using namespace std;

int main() {
    const char* month[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
    float monthNumber;
    cout << "�������·�(1-12)" << endl;
    cin >> monthNumber;
    if (cin.fail() || monthNumber < 1 || monthNumber > 12)
        cout << "Invalid" << endl;
    else 
        cout << *(month + int(monthNumber) - 1) << endl;
    return 0;
}