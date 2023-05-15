
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

        if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QMessageBox::warning(nullptr, "Error", "Failed to open file");
            return { false, QJsonObject() };
        }

        QVariantList data;

        QTextStream stream(&file);
        while(!stream.atEnd()){
            const QString line = stream.readLine();
            const QStringList values = line.split(",");
            QVariantMap row;

            for(int i = 0; i < values.size(); ++i){
                row.insert(QString("Column %1").arg(i + 1), values[i]);
            }

            data.append(row);
        }

        file.close();

        return { true, QJsonObject::fromVariantMap({{"data", data}}) };
    }
    else {
        QMessageBox::warning(nullptr, "Error", "Unsupported file format");
        return { false, QJsonObject() };
    }
}

