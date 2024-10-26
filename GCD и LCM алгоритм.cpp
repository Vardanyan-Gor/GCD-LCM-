#include <iostream>
using namespace std;

int GCD (int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}
int LCM (int x, int y) {
    return (x * y) / GCD(x, y);
}
int main() {
    int num1 = 48, num2 = 60;
    cout << "GCD: " << GCD(num1, num2) << endl;
    cout << "LCM: " << LCM(num1, num2) << endl;
    return 0;
}