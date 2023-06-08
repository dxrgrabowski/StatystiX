#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <QJsonValue>

//export module tools;



//export namespace Tools {
    bool isInteger(QJsonValue value) {
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
//}

#endif // TOOLS_H
