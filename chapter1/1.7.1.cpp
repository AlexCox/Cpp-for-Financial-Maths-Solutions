#include <iostream>
#include <cmath>
using namespace std;

int main() {
	double revenue;
	double costs;
	double taxRate;

	cout << "Enter revenue:\n";
	cin >> revenue;

	cout << "Enter costs:\n";
	cin >> costs;

	cout << "Enter the tax rate (%):\n";
	cin >> taxRate;

	double grossProfit = revenue - costs;
	double netProfit = 0;

	if (grossProfit > 0) {
		netProfit = grossProfit * (1 - taxRate / 100);
	}

	cout << "The net profit is\n";
	cout << netProfit;

	return 0;
}