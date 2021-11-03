#include "BlackScholesModel.h"
#include "stdafx.h"
#include "testing.h"
#include "matlib.h"
#include "LineChart.h"


BlackScholesModel::BlackScholesModel() :
	drift(0.0),
	stockPrice(0.0),
	volatility(0.0),
	riskFreeRate(0.0),
	date(0.0) {
}

std::vector<double> BlackScholesModel::generatePricePath(
	double toDate, int nSteps, double drift) const {
	std::vector<double> path(nSteps, 0.0);
	std::vector<double> epsilon = randn(nSteps);
	double dt = (toDate - date) / nSteps;
	double a = (drift - volatility * volatility * 0.5) * dt;
	double b = volatility * sqrt(dt);
	double currentLogS = log(stockPrice);
	for (int i = 0; i < nSteps; i++) {
		double dLogS = a + b * epsilon[i];
		double logS = currentLogS + dLogS;
		path[i] = exp(logS);
		currentLogS = logS;
	}
	return path;
}

std::vector<double> BlackScholesModel::generatePricePath(
	double toDate, int nSteps) const {
	return generatePricePath(toDate, nSteps, drift);
}

std::vector<double> BlackScholesModel::generateRiskNeutralPricePath(
	double toDate, int nSteps) const {
	return generatePricePath(toDate, nSteps, riskFreeRate);
}

void testVisually() {
	BlackScholesModel bsm;
	bsm.riskFreeRate = 0.05;
	bsm.volatility = 0.1;
	bsm.stockPrice = 100.0;
	bsm.date = 2.0;

	int nSteps = 1000;
	double maturity = 4.0;

	std::vector<double> path = bsm.generatePricePath(maturity, nSteps);
	double dt = (maturity - bsm.date) / nSteps;
	std::vector<double> times = linspace(dt, maturity, nSteps);
	LineChart lineChart;
	lineChart.setTitle("Stock price path");
	lineChart.setSeries(times, path);
	lineChart.writeAsHTML("examplePricePath.html");
}

void testRiskNeutralPricePath() {
	rng("default");

	BlackScholesModel bsm;
	bsm.riskFreeRate = 0.05;
	bsm.volatility = 0.1;
	bsm.stockPrice = 100.0;
	bsm.date = 2.0;

	int nPaths = 10000;
	int nSteps = 5;
	double maturity = 4.0;
	std::vector<double> finalPrices(nPaths, 0.0);
	for (int i = 0; i < nPaths; i++) {
		std::vector<double> path = bsm.generateRiskNeutralPricePath(
			maturity, nSteps);
		finalPrices[i] = path.back();
	}
	ASSERT_APPROX_EQUAL(mean(finalPrices), exp(bsm.riskFreeRate * 2.0) * bsm.stockPrice, 0.5);
}