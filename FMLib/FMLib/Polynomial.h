#pragma once

#include "stdafx.h"

class Polynomial {
public:
	Polynomial();
	Polynomial(std::vector<double> c);
	Polynomial(double c);

	std::vector<double> coefficients;
	double evaluate(double x) const;
	void add(Polynomial& p);

};

void testPolynomial();