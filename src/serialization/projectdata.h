#ifndef PROJECTDATA_H
#define PROJECTDATA_H

#include <QString>
#include <QVector>

struct Track {
    QString filePath;
    QString name;
    QString artist;
};

class ProjectData
{
public:
    ProjectData();

    QString projectName;
    QString albumName;
    QString coverArtPath;
    QVector<Track> tracks;
};

#endif // PROJECTDATA_H
