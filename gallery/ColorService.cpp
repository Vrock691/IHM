#include "ColorService.h"
#include <QColor>

QColor ColorService::getMajorityColor(const QImage &image) {
    if (image.isNull()) {
        return Qt::transparent;
    }

    // Map pour stocker le nombre de répétitions
    QMap<QRgb, int> colorCounts;

    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            QRgb pixel = image.pixel(x, y);

            // ignorer les pixels transparents
            if (qAlpha(pixel) > 0) {
                colorCounts[pixel]++;
            }
        }
    }

    // couleur avec le compte le plus élevé
    QRgb majorityRgb = 0;
    int maxCount = 0;

    QMap<QRgb, int>::const_iterator it = colorCounts.constBegin();
    while (it != colorCounts.constEnd()) {
        if (it.value() > maxCount) {
            maxCount = it.value();
            majorityRgb = it.key();
        }
        ++it;
    }

    return QColor(majorityRgb);
}

