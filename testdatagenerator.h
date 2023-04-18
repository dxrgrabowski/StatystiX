#ifndef TESTDATAGENERATOR_H
#define TESTDATAGENERATOR_H

#include <QtCore/QCoreApplication>
#include <QtCore/QJsonArray>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QFile>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>

class TestDataGenerator
{
public:
    TestDataGenerator(int minValue, int maxValue, int dataSize);

    virtual void generateTestData(const QString& fileName) = 0;

protected:
    int m_minValue;
    int m_maxValue;
    int m_dataSize;
};



class JsonTestDataGenerator : public TestDataGenerator
{
public:
    JsonTestDataGenerator(int minValue, int maxValue, int dataSize)
        : TestDataGenerator(minValue, maxValue, dataSize)
    {
    }

    void generateTestData(const QString& fileName) override;
};


class CsvTestDataGenerator : public TestDataGenerator
{
public:
    CsvTestDataGenerator(int minValue, int maxValue, int dataSize)
        : TestDataGenerator(minValue, maxValue, dataSize)
    {
    }

    void generateTestData(const QString& fileName) override;
};

#endif // TESTDATAGENERATOR_H
