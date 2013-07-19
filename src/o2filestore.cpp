#include <QStringList>
#include <QDebug>

#include "o2filestore.h"

O2FileStore::O2FileStore(const QString &filename, QObject *parent) :
    O2AbstractStore(parent)
{
    file_ = new QFile(filename, this);
    keyValueSeparator_ = '=';
}

O2FileStore::O2FileStore(QFile *file, QObject *parent) :
    O2AbstractStore(parent)
{
    file_ = file;
    file_->setParent(this);
    keyValueSeparator_ = '=';
}

O2FileStore::~O2FileStore() {
    if (file_) {
        file_->close();
    }
}

QString O2FileStore::value(const QString &key, const QString &defaultValue) {
    if (!file_->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Unable to open device in read-only & text mode!";
        emit error(file_->errorString());
        return defaultValue;
    }

    QMap<QString, QString> data = parseFileData(file_);
    file_->close();

    return data.value(key, defaultValue);
}

void O2FileStore::setValue(const QString &key, const QString &value) {
    QMap<QString, QString> data;
    if (file_->open(QIODevice::ReadOnly | QIODevice::Text)) {
        data = parseFileData(file_);
        file_->close();
    }

    if (!file_->open(QIODevice::ReadWrite | QIODevice::Truncate)) {
        qCritical() << "Unable to open device in truncate mode for writing!";
        emit error(file_->errorString());
        return;
    }

    data.insert(key, value);

    writeFileData(data, file_);
    file_->close();
}

QMap<QString, QString> O2FileStore::parseFileData(QFile *file) const {
    QTextStream inStream(file);
    QMap<QString, QString> parsedData;
    while (!inStream.atEnd()) {
        QString line = inStream.readLine();
        QStringList kvpair = line.split(keyValueSeparator_);
        if (kvpair.isEmpty() || (kvpair.size() < 2)) {
            continue;
        }
        parsedData.insert(kvpair.at(0), kvpair.at(1));
    }
    return parsedData;
}

void O2FileStore::writeFileData(const QMap<QString, QString> &data, QFile *file) {
    QTextStream outStream(file);
    foreach (QString key, data.keys()) {
        QString line = key + keyValueSeparator_ + data.value(key);
        outStream << line << endl;
    }
}
