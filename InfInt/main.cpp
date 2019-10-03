#include "inf_int.h"
#include <iostream>
using namespace std;

int main() {
    inf_int a = -1234567890;
    inf_int b = "-1234567890";
    inf_int c(-1234567890);
    inf_int d("-1234567890");
    inf_int e(c);
    inf_int f = d;
    inf_int g; g = c;
    inf_int h; h = h - "1234567890";
    inf_int i; i = i - 1234567890;
    inf_int j; j = "-1234567890" + j;
    inf_int k; k = -1234567890 + k;
    inf_int l; l = l + "-1234567890";
    inf_int m; m = m + (-1234567890);
    inf_int n = 0; n = n - 1234567890;
    inf_int o = "0"; o = o - "1234567890";
    inf_int p = "1"; p = p * (-1234567890) + "0" - 0;
    inf_int q = 1234567890; q = q * "-1" - "-99999999" - 99999999;
    inf_int r((inf_int(111111111) * 10 + 123456780) * -1);
    inf_int s = -617283945 * inf_int(2) + "99999999" + (-99999999);
    inf_int t = inf_int(-1) + inf_int(-1234567889);
    inf_int u = inf_int(10) - inf_int(1234567900);
    inf_int v = inf_int(10) * inf_int(-123456789);


    cout << "[Constructor & Calculation Test. Every number must be -1234567890]" << endl;
    cout << "A = " << a << endl;
    cout << "B = " << b << endl;
    cout << "C = " << c << endl;
    cout << "D = " << d << endl;
    cout << "E = " << e << endl;
    cout << "F = " << f << endl;
    cout << "G = " << g << endl;
    cout << "H = " << h << endl;
    cout << "I = " << i << endl;
    cout << "J = " << j << endl;
    cout << "K = " << k << endl;
    cout << "L = " << l << endl;
    cout << "M = " << m << endl;
    cout << "N = " << n << endl;
    cout << "O = " << o << endl;
    cout << "P = " << p << endl;
    cout << "Q = " << q << endl;
    cout << "R = " << r << endl;
    cout << "S = " << s << endl;
    cout << "T = " << t << endl;
    cout << "U = " << u << endl;
    cout << "V = " << v << endl << endl;

    cout << "[Custom Input Test]" << endl;
    cout << "Input A, B : ";
    cin >> a >> b;

    cout << endl;
    cout << "A = " << a << endl;
    cout << "B = " << b << endl;
    cout << "A+B = " << a + b << endl;
    cout << "A-B = " << a - b << endl;
    cout << "A*B = " << a * b << endl;
    cout << "(A==B) = " << (a == b ? "true" : "false") << endl;
    cout << "(A!=B) = " << (a != b ? "true" : "false") << endl;
    cout << "(A<B) = " << (a < b ? "true" : "false") << endl;
    cout << "(A>B) = " << (a > b ? "true" : "false") << endl;

    return 0;
}
