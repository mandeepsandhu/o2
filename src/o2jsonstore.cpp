#include <QJsonDocument>
#include <QJsonObject>

#include "o2jsonstore.h"

O2JsonStore::O2JsonStore(const QString &filename, QObject *parent) :
    O2FileStore(filename, parent) {
}

O2JsonStore::O2JsonStore(QFile *file, QObject *parent) :
    O2FileStore(file, parent) {
}

QVariantMap O2JsonStore::parseFileData(QFile *file) const {
    QJsonDocument doc = QJsonDocument::fromJson(file->readAll());
    return doc.object().toVariantMap();
}

void O2JsonStore::writeFileData(const QVariantMap &data, QFile *file) {
    QJsonDocument doc = QJsonDocument(QJsonObject::fromVariantMap(data));
    file->write(doc.toJson());
}
