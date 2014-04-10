#ifndef _TRACK_H
#define _TRACK_H
#include "Tools.h"
#include <vector>
#include <TTree.h>

struct Track {
	bool reconstructible_asLong;
	bool reconstructible_asUpstream;
	bool fromB;
	int pid;
	double true_p;
	double true_px;
	double true_py;
	double true_pt;
	double true_eta;
	int true_threeCharge;
	int nHits;
	int len;
	double x_hit;
	double y_min_hit;
	double y_max_hit;
	double z_hit;
	int planeCode;
	double x_UT;
	double x_velo;
	double y_velo;
	double z_velo;
	double tx_velo;
	double ty_velo;
	bool hasVelo;
	int vplen;
	double velo_x_hit;
	double velo_y_hit;
	double velo_z_hit;
};

bool isGood(const Track &track);
std::vector<Track> getTracks(TTree* tree);
void printTracks(const std::vector<Track> &track);

#endif