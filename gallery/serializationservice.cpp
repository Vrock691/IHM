#include "serializationservice.h"
#include "filterfactory.h"
#include "ordererfactory.h"
#include "qjsonarray.h"
#include "qjsonobject.h"

SerializationService::SerializationService() {
    QDir dir = QDir();
    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    dir.mkpath(configsPath);
    dir.mkpath(configsPath + QDir::separator() + "configs" + QDir::separator() + "images");
    dir.mkpath(configsPath + QDir::separator() + "configs" + QDir::separator() + "tabs");
}

QString SerializationService::getSha1FromString(const QString value) {
    QByteArray pathBytes = value.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(pathBytes, QCryptographicHash::Sha1);
    return QString(hashBytes.toHex());
}

Color SerializationService::getColorFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "white") {
        return WHITE;
    } else {
        return UNKNOWN_COLOR;
    }
}

QString SerializationService::colorToString(const Color color) {
    if (color == Color::WHITE) {
        return "WHITE";
    } else {
        return "UNKNOWN_COLOR";
    }
}

Feeling SerializationService::getFeelingFromString(const QString value) {
    std::string lowerStr = value.toStdString();
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerStr == "happy") {
        return HAPPY;
    } else {
        return UNKNOWN_FEELING;
    }
}

QString SerializationService::feelingToString(const Feeling feeling) {
    if (feeling == Feeling::HAPPY) {
        return "HAPPY";
    } else {
        return "UNKNOWN_FEELING";
    }
}

void SerializationService::serializeImageModel(ImageModel imageModel) {

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
    jobject["mainColor"] = colorToString(imageModel.mainColor());
    jobject["description"] = QString::fromStdString(imageModel.description());
    jobject["score"] = QJsonValue::fromVariant(QVariant(imageModel.score()));
    jobject["feeling"] = feelingToString(imageModel.feeling());

    QJsonArray keywords;
    for (const auto& str : imageModel.keyWords()) {
        keywords.append(QString::fromStdString(str));
    }
    jobject["keyWords"] = keywords;

    QJsonDocument doc( jobject );

    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString configFilePath = QString("%1/configs/images/%2.json")
                                .arg(configsPath)
                                .arg(fileID);
    QFile file(configFilePath);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();

}

std::vector<ImageModel> SerializationService::deserializeImageModels()
{
    std::vector<ImageModel> models;
    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir configDir(configsPath + "/configs/images");
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

void SerializationService::serializeTabModel(const TabModel& tabModel) {
    QJsonObject jobject;
    jobject["index"] = tabModel.getIndex();
    jobject["name"] = tabModel.getName();
    jobject["orderer"] = tabModel.getOrderer()->serialize();

    QJsonArray filters;
    for (const auto& filter : tabModel.getFilters()) {
        filters.append(filter->serialize());
    }
    jobject["filters"] = filters;

    QJsonDocument doc( jobject );

    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString configFilePath = QString("%1/configs/tabs/%2.json")
                                 .arg(configsPath)
                                 .arg(tabModel.getIndex());
    QFile file(configFilePath);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();
}

std::vector<TabModel*> SerializationService::deserializeTabModels() {
    std::vector<TabModel*> tabs;

    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir configDir(configsPath + "/configs/tabs");
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
        TabModel* model = new TabModel(
            jobject["index"].toInt(),
            jobject["name"].toString(),
            {},
            nullptr
        );

        QJsonArray filtersArray = jobject["filters"].toArray();
        std::vector<std::unique_ptr<IFilter>> filters;
        FilterFactory filterFactory;
        for (const QJsonValue& filterValue : filtersArray) {
            qDebug() << filterValue.toObject();
            std::unique_ptr<IFilter> filter = filterFactory.parse(filterValue.toObject());
            filters.push_back(std::move(filter));
        }
        model->setFilters(std::move(filters));

        OrdererFactory ordererFactory;
        std::unique_ptr<IOrderer> orderer = ordererFactory.parse(jobject["orderer"].toObject());
        model->setOrderer(std::move(orderer));

        tabs.push_back(std::move(model));
    }

    return tabs;

}
