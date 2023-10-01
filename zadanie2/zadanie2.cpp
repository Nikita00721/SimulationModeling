#include <iostream>
#include <random>
#include <vector>
#include <cmath>
#include <iomanip>

// Реализация Линейного конгруэнтного метода
class LinearCongruentialGenerator {
private:
    uint32_t seed;
    const uint32_t a = 1664525;
    const uint32_t c = 1013904223;
    const uint32_t m = 0xFFFFFFFF;

public:
    LinearCongruentialGenerator(uint32_t initialSeed) : seed(initialSeed) {}

    // Генерация случайного числа
    uint32_t generate() {
        seed = (a * seed + c) % m;
        return seed;
    }

    // Получение значения m
    uint32_t getM() const {
        return m;
    }
};

// Функция для проведения графического теста
void graphicalTest(std::vector<double>& data) {
    // Гистограмма для оценки равномерности распределения
    const int numBins = 10;
    std::vector<int> histogram(numBins, 0);
    double min = *min_element(data.begin(), data.end());
    double max = *max_element(data.begin(), data.end());

    for (double value : data) {
        int bin;
        if (max != min) {
            bin = static_cast<int>((value - min) / (max - min) * numBins);
        }
        else {
            bin = 0; // Если max и min равны, то bin 0
        }
        if (bin < 0) {
            bin = 0;
        }
        else if (bin >= numBins) {
            bin = numBins - 1;
        }

        histogram[bin]++; // Все эти проверки нужны для обработки исключения улетания в 0
    }

    // Вывод гистограммы
    std::cout << "Гистограмма равномерности распределения:" << std::endl;
    int maxCount = *max_element(histogram.begin(), histogram.end());
    for (int i = 0; i < numBins; i++) {
        double binStart = min + i * (max - min) / numBins;
        double binEnd = min + (i + 1) * (max - min) / numBins;

        std::cout << "[" << std::fixed << std::setprecision(2) << binStart << ", " << binEnd << "]: ";

        int barLength = static_cast<int>(static_cast<double>(histogram[i]) / maxCount * 40); // Ширина столбца
        for (int j = 0; j < barLength; j++) {
            std::cout << "*";
        }

        std::cout << " " << histogram[i] << std::endl;
    }
}


void chiSquareTest(std::vector<double>& data, int numBins) {
    // Гистограмма для оценки равномерности распределения
    std::vector<int> histogram(numBins, 0);
    double min = *min_element(data.begin(), data.end());
    double max = *max_element(data.begin(), data.end());

    for (double value : data) {
        int bin;
        if (max != min) {
            bin = static_cast<int>((value - min) / (max - min) * numBins);
        }
        else {
            bin = 0; // Если max и min равны, то bin 0
        }
        if (bin < 0) {
            bin = 0;
        }
        else if (bin >= numBins) {
            bin = numBins - 1;
        }

        histogram[bin]++;
    }

    // Статистическое тестирование (тест хи-квадрат)
    double chiSquared = 0.0;
    double expectedFrequency = static_cast<double>(data.size()) / numBins;
    for (int i = 0; i < numBins; i++) {
        chiSquared += pow(histogram[i] - expectedFrequency, 2) / expectedFrequency;
    }

    int degreesOfFreedom = numBins - 1; // Степени свободы (число интервалов - 1)
    double significanceLevel = 0.05; // Уровень значимости
    double chiSquaredTable(int degreesOfFreedom, double significanceLevel);

    // Вычисление критического значения из таблицы хи-квадрат для заданного уровня значимости и степеней свободы
    double criticalValue = chiSquaredTable(degreesOfFreedom, significanceLevel);

    std::cout << "Статистический тест хи-квадрат:" << std::endl;
    std::cout << "Значение хи-квадрат: " << chiSquared << std::endl;
    std::cout << "Степени свободы: " << degreesOfFreedom << std::endl;
    std::cout << "Критическое значение: " << criticalValue << std::endl;

    if (chiSquared <= criticalValue) {
        std::cout << "Тест пройден. Распределение является равномерным." << std::endl;
    }
    else {
        std::cout << "Тест не пройден. Распределение не является равномерным." << std::endl;
    }
}

double chiSquaredTable(int degreesOfFreedom, double significanceLevel) {
    if (degreesOfFreedom >= 1 && significanceLevel == 0.05) { // Таблицу взял из интернета, степеней свободы при данных условиях 9
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

    // Инициализация Линейного конгруэнтного генератора
    LinearCongruentialGenerator lcg(12345);

    // Генерация случайных чисел
    for (int i = 0; i < numSamples; i++) {
        double randomValue = static_cast<double>(lcg.generate()) / static_cast<double>(lcg.getM());
        generatedValues.push_back(randomValue);
    }

    std::cout << "Тестирование Линейного конгруэнтного генератора:" << std::endl;
    // Графический тест
    graphicalTest(generatedValues);

    // Проведение теста хи-квадрат
    int numBins = 10; // Количество интервалов в гистограмме
    chiSquareTest(generatedValues, numBins);

    // Используем библиотечный генератор
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(0.0, 1.0);
    std::vector<double> libraryGeneratedValues;

    // Генерация случайных чисел с использованием библиотечного генератора
    for (int i = 0; i < numSamples; i++) {
        double randomValue = dist(mt);
        libraryGeneratedValues.push_back(randomValue);
    }

    std::cout << "Тестирование библиотечного генератора:" << std::endl;
    // Графический тест для библиотечного генератора
    graphicalTest(libraryGeneratedValues);

    // Проведение теста хи-квадрат для библиотечного генератора
    chiSquareTest(libraryGeneratedValues, numBins);

    return 0;
}