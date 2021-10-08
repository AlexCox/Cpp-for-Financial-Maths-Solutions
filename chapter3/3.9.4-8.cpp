#include <iostream>
#include <cmath>
using namespace std;

// Save computation time in normcdf function
const double root2pi = sqrt(2.0 * 3.14159265359);

// Constants for Moro algorithm 
const double a0 = 2.50662823884;
const double a1 = -18.61500062529;
const double a2 = 41.39119773534;
const double a3 = -25.44106049637;
const double b1 = -8.47351093090;
const double b2 = 23.08336743743;
const double b3 = -21.06224101826;
const double b4 = 3.13082909833;
const double c0 = 0.3374754822726147;
const double c1 = 0.9761690190917186;
const double c2 = 0.1607979714918209;
const double c3 = 0.0276438810333863;
const double c4 = 0.0038405729373609;
const double c5 = 0.0003951896511919;
const double c6 = 0.0000321767881768;
const double c7 = 0.0000002888167364;
const double c8 = 0.0000003960315187;

double hornerFunction(double x, double a) {
    return a;
}

double hornerFunction(double x, double a, double b) {
    return a + x * hornerFunction(x, b);
}

double hornerFunction(double x, double a, double b, double c) {
    return a + x * hornerFunction(x, b, c);
}

double hornerFunction(double x, double a, double b, double c, double d) {
    return a + x * hornerFunction(x, b, c, d);
}

double hornerFunction(double x, double a, double b, double c, double d, double e) {
    return a + x * hornerFunction(x, b, c, d, e);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f) {
    return a + x * hornerFunction(x, b, c, d, e, f);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g) {
    return a + x * hornerFunction(x, b, c, d, e, f, g);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g,
    double h) {
    return a + x * hornerFunction(x, b, c, d, e, f, g, h);
}

double hornerFunction(double x, double a, double b, double c, double d, double e, double f, double g,
    double h, double i) {
    return a + x * hornerFunction(x, b, c, d, e, f, g, h, i);
}

double normcdf(double x) {
    if (x < 0) {
        return 1 - normcdf(-x);
    }

    double k = 1.0 / (1.0 + 0.2316419 * x);

    return 1.0 - (1.0 / root2pi) * exp(-0.5 * x * x) * k * (0.319381530 +
        k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + k * (1.330274429)))));
}

double normcdfHorner(double x) {
    if (x < 0) {
        return 1.0 - normcdf(-x);
    }

    double k = 1 / (1 + 0.2316419 * x);

    return 1.0 - (1.0 / root2pi) * exp(-0.5 * x * x) *
        hornerFunction(k, 0, 0.319381530, -0.356563782, 1.781477937,
            -1.821255978, 1.330274429);
}

double norminv(double x) {
    // Moro algorithm
    double y = x - 0.5;
    if (abs(y) < 0.42) {
        double r = y * y;
        return y * hornerFunction(r, a0, a1, a2, a3) /
            hornerFunction(r, 1.0, b1, b2, b3, b4);
    }
    else {
        double r;
        if (y > 0) {
            r = 1.0 - x;
        }
        else {
            r = x;
        }
        double s = log(-log(r));
        double t = hornerFunction(s, c0, c1, c2, c3, c4, c5, c6, c7, c8);
        if (x > 0.5) {
            return t;
        }
        else {
            return -t;
        }
    }
}

double blackScholesCallPrice(double strike, double timeToMaturity,
    double spot, double volatility, double rfRate) {
    double denominator = volatility * sqrt(timeToMaturity);
    double d1 = (log(spot / strike) + (rfRate + 0.5 * volatility * volatility) * timeToMaturity) / denominator;
    double d2 = d1 - denominator;
    return normcdfHorner(d1) * spot - normcdf(d2) * strike * exp(-rfRate * timeToMaturity);
}

int main() {
    cout << "Testing normcdf and norminv, values should be approx 0.0 through 1.0 in 0.1 increments" << endl;
    for (double i = 0.0; i < 1; i += 0.1) {
        cout << norminv(normcdfHorner(i)) << endl;
    }

    cout << "Test pricing an option using our blackScholesCallPrice method. The expected value is 11.677." << endl;
    double strike = 100.0;
    double timeToMaturity = 0.5;
    double spot = 110.0;
    double volatility = 0.1;
    double rfRate = 0.03;
    cout << "Output: " << blackScholesCallPrice(strike, timeToMaturity, spot, volatility, rfRate) << endl;

    return 0;
}