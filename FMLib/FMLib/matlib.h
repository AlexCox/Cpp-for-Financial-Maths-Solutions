#pragma once

/*
	Computes the cumulative distribution function of the normal distribution
*/
double normcdf(double x);

/*
	Computes the inverse of normcdf
*/
double norminv(double x);

/*
	Black-Scholes call and put price calculations
*/
double blackScholesCallPrice(double K, double T, double S, double sigma, double r);

double blackScholesPutPrice(double K, double T, double S, double sigma, double r);

/*
	Testing normcdf and norminv functions
*/
void testMatlib();