#ifndef COLORSERVICE_H
#define COLORSERVICE_H

#include <QImage>
#include <QColor>
#include <QMap>

class ColorService {
public:
    static QColor getMajorityColor(const QImage &image);
};

#endif // COLORSERVICE_H
