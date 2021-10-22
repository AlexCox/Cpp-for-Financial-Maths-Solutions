#pragma once

const double PI = 3.14159265358979;

class CartesianPoint {
public:
	double x;
	double y;
	double distanceTo(const CartesianPoint& p) const;
};

class PolarPoint {
public:
	double r;
	double theta;
};

class Circle {
public:
	double radius;
	double area() const;
	double circumference() const;
};

/*
	Computing the area of a circle of radius r
*/
double circleArea(int r);


/*
	Computing the circumference of a circle of radius r
*/
double circleCircumference(int r);

/*
	Testing circleArea and circleCircumference functions
*/
void testGeometry();

CartesianPoint polarToCartesian(const PolarPoint& p);

double perimeter(const CartesianPoint& p1,
	const CartesianPoint& p2, const CartesianPoint& p3);