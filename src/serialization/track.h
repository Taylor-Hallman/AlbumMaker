#ifndef TRACK_H
#define TRACK_H

#include <QString>
#include <QJsonObject>

struct Track
{
    QString filePath;
    QString name;
    QString artist;

    Track(QString path, QString name, QString artist) : filePath(path), name(name), artist(artist) {}

    QJsonObject toJson() const;
    static Track fromJson(const QJsonObject& obj);
};

#endif // TRACK_H
