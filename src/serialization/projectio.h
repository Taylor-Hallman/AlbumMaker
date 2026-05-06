#ifndef PROJECTIO_H
#define PROJECTIO_H

#include "project.h"
#include <optional>

namespace ProjectIO {
    bool saveToFile(const Project& project, const QString& path);
    std::optional<Project> loadFromFile(const QString& path);
};
#endif // PROJECTIO_H
