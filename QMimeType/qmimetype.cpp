#include "qmimetype.h"


QMimeType::QMimeType(QString mimeFile)
{
    doc = new QDomDocument("mydoc");
    file = new QFile(mimeFile);
    if(!file->open(QFile::ReadOnly | QFile::Text))
        qDebug() << "Can't open " << mimeFile;

    if(!doc->setContent(file)) {
        file->close();
        qDebug() << "Can't read the contents of " << mimeFile;
    }

    file->close();
}

void QMimeType::setByName(QString file)
{
    QDomElement docElem = doc->documentElement();
    QDomNode n = docElem.firstChild();

    while(!n.isNull()) {
        QDomElement mimetype = n.toElement();
        if(!mimetype.isNull()) {

            QString pattern = mimetype.firstChildElement("pattern").attribute("value");

            if (file.endsWith(pattern) == true) {
                mimeType = mimetype.attribute("value");
                mimeSummary = mimetype.firstChildElement("summary").text();
                mimeDescription = mimetype.firstChildElement("description").text();
                mimeIcon = mimetype.firstChildElement("icon").attribute("value");
                mimePattern = mimetype.firstChildElement("pattern").attribute("value");
                mimeApplication = mimetype.firstChildElement("application").attribute("value");
                break;
            }

        }
        n = n.nextSibling();
    }
}

QString QMimeType::type()
{
    return mimeType;
}

QString QMimeType::summary()
{
    return mimeSummary;
}

QString QMimeType::description()
{
    return mimeDescription;
}

QString QMimeType::icon()
{
    return mimeIcon;
}

QString QMimeType::pattern()
{
    return mimePattern;
}

QString QMimeType::application()
{
    return mimeApplication;
}
