#ifndef FEELING_H
#define FEELING_H

#include<QString>

enum Feeling {
    UNKNOWN_FEELING,
    HAPPY,
    SAD,
    INSPIRED,
    CALM,
    EXCITED
};

inline std::vector<Feeling> getFeelings()
{
    return {
        Feeling::UNKNOWN_FEELING,
        Feeling::HAPPY,
        Feeling::SAD,
        Feeling::INSPIRED,
        Feeling::CALM,
        Feeling::EXCITED
    };
}

inline std::vector<QString> getFeelingNames()
{
    return {
        "- Aucun ressenti -",
        "Heureux",
        "Triste",
        "Inspiré",
        "Calme",
        "Excité"
    };
}

inline Feeling getFeelingFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "happy") {
        return HAPPY;
    } else {
        return UNKNOWN_FEELING;
    }
}

inline QString feelingToString(const Feeling feeling) {
    if (feeling == Feeling::HAPPY) {
        return "HAPPY";
    } else {
        return "UNKNOWN_FEELING";
    }
}

#endif // FEELING_H
