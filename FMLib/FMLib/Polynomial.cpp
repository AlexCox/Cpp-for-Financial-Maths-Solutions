#include "Polynomial.h"

Polynomial::Polynomial() : coefficients(std::vector<double>{0}) {
}

Polynomial::Polynomial(std::vector<double> c) :
	coefficients(c) {
}

Polynomial::Polynomial(double c) :
	coefficients(std::vector<double>{c}) {
}

double Polynomial::evaluate(double x) const {
	size_t N = coefficients.size();
	double total = coefficients[0];
	for (int i = 1; i < N; i++) {
		total += coefficients[i] * pow(x, i);
	}
	return total;
}

void Polynomial::add(Polynomial& p) {
	size_t n = coefficients.size();
	size_t N = p.coefficients.size();

	for (int i = 0; i < N; i++) {
		if (i >= n) {
			coefficients.push_back(p.coefficients[i]);
		}
		else {
			coefficients[i] += p.coefficients[i];
		}
	}
}

static void testEvaluate() {
	std::vector<double> coefficients{ 1, 2.5, 7 }; // 7x^2 + 5x/2 + 1
	Polynomial p(coefficients);
	double result = p.evaluate(5);
	ASSERT_APPROX_EQUAL(188.5, result, 0.001);
}

static void testAdd() {
	std::vector<double> c1{ 1, 2.5, 7 }; // 7x^2 + 5x/2 + 1
	std::vector<double> c2{ 4.2, 2.5, 3, 1 }; // x^3 + 3x^2 + 5x/2 + 4.2
	double result;
	/*
		Test adding a larger polynomial to a smaller one
	*/
	Polynomial p1(c1);
	Polynomial p2(c2);
	p1.add(p2); // x^3 + 10x^2 + 5x + 5.2
	result = p1.evaluate(3);
	ASSERT_APPROX_EQUAL(137.2, result, 0.001);

	/*
		Test adding a smaller polynomial to a larger one
	*/
	Polynomial p3(c1);
	p1.add(p3); // x^3 + 17x^2 + 15x/2 + 6.2
	result = p1.evaluate(-0.5);
	ASSERT_APPROX_EQUAL(6.575, result, 0.001);
}

void testPolynomial() {
	TEST(testEvaluate);
	TEST(testAdd);
}