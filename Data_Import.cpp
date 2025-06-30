#include "Header.hpp"

void importData(std::string name_csv, std::vector<std::vector<std::string>>& data) {
    std::ifstream file(name_csv);
    
    if (file.is_open()) {
        std::string line, word;
        
        while (std::getline(file, line)) {
            std::vector<std::string> row;
            std::stringstream str(line);
            
            while (std::getline(str, word, ',')) {
                row.push_back(word);
            }
            data.push_back(row);
        }
        file.close();
    } else {
        std::cout << "Error: Unable to open file." << std::endl;
    }
}

void computeStatistics(const std::vector<std::vector<std::string>>& data, float& mean, float& stdev, float& r) {
    float sum = 0;
    
    for (int i = 0; i < data.size(); i++) {
        sum += std::stof(data[i][0]);
    }
    mean = sum / data.size();

    sum = 0;
    for (int i = 0; i < data.size(); i++) {
        sum += pow((std::stof(data[i][0]) - mean), 2);
    }
    stdev = sqrt(sum / (data.size() - 1));

    float bond = 0.03456, inflation = 0.0327; 
    r = (1 + bond) / (1 + inflation) - 1; // Risk-free interest rate
}