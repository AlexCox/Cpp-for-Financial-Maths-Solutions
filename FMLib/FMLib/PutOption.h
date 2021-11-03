#pragma once

#include "stdafx.h"
#include "BlackScholesModel.h"
#include "ContinuousTimeOptionBase.h"

class PutOption : public ContinuousTimeOptionBase {
public:
	double payoff(const std::vector<double>& stockprices) const;
	double price(const BlackScholesModel& model) const;

	bool isPathDependent() const {
		return false;
	}
};

void testPutOption();
