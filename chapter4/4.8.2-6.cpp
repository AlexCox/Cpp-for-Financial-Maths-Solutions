#include <iostream>
#include <cmath>
#include <stdexcept>
using namespace std;

const double root2pi = sqrt(2.0 * 3.14159265359);

// Constants for Moro algorithm 
const double a0 = 2.50662823884;
const double a1 = -18.61500062529;
const double a2 = 41.39119773534;
const double a3 = -25.44106049637;
const double b1 = -8.47351093090;
const double b2 = 23.08336743743;
const double b3 = -21.06224101826;
const double b4 = 3.13082909833;
const double c0 = 0.3374754822726147;
const double c1 = 0.9761690190917186;
const double c2 = 0.1607979714918209;
const double c3 = 0.0276438810333863;
const double c4 = 0.0038405729373609;
const double c5 = 0.0003951896511919;
const double c6 = 0.0000321767881768;
const double c7 = 0.0000002888167364;
const double c8 = 0.0000003960315187;

double hornerFunction(double x, double a) {
	return a;
}

double hornerFunction(double x, double a, double b) {
	return a + x * hornerFunction(x, b);
}

double hornerFunction(double x, double a, double b, double c) {
	return a + x * hornerFunction(x, b, c);
}

double hornerFunction(double x, double a, double b, double c, double d) {
	return a + x * hornerFunction(x, b, c, d);
}

double hornerFunction(double x, double a, double b, double c, double d, double e) {
	return a + x * hornerFunction(x, b, c, d, e);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f) {
	return a + x * hornerFunction(x, b, c, d, e, f);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g) {
	return a + x * hornerFunction(x, b, c, d, e, f, g);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g,
	double h) {
	return a + x * hornerFunction(x, b, c, d, e, f, g, h);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g,
	double h, double i) {
	return a + x * hornerFunction(x, b, c, d, e, f, g, h, i);
}

double integrateSin(double a, double b, int N = 1000) {
	double result = 0.0;
	double h = (b - a) / N;
	for (int i = 0; i < N; i++) {
		result += sin(a + h * (i + 0.5));
	}
	return result * h;
}

double integrateExp(double x, int N = 1000) {
	double result = 0.0;
	double arg;
	for (int i = 0; i < N; i++) {
		arg = (i + 0.5) / N;
		result += (1 / (arg * arg)) * exp(-0.5 * pow(x + 1 - 1 / arg, 2));
	}
	return result / N;
}

int Fibonacci(int n) {
	if (n < 2) {
		return n;
	}
	int a0 = 0;
	int a1 = 1;
	int result = 0;
	for (int i = 0; i < n-1; i++) {
		result = a0 + a1;
		a0 = a1;
		a1 = result;
	}
	return result;
}

double normcdf(double x) {
	if (x < 0) {
		return 1.0 - normcdf(-x);
	}
	double k = 1 / (1 + 0.2316419 * x);
	return 1.0 - (1.0 / root2pi) * exp(-0.5 * x * x) *
		hornerFunction(k, 0, 0.319381530, -0.356563782, 1.781477937,
			-1.821255978, 1.330274429);
}

double norminv(double x, bool error = true) {
	if (error && (x < 0.0 || x > 1.0)) {
		throw logic_error("Argument out of bounds. norminv only takes real numbers between 0 and 1 inclusive.");
	}
	double y = x - 0.5;
	if (abs(y) < 0.42) {
		double r = y * y;
		return y * hornerFunction(r, a0, a1, a2, a3) /
			hornerFunction(r, 1.0, b1, b2, b3, b4);
	}
	else {
		double r = (y > 0) ? 1.0 - x : x;
		double s = log(-log(r));
		double t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
		return (x > 0.5) ? t : -t;
	}
}

int main() {
	cout << "Integrating sin(x) from x = 0 to x = pi" << endl;
	cout << "Expected: 2, Actual: " << integrateSin(0, 3.14159) << endl;

	cout << "Integrating the infinite integral from -infty to 1.96" << endl;
	cout << "Expected: " << 0.975 * sqrt(2 * 3.14159) << ", Actual: " << integrateExp(1.96) << endl;

	cout << "Testing Fibonacci numbers F_0 through F_15" << endl;
	for (int i = 0; i < 16; i++) {
		cout << Fibonacci(i) << " ";
	}
	cout << endl;

	cout << "Testing norminv with out of bound value: " << norminv(1.2);
	// Application terminates from the logic_error
	return 0;
}