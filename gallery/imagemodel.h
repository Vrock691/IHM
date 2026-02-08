#ifndef IMAGEMODEL_H
#define IMAGEMODEL_H

#include "color.h"
#include "feeling.h"
#include <string>
#include <vector>

class ImageModel {
    std::string _path;

    // Extracted properties (seulement getter, valeurs écrites à la création de l'objet, refresh à la déserialisation)
    unsigned int _width;
    unsigned int _height;
    std::string _format;
    std::string _fileName;
    unsigned long _sizeBytes;
    std::string _creationDate;
    std::string _lastModificationDate;
    Color _mainColor;

    // User properties (getter et setter)
    std::string _description;
    std::vector<std::string> _keyWords;
    unsigned int _score;
    Feeling _feeling;

    // TODO: Ajouter rognage

public:
    explicit ImageModel(const std::string& path);

    unsigned int width() const;
    unsigned int height() const;
    std::string format() const;
    std::string fileName() const;
    unsigned long sizeBytes() const;
    std::string creationDate() const;
    std::string lastModificationDate() const;
    Color mainColor() const;

    std::string description() const;
    void setDescription(const std::string &newDescription);
    std::vector<std::string> keyWords() const;
    void setKeyWords(const std::vector<std::string> &newKeyWords);
    unsigned int score() const;
    void setScore(unsigned int newScore);
    Feeling feeling() const;
    void setFeeling(Feeling newFeeling);
    std::string path() const;
};


#endif // IMAGEMODEL_H
