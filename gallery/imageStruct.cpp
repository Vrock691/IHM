#include <string>

struct Image {
    std::string filename;
    std::string path;
    unsigned int width;
    unsigned int height;
    std::string format;
    unsigned long sizeBytes;
    std::string creationDate;
    std::string modificationDate;
};
