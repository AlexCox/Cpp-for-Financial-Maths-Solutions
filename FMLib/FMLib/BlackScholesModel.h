#pragma once

class BlackScholesModel {
public:
	BlackScholesModel();

	double stockPrice;
	double volatility;
	double riskFreeRate;
	double date;
};