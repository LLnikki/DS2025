#include "largest_rectangle.h"
#include <iostream>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
int largestRectangleArea(vector<int>& heights) {
    int n = heights.size();
    vector<int> left(n), right(n);
    stack<int> mono_stack;
    // ������߽�
    for (int i = 0; i < n; ++i) {
        while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
            mono_stack.pop();
        }
        left[i] = mono_stack.empty() ? -1 : mono_stack.top();
        mono_stack.push(i);
    }
    
    // ���ջ
    while (!mono_stack.empty()) mono_stack.pop();
    // �����ұ߽�
    for (int i = n - 1; i >= 0; --i) {
        while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
            mono_stack.pop();
        }
        right[i] = mono_stack.empty() ? n : mono_stack.top();
        mono_stack.push(i);
    }
    int maxArea = 0;
    for (int i = 0; i < n; ++i) {
        maxArea = max(maxArea, heights[i] * (right[i] - left[i] - 1));
    }
    return maxArea;
}
void generateTestData() {
    srand(time(NULL));  // ��ʼ�����������   
    for (int test = 1; test <= 10; ++test) {
        int n = rand() % 20 + 1;  // 1 �� 20 ��Ԫ��
        vector<int> heights;
        for (int i = 0; i < n; ++i) {
            heights.push_back(rand() % 51);  // 0 �� 50 �ĸ߶�
        }
        int area = largestRectangleArea(heights);
        cout << "���� " << test << ":\n";
        cout << "����: [";
        for (int i = 0; i < n; ++i) {
            cout << heights[i];
            if (i < n - 1) cout << ", ";
        }
        cout << "]\n";
        cout << "���: " << area << "\n\n";
    }
}
void testLargestRectangle() {
    cout << "�������������\n";
    vector<int> heights1;
    heights1.push_back(2);
    heights1.push_back(1);
    heights1.push_back(5);
    heights1.push_back(6);
    heights1.push_back(2);
    heights1.push_back(3);
    vector<int> heights2;
    heights2.push_back(2);
    heights2.push_back(4);
    cout << "ʾ��1 [2,1,5,6,2,3]: " << largestRectangleArea(heights1);
    cout << " (����: 10)" << endl;
    cout << "ʾ��2 [2,4]: " << largestRectangleArea(heights2);
    cout << " (����: 4)" << endl;
    cout << "\nʹ�������������\n";
    generateTestData();
}
