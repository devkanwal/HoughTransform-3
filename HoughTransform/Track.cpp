#include "Track.h"

bool isGood(const Track &track) {
	return (track.reconstructible_asLong  // long track
		&& track.true_p > 3000            //     # min momentum
		&& track.true_pt > 500           //       # min transverse momentum (momentum perpendicular to the beam pipe - aka physics happened)
		&& track.true_eta > 2             //       # pseudorapidity (spatial coordinate describing the angle of a particle relative to the beam axis) range 
		&& track.true_eta < 5            //        # 
		&& abs(track.pid) != 22           //      # not an electron/positron
		&& track.fromB);
}

void printTracks(const std::vector<Track> &track) {
	std::cout << "x_velo\t" << "y_velo\t" << "z_velo\t" << std::endl;
	for (uint i = 0; i<track.size(); i++) {
		std::cout << track[i].x_velo << "\t" << track[i].y_velo << "\t" << track[i].z_velo << std::endl;
	}
}

std::vector<Track> getTracks(TTree* tree) {
	std::vector<Track> tracks(tree->GetEntries());
	static Track t;
	tree->SetBranchAddress("reconstructible_asLong",&t.reconstructible_asLong);
	tree->SetBranchAddress("reconstructible_asUpstream",&t.reconstructible_asUpstream);
	tree->SetBranchAddress("fromB",&t.fromB);
	tree->SetBranchAddress("x_velo",&t.x_velo);
	tree->SetBranchAddress("y_velo",&t.y_velo);
	tree->SetBranchAddress("z_velo",&t.z_velo);
	for (unsigned long i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);
		tracks[i] = t;
	}
	return tracks;
}
