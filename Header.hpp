#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <random>
#include <ctime>

class monteCarlo {
public:
    monteCarlo(int nScenarios, double S_t, double T, double t, double r, double sigma, double strike1, double strike2, double strike3, double optionType);

    double* sample(int nScenarios, double S_t, double T, int t, double r, double sigma);

    double* run(int nScenarios, double S_T, double T, int t, double r, double sigma, double strike1, double strike2, double strike3, int optionType);

    double show(int nScenarios, double S_t, double T, int t, double r, double sigma, double strike1, double strike2, double strike3, int optionType);

private:
    int nScenarios, optionType;
    double S_t, r, sigma, strike1, strike2, strike3, t, T;
};

double normal(const double& x);

double ft_greek(std::string s, double S, double K, double r, double sigma, double T);

void show_greek(double finale_1, double finale_2, double finale_3, double optionType);

#endif // HEADER_HPP