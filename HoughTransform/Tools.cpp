#include "Tools.h"


double round(double d)
{
	return floor(d + 0.5);
}

double get_minimum(std::vector<Float_t> x) {
	double min = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] < min) min = x[i];
	}
	return min;
}

double get_maximum(std::vector<Float_t> x) {
	double max = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] > max) max = x[i];
	}
	return max;
}
