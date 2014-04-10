#include "Events.h"
#include "Track.h"

Events getEvents(TTree* tree) {
	Events events;
	static Track t;
	tree->SetBranchAddress("reconstructible_asLong",&t.reconstructible_asLong);
	tree->SetBranchAddress("reconstructible_asUpstream",&t.reconstructible_asUpstream);
	tree->SetBranchAddress("fromB",&t.fromB);
	tree->SetBranchAddress("pid",&t.pid);
	tree->SetBranchAddress("true_p",&t.true_p);
	tree->SetBranchAddress("true_px",&t.true_px);
	tree->SetBranchAddress("true_py",&t.true_py);
	tree->SetBranchAddress("true_pt",&t.true_pt);
	tree->SetBranchAddress("true_eta",&t.true_eta);
	tree->SetBranchAddress("true_threeCharge",&t.true_threeCharge);
	tree->SetBranchAddress("nHits",&t.nHits);
	tree->SetBranchAddress("len",&t.len);
	tree->SetBranchAddress("x_hit",&t.x_hit);
	tree->SetBranchAddress("y_min_hit",&t.y_min_hit);
	tree->SetBranchAddress("y_max_hit",&t.y_max_hit);
	tree->SetBranchAddress("z_hit",&t.z_hit);
	tree->SetBranchAddress("planeCode",&t.planeCode);
	tree->SetBranchAddress("x_UT",&t.x_UT);
	tree->SetBranchAddress("x_velo",&t.x_velo);
	tree->SetBranchAddress("y_velo",&t.y_velo);
	tree->SetBranchAddress("z_velo",&t.z_velo);
	tree->SetBranchAddress("tx_velo",&t.tx_velo);
	tree->SetBranchAddress("ty_velo",&t.ty_velo);
	tree->SetBranchAddress("hasVelo",&t.hasVelo);
	tree->SetBranchAddress("vplen",&t.vplen);
	tree->SetBranchAddress("velo_x_hit",&t.velo_x_hit);
	tree->SetBranchAddress("velo_y_hit",&t.velo_y_hit);
	tree->SetBranchAddress("velo_z_hit",&t.velo_z_hit);

	for (unsigned long i=0; i<tree->GetEntries(); i++) {
		tree->GetEntry(i);
		if (isGood(t)) {
			events.velo_x_hit.push_back(t.velo_x_hit);
			events.velo_y_hit.push_back(t.velo_y_hit);
			events.velo_z_hit.push_back(t.velo_z_hit);
		}
	}

	return events;
}

void print(const Events &events) {
	std::cout << "x_velo     \t" << "y_velo     \t" << "z_velo     \t" << std::endl;
	for (uint i = 0; i<events.velo_x_hit.size(); i++) {
		std::cout << events.velo_x_hit[i] << "   \t" << events.velo_y_hit[i] << "   \t" << events.velo_z_hit[i] << std::endl;
	}
}