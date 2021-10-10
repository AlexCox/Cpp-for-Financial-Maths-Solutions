#include <iostream>
#include "matlib.h"
#include "geometry.h"
#include "testing.h"
using namespace std;

int main() {
	//setDebugEnabled(true);
	testMatlib();
	testGeometry();
	//setDebugEnabled(false);
	return 0;
}