#pragma once

#include "ContinuousTimeOptionBase.h"

class KnockoutOption : public ContinuousTimeOptionBase {
private:
	double barrier;
public:
	virtual ~KnockoutOption() {};

	double getBarrier() const {
		return barrier;
	}

	void setBarrier(double barrier) {
		this->barrier = barrier;
	}

	bool isPathDependent() const {
		return true;
	}
};