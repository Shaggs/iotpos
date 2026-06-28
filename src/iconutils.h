#ifndef ICONUTILS_H
#define ICONUTILS_H

#include <QIcon>
#include <QPixmap>
#include <QString>

inline QIcon themedIcon(const QString &name)
{
    return QIcon::fromTheme(name);
}

inline QPixmap themedPixmap(const QString &name, int size)
{
    return themedIcon(name).pixmap(size, size);
}

#endif
