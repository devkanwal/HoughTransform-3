#ifndef _HT_H
#define _HT_H
#include "Tools.h"


// Structs used for HT //
struct binCoordValue {
	double i, j;
	int value;
	binCoordValue(double _i, double _j, int _value) { i = _i; j = _j; value = _value; }
};

struct binCoord {
	double i,j;
	binCoord(double _i, double _j) { i = _i, j = _j; }
};

struct HTCoord {
	double r, theta;
	HTCoord(double _r, double _theta) { r = _r; theta = _theta; }
};


std::vector<HTCoord> convertBinVal(TH2F* h, std::vector<binCoord> cleanMaxbins);
std::vector<TF1*> findLines(std::vector<HTCoord> myMax, double mx,double Mx);
std::vector<binCoord> makeCluster(std::vector<binCoordValue> max, int resX, int resY);
void fillHistogram(std::vector<double> x, std::vector<double> y, TH2F* h, int nTheta);
std::vector<binCoordValue> getCoords(TH2F* h, int nRho, int nTheta, int thr);
void HT(std::vector<double> x, std::vector<double> y, int thr);

#endif