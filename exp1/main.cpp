#include <iostream>
#include "complex_vector.h"
#include "calculator.h"
#include "largest_rectangle.h"
using namespace std;
int main() {
    int choice;
    do {
        cout << "\n��������ѡ��ʵ��:\n";
        cout << "1. ������������������\n";
        cout << "2. �ַ���������\n";
        cout << "3. ���������\n";
        cout << "4. �������в���\n";
        cout << "0. �˳�\n";
        cout << "������ѡ��: ";
        cin >> choice;
        switch(choice) {
            case 1:
                testComplexVector();
                break;
            case 2:
                testCalculator();
                break;
            case 3:
                testLargestRectangle();
                break;
            case 4:
                testComplexVector();
                testCalculator();
                testLargestRectangle();
                break;
            case 0:
                cout << "�������\n";
                break;
            default:
                cout << "��Чѡ������������\n";
        }
    } while (choice != 0);
    cout << "\n�����������...";
    cin.get();
    cin.get();
    return 0;
}
