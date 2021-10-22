#include <iostream>
#include "matlib.h"
#include "geometry.h"
#include "testing.h"
#include "charts.h"
#include "PieChart.h"
#include "LineChart.h"
#include "CallOption.h"
#include "Polynomial.h"
using namespace std;

int main() {
	//setDebugEnabled(true);
	testMatlib();
	testGeometry();
	testCharts();
	testPieChart();
	testLineChart();
	testCallOption();
	testPolynomial();
	//setDebugEnabled(false);
	return 0;
}