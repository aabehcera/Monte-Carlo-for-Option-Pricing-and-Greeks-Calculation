#include "Header.hpp"

double normal(const double& x) {
    double k = 1.0 / (1.0 + 0.2316419 * x);
    double k_sum = k * (0.319381530 + k * (-0.356563782 + k * (1.781477937 + k * (-1.821255978 + 1.330274429 * k))));

    if (x >= 0.0) {
        return (1.0 - (1.0 / (pow(2 * M_PI, 0.5))) * exp(-0.5 * x * x) * k_sum);
    } else {
        return 1.0 - normal(-x);
    }
}

double ft_greek(std::string s, double S, double K, double r, double sigma, double T) {
    double d1;
    double d2;

    d1 = (log(S / K) + (r + sigma * sigma / 2) * T) / (sigma * sqrt(T));
    d2 = d1 - sigma * sqrt(T);

    if (s == "delta")
        return (normal(d1));
    if (s == "gamma")
        return (normal(d1) / (S * sigma * sqrt(T)));
    if (s == "theta")
        return (-(S * normal(d1) * sigma) / (2 * sqrt(T)) - r * K * exp(-r * T) * normal(d2));
    if (s == "vega")
        return (S * normal(d1) * sqrt(T));
    if (s == "rho")
        return (K * T * exp(-r * T) * normal(d2));
    else
        return (0);
}

void show_greek(double finale_1, double finale_2, double finale_3, double optionType) {
    double finale;

    if (optionType < 1) {
        finale = finale_1 - finale_3;
        std::cout << "The result of computing the greek is: " << finale << std::endl;
    } else if (optionType < 2) {
        finale = finale_3 - finale_1;
        std::cout << "The result of computing the greek is: " << finale << std::endl;
    } else {
        finale = finale_3 + finale_1 - 2 * finale_2;
        std::cout << "The result of computing the greek is: " << finale << std::endl;
    }
}