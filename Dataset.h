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

    Dataset(QJsonArray JSONdataset) : JSONdataset(JSONdataset) {
        fillDatasetFromJson();
        std::sort(dataset.begin(), dataset.end());
    }



    void debugDataset() {
        qDebug() << "Dataset:";
        for (const auto& value : JSONdataset) {
            if (value.isDouble()) {
                JSONdataset.push_back(value.toDouble());
            }else if (value.isString()) {
                qDebug() << value.toString();
            } else {
                qDebug() << "Unknown type";
            } ;

        }
    }



    void fillDatasetFromJson() {
        for (const auto& value : JSONdataset) {
            if (value.isDouble()) {
                dataset.push_back(value.toDouble());
            } else if (isIntegral(value)) {
                dataset.push_back(value.toInt());
            } else {
                qWarning() << "Unsupported data type in JSON array";
            }
        }
    }




    double minValue() const {
        double min = std::numeric_limits<double>::infinity();
        for (const auto& value : dataset) {
            double current = toDouble(value);
            if (current < min) {
                min = current;
            }
        }
        return min;
    }



    double maxValue() const {
        double max = -std::numeric_limits<double>::infinity();
        for (const auto& value : dataset) {
            double current = toDouble(value);
            if (current > max) {
                max = current;
            }
        }
        return max;
    }



    double meanValue() const {
        double xSum = 0.0;
        for (int i = 0; i < dataset.size(); ++i) {
            xSum += toDouble(dataset[i]);
        }
        return xSum / dataset.size();
    }



    double medianValue() const {
        int n = dataset.size();
        if (n % 2 == 0) {
            return (toDouble(dataset[n/2]) + toDouble(dataset[n/2 - 1])) / 2.0;
        } else {
            return toDouble(dataset[n/2]);
        }
    }



    double standardDeviationValue() const {
        double xMean = this->meanValue();
        double xVar = 0.0;
        for (int i = 0; i < dataset.size(); ++i) {
            xVar += pow(toDouble(dataset[i]) - xMean, 2.0);
        }
        xVar /= dataset.size() - 1;
        return sqrt(xVar);
    }



    double varianceValue() const {
        double mean = meanValue();
        double sum = 0;
        for (const auto& value : dataset) {
            double diff = toDouble(value) - mean;
            sum += diff * diff;
        }
        return sum / (dataset.size() - 1);
    }



    bool isIntegral(double d) {
        return std::floor(d) == d;
    }



    bool isIntegral(QJsonValueRef value)
    {
        if (value.isDouble()) {
            double d = value.toDouble();
            return std::floor(d) == d;
        } else if (value.isString()) {
            bool ok;
            double d = value.toString().toDouble(&ok);
            return ok && std::floor(d) == d;
        } else if (value.isBool() || value.isNull()) {
            return true;
        } else if (value.isObject() || value.isArray()) {
            return false;
        } else {
            return false;
        }
    }



    double toDouble (const std::variant<int, double>& value) const {
        if (std::holds_alternative<int>(value)) {
            return static_cast<double>(std::get<int>(value));
        } else {
            return std::get<double>(value);
        }
    }
};

#endif // DATASET_H
