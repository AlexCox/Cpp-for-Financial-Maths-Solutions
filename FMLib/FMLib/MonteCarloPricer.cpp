#include "MonteCarloPricer.h"
#include "matlib.h"

MonteCarloPricer::MonteCarloPricer() :
	nScenarios(10000) {
}

double MonteCarloPricer::price(
	const CallOption& option, const BlackScholesModel& bsm) {
	double total = 0.0;
	for (int i = 0; i < nScenarios; i++) {
		std::vector<double> path = bsm.generateRiskNeutralPricePath(
			option.maturity, 1);
		double stockPrice = path.back();
		double payoff = option.payoff(stockPrice);
		total += payoff;
	}
	double mean = total / nScenarios;
	double r = bsm.riskFreeRate;
	double T = option.maturity - bsm.date;
	return exp(-r * T) * mean;
}

static void testPriceCallOption() {
	rng("default");

	CallOption c;
	c.strike = 110;
	c.maturity = 2;

	BlackScholesModel m;
	m.volatility = 0.1;
	m.riskFreeRate = 0.05;
	m.stockPrice = 100.0;
	m.drift = 0.1;
	m.date = 1;

	MonteCarloPricer pricer;
	double price = pricer.price(c, m);
	double expected = c.price(m);
	ASSERT_APPROX_EQUAL(price, expected, 0.1);
}