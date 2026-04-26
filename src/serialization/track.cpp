#include "track.h"
#include <stdexcept>

QJsonObject Track::toJson() const
{
    return {
        {"path", filePath},
        {"name", name},
        {"artist", artist}
    };
}

Track Track::fromJson(const QJsonObject& obj)
{
    if (!obj.contains("path") || !obj.contains("name") || !obj.contains("artist"))
        throw std::runtime_error("Invalid Track JSON");
    return {
        obj["path"].toString(),
        obj["name"].toString(),
        obj["artist"].toString()
    };
}
