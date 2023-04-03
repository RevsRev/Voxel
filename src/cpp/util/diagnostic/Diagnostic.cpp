#include <util/diagnostic/Diagnostic.h>

void Diagnostic::submit(double qty) {
	if (min == NULL) {
		min = qty;
	}
	if (max == NULL) {
		max = qty;
	}

	max = std::max(max, qty);
	min = std::min(min, qty);
	avg.submit(qty);
}

void Diagnostic::dump() {
	std::cout << "Min: " << min << ", Max: " << max << ", Avg: " << avg.getAvg();
}