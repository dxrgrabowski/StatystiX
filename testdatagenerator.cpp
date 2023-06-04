#include "testdatagenerator.h"


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
    stream << "x,y\n";  // Nagłówki

    QRandomGenerator randomGenerator;

    for (int i = 0; i < this->m_dataSize; i++)
    {
        int randomNumberX = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);
        int randomNumberY = randomGenerator.bounded(this->m_minValue, this->m_maxValue + 1);

        stream << QString::number(randomNumberX) << "," << QString::number(randomNumberY) << "\n";
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


