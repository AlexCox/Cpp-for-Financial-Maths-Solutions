#pragma once

#include "stdafx.h"
#include "CallOption.h"
#include "BlackScholesModel.h"

class MonteCarloPricer {
public:
	MonteCarloPricer();

	int nScenarios;
	double price(const CallOption& option,
		const BlackScholesModel& bsm);
};

void testMonteCarloPricer();