#include "PutOption.h"
#include "matlib.h"

PutOption::PutOption() :
	strike(0.0), maturity(0.0) {
}

double PutOption::payoff(double stockAtMaturity) const {
	if (stockAtMaturity > strike) {
		return strike - stockAtMaturity;
	}
	else {
		return 0.0;
	}
}

double PutOption::price(
	const BlackScholesModel& bsm) const {
	double S = bsm.stockPrice;
	double K = strike;
	double sigma = bsm.volatility;
	double r = bsm.riskFreeRate;
	double T = maturity - bsm.date;

	double denominator = sigma * sqrt(T);
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / denominator;
	double d2 = d1 - denominator;
	return normcdf(-d2) * K * exp(-r * T) - normcdf(-d1) * S;
}

static void testPayoff() {
	PutOption putOption;
	putOption.strike = 105.0;
	putOption.maturity = 2.0;
	ASSERT_APPROX_EQUAL(putOption.payoff(110.0), 0.0, 0.001);
	ASSERT_APPROX_EQUAL(putOption.payoff(100.0), 5.0, 0.001);
}

static void testPutOptionPrice() {
	PutOption putOption;
	putOption.strike = 105.0;
	putOption.maturity = 2.0;

	BlackScholesModel bsm;
	bsm.date = 1.0;
	bsm.volatility = 0.1;
	bsm.riskFreeRate = 0.05;
	bsm.stockPrice = 100.0;

	double price = putOption.price(bsm);
	ASSERT_APPROX_EQUAL(price, 3.925, 0.01);
}

void testPutOption() {
	TEST(testPayoff);
	TEST(testPutOptionPrice);
}