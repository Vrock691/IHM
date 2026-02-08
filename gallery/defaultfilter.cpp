#include "ifilter.h"

class DefaultFilter : public IFilter {
public:
    bool isAcceptable() override {
        return true;
    }
};
