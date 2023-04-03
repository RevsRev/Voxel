#pragma once

#include <util/diagnostic/RollingAvg.h>
#include <cmath>
#include <iostream>

class Diagnostic {
private:
	RollingAvg avg{};
	double min = NULL;
	double max = NULL;

public:
	void submit(double qty);
	void dump();
};