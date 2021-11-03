#pragma once

#include "stdafx.h"

class ContinuousTimeOption {
public:
	virtual ~ContinuousTimeOption() {};

	virtual double getMaturity() const = 0;

	virtual double payoff(const std::vector<double>& stockPrices) const = 0;

	virtual bool isPathDependent() const = 0;
};