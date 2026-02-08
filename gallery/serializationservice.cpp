#include "serializationservice.h"
#include "qjsonobject.h"

serializationservice::serializationservice() {
    QString configsPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(configsPath);
}

void serializationservice::serializeImageModel(ImageModel imageModel) {

    QString fileID = getSha1FromString(QString::fromStdString(imageModel.path));

    QJsonObject jobject;
    jobject["fileID"] = fileID;
    jobject["filename"] = QString::fromStdString(imageModel.filename);
    jobject["path"] = QString::fromStdString(imageModel.path);
    jobject["width"] = QJsonValue::fromVariant(QVariant(imageModel.width));
    jobject["height"] = QJsonValue::fromVariant(QVariant(imageModel.height));
    jobject["format"] = QString::fromStdString(imageModel.format);
    jobject["sizeBytes"] = QJsonValue::fromVariant(QVariant(static_cast<qlonglong>(imageModel.sizeBytes)));
    jobject["creationDate"] = QString::fromStdString(imageModel.creationDate);
    jobject["modificationDate"] = QString::fromStdString(imageModel.modificationDate);
    QJsonDocument doc( jobject );

    QString configFilePath = QString("configs/%1.json").arg(fileID);
    QFile file(configFilePath);
    file.open(QIODevice::ReadWrite|QIODevice::Text);
    file.write(doc.toJson());
    file.close();

}

void serializationservice::serializeTabModel(TabModel tabModel) {}

ImageModel serializationservice::deserializeImageModels() {}

TabModel serializationservice::deserializeTabModels() {}

QString getSha1FromString(const QString &value) {
    QByteArray pathBytes = value.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(pathBytes, QCryptographicHash::Sha1);
    return QString(hashBytes.toHex());
}
