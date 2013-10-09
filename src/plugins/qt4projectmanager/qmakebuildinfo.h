/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#ifndef QMAKEBUILDINFO_H
#define QMAKEBUILDINFO_H

#include "qt4buildconfiguration.h"

#include <projectexplorer/buildinfo.h>
#include <projectexplorer/kitmanager.h>
#include <qtsupport/baseqtversion.h>
#include <qtsupport/qtkitinformation.h>

namespace Qt4ProjectManager {

class QmakeBuildInfo : public ProjectExplorer::BuildInfo
{
public:
    QmakeBuildInfo(const Qt4BuildConfigurationFactory *f) : ProjectExplorer::BuildInfo(f) { }

    ProjectExplorer::BuildConfiguration::BuildType type;
    QString additionalArguments;
    QString makefile;

    QList<ProjectExplorer::Task> reportIssues(const QString &projectPath,
                                              const QString &buildDir) const
    {
        ProjectExplorer::Kit *k = ProjectExplorer::KitManager::find(kitId);
        QtSupport::BaseQtVersion *version = QtSupport::QtKitInformation::qtVersion(k);
        return version ? version->reportIssues(projectPath, buildDir)
                       : QList<ProjectExplorer::Task>();
    }
};

} // namespace Qt4ProjectManager

#endif // QMAKEBUILDINFO_H