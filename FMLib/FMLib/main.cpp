#include <iostream>
#include "matlib.h"
using namespace std;

int main() {
	cout << "normcdf(1.96)=" << normcdf(1.96) << endl;
	cout << "norminv(0.975)=" << norminv(0.975) << endl;

	return 0;
}