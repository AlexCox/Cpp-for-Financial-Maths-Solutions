#include "geometry.h"
#include "stdafx.h"
#include "testing.h"

double circleArea(int r) {
	DEBUG_PRINT("Computing circleArea(" << r << ")");
	double answer = PI * r * r;
	DEBUG_PRINT("Returning " << answer);
	return answer;
}

double circleCircumference(int r) {
	DEBUG_PRINT("Computing circleCircumference(" << r << ")");
	double answer = 2.0 * PI * r;
	DEBUG_PRINT("Returning " << answer);
	return answer;
}

void polarToCartesian(double r, double theta, double& x, double& y) {
	x = r * cos(theta);
	y = r * sin(theta);
}

/*
	TESTS
*/

static void testCircleArea() {
	ASSERT_APPROX_EQUAL(circleArea(2), 12.56637, 0.01);
}

static void testCircleCircumference() {
	ASSERT_APPROX_EQUAL(circleCircumference(3), 18.84956, 0.01);
}

static void testPolarToCartesian() {
	double r = 2.0;
	double theta = PI / 2;
	double x = 0.0, y = 0.0;
	polarToCartesian(r, theta, x, y);
	ASSERT_APPROX_EQUAL(x, 0.0, 0.001);
	ASSERT_APPROX_EQUAL(y, 2.0, 0.001);
}

void testGeometry() {
	TEST(testCircleArea);
	TEST(testCircleCircumference);
	TEST(testPolarToCartesian);
}
