#ifndef COMPLEX_VECTOR_H
#define COMPLEX_VECTOR_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <cstdlib>
class Complex {
private:
    double real;
    double imag;
public:
    Complex(double r = 0, double i = 0);
    double getReal() const;
    double getImag() const;
    double getMod() const;
    bool operator==(const Complex& other) const;
    bool operator<(const Complex& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Complex& c);
};
class ComplexVector {
private:
    std::vector<Complex> data;
public:
    ComplexVector(int n = 0);
    void shuffle();
    int find(const Complex& target) const;
    void insert(int pos, const Complex& c);
    void remove(int pos);
    void bubbleSort();
    void mergeSort();
    ComplexVector rangeSearch(double m1, double m2) const;
    void display() const;
    void reverse();
    const std::vector<Complex>& getData() const { return data; }
private:
    void mergeSortHelper(int left, int right);
};
void testComplexVector();

#endif
