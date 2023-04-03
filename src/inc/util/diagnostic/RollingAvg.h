#pragma once

#include <list>

class RollingAvg {
private:
	int windowSize = DEFAULT_WINDOW_SIZE;
	std::list<double> elements;

	double getTotal();

public:

	RollingAvg();
	RollingAvg(int windowSize);

	const static int DEFAULT_WINDOW_SIZE{ 10 };

	void submit(double qty);
	double getAvg();
};