#include "matlib.h"
#include "stdafx.h"

static const double root2pi = sqrt(2.0 * 3.14159265359);

/*
	Constants for Moro's algorithm
*/
static const double a0 = 2.50662823884;
static const double a1 = -18.61500062529;
static const double a2 = 41.39119773534;
static const double a3 = -25.44106049637;
static const double b1 = -8.47351093090;
static const double b2 = 23.08336743743;
static const double b3 = -21.06224101826;
static const double b4 = 3.13082909833;
static const double c0 = 0.3374754822726147;
static const double c1 = 0.9761690190917186;
static const double c2 = 0.1607979714918209;
static const double c3 = 0.0276438810333863;
static const double c4 = 0.0038405729373609;
static const double c5 = 0.0003951896511919;
static const double c6 = 0.0000321767881768;
static const double c7 = 0.0000002888167364;
static const double c8 = 0.0000003960315187;

static double hornerFunction(double x, double a) {
	return a;
}

static inline double hornerFunction(double x, double a, double b) {
	return a + x * hornerFunction(x, b);
}

static inline double hornerFunction(double x, double a, double b, double c) {
	return a + x * hornerFunction(x, b, c);
}

static inline double hornerFunction(double x, double a, double b, double c, double d) {
	return a + x * hornerFunction(x, b, c, d);
}

static inline double hornerFunction(double x, double a, double b, double c, double d, double e) {
	return a + x * hornerFunction(x, b, c, d, e);
}

static inline double hornerFunction(double x, double a, double b, double c, double d, double e,
	double f) {
	return a + x * hornerFunction(x, b, c, d, e, f);
}

static inline double hornerFunction(double x, double a, double b, double c, double d, double e,
	double f, double g) {
	return a + x * hornerFunction(x, b, c, d, e, f, g);
}

static inline double hornerFunction(double x, double a, double b, double c, double d, double e,
	double f, double g, double h) {
	return a + x * hornerFunction(x, b, c, d, e, f, g, h);
}

static inline double hornerFunction(double x, double a, double b, double c, double d, double e,
	double f, double g, double h, double i) {
	return a + x * hornerFunction(x, b, c, d, e, f, g, h, i);
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

double norminv(double x) {
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
