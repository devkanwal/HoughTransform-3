#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TH2F.h>
#include <TF1.h>
#include <TCanvas.h>
#include <boost/assign/std/vector.hpp>


using namespace boost::assign;

double get_minimum(std::vector<double> x) {
	double min = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] < min) min = x[i];
	}
	return min;
}

double get_maximum(std::vector<double> x) {
	double max = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] > max) max = x[i];
	}
	return max;
}

void makeLinearHT(std::vector<double> x, std::vector<double> y, double thr, int nTheta, int nRho, int resX, int resY) {
	double mx = get_minimum(x);
	double Mx = get_maximum(x);
	double my = get_minimum(y);
	double My = get_maximum(y);

	double step = M_PI/nTheta;
	double tmp = 0.;
	std::vector<double> thetas;

	for (unsigned int i=0; i<nTheta;i++) {
		tmp += step;
		thetas.push_back(tmp);
	}
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;
	TH2F* h = new TH2F("h","h", nTheta, mtheta, Mtheta, nRho, mrho, Mrho);
	TCanvas* c = new TCanvas("c","c");
	std::vector<TF1> sinu;
	for (unsigned int i=0; i<x.size(); i++) {
		//sinu.push_back(TF1("sinu //continue here
	}
}

int main() {
	std::vector<double> x;
	x += 4.0,3.2,1.8,1.0,1.0,2.0,3.0;
	std::cout << get_minimum(x) << std::endl;
}
