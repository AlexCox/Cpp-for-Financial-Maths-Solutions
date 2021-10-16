#include "stdafx.h"
#include "testing.h"

const double PI = 3.14159265359;

int solveQuadratic(double a, double b, double c,
	double& root_1, double& root_2) {
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return 0;
	}
	else if (discriminant == 0) {
		root_1 = -0.5 * b / a;
		return 1;
	}
	else {
		root_1 = 0.5 * (-b + sqrt(discriminant)) / a;
		root_2 = 0.5 * (-b - sqrt(discriminant)) / a;
		return 2;
	}
}

int solveQuadratic(double a, double b, double c,
	std::vector<double>& roots) {
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		return 0;
	}
	else if (discriminant == 0) {
		roots[0] = -0.5 * b / a;
		return 1;
	}
	else {
		roots[0] = 0.5 * (-b + sqrt(discriminant)) / a;
		roots[1] = 0.5 * (-b - sqrt(discriminant)) / a;
		return 2;
	}
}

double mean(std::vector<double>& values) {
	size_t N = values.size();
	double total = 0.0;
	for (int i = 0; i < N; i++) {
		total += values[i];
	}
	total = total / N;
	return total;
}

double standardDeviation(std::vector<double>& values,
	bool populationStdDev = false) {
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

double min(std::vector<double>& values) {
	size_t N = values.size();
	double minimum = values[0];
	for (int i = 1; i < N; i++) {
		if (values[i] < minimum) {
			minimum = values[i];
		}
	}
	return minimum;
}

double max(std::vector<double>& values) {
	size_t N = values.size();
	double maximum = values[0];
	for (int i = 1; i < N; i++) {
		if (values[i] > maximum) {
			maximum = values[i];
		}
	}
	return maximum;
}

std::vector<double> randuniform(int n) {
	std::vector<double> values(n);
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		values[i] = rand() / (double)RAND_MAX;
	}
	return values;
}

std::vector<double> randn(int n) {
	std::vector<double> values(n);
	std::default_random_engine generator;
	std::normal_distribution<double> distribution(0.0, 1.0);
	for (int i = 0; i < n; i++) {
		values[i] = distribution(generator);
	}
	return values;
}

std::vector<double> boxMullerNormDist(int n) {
	if (n % 2 == 1)
		n++;
	std::vector<double> values;
	double u1, u2, n1, n2;
	std::random_device rd;  // Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	for (int i = 0; i < n / 2; i++) {
		u1 = dis(gen);
		u2 = dis(gen);
		n1 = sqrt(-2.0 * log(u1)) * cos(2 * PI * u2);
		n2 = sqrt(-2.0 * log(u1)) * sin(2 * PI * u2);
		values.push_back(n1);
		values.push_back(n2);
	}
	return values;
}

static void testMean() {
	std::vector<double> testVals({ 1.5, 2.5 });
	ASSERT(mean(testVals) == 2.0);
}

static void testStandardDeviation() {
	std::vector<double> populationData({ 4, 9, 11, 12, 17, 5, 8, 12, 14 });
	ASSERT_APPROX_EQUAL(standardDeviation(populationData, true),
		3.94, 0.01);

	std::vector<double> sampleData({ 9, 2, 5, 4, 12, 7 });
	ASSERT_APPROX_EQUAL(standardDeviation(sampleData),
		3.619, 0.01);
}

static void testMinAndMax() {
	std::vector<double> values({ 0.3, -23.2, 1.2, 20, 0, 27, -1.2 });
	ASSERT(min(values) == -23.2);
	ASSERT(max(values) == 27);
}

static void testRandUniform() {
	std::vector<double> values = randuniform(1000);
	ASSERT(values.size() == 1000);
	ASSERT_APPROX_EQUAL(mean(values), 0.5, 0.1);
}

static void testRandn() {
	std::vector<double> values = randn(1000);
	ASSERT_APPROX_EQUAL(mean(values), 0.0, 0.01);
	ASSERT_APPROX_EQUAL(standardDeviation(values), 1.0, 0.01);
}

static void testBoxMullerNormDist() {
	std::vector<double> values = boxMullerNormDist(1000);
	std::cout << "Mean: " << mean(values) << std::endl;
	std::cout << "Std dev: " << standardDeviation(values) << std::endl;
	ASSERT_APPROX_EQUAL(0.0, mean(values), 0.1);
	ASSERT_APPROX_EQUAL(1.0, standardDeviation(values), 0.1);
}

int main() {
	TEST(testMean);
	TEST(testStandardDeviation);
	TEST(testMinAndMax);
	TEST(testRandUniform);
	TEST(testRandn);
	TEST(testBoxMullerNormDist);
	return 0;
}