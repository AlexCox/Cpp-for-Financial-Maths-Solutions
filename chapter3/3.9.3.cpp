#include <iostream>
#include <cmath>
using namespace std;

int Fibonacci(int n) {
	if (n <= 1)
		return n;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
	cout << "Outputting the first 20 Fibonacci numbers" << endl;
	for (int i = 0; i < 20; i++) {
		cout << "F_" << i << " = " << Fibonacci(i) << endl;;
	}

	return 0;
}