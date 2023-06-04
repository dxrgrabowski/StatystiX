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
    TestDataGenerator();

    int m_dataSize = NULL;
    int m_minValue;
    int m_maxValue;
    QString filePath;

    QString state = "NULL";

    void generateJsonTestData();
    void generateCsvTestData();
};

#endif // TESTDATAGENERATOR_H
