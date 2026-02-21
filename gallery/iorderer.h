#ifndef IORDERER_H
#define IORDERER_H

#include "imagemodel.h"
#include "qjsonobject.h"

enum AvailableOrderers {
    DEFAULT_ORDERER,
    OLDER_FIRST_ORDERER,
    LAST_MODIFICATION_FIRST,
    SCORE_ORDERED
};

inline std::vector<AvailableOrderers> getOrderers()
{
    return {
        DEFAULT_ORDERER,
        //OLDER_FIRST_ORDERER,
        LAST_MODIFICATION_FIRST,
        SCORE_ORDERED
    };
}

inline std::vector<QString> getOrderersNames()
{
    return {
        "Défaut",
        //"Date de création",
        "Date de modification",
        "Note"
    };
}

struct IOrderer {
public:
    virtual ~IOrderer() = default;
    virtual bool orderer(ImageModel* a, ImageModel* b) = 0;
    virtual AvailableOrderers id() = 0;
    virtual QJsonObject serialize() = 0;

    bool operator()(ImageModel* a, ImageModel* b) {
        return orderer(a, b);
    }
};

#endif // IORDERER_H
