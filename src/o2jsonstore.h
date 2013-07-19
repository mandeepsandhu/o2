#ifndef O2JSONSTORE_H
#define O2JSONSTORE_H

#include "o2filestore.h"

class O2JsonStore : public O2FileStore
{
    Q_OBJECT

public:

    explicit O2JsonStore(const QString &filename, QObject *parent = 0);

    explicit O2JsonStore(QFile *file, QObject *parent = 0);

protected:
    virtual QVariantMap parseFileData(QFile *file) const;
    virtual void writeFileData(const QVariantMap &data, QFile *file);
};

#endif // O2JSONSTORE_H
