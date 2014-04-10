#include "HT.h"


std::vector<HTCoord> convertBinVal(TH2F* h, std::vector<binCoord> cleanMaxbins) {
	std::vector<HTCoord> M;
	for (unsigned int i=0;i<cleanMaxbins.size(); i++){
		double R = h->GetYaxis()->GetBinCenter(int( round(cleanMaxbins[i].j) ));
		double Theta = h->GetXaxis()->GetBinCenter(int( round(cleanMaxbins[i].i) ));
		M.push_back(HTCoord(R,Theta));
	}
	return M;
}

std::vector<TF1*> findLines(std::vector<HTCoord> myMax, double mx,double Mx) {
	std::vector<TF1*> lines;
	for (unsigned int i=0; i<myMax.size(); i++) {
		char* fname = "test ";
		fname += i;
		lines.push_back(new TF1(fname,"([0]-cos([1])*x)/sin([1])",mx,Mx));
		lines[i]->SetParameter(0,myMax[i].r);
		lines[i]->SetParameter(1,myMax[i].theta);
	}
	return lines;
}


std::vector<binCoord> makeCluster(std::vector<binCoordValue> max, int resX, int resY) {
	std::vector<binCoord> M;
	double a = max[0].i;
	double b = max[0].j;
	for (unsigned int i=1; i<max.size(); i++) {
		double c = max[i].i;
		double d = max[i].j;
		//		std::cout << c << "\t" << d << std::endl;

		if ( (fabs(a-c) <= resX) && (fabs(b-d) <= resY)) {
			a = (a+c)/2.;
			b = (b+d)/2.;
			//M->push_back(binCoord(a,b));
		}
		else {
			M.push_back(binCoord(a,b));
			a = c;
			b = d;
		}


	}
	M.push_back(binCoord(a,b));
	return M;
}

void fillHistogram(std::vector<Float_t> x, std::vector<Float_t> y, TH2F* h, int nTheta) {
	double step = M_PI/nTheta;
	double tmp = 0.;
	std::vector<double> thetas;

	for (int i=0; i<nTheta;i++) {
		tmp += step;
		thetas.push_back(tmp);
	}
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;

	for (unsigned int i = 0; i<x.size(); i++) {
		for (unsigned int t = 0; t<thetas.size(); t++) {
			double r = x[i]*cos(thetas[t]) + y[i]*sin(thetas[t]);
			//std::cout << r << "\t" << t << std::endl;
			h->Fill(thetas[t],r);
		}
	}
}

std::vector<binCoordValue> getCoords(TH2F* h, int nRho, int nTheta, int thr) {
	std::vector<binCoordValue> preliminaryMax;	
	for (int i=0;i<nTheta;i++) {
		for (int j=0;j<nRho;j++) {
			int tmp = h->GetBinContent(i,j);
			if (tmp >= thr) { 
				preliminaryMax.push_back(binCoordValue(i,j,tmp));
			}
		}
	}

	return preliminaryMax;
}


void HT(std::vector<Float_t> x, std::vector<Float_t> y, int thr) {

	int nTheta = 1000;
	int nRho = 1000;
	int resX = 2;
	int resY = 2;
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;

	TH2F* h = new TH2F("h","h",nTheta,mtheta,Mtheta,nRho,mrho,Mrho);
	fillHistogram(x, y, h, nTheta);

	double mx = get_minimum(x);
	double Mx = get_maximum(x);

	//std::vector<binCoordValue> binCoords = getCoords(h, nRho, nTheta, thr);
	//std::vector<binCoord> M = makeCluster(binCoords, resX, resY);
	//std::vector<HTCoord> cleanMax = convertBinVal(h, M);
	//std::vector<TF1*> lines = findLines(cleanMax, mx, Mx);
	TGraph* hPs = new TGraph(x.size(), &x[0], &y[0]);// &x[0] converts vector to double* array, same for y

	//drawGraphs(h, lines, hPs);

	TCanvas* c2 = new TCanvas("c2","c2");
	h->GetXaxis()->SetTitle("#theta");
	h->GetYaxis()->SetTitle("#rho");
	h->Draw("colz");


	TCanvas* c4 = new TCanvas("c4","found lines");
	hPs->Draw("A*");
	//for (unsigned int i=0; i<lines.size(); i++){
	//	//if (i == 0) lines->at(i).Draw();
	//	//else lines->at(i).Draw("same");
	//	lines[i]->Draw("same");
	//}
	c4->Update();
}

void fillHistogram(std::vector<Track> tracks, TH2F* h, int nTheta) {
	double step = M_PI/nTheta;
	double tmp = 0.;
	std::vector<double> thetas;

	for (int i=0; i<nTheta;i++) {
		tmp += step;
		thetas.push_back(tmp);
	}
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;
	for (unsigned int i = 0; i<tracks.size(); i++) {
		for (unsigned int t = 0; t<thetas.size(); t++) {
			double r = tracks[i].velo_y_hit *cos(thetas[t]) + tracks[i].velo_z_hit*sin(thetas[t]);
			//std::cout << r << "\t" << t << std::endl;
			h->Fill(thetas[t],r);
		}
	}
}

void HT(std::vector<Track> t, int thr) {

	int nTheta = 1000;
	int nRho = 1000;
	int resX = 2;
	int resY = 2;
	double mtheta = 0.;
	double Mtheta = M_PI;
	double mrho = -10;
	double Mrho = 10;

	TH2F* h = new TH2F("h","h",nTheta,mtheta,Mtheta,nRho,mrho,Mrho);
	fillHistogram(t, h, nTheta);

}