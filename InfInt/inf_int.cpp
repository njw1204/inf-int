// 20181401 나종우
#define _CRT_SECURE_NO_WARNINGS
#include "inf_int.h"
#include <iostream>
#include <string>
#include <cstring>
using namespace std;

inf_int::inf_int() {
    // 기본값으로 0 할당
    this->length = 1;
    this->digits = new char[this->length + 1];
    this->digits[0] = '0';
    this->digits[1] = '\0';
    this->thesign = true;
}

inf_int::inf_int(int n) {
    // 부호 처리 및 절댓값으로 변환
    if (n >= 0) {
        this->thesign = true;
    }
    else {
        this->thesign = false;
        n = -n;
    }

    // n의 자리수 세기
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

    // n을 문자열로 변환해 저장 (규칙에 맞게 거꾸로 저장)
    for (int i = 0; i < this->length; i++) {
        this->digits[i] = n % 10 + '0';
        n /= 10;
    }
    this->digits[this->length] = '\0';
}

inf_int::inf_int(const char* str) {
    // 부호 처리
    if (str[0] == '-') {
        this->thesign = false;
        str++; // 부호 스킵
    }
    else if (str[0] == '+') {
        this->thesign = true;
        str++; // 부호 스킵
    }
    else {
        this->thesign = true;
    }

    this->length = strlen(str);
    this->digits = new char[this->length + 1];

    // 문자열을 규칙에 맞게 거꾸로 복사
    for (int i = 0; i < this->length; i++) {
        this->digits[i] = str[this->length - i - 1];
    }
    this->digits[this->length] = '\0';

    // 0일경우 부호는 무조건 플러스로 설정
    if (this->isZero()) {
        this->thesign = true;
    }
}

inf_int::inf_int(const inf_int& copy) {
    // 깊은 복사
    this->digits = new char[copy.length + 1];
    this->length = copy.length;
    this->thesign = copy.thesign;
    strcpy(this->digits, copy.digits);
}

inf_int::~inf_int() {
    // 동적 할당 해제
    delete[] this->digits;
}

// digits 메모리의 크기를 변경한다. (반환값 : 성공 여부)
bool inf_int::resize(int size) {
    if (size <= this->length) {
        return false;
    }

    // 새롭게 동적할당하고 기존의 데이터를 복사해옴
    char* newDigits = new char[size];
    strcpy(newDigits, this->digits);
    delete[] this->digits;
    this->digits = newDigits;
    return true;
}

// 절댓값을 인자와 비교한다. (양수 : 내가 더 클때, 음수 : 내가 더 작을때, 0 : 같을 때)
int inf_int::compareAbsoluteDigits(const inf_int& compare) const {
    // 길이가 긴 수가 절댓값이 크다.
    if (this->length != compare.length) {
        return (this->length - compare.length);
    }

    // 길이가 같은 경우에는 큰 자리의 숫자부터 작은 자리의 숫자까지 차례대로 비교한다.
    for (int i = this->length - 1; i >= 0; i--) {
        if (this->digits[i] != compare.digits[i]) {
            return (this->digits[i] - compare.digits[i]);
        }
    }

    // 모든 자리의 숫자가 동일하다면 절댓값이 같은 경우이다.
    return 0;
}

// 저장된 값이 0인지 판별
bool inf_int::isZero() const {
    return (strcmp(this->digits, "0") == 0);
}

// 저장된 값에 10을 mulCount번 곱한다.
void inf_int::mul10(int mulCount) {
    if (!this->isZero()) {
        // '0'을 넣을 메모리 공간 마련
        this->resize(this->length + mulCount + 1);
        memmove(this->digits + mulCount, this->digits, this->length);

        // 10을 곱하는 횟수만큼 '0'을 붙이면 됨
        for (int i = 0; i < mulCount; i++) {
            this->digits[i] = '0';
        }
        this->length += mulCount;
        this->digits[this->length] = '\0';
    }
}

inf_int& inf_int::operator=(const inf_int& copy) {
    // 기존의 동적할당한 메모리는 해제
    if (this->digits) {
        delete[] this->digits;
    }

    // copy의 데이터를 현재 객체로 복사
    this->digits = new char[copy.length + 1];
    this->length = copy.length;
    this->thesign = copy.thesign;
    strcpy(this->digits, copy.digits);

    return *this;
}

bool operator==(const inf_int& a, const inf_int& b) {
    // 부호가 일치하고 절댓값도 일치해야함
    return (a.thesign == b.thesign) && (a.compareAbsoluteDigits(b) == 0);
}

bool operator!=(const inf_int& a, const inf_int& b) {
    return !operator==(a, b);
}

bool operator>(const inf_int& a, const inf_int& b) {
    if (a.thesign != b.thesign) {
        // 부호가 다르다면 양수인 것이 더 큰 것이다.
        // a의 부호진리값이 곧 비교 결과와 같게 된다.
        return a.thesign;
    }
    else {
        int absCmp = a.compareAbsoluteDigits(b); // a의 절댓값이 크면 양수, b의 절댓값이 크면 음수, 같으면 0
        if (a.thesign == true) {
            // 둘 다 양수라면 절댓값이 큰 것이 큰 수이다.
            return (absCmp > 0); // a의 절댓값이 크면 true
        }
        else {
            // 둘 다 음수라면 절댓값이 작은 것이 큰 수이다.
            return (absCmp < 0); // b의 절댓값이 크면 true
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

    // 좌항이 우항보다 절댓값이 작다면 서로 바꿈 (좌항의 절댓값이 더 크게 만들어야 덧셈이 쉽다)
    if (left.compareAbsoluteDigits(right) < 0) {
        inf_int temp = left;
        left = right;
        right = temp;
    }

    if (right.isZero()) {
        return left;
    }

    // 좌항과 우항의 부호가 같을때 실제로 덧셈 처리를 시행한다.
    if (left.thesign == right.thesign) {
        int carry = 0; // 올림값

        for (int i = 0; i < left.length; i++) {
            // 한자리씩 숫자끼리 더한다.
            int sum = left.digits[i] - '0' + carry;
            if (i < right.length) {
                sum += right.digits[i] - '0';
            }

            // 숫자끼리 더한게 10을 넘어가면 윗 자리로 하나 올려준다. (올림값 전달)
            if (sum >= 10) {
                sum -= 10;
                carry = 1;
            }
            else {
                carry = 0;
            }

            // 현재 자리의 연산 결과를 저장한다.
            left.digits[i] = sum + '0';
        }

        if (carry) {
            // 최종적으로 자리 올림이 발생하면 추가 자리수가 필요하므로 동적 할당을 다시 한다.
            left.length++;
            left.resize(left.length + 1);
            left.digits[left.length - 1] = '1';
            left.digits[left.length] = '\0';
        }

        // 만약 연산결과가 0이라면 무조건 플러스 부호 처리를 한다.
        if (left.isZero()) {
            left.thesign = true;
        }

        return left;
    }
    else {
        // 부호가 다른 경우 우항의 부호를 반전하고 뺄셈으로 처리한다.
        // a+b = a-(-b) 성질 이용
        right.thesign = !right.thesign;
        return left - right;
    }
}

inf_int operator-(const inf_int& a, const inf_int& b) {
    inf_int left = a, right = b;

    if (left.thesign != right.thesign) {
        // 부호가 다른 경우 우항의 부호를 반전하고 덧셈으로 처리한다.
        // a-b = a+(-b) 성질 이용
        right.thesign = !right.thesign;
        return left + right;
    }

    if (left.thesign == false && right.thesign == false) {
        // 부호가 둘 다 음수이면 둘 다 부호를 반전하고 빼는 순서를 뒤바꾼다.
        // a-b = (-b)-(-a) 성질 이용
        left.thesign = !left.thesign;
        right.thesign = !right.thesign;
        return right - left;
    }

    // 좌항과 우항이 모두 양수일 때 아래의 과정들이 시행된다.
    // 그 이외의 경우들은 위에서 모두 처리되었다.

    // 좌항과 우항 절댓값 비교 (좌항의 절댓값이 더 크게 만들어야 뺄셈이 쉽다)
    int absCmp = left.compareAbsoluteDigits(right);
    if (absCmp < 0) {
        // 좌항의 절댓값이 더 작은 경우
        // 좌항과 우항을 서로 바꾼다.
        // 최종 뺄셈 결과는 음수가 될 것이므로 부호 플래그를 false로 설정한다.
        // 뒤에 있을 뺄셈 연산 과정이 절댓값 기준으로 이루어지므로 이렇게 하면 맞는 결과가 나온다.
        inf_int temp = left;
        left = right;
        right = temp;
        left.thesign = false;
    }
    else if (absCmp == 0) {
        // 절댓값이 같은 경우
        // 앞에서 좌항과 우항이 모두 양수인 것은 알았으므로 뺄셈 결과는 0이 된다.
        return inf_int(0);
    }

    if (right.isZero()) {
        return left;
    }

    int carry = 0; // 내림값

    for (int i = 0; i < left.length; i++) {
        // 한자리씩 숫자끼리 뺀다.
        int sum = left.digits[i] - '0' + carry;
        if (i < right.length) {
            sum -= right.digits[i] - '0';
        }

        // 숫자끼리 뺀게 음수이면 윗 자리에서 하나 가져온다. (내림값 전달)
        if (sum < 0) {
            sum += 10;
            carry = -1;
        }
        else {
            carry = 0;
        }

        // 현재 자리의 연산 결과를 저장한다.
        left.digits[i] = sum + '0';
    }

    // 뺄셈 결과에는 쓸모없는 0이 맨 앞에 붙어있을 수도 있다.
    // 아래 코드로 leading zero를 제거한다. (단, 연산 결과가 0일수도 있으니 일의 자리의 0은 제거하지 않음)
    for (int i = left.length - 1; i >= 1; i--) {
        if (left.digits[i] == '0') {
            left.digits[i] = '\0';
            left.length--;
        }
        else {
            break;
        }
    }

    // 만약 연산결과가 0이라면 무조건 플러스 부호 처리를 한다.
    if (left.isZero()) {
        left.thesign = true;
    }

    return left;
}

inf_int operator*(const inf_int& a, const inf_int& b) {
    inf_int left = a, right = b;

    // 하나라도 0이면 곱하면 0이다.
    if (left.isZero() || right.isZero()) {
        return inf_int(0);
    }

    // 부호가 같으면 곱셈 결과는 플러스, 다르면 곱셈 결과는 마이너스
    bool signFlag = true; // 부호 플래그
    if (left.thesign != right.thesign) {
        signFlag = false;
    }

    // 곱셈 결과의 부호를 판별했으면 좌항과 우항을 모두 양수로 가정하고 곱셈을 진행한다.
    left.thesign = true;
    right.thesign = true;

    // 좌항을 1번~9번 곱했을 때의 값을 미리 저장해둔다. (곱셈 연산 과정에서 활용)
    inf_int leftMultipliedBy[10];
    for (int i = 1; i < 10; i++) {
        leftMultipliedBy[i] = leftMultipliedBy[i - 1] + left;
    }

    inf_int result; // 최종 곱셈 결과를 저장하는 객체
    for (int i = 0; i < right.length; i++) {
        // 필산 하는 방식을 따라서 한자리씩 곱한다.
        if (right.digits[i] == '0') {
            continue;
        }

        inf_int temp = leftMultipliedBy[right.digits[i] - '0'];
        temp.mul10(i);
        result = result + temp;
    }

    // 곱셈 결과의 부호는 이전에 구했던 부호 플래그
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