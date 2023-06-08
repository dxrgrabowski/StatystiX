#include "dataset.h"
#include <iostream>

Dataset::Dataset(std::vector<std::variant<int, double>> dataset) : dataset(dataset) {
    std::sort(dataset.begin(), dataset.end());
}

double Dataset::minValue() const {
    double min = std::numeric_limits<double>::infinity();
    for (const auto& value : dataset) {
        if (std::holds_alternative<int>(value)) {
            int intValue = std::get<int>(value);
            double current = static_cast<double>(intValue);
            if (current < min) {
                min = current;
            }
        } else if (std::holds_alternative<double>(value)) {
            double current = std::get<double>(value);
            if (current < min) {
                min = current;
            }
        }
    }
    return min;
}
double Dataset::maxValue() const {
    double max = -std::numeric_limits<double>::infinity();
    for (const auto& value : dataset) {
        if (std::holds_alternative<int>(value)) {
            int intValue = std::get<int>(value);
            double current = static_cast<double>(intValue);
            if (current > max) {
                max = current;
            }
        } else if (std::holds_alternative<double>(value)) {
            double current = std::get<double>(value);
            if (current > max) {
                max = current;
            }
        }
    }
    return max;
}


double Dataset::meanValue() const {
    double sum = 0.0;
    size_t count = 0;
    for (const auto& value : dataset) {
        if (std::holds_alternative<int>(value)) {
            int intValue = std::get<int>(value);
            sum += static_cast<double>(intValue);
            ++count;
        } else if (std::holds_alternative<double>(value)) {
            sum += std::get<double>(value);
            ++count;
        }
    }
    return count > 0 ? sum / count : 0.0;
}

double Dataset::medianValue() const {
    std::vector<double> values;
    for (const auto& value : dataset) {
        if (std::holds_alternative<int>(value)) {
            int intValue = std::get<int>(value);
            values.push_back(static_cast<double>(intValue));
        } else if (std::holds_alternative<double>(value)) {
            values.push_back(std::get<double>(value));
        }
    }
    std::sort(values.begin(), values.end());
    size_t n = values.size();
    if (n % 2 == 0) {
        return (values[n/2] + values[n/2 - 1]) / 2.0;
    } else {
        return values[n/2];
    }
}

double Dataset::standardDeviationValue() const {
    double mean = meanValue();
    double variance = varianceValue();
    return std::sqrt(variance);
}

double Dataset::varianceValue() const {
    double mean = meanValue();
    double sum = 0.0;
    size_t count = 0;
    for (const auto& value : dataset) {
        if (std::holds_alternative<int>(value)) {
            int intValue = std::get<int>(value);
            double diff = static_cast<double>(intValue) - mean;
            sum += diff * diff;
            ++count;
        } else if (std::holds_alternative<double>(value)) {
            double diff = std::get<double>(value) - mean;
            sum += diff * diff;
            ++count;
        }
    }
    return count > 1 ? sum / (count - 1) : 0.0;
}


bool Dataset::isInteger(double d) {
    return std::floor(d) == d;
}


