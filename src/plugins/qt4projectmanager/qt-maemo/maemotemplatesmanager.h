/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2010 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** Commercial Usage
**
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
**
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** If you are unsure which license is appropriate for your use, please
** contact the sales department at qt-sales@nokia.com.
**
**************************************************************************/

#ifndef MAEMOTEMPLATESCREATOR_H
#define MAEMOTEMPLATESCREATOR_H

#include <QtCore/QFile>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QSharedPointer>
#include <QtGui/QIcon>

QT_FORWARD_DECLARE_CLASS(QFileSystemWatcher);

namespace ProjectExplorer {
class Project;
class ProjectNode;
class Target;
}

namespace Qt4ProjectManager {
class Qt4Project;

namespace Internal {
class Qt4ProFileNode;
class Qt4Target;

class MaemoTemplatesManager : public QObject
{
    Q_OBJECT

public:
    static MaemoTemplatesManager *instance(QObject *parent = 0);

    QString version(const ProjectExplorer::Project *project,
        QString *error) const;
    bool setVersion(const ProjectExplorer::Project *project,
        const QString &version, QString *error) const;

    QString debianDirPath(const ProjectExplorer::Project *project) const;
    QStringList debianFiles(const ProjectExplorer::Project *project) const;

    QIcon packageManagerIcon(const ProjectExplorer::Project *project,
        QString *error) const;
    bool setPackageManagerIcon(const ProjectExplorer::Project *project,
        const QString &iconFilePath, QString *error) const;

signals:
    void debianDirContentsChanged(const ProjectExplorer::Project *project);
    void changeLogChanged(const ProjectExplorer::Project *project);
    void controlChanged(const ProjectExplorer::Project *project);

private slots:
    void handleActiveProjectChanged(ProjectExplorer::Project *project);
    bool handleTarget(ProjectExplorer::Target *target);
    void handleDebianDirContentsChanged();
    void handleDebianFileChanged(const QString &filePath);
    void handleProjectToBeRemoved(ProjectExplorer::Project *project);
    void handleProFileUpdated();

private:
    explicit MaemoTemplatesManager(QObject *parent);
    void raiseError(const QString &reason);
    QString changeLogFilePath(const ProjectExplorer::Project *project) const;
    QString controlFilePath(const ProjectExplorer::Project *project) const;
    bool createDebianTemplatesIfNecessary(const ProjectExplorer::Target *target);
    bool updateDesktopFiles(const Qt4Target *target);
    bool updateDesktopFile(const Qt4Target *target,
        Qt4ProFileNode *proFileNode);
    ProjectExplorer::Project *findProject(const QFileSystemWatcher *fsWatcher) const;
    void findLine(const QByteArray &string, QByteArray &document,
        int &lineEndPos, int &valuePos);

    QSharedPointer<QFile> openFile(const QString &filePath,
        QIODevice::OpenMode mode, QString *error) const;

    static MaemoTemplatesManager *m_instance;

    typedef QMap<ProjectExplorer::Project *, QFileSystemWatcher *> MaemoProjectMap;
    MaemoProjectMap m_maemoProjects;
};

} // namespace Internal
} // namespace Qt4ProjectManager

#endif // MAEMOTEMPLATESCREATOR_H
