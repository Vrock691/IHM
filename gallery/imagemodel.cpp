#include "imagemodel.h"


unsigned int ImageModel::height() const
{
    return _height;
}

std::string ImageModel::format() const
{
    return _format;
}

std::string ImageModel::fileName() const
{
    return _fileName;
}

unsigned long ImageModel::sizeBytes() const
{
    return _sizeBytes;
}

std::string ImageModel::creationDate() const
{
    return _creationDate;
}

std::string ImageModel::lastModificationDate() const
{
    return _lastModificationDate;
}

Color ImageModel::mainColor() const
{
    return _mainColor;
}

std::string ImageModel::description() const
{
    return _description;
}

void ImageModel::setDescription(const std::string &newDescription)
{
    _description = newDescription;
}

std::vector<std::string> ImageModel::keyWords() const
{
    return _keyWords;
}

void ImageModel::setKeyWords(const std::vector<std::string> &newKeyWords)
{
    _keyWords = newKeyWords;
}

unsigned int ImageModel::score() const
{
    return _score;
}

void ImageModel::setScore(unsigned int newScore)
{
    _score = newScore;
}

Feeling ImageModel::feeling() const
{
    return _feeling;
}

void ImageModel::setFeeling(Feeling newFeeling)
{
    _feeling = newFeeling;
}

std::string ImageModel::path() const
{
    return _path;
}

unsigned int ImageModel::width() const
{
    return _width;
}
