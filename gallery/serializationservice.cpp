#include "serializationservice.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

serializationservice::serializationservice() {
    QDir dir = QDir();
    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    dir.mkpath(configsPath);
    dir.mkpath(configsPath + QDir::separator() + "configs" + QDir::separator() + "images");
    dir.mkpath(configsPath + QDir::separator() + "configs" + QDir::separator() + "tabs");
}

QString serializationservice::getSha1FromString(const QString value) {
    QByteArray pathBytes = value.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(pathBytes, QCryptographicHash::Sha1);
    return QString(hashBytes.toHex());
}

Color serializationservice::getColorFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "white") {
        return WHITE;
    } else {
        return UNKNOWN_COLOR;
    }
}

Feeling serializationservice::getFeelingFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "happy") {
        return HAPPY;
    } else {
        return UNKNOWN_FEELING;
    }
}

void serializationservice::serializeImageModel(ImageModel imageModel) {

    QString fileID = getSha1FromString(QString::fromStdString(imageModel.path()));

    QJsonObject jobject;
    jobject["fileID"] = fileID;
    jobject["fileName"] = QString::fromStdString(imageModel.fileName());
    jobject["path"] = QString::fromStdString(imageModel.path());
    jobject["width"] = QJsonValue::fromVariant(QVariant(imageModel.width()));
    jobject["height"] = QJsonValue::fromVariant(QVariant(imageModel.height()));
    jobject["format"] = QString::fromStdString(imageModel.format());
    jobject["sizeBytes"] = QJsonValue::fromVariant(QVariant(static_cast<qlonglong>(imageModel.sizeBytes())));
    jobject["creationDate"] = QString::fromStdString(imageModel.creationDate());
    jobject["lastModificationDate"] = QString::fromStdString(imageModel.lastModificationDate());
    jobject["mainColor"] = imageModel.mainColor();
    jobject["description"] = QString::fromStdString(imageModel.description());
    jobject["score"] = QJsonValue::fromVariant(QVariant(imageModel.score()));
    jobject["feeling"] = imageModel.feeling();

    QJsonArray keywords;
    for (const auto& str : imageModel.keyWords()) {
        keywords.append(QString::fromStdString(str));
    }
    jobject["keyWords"] = keywords;

    QJsonDocument doc( jobject );

    QString configFilePath = QString("configs/images/%1.json").arg(fileID);
    QFile file(configFilePath);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();

}

std::vector<ImageModel> serializationservice::deserializeImageModels()
{
    std::vector<ImageModel> models;
    QDir configDir("configs/images");
    QStringList jsonFiles = configDir.entryList(QStringList() << "*.json", QDir::Files);

    for (const QString& jsonFileName : jsonFiles) {
        QString filePath = configDir.filePath(jsonFileName);
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isNull()) {
            continue;
        }

        QJsonObject jobject = doc.object();
        ImageModel model = ImageModel(
            jobject["path"].toString().toStdString(),
            jobject["width"].toInt(),
            jobject["height"].toInt(),
            jobject["format"].toString().toStdString(),
            jobject["fileName"].toString().toStdString(),
            jobject["sizeBytes"].toInt(),
            jobject["creationDate"].toString().toStdString(),
            jobject["lastModificationDate"].toString().toStdString(),
            getColorFromString(jobject["mainColor"].toString()),
            jobject["description"].toString().toStdString(),
            {},
            jobject["score"].toInt(),
            getFeelingFromString(jobject["feeling"].toString())
        );

        QJsonArray keywordsArray = jobject["keyWords"].toArray();
        std::vector<std::string> keywords;
        for (const QJsonValue& keywordValue : keywordsArray) {
            keywords.push_back(keywordValue.toString().toStdString());
        }
        model.setKeyWords(keywords);
        models.push_back(model);
    }

    return models;
}

void serializationservice::serializeTabModel(TabModel tabModel) {
    QString fileID = &"tab_"[tabModel.getIndex()];

    QJsonObject jobject;
    jobject["index"] = tabModel.getIndex();
    jobject["name"] = tabModel.getName();
    jobject["orderer"] = tabModel.getOrderer()->id();

    QJsonArray filters;
    for (const auto& filter : tabModel.getFilters()) {
        filters.append(filter->id());
    }
    jobject["filters"] = filters;

    QJsonDocument doc( jobject );

    QString configFilePath = QString("configs/tabs/%1.json").arg(fileID);
    QFile file(configFilePath);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}

std::vector<TabModel> serializationservice::deserializeTabModels() {
    std::vector<TabModel> tabs;

    /*QDir configDir("configs/tabs");
    QStringList jsonFiles = configDir.entryList(QStringList() << "*.json", QDir::Files);

    for (const QString& jsonFileName : jsonFiles) {
        QString filePath = configDir.filePath(jsonFileName);
        QFile file(filePath);

        if (!file.open(QIODevice::ReadOnly)) {
            continue;
        }

        QByteArray jsonData = file.readAll();
        file.close();

        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isNull()) {
            continue;
        }

        QJsonObject jobject = doc.object();
        TabModel model = TabModel(
            jobject["index"].toInt(),
            jobject["name"].toString(),
            {},
            nullptr
        );

        QJsonArray filtersArray = jobject["keyWords"].toArray();
        std::vector<std::unique_ptr<IFilter>> filters;
        for (const QJsonValue& filter : filtersArray) {
            filters.push_back(nullptr);
        }
        model.setFilters(filters);
        tabs.push_back(model);
    }*/

    return tabs;

}
