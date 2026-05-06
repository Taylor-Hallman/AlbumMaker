#include "project.h"

#include <QJsonArray>
#include <QFile>
#include <stdexcept>

QJsonObject Project::toJson() const
{
    QJsonArray trackArr;
    for (const auto& track : tracks)
        trackArr.append(track.toJson());
    return {
        {"albumName", albumName},
        {"artist", artist},
        {"tracks", trackArr}
    };
}

Project Project::fromJson(const QJsonObject obj)
{
    if (!obj.contains("projectName") || !obj.contains("albumName") || !obj.contains("artist") || !obj.contains("tracks"))
        throw std::runtime_error("Invalid Project JSON");

    Project project;
    project.albumName = obj["albumName"].toString();
    project.artist = obj["artist"].toString();

    const QJsonArray trackArr = obj["tracks"].toArray();
    project.tracks.reserve(trackArr.size());

    for (const auto& track : trackArr)
        project.tracks.append(Track::fromJson(track.toObject()));

    return project;
}