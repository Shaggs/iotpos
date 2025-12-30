#pragma once

#include <QDate>
#include <QDateTime>
#include <QLocale>
#include <QTime>

namespace LocaleUtils {
inline QLocale systemLocale()
{
    return QLocale::system();
}

inline QString formatDateTime(const QDateTime &dateTime, QLocale::FormatType format)
{
    return systemLocale().toString(dateTime, format);
}

inline QString formatDate(const QDate &date, QLocale::FormatType format)
{
    return systemLocale().toString(date, format);
}

inline QString formatTime(const QTime &time, QLocale::FormatType format = QLocale::ShortFormat)
{
    return systemLocale().toString(time, format);
}

inline QString formatMoney(double amount, const QString &symbol = QString(), int precision = 2)
{
    return systemLocale().toCurrencyString(amount, symbol, precision);
}

inline QString currencySymbol()
{
    return systemLocale().currencySymbol(QLocale::CurrencySymbol);
}
} // namespace LocaleUtils
