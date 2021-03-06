/**************************************************************************
**
** Copyright (C) 2014 Klarälvdalens Datakonsult AB, a KDAB Group company
** Contact: info@kdab.com
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

#include "qnxattachdebugdialog.h"

#include <utils/pathchooser.h>
#include <utils/qtcassert.h>

#include <QFormLayout>
#include <QLabel>
#include <QVBoxLayout>

using namespace Qnx;
using namespace Qnx::Internal;

QnxAttachDebugDialog::QnxAttachDebugDialog(ProjectExplorer::KitChooser *kitChooser, QWidget *parent)
    : ProjectExplorer::DeviceProcessesDialog(kitChooser, parent)
{
    QVBoxLayout *mainLayout = dynamic_cast<QVBoxLayout*>(layout());
    QTC_ASSERT(mainLayout, return);

    QFormLayout *formLayout = new QFormLayout;

    QLabel *sourceLabel = new QLabel(tr("Project source directory:"), this);
    m_projectSource = new Utils::PathChooser(this);
    m_projectSource->setExpectedKind(Utils::PathChooser::ExistingDirectory);
    formLayout->addRow(sourceLabel, m_projectSource);

    QLabel *binaryLabel = new QLabel(tr("Local executable:"), this);
    m_localExecutable = new Utils::PathChooser(this);
    m_localExecutable->setExpectedKind(Utils::PathChooser::File);
    formLayout->addRow(binaryLabel, m_localExecutable);

    mainLayout->insertLayout(mainLayout->count() - 2, formLayout);
}

QString QnxAttachDebugDialog::projectSource() const
{
    return m_projectSource->path();
}

QString QnxAttachDebugDialog::localExecutable() const
{
    return m_localExecutable->path();
}
