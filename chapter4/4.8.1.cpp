#include <iostream>
#include <cmath>
using namespace std;

int factorialWhile(int n) {
	if (n <= 1) {
		return 1;
	}
	int result = n;
	while (n > 2) {
		result *= (--n);
	}
	return result;
}

int factorialFor(int n) {
	if (n <= 1) {
		return 1;
	}
	int result = n;
	for (int i = 2; i < n; i++) {
		result *= i;
	}
	return result;
}

int factorialDoWhile(int n) {
	if (n <= 1) {
		return 1;
	}
	int result = n;
	do {
		result *= (--n);
	} while (n > 2);
	return result;
}

int main() {
	// Testing factorial of 1 through 10
	cout << "n | factorialWhile | factorialFor | factorialDoWhile" << endl;
	for (int i = 1; i < 11; i++) {
		cout << i << " | " << factorialWhile(i) << " | " << factorialFor(i) << " | " << factorialDoWhile(i) << endl;
	}
	return 0;
}