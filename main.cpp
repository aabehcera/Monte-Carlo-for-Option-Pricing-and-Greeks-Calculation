#include "Header.hpp"
#include "Monte-Carlo.cpp"
#include "Greeks.cpp"
#include "Data_Import.cpp"

int main() {
    // Importation of the data
    std::string name_csv = "AZN.csv"; // AstraZeneca PLC Stock price - Nasdaq
    std::cout << "Hello user, this program implements the price of 3 different options for the Astra Zeneca." << std::endl;
    std::cout << "*********************************************************************************" << std::endl;

    // Creating 2d array from csv file
    std::vector<std::vector<std::string>> data;
    importData(name_csv, data);

    float mean, stdev, r;
    computeStatistics(data, mean, stdev, r);

    int nScenarios, optionType;
    double S_t = 67; // current price
    double T, t;
    double sigma = stdev / S_t, strike1 = 72, strike2 = 67, strike3 = 62; // Explained in the PDF

    std::cout << "\nPlease type 1 for a bear spread call: ";
    std::cout << "\nPlease type 2 for a bull spread call: ";
    std::cout << "\nPlease type 3 for a butterfly call: ";
    std::cin >> optionType;
    while (optionType != 1 && optionType != 2 && optionType != 3) {
        std::cout << "Please type 1, 2, or 3 to choose the option type: ";
        std::cin >> optionType;
    }
    std::cout << "Please type the maturity T of the option in years: ";
    std::cin >> T;
    while (T <= 0 || T > 2.0) {
        std::cout << "Please type a positive number smaller than 2: ";
        std::cin >> T;
    }
    std::cout << "Please type the time when you want to price the option: ";
    std::cin >> t;
    while (t < 0 || t >= T) {
        std::cout << "Please type a positive number smaller than T: ";
        std::cin >> t;
    }

    std::cout << "Please type the number of simulations for the Monte Carlo method of pricing an option: ";
    std::cin >> nScenarios;
    while (nScenarios < 1000) {
        std::cout << "Please type an integer larger than 1000: ";
        std::cin >> nScenarios;
    }

    monteCarlo mC(nScenarios, S_t, T, t, r, sigma, strike1, strike2, strike3, optionType); // Monte Carlo class
    mC.sample(nScenarios, S_t, T, t, r, sigma);
    mC.run(nScenarios, S_t, T, t, r, sigma, strike1, strike2, strike3, optionType); // Simulation
    mC.show(nScenarios, S_t, T, t, r, sigma, strike1, strike2, strike3, optionType); // Results

    // Greeks part
    double* S_T;
    S_T = mC.sample(nScenarios, S_t, T, t, r, sigma); // Price for each scenario
    std::string greek;
    double finale_1 = 0, finale_2 = 0, finale_3 = 0;

    while (greek != "no") {
        std::cout << "Which Greek do you want to know? (delta, gamma, vega, theta, rho, no): ";
        std::cin >> greek;

        for (int i = 0; i < nScenarios; i++) {
            finale_1 += ft_greek(greek, S_T[i], strike1, r, sigma, T);
            finale_2 += ft_greek(greek, S_T[i], strike2, r, sigma, T);
            finale_3 += ft_greek(greek, S_T[i], strike3, r, sigma, T);
        }
        show_greek(finale_1 / nScenarios, finale_2 / nScenarios, finale_3 / nScenarios, optionType);
        finale_1 = 0;
        finale_2 = 0;
        finale_3 = 0;
    }

    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n*********************************************************************************";

    return 0;
}