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


#include "iotstock.h"
#include <KAboutData>
#include <KLocalizedString>
#include <QApplication>
#include <QCommandLineParser>
#include <QString>


static const char description[] =
    I18N_NOOP("Iotstock your iotpos!");

static const char version[] = "0.9.6.0 | March 04, 2013";

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    KAboutData about(
        QStringLiteral("iotstock"),
        i18n("IotStock"),
        QString::fromLatin1(version),
        i18n(description),
        KAboutData::License_GPL,
        i18n("(C) 2007-2011 Miguel Chavez Gamboa"),
        QString(),
        QString(),
        QStringLiteral("miguel@iotpospos.org")
    );
    about.addAuthor( i18n("Miguel Chavez Gamboa"), QString(), QStringLiteral("miguel@iotpospos.org") );
    about.setBugAddress("bugs.iotstock@iotpospos.org");
    KAboutData::setApplicationData(about);

    about.addCredit(i18n("Roberto Aceves"), i18n("Many ideas and general help"));
    about.addCredit(i18n("Biel Frontera"), i18n("Code contributor"));
    about.addCredit(i18n("Vitali Kari"), i18n("Code contributor"));
    about.addCredit(i18n("Jose Nivar"), i18n("Many ideas, bug reports and testing"));
    about.addCredit(i18n("Benjamin Burt"), i18n("Many ideas, Documentation Writer, How-to Videos Creation, and general help and support"));

    QCommandLineParser parser;
    about.setupCommandLine(&parser);
    parser.process(app);
    about.processCommandLine(&parser);

    iotstock *widget = new iotstock;
    widget->show();

    return app.exec();
}
