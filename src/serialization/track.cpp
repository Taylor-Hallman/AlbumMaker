#include "track.h"

QJsonObject Track::toJson() const
{
    return {
        {"path", filePath},
        {"name", name},
        {"artist", artist}
    };
}

Track Track::fromJson(const QJsonObject &obj)
{

}
