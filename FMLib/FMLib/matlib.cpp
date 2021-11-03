#include "matlib.h"
#include "stdafx.h"
#include "geometry.h"
#include "testing.h"

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

double blackScholesCallPrice(double K, double T, double S, double sigma, double r) {
	DEBUG_PRINT("Calculating Black-Scholes call price");
	double denominator = sigma * sqrt(T);
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / denominator;
	double d2 = d1 - denominator;
	double C = normcdf(d1) * S - normcdf(d2) * K * exp(-r * T);
	DEBUG_PRINT("Returned value: " << C);
	return C;
}

double blackScholesPutPrice(double K, double T, double S, double sigma, double r) {
	DEBUG_PRINT("Calculating Black-Scholes put price");
	double denominator = sigma * sqrt(T);
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / denominator;
	double d2 = d1 - denominator;
	double P = normcdf(-d2) * K * exp(-r * T) - normcdf(-d1) * S;
	DEBUG_PRINT("Returned value: " << P);
	return P;
}

std::vector<double> linspace(double from, double to, int numPoints) {
	ASSERT(numPoints >= 2);
	std::vector<double> ret(numPoints, 0.0);
	double step = (to - from) / (numPoints - 1);
	double current = from;
	for (int i = 0; i < numPoints; i++) {
		ret[i] = current;
		current += step;
	}
	return ret;
}

double sum(const std::vector<double>& v) {
	double total = 0.0;
	int n = v.size();
	for (int i = 0; i < n; i++) {
		total += v[i];
	}
	return total;
}

double mean(const std::vector<double>& values) {
	size_t N = values.size();
	double total = sum(values);
	return total / N;
}

double standardDeviation(const std::vector<double>& values, bool populationStdDev) {
	double total = 0.0;
	size_t N = values.size();
	double mu = mean(values);
	for (int i = 0; i < N; i++) {
		total += pow(values[i] - mu, 2);
	}
	if (populationStdDev) {
		return sqrt(total / N);
	}
	else {
		return sqrt(total / (N - 1));
	}

}

double min(const std::vector<double>& values) {
	size_t N = values.size();
	double minimum = values[0];
	for (int i = 1; i < N; i++) {
		if (values[i] < minimum) {
			minimum = values[i];
		}
	}
	return minimum;
}

double max(const std::vector<double>& values) {
	size_t N = values.size();
	double maximum = values[0];
	for (int i = 1; i < N; i++) {
		if (values[i] > maximum) {
			maximum = values[i];
		}
	}
	return maximum;
}


static std::mt19937 mersenneTwister;

void rng(const std::string& description) {
	ASSERT(description == "default");
	mersenneTwister.seed(std::mt19937::default_seed);
}

std::vector<double> randuniform(int n) {
	std::vector<double> ret(n, 0.0);
	for (int i = 0; i < n; i++) {
		ret[i] = (mersenneTwister() + 0.5) /
			(mersenneTwister.max() + 1.0);
	}
	return ret;
}

/*  Create normally distributed random numbers */
std::vector<double> randn(int n) {
	std::vector<double> v = randuniform(n);
	for (int i = 0; i < n; i++) {
		v[i] = norminv(v[i]);
	}
	return v;
}

std::vector<double> sort(const std::vector<double>& v) {
	std::vector<double> copy(v);
	std::sort(copy.begin(), copy.end());
	return copy;
}

/**
 *  Find the given percentile of a distribution
 */
double prctile(const std::vector<double>& v, double percentage) {
	ASSERT(percentage >= 0.0);
	ASSERT(percentage <= 100.0);
	int n = v.size();
	std::vector<double> sorted = sort(v);

	int indexBelow = (int)(n * percentage / 100.0 - 0.5);
	int indexAbove = indexBelow + 1;
	if (indexAbove > n - 1) {
		return sorted[n - 1];
	} if (indexBelow < 0) {
		return sorted[0];
	}
	double valueBelow = sorted[indexBelow];
	double valueAbove = sorted[indexAbove];
	double percentageBelow = 100.0 * (indexBelow + 0.5) / n;
	double percentageAbove = 100.0 * (indexAbove + 0.5) / n;
	if (percentage <= percentageBelow) {
		return valueBelow;
	}
	if (percentage >= percentageAbove) {
		return valueAbove;
	}
	double correction = (percentage - percentageBelow) * (valueAbove - valueBelow) / (percentageAbove - percentageBelow);
	return valueBelow + correction;
}

double integral(RealFunction& f, double a, double b, int steps) {
	double h = (b - a) / steps;
	double x = a + 0.5 * h;
	double total = 0.0;
	for (int i = 0; i < steps; i++) {
		double y = f.evaluate(x);
		total += y;
		x += h;
	}
	return h * total;
}

/*
	TESTS
*/

static void testNormCdf() {
	// test bounds
	ASSERT(normcdf(0.3) > 0);
	ASSERT(normcdf(0.3) < 1);
	// test extreme values
	ASSERT_APPROX_EQUAL(normcdf(-1e10), 0, 0.001);
	ASSERT_APPROX_EQUAL(normcdf(1e10), 1.0, 0.001);
	// test increasing
	ASSERT(normcdf(0.3) < normcdf(0.5));
	// test symmetry
	ASSERT_APPROX_EQUAL(normcdf(0.3),
		1 - normcdf(-0.3), 0.0001);
	ASSERT_APPROX_EQUAL(normcdf(0.0), 0.5, 0.0001);
	// test inverse
	ASSERT_APPROX_EQUAL(normcdf(norminv(0.3)),
		0.3, 0.0001);
	// test well known value
	ASSERT_APPROX_EQUAL(normcdf(1.96), 0.975, 0.001);
}

static void testNormInv() {
	ASSERT_APPROX_EQUAL(norminv(0.975), 1.96, 0.01);
}

static void testBlackScholesCallPrice() {
	double strike = 100.0;
	double timeToMaturity = 0.5;
	double spot = 110.0;
	double volatility = 0.1;
	double riskFreeRate = 0.03;

	ASSERT_APPROX_EQUAL(blackScholesCallPrice(
		strike, timeToMaturity, spot, volatility, riskFreeRate
	), 11.677, 0.01);
}

static void testBlackScholesPutPrice() {
	double strike = 105.0;
	double timeToMaturity = 1.0;
	double spot = 100.0;
	double volatility = 0.1;
	double riskFreeRate = 0.05;

	ASSERT_APPROX_EQUAL(blackScholesPutPrice(
		strike, timeToMaturity, spot, volatility, riskFreeRate
	), 3.925, 0.01);
}

void testMatlib() {
	TEST(testNormCdf);
	TEST(testNormInv);
	TEST(testBlackScholesCallPrice);
	TEST(testBlackScholesPutPrice);
}