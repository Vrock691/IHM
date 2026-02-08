#include "iorderer.h"

class DefaultOrderer : public IOrderer {
public:
    std::vector<ImageModel> order(std::vector<ImageModel> images) override {
        return images;
    }
};
