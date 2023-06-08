#ifndef DATASET_H
#define DATASET_H
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QtCore>
#include <cmath>
#include <algorithm>
//#include <variant>

class Dataset {

public:

    std::vector<std::variant<int, double>> dataset;
    Dataset(std::vector<std::variant<int, double>> dataset);
    Dataset() = default;

    std::variant<int, double> at(int index){
        return dataset[index];
    }

    double minValue() const;
    double maxValue() const;
    double meanValue() const;
    double medianValue() const;
    double standardDeviationValue() const;
    double varianceValue() const;

    bool isInteger(double d);
    bool isInteger(QJsonValue value);
 };

#endif // DATASET_H
