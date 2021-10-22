#include "BlackScholesModel.h"
#include "stdafx.h"
#include "testing.h"

BlackScholesModel::BlackScholesModel() :
	stockPrice(0.0),
	volatility(0.0),
	riskFreeRate(0.0),
	date(0.0) {
}