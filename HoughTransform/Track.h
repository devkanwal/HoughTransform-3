#ifndef _TRACK_H
#define _TRACK_H
#include "Tools.h"
#include <vector>
#include <TTree.h>

struct Track {
	bool reconstructible_asLong;
	bool reconstructible_asUpstream;
	bool fromB;
	Int_t pid;
	Double_t true_p;
	Double_t true_px;
	Double_t true_py;
	Double_t true_pt;
	Double_t true_eta;
	Int_t true_threeCharge;
	Int_t nHits;
	Int_t len;
	Float_t x_hit;
	Float_t y_min_hit;
	Float_t y_max_hit;
	Float_t z_hit;
	Float_t planeCode;
	Float_t x_UT;
	Double_t x_velo;
	Double_t y_velo;
	Double_t z_velo;
	Double_t tx_velo;
	Double_t ty_velo;
	bool hasVelo;
	Int_t vplen;
	Float_t velo_x_hit;
	Float_t velo_y_hit;
	Float_t velo_z_hit;
};

bool isGood(const Track &track);
std::vector<Track> getTracks(TTree* tree);
void printTracks(const std::vector<Track> &track);

#endif