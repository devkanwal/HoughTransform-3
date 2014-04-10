#ifndef _EVENTS_H
#define _EVENTS_H
#include "Tools.h"
#include <vector>
#include <TTree.h>

struct Events {
	/*std::vector<bool> reconstructible_asLong;
	std::vector<bool> reconstructible_asUpstream;
	std::vector<bool> fromB;
	std::vector<Int_t> pid;
	std::vector<Double_t> true_p;
	std::vector<Double_t> true_px;
	std::vector<Double_t> true_py;
	std::vector<Double_t> true_pt;
	std::vector<Double_t> true_eta;
	std::vector<Int_t> true_threeCharge;
	std::vector<Int_t> nHits;
	std::vector<Int_t> len;
	std::vector<Float_t> x_hit;
	std::vector<Float_t> y_min_hit;
	std::vector<Float_t> y_max_hit;
	std::vector<Float_t> z_hit;
	std::vector<Float_t> planeCode;
	std::vector<Float_t> x_UT;
	std::vector<Double_t> x_velo;
	std::vector<Double_t> y_velo;
	std::vector<Double_t> z_velo;
	std::vector<Double_t> tx_velo;
	std::vector<Double_t> ty_velo;
	std::vector<bool> hasVelo;
	std::vector<Int_t> vplen;*/
	std::vector<Float_t> velo_x_hit;
	std::vector<Float_t> velo_y_hit;
	std::vector<Float_t> velo_z_hit;
};

Events getEvents(TTree* tree);
void print(const Events &E);

#endif