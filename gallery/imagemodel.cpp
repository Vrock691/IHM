#include "imagemodel.h"
#include <filesystem>
#include <QImage>

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

    // informations sur le fichier 
    _fileName = p.filename().string();
    _format = p.extension().string();

    if (std::filesystem::exists(p)) {
        _sizeBytes = std::filesystem::file_size(p);
    } else {
        _sizeBytes = 0;
    }
    // charge l'image 
    QImage img(QString::fromStdString(path));

    if (!img.isNull()) {
        _width = img.width();
        _height = img.height();
        
        _cropRect = QRect(0, 0, _width, _height);
    } else {
        //si l'image ne peut pas être vu
        _width = 0;
        _height = 0;
        _cropRect = QRect(0, 0, 0, 0);
    }

    //propriétés utilisateur
    _score = 0;
    _feeling = HAPPY; 
    _mainColor = WHITE; 
}



