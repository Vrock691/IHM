#ifndef FEELING_H
#define FEELING_H

#include<QString>

enum Feeling {
    UNKNOWN_FEELING,
    HAPPY,
};

inline std::vector<Feeling> getFeelings()
{
    return {
        Feeling::UNKNOWN_FEELING,
        Feeling::HAPPY
    };
}

inline Feeling getFeelingFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "happy" || lowerStr == "heureux") {
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

inline QString feelingToStringForUser(const Feeling feeling) {
    if (feeling == Feeling::HAPPY) {
        return "Heureux";
    } else {
        return "Aucun";
    }
}

#endif // FEELING_H
