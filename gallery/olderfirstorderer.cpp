#include "iorderer.h"
#include "QDateTime"

class OlderFirstOrderer : public IOrderer {
public:
    bool orderer(ImageModel* a, ImageModel* b) override {
        if (a == b) return false;
        if (!a) return false;
        if (!b) return true;

        auto parseDate = [](const std::string &s) -> QDateTime {
            if (s.empty()) return QDateTime();
            QString qs = QString::fromStdString(s);
            return QDateTime::fromString(qs, Qt::ISODate);
        };

        QDateTime da = parseDate(a->creationDate());
        QDateTime db = parseDate(b->creationDate());

        if (da.isValid() && db.isValid()) return da < db;
        if (da.isValid()) return true;
        if (db.isValid()) return false;
        return false;
    }

    AvailableOrderers id() override {
        return OLDER_FIRST_ORDERER;
    }

    QJsonObject serialize() override {
        QJsonObject json;
        json["id"] = "OLDER_FIRST_ORDERER";
        return json;
    }
};
