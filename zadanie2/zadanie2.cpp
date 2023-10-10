#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <iomanip>

class RandomNumberGenerator {
private:
    uint32_t seed;
    const uint32_t multiplier = 1664525;
    const uint32_t increment = 1013904223;
    const uint32_t modulus = 0xFFFFFFFF;

public:
    RandomNumberGenerator(uint32_t initialSeed) : seed(initialSeed) {}

    uint32_t generate() {
        seed = (multiplier * seed + increment) % modulus;
        return seed;
    }

    uint32_t getModulus() const {
        return modulus;
    }
};

void visualizeDistribution(std::vector<double>& data) {
    const int numBins = 10;
    std::vector<int> histogram(numBins, 0);
    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());

    for (double value : data) {
        int bin;
        if (maxVal != minVal) {
            bin = static_cast<int>((value - minVal) / (maxVal - minVal) * numBins);
        }
        else {
            bin = 0;
        }
        if (bin < 0) {
            bin = 0;
        }
        else if (bin >= numBins) {
            bin = numBins - 1;
        }

        histogram[bin]++;
    }

    std::cout << "Гистограмма распределения:" << std::endl;
    int maxCount = *max_element(histogram.begin(), histogram.end());
    for (int i = 0; i < numBins; i++) {
        double binStart = minVal + i * (maxVal - minVal) / numBins;
        double binEnd = minVal + (i + 1) * (maxVal - minVal) / numBins;

        std::cout << "[" << std::fixed << std::setprecision(2) << binStart << ", " << binEnd << "]: ";

        int barLength = static_cast<int>(static_cast<double>(histogram[i]) / maxCount * 40);
        for (int j = 0; j < barLength; j++) {
            std::cout << "*";
        }

        std::cout << " " << histogram[i] << std::endl;
    }
}

void chiSquareStatisticalTest(std::vector<double>& data, int numBins) {
    std::vector<int> histogram(numBins, 0);
    double minVal = *min_element(data.begin(), data.end());
    double maxVal = *max_element(data.begin(), data.end());

    for (double value : data) {
        int bin;
        if (maxVal != minVal) {
            bin = static_cast<int>((value - minVal) / (maxVal - minVal) * numBins);
        }
        else {
            bin = 0;
        }
        if (bin < 0) {
            bin = 0;
        }
        else if (bin >= numBins) {
            bin = numBins - 1;
        }

        histogram[bin]++;
    }

    double chiSquaredValue = 0.0;
    double expectedFrequency = static_cast<double>(data.size()) / numBins;
    for (int i = 0; i < numBins; i++) {
        chiSquaredValue += pow(histogram[i] - expectedFrequency, 2) / expectedFrequency;
    }

    int degreesOfFreedom = numBins - 1;
    double significanceLevel = 0.05;
    double lookupChiSquared(int degreesOfFreedom, double significanceLevel);

    double criticalValue = lookupChiSquared(degreesOfFreedom, significanceLevel);

    std::cout << "Статистический тест хи-квадрат:" << std::endl;
    std::cout << "Значение хи-квадрат: " << chiSquaredValue << std::endl;
    std::cout << "Степени свободы: " << degreesOfFreedom << std::endl;
    std::cout << "Критическое значение: " << criticalValue << std::endl;

    if (chiSquaredValue <= criticalValue) {
        std::cout << "Тест пройден. Распределение равномерное." << std::endl;
    }
    else {
        std::cout << "Тест не пройден. Распределение не равномерное." << std::endl;
    }
}

double lookupChiSquared(int degreesOfFreedom, double significanceLevel) {
    if (degreesOfFreedom >= 1 && significanceLevel == 0.05) {
        switch (degreesOfFreedom) {
        case 1: return 3.841;
        case 2: return 5.991;
        case 3: return 7.815;
        case 4: return 9.488;
        case 5: return 11.070;
        case 6: return 12.592;
        case 7: return 14.067;
        case 8: return 15.507;
        case 9: return 16.919;
        default: return 0.0;
        }
    }
    else {
        return 0.0;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    const int numSamples = 10000;
    std::vector<double> generatedValues;

    RandomNumberGenerator rng(12345);

    for (int i = 0; i < numSamples; i++) {
        double randomValue = static_cast<double>(rng.generate()) / static_cast<double>(rng.getModulus());
        generatedValues.push_back(randomValue);
    }

    std::cout << "Тестирование генератора случайных чисел:" << std::endl;
    visualizeDistribution(generatedValues);

    int numBins = 10;
    chiSquareStatisticalTest(generatedValues, numBins);

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<double> libraryGeneratedValues;

    for (int i = 0; i < numSamples; i++) {
        double randomValue = dist(mt);
        libraryGeneratedValues.push_back(randomValue);
    }

    std::cout << "Тестирование библиотечного генератора случайных чисел:" << std::endl;
    visualizeDistribution(libraryGeneratedValues);
    chiSquareStatisticalTest(libraryGeneratedValues, numBins);

    return 0;
}
