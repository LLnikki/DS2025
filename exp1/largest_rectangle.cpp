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
    // 计算左边界
    for (int i = 0; i < n; ++i) {
        while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) {
            mono_stack.pop();
        }
        left[i] = mono_stack.empty() ? -1 : mono_stack.top();
        mono_stack.push(i);
    }
    
    // 清空栈
    while (!mono_stack.empty()) mono_stack.pop();
    // 计算右边界
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
    srand(time(NULL));  // 初始化随机数种子   
    for (int test = 1; test <= 10; ++test) {
        int n = rand() % 20 + 1;  // 1 到 20 个元素
        vector<int> heights;
        for (int i = 0; i < n; ++i) {
            heights.push_back(rand() % 51);  // 0 到 50 的高度
        }
        int area = largestRectangleArea(heights);
        cout << "测试 " << test << ":\n";
        cout << "输入: [";
        for (int i = 0; i < n; ++i) {
            cout << heights[i];
            if (i < n - 1) cout << ", ";
        }
        cout << "]\n";
        cout << "输出: " << area << "\n\n";
    }
}
void testLargestRectangle() {
    cout << "测试最大矩形面积\n";
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
    cout << "示例1 [2,1,5,6,2,3]: " << largestRectangleArea(heights1);
    cout << " (期望: 10)" << endl;
    cout << "示例2 [2,4]: " << largestRectangleArea(heights2);
    cout << " (期望: 4)" << endl;
    cout << "\n使用随机测试数据\n";
    generateTestData();
}
