// 20181401 ������

#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

inf_int::inf_int() {
    // �⺻������ 0 �Ҵ�
    this->length = 1;
    this->digits = new char[this->length + 1];
    this->digits[0] = '0';
    this->digits[1] = '\0';
    this->thesign = true;
}

inf_int::inf_int(int n) {
    // ��ȣ ó�� �� �������� ��ȯ
    if (n >= 0) {
        this->thesign = true;
    }
    else {
        this->thesign = false;
        n = -n;
    }

    // n�� �ڸ��� ����
    if (n == 0) {
        this->length = 1;
    }
    else {
        int tempN = n;
        this->length = 0;
        while (tempN) {
            tempN /= 10;
            this->length++;
        }
    }

    this->digits = new char[this->length + 1];

    // n�� ���ڿ��� ��ȯ�� ���� (��Ģ�� �°� �Ųٷ� ����)
    for (int i = 0; i < this->length; i++) {
        this->digits[i] = n % 10 + '0';
        n /= 10;
    }
    this->digits[this->length] = '\0';
}

inf_int::inf_int(const char* str) {
    // ��ȣ ó��
    if (str[0] == '-') {
        this->thesign = false;
        str++; // ��ȣ ��ŵ
    }
    else if (str[0] == '+') {
        this->thesign = true;
        str++; // ��ȣ ��ŵ
    }
    else {
        this->thesign = true;
    }

    this->length = strlen(str);
    this->digits = new char[this->length + 1];

    // ���ڿ��� ��Ģ�� �°� �Ųٷ� ����
    for (int i = 0; i < this->length; i++) {
        this->digits[i] = str[this->length - i - 1];
    }
    this->digits[this->length] = '\0';

    // 0�ϰ�� ��ȣ�� ������ �÷����� ����
    if (this->isZero()) {
        this->thesign = true;
    }
}

inf_int::inf_int(const inf_int& copy) {
    this->digits = new char[copy.length + 1];
    this->length = copy.length;
    this->thesign = copy.thesign;
    strcpy(this->digits, copy.digits);
}

inf_int::~inf_int() {
    delete[] this->digits;
}

// digits �޸��� ũ�⸦ �����Ѵ�. (��ȯ�� : ���� ����)
bool inf_int::resize(int size) {
    if (size <= this->length) {
        return false;
    }

    char* newDigits = new char[size];
    strcpy(newDigits, this->digits);
    delete[] this->digits;
    this->digits = newDigits;
    return true;
}

// ������ ���ڿ� ���Ѵ�. (��� : ���� �� Ŭ��, ���� : ���� �� ������, 0 : ���� ��)
int inf_int::compareAbsoluteDigits(const inf_int& compare) const {
    // ���̰� �� ���� ������ ũ��.
    if (this->length != compare.length) {
        return (this->length - compare.length);
    }

    // ���̰� ���� ��쿡�� ū �ڸ��� ���ں��� ���� �ڸ��� ���ڱ��� ���ʴ�� ���Ѵ�.
    for (int i = this->length - 1; i >= 0; i--) {
        if (this->digits[i] != compare.digits[i]) {
            return (this->digits[i] - compare.digits[i]);
        }
    }

    // ��� �ڸ��� ���ڰ� �����ϴٸ� ������ ���� ����̴�.
    return 0;
}

// ����� ���� 0���� �Ǻ�
bool inf_int::isZero() const {
    return (strcmp(this->digits, "0") == 0);
}

// ����� ���� 10�� mulCount�� ���Ѵ�.
void inf_int::mul10(int mulCount) {
    if (!this->isZero()) {
        this->resize(this->length + mulCount + 1);
        memmove(this->digits + mulCount, this->digits, this->length);
        for (int i = 0; i < mulCount; i++) {
            this->digits[i] = '0';
        }
        this->length += mulCount;
        this->digits[this->length] = '\0';
    }
}

inf_int& inf_int::operator=(const inf_int& copy) {
    // ������ �����Ҵ��� �޸𸮴� ����
    if (this->digits) {
        delete[] this->digits;
    }

    // copy�� �����͸� ���� ��ü�� ����
    this->digits = new char[copy.length + 1];
    this->length = copy.length;
    this->thesign = copy.thesign;
    strcpy(this->digits, copy.digits);

    return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
    // ��ȣ�� ��ġ�ϰ� ���񰪵� ��ġ�ؾ���
    return (a.thesign == b.thesign) && (a.compareAbsoluteDigits(b) == 0);
}

bool operator!=(const inf_int& a, const inf_int& b) {
    return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
    if (a.thesign != b.thesign) {
        // ��ȣ�� �ٸ��ٸ� ����� ���� �� ū ���̴�.
        // a�� ��ȣ�������� �� �� ����� ���� �ȴ�.
        return a.thesign;
    }
    else {
        int absCmp = a.compareAbsoluteDigits(b); // a�� ������ ũ�� ���, b�� ������ ũ�� ����, ������ 0
        if (a.thesign == true) {
            // �� �� ������ ������ ū ���� ū ���̴�.
            return (absCmp > 0); // a�� ������ ũ�� true
        }
        else {
            // �� �� ������� ������ ���� ���� ū ���̴�.
            return (absCmp < 0); // b�� ������ ũ�� true
        }
    }
}

bool operator<(const inf_int& a, const inf_int& b) {
    if (operator>(a, b) || operator==(a, b)) {
        return false;
    }
    else {
        return true;
    }
}

inf_int operator+(const inf_int& a, const inf_int& b) {
    inf_int left = a, right = b;

    if (left.compareAbsoluteDigits(right) < 0) {
        inf_int temp = left;
        left = right;
        right = temp;
    }

    if (right.isZero()) {
        return left;
    }

    if (left.thesign == right.thesign) {
        int carry = 0;

        for (int i = 0; i < left.length; i++) {
            int sum = left.digits[i] - '0' + carry;
            if (i < right.length) {
                sum += right.digits[i] - '0';
            }

            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            else {
                carry = 0;
            }
            left.digits[i] = sum + '0';
        }

        if (carry) {
            // ���������� �ڸ� �ø��� �߻��ϸ� �߰� �ڸ����� �ʿ��ϹǷ� ���� �Ҵ��� �ٽ� �Ѵ�.
            left.length++;
            left.resize(left.length + 1);
            left.digits[left.length - 1] = '1';
            left.digits[left.length] = '\0';
        }

        if (left.isZero()) {
            left.thesign = true;
        }

        return left;
    }
    else {
        // ��ȣ�� �ٸ� ��� ������ ��ȣ�� �����ϰ� �������� ó���Ѵ�.
        // a+b = a-(-b) ���� �̿�
        right.thesign = !right.thesign;
        return left - right;
    }
}

inf_int operator-(const inf_int& a, const inf_int& b) {
    inf_int left = a, right = b;

    if (left.thesign != right.thesign) {
        // ��ȣ�� �ٸ� ��� ������ ��ȣ�� �����ϰ� �������� ó���Ѵ�.
        // a-b = a+(-b) ���� �̿�
        right.thesign = !right.thesign;
        return left + right;
    }

    if (left.thesign == false && right.thesign == false) {
        // ��ȣ�� �� �� �����̸� �� �� ��ȣ�� �����ϰ� ���� ������ �ڹٲ۴�.
        // a-b = (-b)-(-a) ���� �̿�
        left.thesign = !left.thesign;
        right.thesign = !right.thesign;
        return right - left;
    }

    int absCmp = left.compareAbsoluteDigits(right);
    if (absCmp < 0) {
        inf_int temp = left;
        left = right;
        right = temp;
        left.thesign = false;
    }
    else if (absCmp > 0) {
        left.thesign = true;
    }
    else {
        return inf_int(0);
    }

    if (right.isZero()) {
        return left;
    }

    int carry = 0;
    for (int i = 0; i < left.length; i++) {
        int sum = left.digits[i] - '0' + carry;
        if (i < right.length) {
            sum -= right.digits[i] - '0';
        }

        if (sum < 0) {
            sum += 10;
            carry = -1;
        }
        else {
            carry = 0;
        }
        left.digits[i] = sum + '0';
    }

    // ���� ������� ������� 0�� �� �տ� �پ����� ���� �ִ�.
    // �Ʒ� �ڵ�� leading zero�� �����Ѵ�.
    for (int i = left.length - 1; i >= 1; i--) {
        if (left.digits[i] == '0') {
            left.digits[i] = '\0';
            left.length--;
        }
        else {
            break;
        }
    }

    if (left.isZero()) {
        left.thesign = true;
    }

    return left;
}

inf_int operator*(const inf_int& a, const inf_int& b) {
    inf_int left = a, right = b;

    if (left.isZero() || right.isZero()) {
        return inf_int(0);
    }

    bool signFlag = true;
    if (left.thesign != right.thesign) {
        signFlag = false;
    }
    left.thesign = true;
    right.thesign = true;

    inf_int leftMultipliedBy[10];
    for (int i = 1; i < 10; i++) {
        leftMultipliedBy[i] = leftMultipliedBy[i - 1] + left;
    }

    inf_int result;
    for (int i = 0; i < right.length; i++) {
        if (right.digits[i] == '0') {
            continue;
        }

        inf_int temp = leftMultipliedBy[right.digits[i] - '0'];
        temp.mul10(i);
        result = result + temp;
    }

    result.thesign = signFlag;
    return result;
}

ostream& operator<<(ostream& out, const inf_int& a) {
    if (a.thesign == false) {
        out << '-';
    }

    for (int i = a.length - 1; i >= 0; i--) {
        out << a.digits[i];
    }

    return out;
}

istream& operator>>(istream& in, inf_int& a) {
    string input;
    in >> input;
    a = input.c_str();
    return in;
}