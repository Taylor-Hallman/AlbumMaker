#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QJsonObject>

struct Track
{
    QString filePath;
    QString name;
    QString artist;

    QJsonObject toJson() const;
    static Track fromJson(const QJsonObject& obj);
};

#endif // TRACK_H
