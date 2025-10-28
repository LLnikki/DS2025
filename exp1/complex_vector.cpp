#include "complex_vector.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
// Complex ��ʵ��
Complex::Complex(double r, double i) : real(r), imag(i) {}
double Complex::getReal() const { return real; }
double Complex::getImag() const { return imag; }
double Complex::getMod() const { return sqrt(real * real + imag * imag); }
bool Complex::operator==(const Complex& other) const {
    return real == other.real && imag == other.imag;
}
bool Complex::operator<(const Complex& other) const {
    double mod1 = getMod();
    double mod2 = other.getMod();
    if (fabs(mod1 - mod2) < 1e-9) {
        return real < other.real;
    }
    return mod1 < mod2;
}
ostream& operator<<(ostream& os, const Complex& c) {
    os << "(" << c.real << " + " << c.imag << "i)";
    return os;
}
// ComplexVector ��ʵ��
ComplexVector::ComplexVector(int n) {
    if (n > 0) {
        srand(time(NULL));  // ��ʼ�����������
        for (int i = 0; i < n; ++i) {
            // ���� -10.0 �� 10.0 �������
            double real = (rand() % 2000 - 1000) / 100.0;
            double imag = (rand() % 2000 - 1000) / 100.0;
            data.push_back(Complex(real, imag));
        }
    }
}
void ComplexVector::shuffle() {
    srand(time(NULL));  // ���³�ʼ�����������
    for (size_t i = data.size() - 1; i > 0; --i) {
        size_t j = rand() % (i + 1);  // ���� 0 �� i ���������
        // ����Ԫ��
        Complex temp = data[i];
        data[i] = data[j];
        data[j] = temp;
    }
}
int ComplexVector::find(const Complex& target) const {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i] == target) {
            return i;
        }
    }
    return -1;
}
void ComplexVector::insert(int pos, const Complex& c) {
    if (pos >= 0 && pos <= static_cast<int>(data.size())) {
        data.insert(data.begin() + pos, c);
    }
}
void ComplexVector::remove(int pos) {
    if (pos >= 0 && pos < static_cast<int>(data.size())) {
        data.erase(data.begin() + pos);
    }
}
void ComplexVector::bubbleSort() {
    int n = data.size();
    for (int i = 0; i < n - 1; ++i) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; ++j) {
            if (!(data[j] < data[j + 1])) {
                swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}
void ComplexVector::mergeSortHelper(int left, int right) {
    if (left >= right) return;   
    // ������ʱ����
    vector<Complex> temp(data.size());
    int mid = left + (right - left) / 2;
    mergeSortHelper(left, mid);
    mergeSortHelper(mid + 1, right);
    // �ϲ�������������
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right) {
        if (data[i] < data[j]) {
            temp[k] = data[i];
            i++;
        } else {
            temp[k] = data[j];
            j++;
        }
        k++;
    }
    // ����ʣ��Ԫ��
    while (i <= mid) {
        temp[k] = data[i];
        i++;
        k++;
    }
    while (j <= right) {
        temp[k] = data[j];
        j++;
        k++;
    }
    // ������ԭ����
    for (int idx = left; idx <= right; ++idx) {
        data[idx] = temp[idx];
    }
}
void ComplexVector::mergeSort() {
    if (data.empty()) return;
    mergeSortHelper(0, data.size() - 1);
}
ComplexVector ComplexVector::rangeSearch(double m1, double m2) const {
    ComplexVector result;
    for (size_t i = 0; i < data.size(); ++i) {
        double mod = data[i].getMod();
        if (mod >= m1 && mod <= m2) {
            result.data.push_back(data[i]);
        }
    }
    for (size_t i = 0; i < result.data.size(); ++i) {
        for (size_t j = i + 1; j < result.data.size(); ++j) {
            if (!(result.data[i] < result.data[j])) {
                swap(result.data[i], result.data[j]);
            }
        }
    }
    return result;
}
void ComplexVector::display() const {
    for (size_t i = 0; i < data.size(); ++i) {
        cout << data[i] << " ";
    }
    cout << endl;
}
void ComplexVector::reverse() {
    for (size_t i = 0; i < data.size() / 2; ++i) {
        swap(data[i], data[data.size() - 1 - i]);
    }
}
// ���Ժ���
void testComplexVector() {
    cout << "����������Ը�������\n";    
    // ��������10������������
    ComplexVector vec(10);
    cout << "ԭʼ����: ";
    vec.display();   
    // ��������
    cout << "\n���Һ�: ";
    vec.shuffle();
    vec.display();
    // ���Բ���
    if (!vec.getData().empty()) {
        Complex target = vec.getData()[0];
        int pos = vec.find(target);
        cout << "\n���� " << target << " ��λ��: " << pos << endl;
    }
    // ���Բ���
    cout << "\n��λ��2���� (0+0i): ";
    vec.insert(2, Complex(0, 0));
    vec.display();
    // ����ɾ��
    cout << "\nɾ��λ��2��Ԫ��: ";
    vec.remove(2);
    vec.display();
    // ��������
    cout << "\nð�������: ";
    vec.bubbleSort();
    vec.display();
    // �����������
    cout << "\n������� [3.0, 7.0]: ";
    ComplexVector result = vec.rangeSearch(3.0, 7.0);
    result.display();
    // ���ܲ���
    cout << "\n���ܲ���\n";
    ComplexVector perfVec(100);  // ������������̫��
    clock_t start = clock();
    perfVec.bubbleSort();
    clock_t end = clock();
    cout << "ð������100��Ԫ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
    perfVec.shuffle();
    start = clock();
    perfVec.mergeSort();
    end = clock();
    cout << "�鲢����100��Ԫ��: " << (double)(end - start) / CLOCKS_PER_SEC << "s\n";
}
