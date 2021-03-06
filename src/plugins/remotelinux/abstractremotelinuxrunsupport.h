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

#ifndef ABSTRACTREMOTELINUXRUNSUPPORT_H
#define ABSTRACTREMOTELINUXRUNSUPPORT_H

#include "remotelinux_export.h"

#include <projectexplorer/devicesupport/idevice.h>

#include <QObject>

namespace ProjectExplorer { class DeviceApplicationRunner; }

namespace Utils { class Environment; }

namespace RemoteLinux {

class RemoteLinuxRunConfiguration;

namespace Internal { class AbstractRemoteLinuxRunSupportPrivate; }

class REMOTELINUX_EXPORT AbstractRemoteLinuxRunSupport : public QObject
{
    Q_OBJECT
protected:
    enum State
    {
        Inactive,
        GatheringPorts,
        StartingRunner,
        Running
    };
public:
    AbstractRemoteLinuxRunSupport(RemoteLinuxRunConfiguration *runConfig,
                          QObject *parent = 0);
    ~AbstractRemoteLinuxRunSupport();

protected:
    void setState(State state);
    State state() const;
    ProjectExplorer::DeviceApplicationRunner *appRunner() const;

    virtual void startExecution() = 0;

    virtual void handleAdapterSetupFailed(const QString &error);
    virtual void handleAdapterSetupDone();

    void setFinished();
    bool setPort(int &port);

    QStringList arguments() const;
    QString remoteFilePath() const;
    Utils::Environment environment() const;
    QString workingDirectory() const;
    const ProjectExplorer::IDevice::ConstPtr device() const;

    void reset();

protected slots:
    virtual void handleRemoteSetupRequested();
    virtual void handleAppRunnerError(const QString &error) = 0;
    virtual void handleRemoteOutput(const QByteArray &output) = 0;
    virtual void handleRemoteErrorOutput(const QByteArray &output) = 0;
    virtual void handleAppRunnerFinished(bool success) = 0;
    virtual void handleProgressReport(const QString &progressOutput) = 0;

private slots:
    void handlePortsGathererError(const QString &message);
    void handlePortListReady();

private:
    friend class Internal::AbstractRemoteLinuxRunSupportPrivate;
    Internal::AbstractRemoteLinuxRunSupportPrivate * const d;
};

} // namespace RemoteLinux

#endif // ABSTRACTREMOTELINUXRUNSUPPORT_H
