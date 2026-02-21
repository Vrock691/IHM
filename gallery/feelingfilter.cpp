#include "ifilter.h"
#include "imagemodel.h"
#include "qjsonobject.h"

class FeelingFilter : public IFilter {
public:
    FeelingFilter(Feeling feeling)
        : _feeling(feeling)
    {}

    bool isAcceptable(ImageModel* model) override
    {
        if (model->feeling() == _feeling) {
            return true;
        }
        return false;
    }

    AvailableFilters id() override
    {
        return FEELING_FILTER;
    }

    QJsonObject serialize() override
    {
        QJsonObject json;
        json["id"] = "FEELING_FILTER";
        json["feeling"] = _feeling;
        return json;
    }

    Feeling getFeeling()
    {
        return _feeling;
    }

private:
    Feeling _feeling;
};
