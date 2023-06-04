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

        QJsonArray JSONdataset;

        std::vector<std::variant<int, double>> dataset;

        public:

        Dataset(QJsonArray JSONdataset);


        void debugDataset();
        void fillDatasetFromJson();


        double minValue() const;
        double maxValue() const;
        double meanValue() const;
        double medianValue() const;
        double standardDeviationValue() const;
        double varianceValue() const;

        bool isInteger(double d);
        bool isInteger(QJsonValue value);
        double toDouble (const std::variant<int, double>& value) const;
    };

#endif // DATASET_H
