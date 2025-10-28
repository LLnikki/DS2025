#include <iostream>
#include "complex_vector.h"
#include "calculator.h"
#include "largest_rectangle.h"
using namespace std;
int main() {
    int choice;
    do {
        cout << "\n输入数字选择实验:\n";
        cout << "1. 复数向量操作和排序\n";
        cout << "2. 字符串计算器\n";
        cout << "3. 最大矩形面积\n";
        cout << "4. 运行所有测试\n";
        cout << "0. 退出\n";
        cout << "请输入选择: ";
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
                cout << "程序结束\n";
                break;
            default:
                cout << "无效选择，请重新输入\n";
        }
    } while (choice != 0);
    cout << "\n按任意键继续...";
    cin.get();
    cin.get();
    return 0;
}
