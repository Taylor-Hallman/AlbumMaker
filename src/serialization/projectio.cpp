#include <QFile>
#include "projectio.h"

bool ProjectIO::saveToFile(const Project& project, const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return false;

    QJsonDocument doc(project.toJson());
    file.write(doc.toJson());
    return true;
}

std::optional<Project> ProjectIO::loadFromFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return std::nullopt;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    return Project::fromJson(doc.object());
}
