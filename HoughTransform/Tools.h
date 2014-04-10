#ifndef _TOOLS_H
#define _TOOLS_H
#include "Track.h"
#include <vector>
#include <TTree.h>
#include <iostream>
/* Define _USE_MATH_DEFINES before including math.h to expose these macro
* definitions for common math constants.  These are placed under an #ifdef
* since these commonly-defined names are not part of the C/C++ standards.
*/

#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>
#include <TH2F.h>
#include <TF1.h>
#include <TGraph.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TTree.h>
#include <boost/assign/std/vector.hpp>

typedef unsigned int uint;

double round(double d);
double get_minimum(std::vector<double> x);
double get_maximum(std::vector<double> x);

#endif