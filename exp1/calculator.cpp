#include "calculator.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <cstdlib> 
using namespace std;
Calculator::Calculator() {
    priority['+'] = 1;
    priority['-'] = 1;
    priority['*'] = 2;
    priority['/'] = 2;
    priority['^'] = 3;
    priority['('] = 0;
    priority[')'] = 0;
}
bool Calculator::isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}
int Calculator::getPriority(char op) {
    return priority[op];
}
double Calculator::calculate(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) throw runtime_error("除零错误");
            return a / b;
        case '^': return pow(a, b);
        default: throw runtime_error("未知运算符");
    }
}
string Calculator::infixToPostfix(const string& infix) {
    stack<char> opStack;
    string postfix;
    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;   
        if (isdigit(c) || c == '.') {
            postfix += c;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix += ' ';
                postfix += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        } else if (isOperator(c)) {
            postfix += ' ';
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(c)) {
                postfix += opStack.top();
                postfix += ' ';
                opStack.pop();
            }
            opStack.push(c);
        }
    }
    while (!opStack.empty()) {
        postfix += ' ';
        postfix += opStack.top();
        opStack.pop();
    }
    return postfix;
}
double stringToDouble(const string& str) {
    double result = 0.0;
    double fraction = 1.0;
    bool negative = false;
    bool decimal = false;   
    size_t start = 0;
    if (str[0] == '-') {
        negative = true;
        start = 1;
    }
    for (size_t i = start; i < str.length(); ++i) {
        if (str[i] == '.') {
            decimal = true;
            continue;
        }   
        if (decimal) {
            fraction *= 0.1;
            result += (str[i] - '0') * fraction;
        } else {
            result = result * 10 + (str[i] - '0');
        }
    }   
    return negative ? -result : result;
}
double Calculator::evaluate(const string& expression) {
    string postfix = infixToPostfix(expression);
    stack<double> numStack;
    istringstream iss(postfix);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            numStack.push(stringToDouble(token));
        } else if (isOperator(token[0])) {
            if (numStack.size() < 2) {
                throw runtime_error("表达式无效");
            }
            double b = numStack.top(); numStack.pop();
            double a = numStack.top(); numStack.pop();
            double result = calculate(a, b, token[0]);
            numStack.push(result);
        }
    }
    if (numStack.size() != 1) {
        throw runtime_error("表达式无效");
    }
    return numStack.top();
}
void testCalculator() {
    cout << "测试字符串计算器\n";
    Calculator calc;
    struct TestCase {
        const char* expression;
        double expected;
    };
    TestCase testCases[] = {
        {"2 + 3", 5},
        {"10 - 4", 6},
        {"3 * 5", 15},
        {"20 / 4", 5},
        {"2 + 3 * 4", 14}
    };
    int testCount = sizeof(testCases) / sizeof(testCases[0]);
    cout << "预定义测试案例:\n";
    for (int i = 0; i < testCount; ++i) {
        try {
            double result = calc.evaluate(testCases[i].expression);
            cout << testCases[i].expression << " = " << result<<endl;
        } 
		catch (const exception& e) {
            cout << testCases[i].expression << " = 错误: " << e.what() << endl;
        }
    }
    // 用户输入交互部分
    cout << "\n用户输入模式\n";
    cout << "输入数学表达式进行计算\n";
    cout << "支持运算符: + - * / ^ ( )\n";
    cout << "输入0 结束计算\n";
    cout <<"请输入表达式:\n";
    string userInput;
    while (true) {
        if (!getline(cin, userInput)) break;
        if (userInput == "0") {
            cout << "退出计算器\n";
            break;
        }
        if (userInput.empty()) {
            continue;  // 静默处理空输入，不显示错误信息
        }
        try {
            double result = calc.evaluate(userInput);
            cout << "计算结果: " << userInput << " = " << result << endl;
        } catch (const exception& e) {
            cout << "表达式无效: " << e.what() << endl;
        }
    }
}
