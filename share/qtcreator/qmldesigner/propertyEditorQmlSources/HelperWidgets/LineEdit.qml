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


import QtQuick 2.1
import QtQuick.Controls 1.1 as Controls
import QtQuick.Controls.Styles 1.0

Controls.TextField {

    id: lineEdit
    property variant backendValue
    property color borderColor: "#222"
    property color highlightColor: "orange"
    property color textColor: "#eee"

//    ExtendedFunctionButton {
//        x: 2
//        y: 2
//        backendValue: checkBox.backendValue
//        visible: spinBox.enabled
//    }

    QtObject {
        property string valueFromBackend: lineEdit.backendValue.valueToString;
        onValueFromBackendChanged: {
            lineEdit.text = valueFromBackend;
        }
    }

    onAccepted: {
        if (backendValue.value !== text)
            backendValue.value = text;
    }


    onFocusChanged: {
        if (focus) {
            transaction.start();
        } else {
            transaction.end();
        }
    }

    style: TextFieldStyle {
        selectionColor: lineEdit.textColor
        selectedTextColor: "black"
        textColor: lineEdit.textColor
        padding.top: 3
        padding.bottom: 1
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 23
            border.color: borderColor
            radius: 3
            gradient: Gradient {
                GradientStop {color: "#2c2c2c" ; position: 0}
                GradientStop {color: "#343434" ; position: 0.15}
                GradientStop {color: "#373737" ; position: 1.0}
            }
            Rectangle {
                border.color: highlightColor
                anchors.fill: parent
                anchors.margins: -1
                color: "transparent"
                radius: 4
                opacity: 0.3
                visible: control.activeFocus
            }
        }
    }
}