#include "iorderer.h"

class ScoreOrderer : public IOrderer {
public:
    bool orderer(ImageModel* a, ImageModel* b) override {
        if (a == b) return false;
        if (!a) return false;
        if (!b) return true;

        return a->score() > b->score();
    }

    AvailableOrderers id() override {
        return SCORE_ORDERED;
    }

    QJsonObject serialize() override {
        QJsonObject json;
        json["id"] = "SCORE_ORDERED";
        return json;
    }
};
