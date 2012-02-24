/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Dmitry Savchenko.
** Copyright (c) 2010 Vasiliy Sorokin.
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

#ifndef SETTINGS_H
#define SETTINGS_H

#include "keyword.h"

#include <QSettings>

namespace Todo {
namespace Internal {

enum ScanningScope {
    ScanningScopeCurrentFile,
    ScanningScopeProject
};

struct Settings {
    KeywordList keywords;
    ScanningScope scanningScope;
    void save(QSettings *settings) const;
    void load(QSettings *settings);
    void setDefault();
    bool equals(const Settings &other) const;
};

bool operator ==(Settings &s1, Settings &s2);
bool operator !=(Settings &s1, Settings &s2);

} // namespace Internal
} // namespace Todo

Q_DECLARE_METATYPE(Todo::Internal::ScanningScope)

#endif // SETTINGS_H
