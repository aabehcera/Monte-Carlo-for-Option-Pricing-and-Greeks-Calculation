#include "Header.hpp"

monteCarlo::monteCarlo(int nScenarios, double S_t, double T, double t, double r, double sigma, double strike1, double strike2, double strike3, double optionType) {
    this->nScenarios = nScenarios;
    this->S_t = S_t;
    this->T = T;
    this->t = t;
    this->sigma = sigma;
    this->r = r;
    this->strike1 = strike1;
    this->strike2 = strike2;
    this->strike3 = strike3;
    this->optionType = optionType;
}

double* monteCarlo::sample(int nScenarios, double S_t, double T, int t, double r, double sigma) {
    double* randomS_T = new double[nScenarios];
    std::default_random_engine generator(std::time(0));

    for (int i = 0; i < nScenarios; i++) {
        std::normal_distribution<double> varGen1(0, 1);
        randomS_T[i] = S_t * exp((r - 0.5 * sigma * sigma) * (T - t)) * exp(sigma * sqrt(T - t) * varGen1(generator));
    }

    return randomS_T;
}

double* monteCarlo::run(int nScenarios, double S_T, double T, int t, double r, double sigma, double strike1, double strike2, double strike3, int optionType) {
    double sum = 0, vol = 0;
    double* a = sample(nScenarios, S_t, T, t, r, sigma);
    double* b = new double[nScenarios];
    double* results = new double[2];

    for (int i = 1; i < nScenarios; i++) {
        if (optionType == 1) {
            b[i] = exp(-r * (T - t)) * (std::max(a[i] - strike1, 0.0) + std::min(strike3 - a[i], 0.0));
        } else if (optionType == 2) {
            b[i] = exp(-r * (T - t)) * (std::max(a[i] - strike3, 0.0) + std::min(strike1 - a[i], 0.0));
        } else {
            b[i] = exp(-r * (T - t)) * (std::max(a[i] - strike3, 0.0) + 2 * std::min(strike2 - a[i], 0.0) + std::max(a[i] - strike1, 0.0));
        }
    }

    for (int i = 0; i < nScenarios; i++) {
        sum = sum + b[i];
    }
    results[0] = sum / nScenarios;

    for (int i = 0; i < nScenarios; i++) {
        vol = vol + pow(b[i] - (results[0]), 2);
    }
    results[1] = vol / (nScenarios - 1);

    return results;
}

double monteCarlo::show(int nScenarios, double S_t, double T, int t, double r, double sigma, double strike1, double strike2, double strike3, int optionType) {
    double* a = sample(nScenarios, S_t, T, t, r, sigma);
    double* b = run(nScenarios, S_t, T, t, r, sigma, strike1, strike2, strike3, optionType);

    for (int i = 0; i < nScenarios; i++) {
        std::cout << "The generated stock price is: " << a[i] << std::endl;
    }
    std::cout << "\n**********************************************" << std::endl;
    std::cout << "\n The price of the option is : " << b[0] << std::endl;
    std::cout << " The standard deviation is: " << b[1] << std::endl;
    std::cout << " The number of simulations: " << nScenarios << std::endl;
    std::cout << "\n**********************************************" << std::endl;

    return 0;
}