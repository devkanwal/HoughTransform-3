/* A General library of often used functions such as random numbers, waiting for enter */

#include <random>

class Tools {

public:
	static double returnRandomD(double start, double end) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(start,end);
		return dis(gen);
	}

	static int returnRandomI(int start, int end) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(start,end);
		return dis(gen);
	}

	static void PressEnterToContinue() {
		int c;
		printf( "Press ENTER to continue... " );
		fflush( stdout );
		do c = getchar(); while ((c != '\n') && (c != EOF));
  }
};