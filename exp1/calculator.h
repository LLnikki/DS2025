#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include <stack>
#include <map>
class Calculator {
private:
    std::map<char, int> priority;
    bool isOperator(char c);
    int getPriority(char op);
    double calculate(double a, double b, char op);
    std::string infixToPostfix(const std::string& infix);
public:
    Calculator();
    double evaluate(const std::string& expression);
};
void testCalculator();
#endif
