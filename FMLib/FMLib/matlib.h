#pragma once

#include "stdafx.h"
#include "RealFunction.h"

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

std::vector<double> linspace(double from, double to, int numPoints);
double sum(const std::vector<double>& v);
double mean(const std::vector<double>& values);
double standardDeviation(const std::vector<double>& values, bool populationStdDev = false);
double min(const std::vector<double>& values);
double max(const std::vector<double>& values);
void rng(const std::string& setting);
std::vector<double> randuniform(int n);
std::vector<double> randn(int n);
std::vector<double> sort(const std::vector<double>& v);
double prctile(const std::vector<double>& v, double percentage);

double integral(RealFunction& f, double a, double b, int steps);

/*
	Testing normcdf and norminv functions
*/
void testMatlib();