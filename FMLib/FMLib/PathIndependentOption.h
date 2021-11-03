#pragma once

#include "stdafx.h"
#include "ContinuousTimeOptionBase.h"

class PathIndependentOption : public ContinuousTimeOptionBase {
public:
	virtual ~PathIndependentOption() {}
	virtual double payoff(double finalStockPrice) const = 0;
	double payoff(const std::vector<double>& stockPrices) const {
		return payoff(stockPrices.back());
	}
	bool isPathDependent() const {
		return false;
	}
};