#include <iostream>
using namespace std;

void recursiveIntegers(int a, int b) {
    cout << a << endl;
    if (a < b)
        recursiveIntegers(a + 1, b);
}

int main() {
    cout << "Integers from 3 to 7 inclusive" << endl;
    recursiveIntegers(3, 7);

    return 0;
}