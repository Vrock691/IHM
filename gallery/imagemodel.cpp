#include "imagemodel.h"
#include <filesystem>

ImageModel::ImageModel(
    const std::string &path,
    unsigned int width, unsigned int height,
    const std::string &format, const std::string &fileName,
    unsigned long sizeBytes, const std::string &creationDate,
    const std::string &lastModificationDate, const Color &mainColor,
    const std::string &description,
    const std::vector<std::string> &keyWords,
    unsigned int score,
    Feeling feeling
    ) :
    _path(path),
    _width(width), _height(height),
    _format(format), _fileName(fileName),
    _sizeBytes(sizeBytes),
    _creationDate(creationDate),
    _lastModificationDate(lastModificationDate),
    _mainColor(mainColor),
    _description(description),
    _keyWords(keyWords),
    _score(score),
    _feeling(feeling)
{}

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

std::vector<std::string>& ImageModel::keyWords()
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

void ImageModel::cropRect(QRect cropRect)
{
    _cropRect = cropRect;
}

QRect ImageModel::cropRect() const
{
    return _cropRect;
}

ImageModel::ImageModel(const std::string& path)
    : _path(path)
{
    std::filesystem::path p(path);

    _fileName = p.filename().string();
    _format = p.extension().string();

    if (std::filesystem::exists(p)) {
        _sizeBytes = std::filesystem::file_size(p);
    } else {
        _sizeBytes = 0;
    }

    _width = 0;
    _height = 0;
    _score =0;

    // TODO: intialiser le rect de crop :
    //QPoint topLeft = ...
    //QPoint bottomRight = ...
    //_cropRect = {topLeft, bottomRight}
    _keyWords = {};
}
