
#include "fileparser.h"


QPair<bool, QJsonObject> FileParser::parseFile(const QString &filename)
{
    const auto extension = filename.split('.').last();

    if(extension == "json") {
        QFile file(filename);

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(nullptr, "Error", "Failed to open file");
            return { false, QJsonObject() };
        }

        const QByteArray data = file.readAll();
        file.close();

        QJsonParseError error;
        const QJsonDocument doc = QJsonDocument::fromJson(data, &error);

        if (doc.isNull()){
            QMessageBox::warning(nullptr, "Error", "Failed to parse JSON");
            return { false, QJsonObject() };
        }

        return { true, doc.object() };
    }
    else if(extension == "csv") {
        QFile file(filename);

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(nullptr, "Error", "Failed to open file");
            return { false, QJsonObject() };
        }

        QVariantList xData;
        QVariantList yData;

        QTextStream stream(&file);
        stream.readLine();

        while (!stream.atEnd()) {
            const QString line = stream.readLine();
            const QStringList values = line.split(",");

            if (values.size() >= 2) {
                xData.append(values[0]);
                yData.append(values[1]);
            }
        }

        file.close();

        QVariantMap dataMap;
        dataMap.insert("x", xData);
        dataMap.insert("y", yData);

        return { true, QJsonObject::fromVariantMap({{"data", dataMap}}) };
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Unsupported file format");
        return { false, QJsonObject() };
    }
}

