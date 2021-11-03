#pragma once

#include "stdafx.h"
#include "CallOption.h"
#include "BlackScholesModel.h"
#include "ContinuousTimeOption.h"

class MonteCarloPricer {
public:
	MonteCarloPricer();

	int nScenarios;
	int nSteps;
	double price(const ContinuousTimeOption& option,
		const BlackScholesModel& model);
};

void testMonteCarloPricer();