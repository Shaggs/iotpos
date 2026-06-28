#pragma once

#include <QStandardPaths>
#include <QString>

namespace PathUtils {
inline QString locateAppData(const QString &relativePath)
{
    if (relativePath.isEmpty()) {
        return QString();
    }

    const bool isDirectory = relativePath.endsWith('/');
    const QString trimmed = isDirectory ? relativePath.left(relativePath.size() - 1) : relativePath;
    const auto locateType = isDirectory ? QStandardPaths::LocateDirectory : QStandardPaths::LocateFile;
    QString located = QStandardPaths::locate(QStandardPaths::AppDataLocation, trimmed, locateType);
    if (isDirectory && !located.isEmpty()) {
        located.append('/');
    }
    return located;
}
} // namespace PathUtils
