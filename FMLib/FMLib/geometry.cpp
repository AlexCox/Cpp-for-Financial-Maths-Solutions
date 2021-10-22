#include "geometry.h"
#include "stdafx.h"

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

CartesianPoint polarToCartesian(const PolarPoint& p) {
	CartesianPoint c;
	c.x = p.r * cos(p.theta);
	c.y = p.r * sin(p.theta);
	return c;
}

double Circle::area() const {
	return PI * radius * radius;
}

double Circle::circumference() const {
	return 2 * PI * radius;
}

double CartesianPoint::distanceTo(const CartesianPoint& p) const {
	double dx = p.x - x;
	double dy = p.y - y;
	return sqrt(dx * dx + dy * dy);
}

double perimeter(const CartesianPoint& p1,
	const CartesianPoint& p2, const CartesianPoint& p3) {
	double d1 = p1.distanceTo(p2);
	double d2 = p2.distanceTo(p3);
	double d3 = p3.distanceTo(p1);
	return d1 + d2 + d3;
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
	PolarPoint p;
	p.r = 2.0;
	p.theta = PI / 2;
	CartesianPoint c = polarToCartesian(p);
	ASSERT_APPROX_EQUAL(c.x, 0.0, 0.001);
	ASSERT_APPROX_EQUAL(c.y, 2.0, 0.001);
}

static void testAreaOfCircle() {
	Circle c;
	c.radius = 4;
	ASSERT_APPROX_EQUAL(c.area(), 16 * PI, 0.01);
}

static void testCircumferenceOfCircle() {
	Circle c;
	c.radius = 2;
	ASSERT_APPROX_EQUAL(c.circumference(), 4 * PI, 0.01);
}

static void testDistanceTo() {
	CartesianPoint p1;
	p1.x = 1;
	p1.y = 1;
	CartesianPoint p2;
	p2.x = 4;
	p2.y = 5;
	double d = p1.distanceTo(p2);
	ASSERT_APPROX_EQUAL(d, 5.0, 0.0001);
}

static void testPerimeter() {
	CartesianPoint p1;
	p1.x = 0;
	p1.y = 0;
	CartesianPoint p2;
	p2.x = 3;
	p2.y = 0;
	CartesianPoint p3;
	p3.x = 0;
	p3.y = 4;
	double p = perimeter(p1, p2, p3);
	ASSERT_APPROX_EQUAL(p, 12, 0.001);
}

void testGeometry() {
	TEST(testCircleArea);
	TEST(testCircleCircumference);
	TEST(testPolarToCartesian);
	TEST(testAreaOfCircle);
	TEST(testCircumferenceOfCircle);
	TEST(testDistanceTo);
	TEST(testPerimeter);
}
