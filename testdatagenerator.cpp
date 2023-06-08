#include "testdatagenerator.h"
#include <algorithm>
#include <ranges>

TestDataGenerator::TestDataGenerator()
{
}

void TestDataGenerator::generateCsvTestData()
{
    QFile file(this->filePath + "/testdata.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << filePath + "/testdata.csv";
        return;
    }

    QTextStream stream(&file);
    stream << "x;y\n";

    QRandomGenerator randomGenerator;

    for (int i = 0; i < this->m_dataSize; i++)
    {
        int randomNumberX = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);
        int randomNumberY = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);
        stream << randomNumberX << ";" << randomNumberY << "\n";
    }

    file.close();
}

void TestDataGenerator::generateJsonTestData()
{
    QFile file(this->filePath + "/testdata.json");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << filePath + "/testdata.json";
        return;
    }

    QJsonObject jsonObject;

    QRandomGenerator randomGenerator;
    QJsonArray xArray, yArray;

    for (int i = 0; i < this->m_dataSize; i++)
    {
        int randomNumber = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);
        xArray.append(randomNumber);

        randomNumber = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);
        yArray.append(randomNumber);
    }
    jsonObject.insert("x", xArray);
    jsonObject.insert("y", yArray);

    QJsonDocument jsonDocument(jsonObject);
    file.write(jsonDocument.toJson());
    file.close();
}

void TestDataGenerator::generateNormalDistributionTestData()
{
    QFile file(this->filePath + "/testdata.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << filePath + "/testdata.csv";
        return;
    }

    QTextStream stream(&file);
    stream << "x;y\n";

    QRandomGenerator randomGenerator;

    // Parametry rozkładu normalnego
    double mean = (this->m_maxValue + this->m_minValue) / 2.0;
    double stddev = (this->m_maxValue - this->m_minValue) / 6.0; // Przykładowe odchylenie standardowe, można dostosować

    for (int i = 0; i < this->m_dataSize; i++)
    {
        double x = i * 1.0; // Inkrementacja wartości x
        double randomNumberY = randomGenerator.generateDouble(); // Losowa liczba z zakresu (0, 1)
        double y = mean + stddev * qSqrt(-2 * qLn(randomNumberY)); // Wyliczenie wartości y na podstawie rozkładu normalnego

        // Ograniczenie wartości y do zakresu [m_minValue, m_maxValue]
        y = std::max((int)y, this->m_minValue);
        y = std::min((int)y, this->m_maxValue);

        stream << x << ";" << y << "\n";
    }

    file.close();
}

void TestDataGenerator::generateRangesDistributionTestData()
{
    QFile file(this->filePath + "/testdata.csv");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << filePath + "/testdata.csv";
        return;
    }

    QTextStream stream(&file);
    stream << "x;y\n";

    // Parametry rozkładu normalnego
    double mean = (this->m_maxValue + this->m_minValue) / 2.0;
    double stddev = (this->m_maxValue - this->m_minValue) / 6.0;

    auto randomGenerator = std::views::iota(0)
                           | std::views::transform([mean, stddev](int i) {
                                 double randomNumberY = static_cast<double>(std::rand()) / RAND_MAX;
                                 return mean + stddev * std::sqrt(-2 * std::log(randomNumberY));
                             })
                           | std::views::transform([this](double y) {
                                 return std::clamp((int)y, this->m_minValue, this->m_maxValue);
                             });

    for (double x : randomGenerator | std::views::take(this->m_dataSize))
    {
        stream << x << ";" << x << "\n";

        // Alternatywnie:
        // double y = *it;
        // file << x << ";" << y << "\n";
    }

    file.close();
}

