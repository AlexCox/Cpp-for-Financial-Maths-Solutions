#include <iostream>
#include "matlib.h"
#include "geometry.h"
#include "testing.h"
#include "charts.h"
#include "PieChart.h"
#include "LineChart.h"
#include "Histogram.h"
#include "CallOption.h"
#include "Polynomial.h"
#include "MonteCarloPricer.h"
#include "UpAndOutOption.h"
#include "DownAndOutOption.h"
using namespace std;

int main() {
	//setDebugEnabled(true);
	testMatlib();
	testGeometry();
	testCharts();
	testPieChart();
	testLineChart();
	testHistogram();
	testCallOption();
	testPolynomial();
	testMonteCarloPricer();
	testUpAndOutOption();
	testDownAndOutOption();
	//setDebugEnabled(false);
	return 0;
}