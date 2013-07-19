#ifndef O2FILESTORE_H
#define O2FILESTORE_H

#include <QString>
#include <QFile>
#include <QMap>

#include "o2abstractstore.h"

class O2FileStore : public O2AbstractStore
{
    Q_OBJECT

public:

    explicit O2FileStore(const QString &filename, QObject *parent = 0);

    explicit O2FileStore(QFile *file, QObject *parent = 0);

    ~O2FileStore();

    QString value(const QString &key, const QString &defaultValue);

    void setValue(const QString &key, const QString &value);

protected:
    virtual QMap<QString, QString> parseFileData(QFile *file) const;
    virtual void writeFileData(const QMap<QString, QString> &data, QFile *file);

signals:
    void error(const QString &errorString);

public slots:

protected:
    QFile* file_;
    char keyValueSeparator_;

};

#endif // O2FILESTORE_H
