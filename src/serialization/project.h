#ifndef PROJECT_H
#define PROJECT_H

#include <QString>
#include <QJsonObject>
#include <QVector>
#include "track.h"

struct Project
{
    QString albumName;
    QString artist;
    QVector<Track> tracks;

    QJsonObject toJson() const;
    static Project fromJson(const QJsonObject obj);
};

#endif // PROJECT_H
