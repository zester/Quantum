#ifndef QMIMETYPE_H
#define QMIMETYPE_H

#include "QMimeType_global.h"

class QMIMETYPESHARED_EXPORT QMimeType {
public:
    QMimeType(QString);
    void setByName (QString);
    QString type();
    QString summery();
    QString description();
    QString icon();
    QString pattern();
    QString application();

private:
    QFile *file;
    QDomDocument *doc;

    QString mimeType;
    QString mimeSummery;
    QString mimeDescription;
    QString mimeIcon;
    QString mimePattern;
    QString mimeApplication;
};

#endif // QMIMETYPE_H
