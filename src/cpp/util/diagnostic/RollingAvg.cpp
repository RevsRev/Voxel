#include <util/diagnostic/RollingAvg.h>

RollingAvg::RollingAvg() : RollingAvg(RollingAvg::DEFAULT_WINDOW_SIZE) {
}
RollingAvg::RollingAvg(int windowSize) {
	this->windowSize = windowSize;
}

void RollingAvg::submit(double qty) {
	if (elements.size() >= windowSize) {
		elements.pop_front();
	}
	elements.push_back(qty);
}
double RollingAvg::getAvg() {
	if (elements.size() == 0) {
		return 0;
	}
	return getTotal() / elements.size();
}
double RollingAvg::getTotal() {
	double total = 0;
	for (auto it = elements.begin(); it != elements.end(); it++) {
		total += *it;
	}
	return total;
}