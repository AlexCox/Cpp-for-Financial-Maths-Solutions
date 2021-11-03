#include "CallOption.h"
#include "matlib.h"

double CallOption::payoff(double stockAtMaturity) const {
	if (stockAtMaturity > getStrike()) {
		return stockAtMaturity - getStrike();
	}
	else {
		return 0.0;
	}
}

double CallOption::price(
	const BlackScholesModel& model) const {
	double S = model.stockPrice;
	double K = getStrike();
	double sigma = model.volatility;
	double r = model.riskFreeRate;
	double T = getMaturity() - model.date;

	double denominator = sigma * sqrt(T);
	double d1 = (log(S / K) + (r + 0.5 * sigma * sigma) * T) / denominator;
	double d2 = d1 - denominator;
	return S * normcdf(d1) - K * normcdf(d2) * exp(-r * T);
}

static void testCallOptionPrice() {
	CallOption callOption;
	callOption.setStrike(105.0);
	callOption.setMaturity(2.0);

	BlackScholesModel m;
	m.date = 1.0;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 100.0;

	double price = callOption.price(m);
	ASSERT_APPROX_EQUAL(price, 4.046, 0.01);
}

void testCallOption() {
	TEST(testCallOptionPrice);
}