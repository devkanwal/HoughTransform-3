#include "Tools.h"
#include "HT.h"

using namespace boost::assign;

int main(int argc, char *argv[]) {

	int FLAG;
	std::cout << "Enter 1 to run Data from Rootfile, press 0 to run Data from trivial example" << std::endl;
	std::cin >> FLAG;
	TApplication theApp("App",&argc,argv);

	if (FLAG == 1) {


		TFile* file = new TFile("UTHits.root");
		TTree* tree = (TTree*) file->Get("UTHits/MatchedTracks");
		std::vector<Track> tracks = getTracks(tree);
		printTracks(tracks);

			//int threshold = 10;
			//HT(y,z,threshold); // or HT(x,z);
			theApp.Run();
	}
	else if (FLAG == 0) {
		std::vector<double> x,y;
		x += 4.0,3.2,1.8,1.0,1.0,2.0,3.0,1.0,4.0,2.7;
		y += 4.0,3.2,1.8,1.0,3.5,2.5,1.5,5.0,1.2,4.1;
		int threshold = 3;
		HT(x,y,threshold);	
		theApp.Run();
	}

	return 0;
}
