/****************************************************************************
**
** Copyright (C) 2014 Digia Plc and/or its subsidiary(-ies).
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

#ifndef PROJECT_H
#define PROJECT_H

#include "projectexplorer_export.h"

#include <coreplugin/id.h>

#include <QObject>
#include <QFileSystemModel>

namespace Core {
class IDocument;
class Context;
}

namespace ProjectExplorer {

class BuildInfo;
class IProjectManager;
class EditorConfiguration;
class ProjectImporter;
class ProjectNode;
class Kit;
class KitMatcher;
class NamedWidget;
class Target;
class ProjectPrivate;

// Documentation inside.
class PROJECTEXPLORER_EXPORT Project
    : public QObject
{
    Q_OBJECT

public:
    // Roles to be implemented by all models that are exported via model()
    enum ModelRoles {
        // Absolute file path
        FilePathRole = QFileSystemModel::FilePathRole,
        EnabledRole
    };

    Project();
    virtual ~Project();

    virtual QString displayName() const = 0;
    Core::Id id() const;
    virtual Core::IDocument *document() const = 0;
    virtual IProjectManager *projectManager() const = 0;

    QString projectFilePath() const;

    bool hasActiveBuildSettings() const;

    // EditorConfiguration:
    EditorConfiguration *editorConfiguration() const;

    // Target:
    void addTarget(Target *target);
    bool removeTarget(Target *target);

    QList<Target *> targets() const;
    // Note: activeTarget can be 0 (if no targets are defined).
    Target *activeTarget() const;
    void setActiveTarget(Target *target);
    Target *target(const Core::Id id) const;
    Target *target(Kit *k) const;
    virtual bool supportsKit(Kit *k, QString *errorMessage = 0) const;

    Target *createTarget(Kit *k);
    Target *restoreTarget(const QVariantMap &data);

    void saveSettings();
    bool restoreSettings();

    virtual ProjectNode *rootProjectNode() const = 0;

    enum FilesMode { AllFiles, ExcludeGeneratedFiles };
    virtual QStringList files(FilesMode fileMode) const = 0;
    // TODO: generalize to find source(s) of generated files?
    virtual QString generatedUiHeader(const QString &formFile) const;

    static QString makeUnique(const QString &preferedName, const QStringList &usedNames);

    virtual QVariantMap toMap() const;

    // The directory that holds the project. This includes the absolute path.
    QString projectDirectory() const;
    static QString projectDirectory(const QString &top);

    Core::Context projectContext() const;
    Core::Context projectLanguages() const;

    QVariant namedSettings(const QString &name) const;
    void setNamedSettings(const QString &name, const QVariant &value);

    virtual bool needsConfiguration() const;
    virtual void configureAsExampleProject(const QStringList &platforms);

    virtual bool supportsNoTargetPanel() const;
    virtual ProjectImporter *createProjectImporter() const;
    virtual KitMatcher *createRequiredKitMatcher() const { return 0; }
    virtual KitMatcher *createPreferredKitMatcher() const { return 0; }

    virtual bool needsSpecialDeployment() const;

    void setup(QList<const BuildInfo *> infoList);

signals:
    void displayNameChanged();
    void fileListChanged();

    // Note: activeTarget can be 0 (if no targets are defined).
    void activeTargetChanged(ProjectExplorer::Target *target);

    void aboutToRemoveTarget(ProjectExplorer::Target *target);
    void removedTarget(ProjectExplorer::Target *target);
    void addedTarget(ProjectExplorer::Target *target);

    void environmentChanged();
    void buildConfigurationEnabledChanged();

    void buildDirectoryChanged();

    void settingsLoaded();
    void aboutToSaveSettings();

    void projectContextUpdated();
    void projectLanguagesUpdated();

protected:
    virtual bool fromMap(const QVariantMap &map);
    virtual bool setupTarget(Target *t);

    void setId(Core::Id id);
    void setProjectContext(Core::Context context);
    void setProjectLanguages(Core::Context language);
    void addProjectLanguage(Core::Id id);
    void removeProjectLanguage(Core::Id id);
    void setProjectLanguage(Core::Id id, bool enabled);

private slots:
    void changeEnvironment();
    void changeBuildConfigurationEnabled();
    void onBuildDirectoryChanged();

private:
    ProjectPrivate *d;
};

} // namespace ProjectExplorer

Q_DECLARE_METATYPE(ProjectExplorer::Project *)

#endif // PROJECT_H
