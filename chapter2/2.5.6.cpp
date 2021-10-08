#include <iostream>
#include <cmath>
using namespace std;

int roundDecimal(double d) {
	int decimal = (int)d;
	if (d - decimal >= 0.5) {
		return decimal + 1;
	}
	else {
		return decimal;
	}
}

int main() {
    cout << "Using roundDecimal function" << endl;
    cout << "5.1 rounds to " << roundDecimal(5.1) << endl;
    cout << "10.5 rounds to " << roundDecimal(10.5) << endl;
    cout << "Using inbuilt round function from cmath" << endl;
    cout << "5.1 rounds to " << round(5.1) << endl;
    cout << "10.5 rounds to " << round(10.5) << endl;
    
    return 0;
}