#ifndef FILEPARSER_H
#define FILEPARSER_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMessageBox>
#include <QTextStream>

class FileParser
{
public:
    FileParser() = default;

    static QPair<bool, QJsonObject> parseFile(const QString& filename);
};


#endif // FILEPARSER_H
