#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
#include <TH2F.h>
#include <TF1.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <boost/assign/std/vector.hpp>


using namespace boost::assign;

struct binCoordValue {
	double i, j;
	int value;
	binCoordValue(int _i, int _j, int _value) { i = _i; j = _j; value = _value; }
};

struct binCoord {
	double i,j;
	binCoord(double _i, double _j) { i = _i, j = _j; }
};

double get_minimum(std::vector<double> x) {
	double min = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] < min) min = x[i];
	}
	return min;
}

std::vector<

double get_maximum(std::vector<double> x) {
	double max = x[0];
	for (unsigned int i=1; i<x.size(); i++) {
		if (x[i] > max) max = x[i];
	}
	return max;
}

void makeCluster(std::vector<binCoordValue> max, int resX, int resY, std::vector<binCoord> *M) {
	double a = max[0].i;
	double b = max[0].j;
	for (unsigned int i=1; i<max.size(); i+) {
		double c = max[i].i;
		double d = max[i].j;

		if (fabs(a-c) <= resX && fabs(b-d) <= resY) {
			a = (a+c)/2.;
			b = (b+d)/2.;
			M->push_back(binCoord(a,b));
		}
		else {
			M->push_back(binCoord(a,b));
			a = c;
			b = d;
		}
	}
}

void makeLinearHT(std::vector<double> x, std::vector<double> y, double thr, int nTheta, int nRho, int resX, int resY, TH2F *h) {
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
	std::vector<TF1> sinu;
	//for (unsigned int i=0; i<x.size(); i++) {
	//	sinu.push_back(TF1(strcat("sinu",i),[0]*cos(x)
	//}
	for (unsigned int i = 0; i<x.size(); i++) {
		for (unsigned int t = 0; t<thetas.size(); t++) {
			double r = x[i]*cos(thetas[t]) + y[i]*sin(thetas[t]);
			//std::cout << r << "\t" << t << std::endl;
			h->Fill(thetas[t],r);
		}
	}
	std::vector<binCoordValue> preliminaryMax;
	for (unsigned int i=0;i<nTheta;i++) {
		for (unsigned int j=0;j<nRho;j++) {
			double tmp = h->GetBinContent(i,j);
			if (tmp >= thr) { 
				preliminaryMax.push_back(binCoordValue(i,j,tmp));
			}
		}
	}
	
}

int main(int argc, char *argv[]) {
	std::vector<double> x,y;
	x += 4.0,3.2,1.8,1.0,1.0,2.0,3.0,1.0,4.0,2.7;
	y += 4.0,3.2,1.8,1.0,3.5,2.5,1.5,5.0,1.2,4.1;

	int nTheta = 1000;
	int nRho = 1000;
	int thr = 3;
	int resX = 2;
	int resY = 2;
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;
	
	TApplication theApp("App",&argc,argv);

	TH2F* h = new TH2F("h","h",nTheta,mtheta,Mtheta,nRho,mrho,Mrho);
	makeLinearHT(x,y,thr,nTheta,nRho,resX,resY,h);
	TCanvas* c2 = new TCanvas("c2","c2");
    h->GetXaxis()->SetTitle("#theta");
    h->GetYaxis()->SetTitle("#rho");
	h->Draw("colz");
	theApp.Run();
	return 0;
}
