/***************************************************************************
 *   Copyright (C) 2013-2015 by Hiram R. Villarreal                      *
 *   hiramvillarreal.ap@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *

 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.         *
 ***************************************************************************/



#include "iotpos.h"
#include "settings.h"

#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>

#include <QProcess>
#include <QStringList>
#include <QString>
#include <QDir>
#include <QDate>

static const char description[] =
    I18N_NOOP("IotPOS, A point of sale for linux");

static const char version[] = "0.9.8.0 | October 04, 2017";



int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    KAboutData about(
        QStringLiteral("iotpos"),
        i18n("IotPOS"),
        QString::fromLatin1(version),
        i18n(description),
        KAboutData::License_GPL,
        i18n("(C) 2013-2017 Hiram Ronquillo Villarreal"),
        QString(),
        QString(),
        "hiramvillarreal.ap@gmail.com"
    );
    about.addAuthor( i18n("Hiram Ronquillo Villarreal"), QString(), QStringLiteral("hiramvillarreal.ap@gmail.com") );
    about.setBugAddress("hiramvillarreal.ap@gmail.com");
    KAboutData::setApplicationData(about);

    about.addCredit(i18n("Miguel Chavez Gamboa"), i18n("Code contributor"));
    about.addCredit(i18n("Biel Frontera"), i18n("Code contributor"));
    about.addCredit(i18n("Vitali Kari"), i18n("Code contributor"));
    about.addCredit(i18n("Jose Nivar"), i18n("Many ideas, bug reports and testing"));
    about.addCredit(i18n("Roberto Aceves"), i18n("Many ideas and general help"));
    about.addCredit(i18n("Benjamin Burt"), i18n("Many ideas, Documentation Writer, How-to Videos Creation, and general help and support"));
    
    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    iotpos *widget = new iotpos;
    widget->show();
    return app.exec();
}
