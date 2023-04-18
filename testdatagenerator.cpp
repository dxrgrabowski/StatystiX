#include "testdatagenerator.h"


TestDataGenerator::TestDataGenerator(int minValue, int maxValue, int dataSize)
    : m_minValue(minValue), m_maxValue(maxValue), m_dataSize(dataSize)
{

}



void CsvTestDataGenerator::generateTestData(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << fileName;
        return;
    }

    QStringList headers = { "Value" };
    file.write(headers.join(",").toUtf8());
    file.write("\n");

    QRandomGenerator randomGenerator;

    for (int i = 0; i < m_dataSize; i++)
    {
        int randomNumber = randomGenerator.bounded(m_minValue, m_maxValue + 1);
        file.write(QString::number(randomNumber).toUtf8());
        file.write("\n");
    }

    file.close();
}


void JsonTestDataGenerator::generateTestData(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file for writing:" << fileName;
        return;
    }

    QJsonObject jsonObject;
    jsonObject.insert("dataSize", m_dataSize);

    QRandomGenerator randomGenerator;
    QJsonArray dataArray;
    for (int i = 0; i < m_dataSize; i++)
    {
        int randomNumber = randomGenerator.bounded(m_minValue, m_maxValue + 1);
        dataArray.append(randomNumber);
    }

    jsonObject.insert("data", dataArray);

    QJsonDocument jsonDocument(jsonObject);
    file.write(jsonDocument.toJson());
    file.close();
}


