#include <iostream>
using namespace std;

int recursiveSum(int n) {
    if (n == 1)
        return 1;
    return n + recursiveSum(n - 1);
}

int sum(int n) {
    return 0.5 * n * (n + 1);
}

int main() {
    cout << "n | recursiveSum(n) | sum(n)" << endl;
    for (int i = 1; i < 11; i++) {
        cout << i << " | " << recursiveSum(i) << " | " << sum(i) << endl;
    }
}