#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QTextStream>

#include "Dataset.h"

class FileParser
{
public:
    FileParser() = default;

    static QPair<Dataset, Dataset> parseFile(const QString& filename);

    static QPair<Dataset, Dataset> parseJson (const QString &filename);
    static QPair<Dataset, Dataset> parseCsv (const QString &filename);

    static bool validateJsonFile(const QString &filename);
};


#endif // FILEPARSER_H
