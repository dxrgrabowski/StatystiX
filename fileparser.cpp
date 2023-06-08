#include "fileparser.h"
#include <regex>
#include <filesystem>
#include "tools.h"

//import tools;

bool FileParser::validateJsonFile(const QString &filename)
{
    std::filesystem::path filePath = filename.toStdString();

    if (!std::filesystem::exists(filePath))
    {
        qCritical() << "File does not exist:" << filename;
        return false;
    }

    if (!std::filesystem::is_regular_file(filePath))
    {
        qCritical() << "Not a regular file:" << filename;
        return false;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file:" << filename;
        return false;
    }

    QString jsonData = file.readAll();
    file.close();

    std::regex pattern(R"(\{ \"x\":\[([\d.,]+)\], \"y\":\[([\d.,]+)\] \})");

    if (!std::regex_match(jsonData.toStdString(), pattern))
    {
        qWarning() << "Invalid JSON file format.";
        return false;
    }

    return true;
}

bool validateJsonFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qCritical() << "Failed to open file:" << filename;
        return false;
    }

    QString jsonData = file.readAll();
    file.close();

    // Wzorzec regularny do dopasowania formatu pliku JSON
    std::regex pattern("\\{\\s*\"x\"\\s*:\\s*\\[(\\d+(\\.\\d+)?(,\\s*)?)*\\],\\s*\"y\"\\s*:\\s*\\[(\\d+(\\.\\d+)?(,\\s*)?)*\\]\\s*\\}");

    if (!std::regex_match(jsonData.toStdString(), pattern))
    {
        qWarning() << "Invalid JSON file format.";
        return false;
    }

    return true;
}

QPair<Dataset, Dataset> FileParser::parseFile(const QString &filename)
{
    const auto extension = filename.split('.').last();

    if(extension == "json") {
        return parseJson(filename);
    }
    else if(extension == "csv") {
        return parseCsv(filename);
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Unsupported file format");
        return { Dataset(), Dataset() };
    }
}


QPair<Dataset, Dataset> FileParser::parseJson (const QString &filename){

    std::vector<std::variant<int, double>> x;
    std::vector<std::variant<int, double>> y;

    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(nullptr, "Error", "Failed to open file");
            return { Dataset(), Dataset() };
    }

    const QByteArray data = file.readAll();
    file.close();

    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(data, &error);

    if (doc.isNull()){
            QMessageBox::warning(nullptr, "Error", "Failed to parse JSON");
            return { Dataset(), Dataset() };
    }

    QJsonArray jsonX = doc.object().value("x").toArray();
    QJsonArray jsonY = doc.object().value("y").toArray();

    for (int i = 0; i < jsonX.size() && i < jsonY.size(); ++i) {
        const QJsonValue& valueX = jsonX.at(i);
        const QJsonValue& valueY = jsonY.at(i);

        if (valueX.isDouble()) {
            x.push_back(valueX.toDouble());
        } else if (isInteger(valueX)) {
            x.push_back(valueX.toInt());
        } else {
            qWarning() << "Unsupported data type in JSON array (x)";
        }

        if (valueY.isDouble()) {
            y.push_back(valueY.toDouble());
        } else if (isInteger(valueY)) {
            y.push_back(valueY.toInt());
        } else {
            qWarning() << "Unsupported data type in JSON array (y)";
        }
    }

    return { Dataset(x), Dataset(y) };
}


QPair<Dataset, Dataset> FileParser::parseCsv (const QString &filename){

    std::vector<std::variant<int, double>> x;
    std::vector<std::variant<int, double>> y;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
            qCritical() << "Failed to open file for reading:" << filename;
            return { Dataset(), Dataset() };
    }

    QTextStream stream(&file);
    QString line;
    while (!stream.atEnd())
    {
            line = stream.readLine();
            QStringList values = line.split(';');

            if (values.size() == 2)
            {
                bool okX, okY;
                int xVal = values[0].toInt(&okX);
                double yVal = values[1].toDouble(&okY);

                if (okX && okY)
                {
                    x.push_back(xVal);
                    y.push_back(yVal);
                }
                else
                {
                    qWarning() << "Failed to convert values to int/double:" << values[0] << values[1];
                }
            }
            else
            {
                qWarning() << "Invalid number of values in line:" << line;
            }
    }

    file.close();

    return { Dataset(x), Dataset(y) };
}

