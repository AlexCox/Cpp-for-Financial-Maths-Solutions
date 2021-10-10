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

/*
	TESTS
*/

static void testCircleArea() {
	ASSERT_APPROX_EQUAL(circleArea(2), 12.56637, 0.01);
}

static void testCircleCircumference() {
	ASSERT_APPROX_EQUAL(circleCircumference(3), 18.84956, 0.01);
}

void testGeometry() {
	TEST(testCircleArea);
	TEST(testCircleCircumference);
}
