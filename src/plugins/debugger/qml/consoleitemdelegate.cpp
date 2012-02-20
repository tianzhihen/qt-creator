/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
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

#include "consoleitemdelegate.h"
#include "consoleeditor.h"
#include "qmlengine.h"

#include <QPainter>
#include <QTreeView>

const char CONSOLE_LOG_BACKGROUND_COLOR[] = "#2378B7";
const char CONSOLE_WARNING_BACKGROUND_COLOR[] = "#E6CD49";
const char CONSOLE_ERROR_BACKGROUND_COLOR[] = "#ED471A";
const char CONSOLE_EDITOR_BACKGROUND_COLOR[] = "#F7F7F7";

const char CONSOLE_LOG_TEXT_COLOR[] = "#333333";
const char CONSOLE_WARNING_TEXT_COLOR[] = "#666666";
const char CONSOLE_ERROR_TEXT_COLOR[] = "#1D5B93";
const char CONSOLE_EDITOR_TEXT_COLOR[] = "#000000";

const char CONSOLE_BORDER_COLOR[] = "#DEDEDE";
const float CONSOLE_ALPHA = 0.7f;

namespace Debugger {
namespace Internal {

///////////////////////////////////////////////////////////////////////
//
// ConsoleItemDelegate
//
///////////////////////////////////////////////////////////////////////

ConsoleItemDelegate::ConsoleItemDelegate(QObject *parent) :
    QStyledItemDelegate(parent),
    m_logIcon(QLatin1String(":/debugger/images/log.png")),
    m_warningIcon(QLatin1String(":/debugger/images/warning.png")),
    m_errorIcon(QLatin1String(":/debugger/images/error.png")),
    m_expandIcon(QLatin1String(":/debugger/images/expand.png")),
    m_collapseIcon(QLatin1String(":/debugger/images/collapse.png")),
    m_prompt(QLatin1String(":/debugger/images/prompt.png")),
    m_consoleBackend(0)
{
}

void ConsoleItemDelegate::emitSizeHintChanged(const QModelIndex &index)
{
    emit sizeHintChanged(index);
}

void ConsoleItemDelegate::setConsoleBackend(ConsoleBackend *consoleBackend)
{
    m_consoleBackend = consoleBackend;
}

void ConsoleItemDelegate::drawBackground(QPainter *painter, const QRect &rect,
                             ConsoleItemModel::ItemType itemType,
                                         bool selected) const
{
    QColor backgroundColor;
    switch (itemType) {
    case ConsoleItemModel::LogType:
        backgroundColor = QColor(CONSOLE_LOG_BACKGROUND_COLOR);
        break;
    case ConsoleItemModel::WarningType:
        backgroundColor = QColor(CONSOLE_WARNING_BACKGROUND_COLOR);
        break;
    case ConsoleItemModel::ErrorType:
        backgroundColor = QColor(CONSOLE_ERROR_BACKGROUND_COLOR);
        break;
    case ConsoleItemModel::InputType:
        backgroundColor = QColor(CONSOLE_EDITOR_BACKGROUND_COLOR);
        break;
    default:
        backgroundColor = QColor(CONSOLE_EDITOR_BACKGROUND_COLOR);
        break;
    }
    if (selected)
        backgroundColor.setAlphaF(0.5f);
    else
        backgroundColor.setAlphaF(1 - CONSOLE_ALPHA);

    painter->setBrush(backgroundColor);

    painter->setPen(Qt::NoPen);
    painter->drawRect(rect);
}

void ConsoleItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);
    painter->save();

    //Set Colors
    QColor textColor;
    QIcon taskIcon;
    ConsoleItemModel::ItemType type =
            (ConsoleItemModel::ItemType)index.data(
                ConsoleItemModel::TypeRole).toInt();
    switch (type) {
    case ConsoleItemModel::LogType:
        textColor = QColor(CONSOLE_LOG_TEXT_COLOR);
        taskIcon = m_logIcon;
        break;
    case ConsoleItemModel::WarningType:
        textColor = QColor(CONSOLE_WARNING_TEXT_COLOR);
        taskIcon = m_warningIcon;
        break;
    case ConsoleItemModel::ErrorType:
        textColor = QColor(CONSOLE_ERROR_TEXT_COLOR);
        taskIcon = m_errorIcon;
        break;
    case ConsoleItemModel::InputType:
        textColor = QColor(CONSOLE_EDITOR_TEXT_COLOR);
        taskIcon = m_prompt;
        break;
    default:
        textColor = QColor(CONSOLE_EDITOR_TEXT_COLOR);
        break;
    }

    //Paint background
    drawBackground(painter, opt.rect, type,
                   bool(opt.state & QStyle::State_Selected));

    //Calculate positions
    const QTreeView *view = qobject_cast<const QTreeView *>(opt.widget);
    int level = 0;
    QModelIndex idx(index);
    while (idx.parent() != QModelIndex()) {
        idx = idx.parent();
        level++;
    }
    int width = view->width() - level * view->indentation();
    bool showTypeIcon = index.parent() == QModelIndex();
    bool showExpandableIcon = type != ConsoleItemModel::InputType &&
            type != ConsoleItemModel::UndefinedType;

    QRect rect(opt.rect.x(), opt.rect.top(), width, opt.rect.height());
    ConsoleItemPositions positions(rect, opt.font, showTypeIcon,
                        showExpandableIcon);

    // Paint TaskIconArea:
    if (showTypeIcon)
        painter->drawPixmap(positions.adjustedLeft(), positions.adjustedTop(),
                            taskIcon.pixmap(positions.typeIconWidth(),
                                            positions.typeIconHeight()));

    // Set Text Color
    painter->setPen(textColor);
    // Paint TextArea:
    // Layout the description
    QTextLayout tl(index.data(Qt::DisplayRole).toString(), opt.font);
    layoutText(tl, positions.textAreaWidth());
    tl.draw(painter, QPoint(positions.textAreaLeft(), positions.adjustedTop()));

    //skip if area is editable
    if (showExpandableIcon) {
        // Paint ExpandableIconArea:
        QIcon expandCollapseIcon;
        if (index.model()->rowCount(index)) {
            if (view->isExpanded(index))
                expandCollapseIcon = m_collapseIcon;
            else
                expandCollapseIcon = m_expandIcon;
        }
        painter->drawPixmap(positions.expandCollapseIconLeft(),
                            positions.adjustedTop(),
                            expandCollapseIcon.pixmap(
                                positions.expandCollapseIconWidth(),
                                positions.expandCollapseIconHeight()));
    }

    // Separator lines
    painter->setPen(QColor(CONSOLE_BORDER_COLOR));
    if (!index.flags() & Qt::ItemIsEditable)
        painter->drawLine(0, opt.rect.bottom(), opt.rect.right(),
                      opt.rect.bottom());
    painter->restore();
}

QSize ConsoleItemDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    QStyleOptionViewItemV4 opt = option;
    initStyleOption(&opt, index);

    const QTreeView *view = qobject_cast<const QTreeView *>(opt.widget);
    int level = 0;
    QModelIndex idx(index);
    while (idx.parent() != QModelIndex()) {
        idx = idx.parent();
        level++;
    }
    int width = view->width() - level * view->indentation();
    if (index.flags() & Qt::ItemIsEditable)
        return QSize(width, view->height() * 1/2);

    ConsoleItemModel::ItemType type =
            (ConsoleItemModel::ItemType)index.data(
                ConsoleItemModel::TypeRole).toInt();
    bool showTypeIcon = index.parent() == QModelIndex();
    bool showExpandableIcon = type != ConsoleItemModel::InputType &&
            type != ConsoleItemModel::UndefinedType;

    QRect rect(level * view->indentation(), 0, width, 0);
    ConsoleItemPositions positions(rect, opt.font,
                        showTypeIcon,
                        showExpandableIcon);

    QTextLayout tl(index.data(Qt::DisplayRole).toString(), option.font);
    qreal height = layoutText(tl, positions.textAreaWidth());
    height += 2 * ConsoleItemPositions::ITEM_PADDING;
    if (height < positions.minimumHeight())
        height = positions.minimumHeight();

    return QSize(width, height);
}

QWidget *ConsoleItemDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem &/*option*/,
                                    const QModelIndex &index) const

{
    ConsoleEditor *editor = new ConsoleEditor(index, m_consoleBackend, parent);
    connect(editor, SIGNAL(appendEditableRow()),
            this, SIGNAL(appendEditableRow()));
    connect(editor, SIGNAL(editingFinished()),
            this, SLOT(commitAndCloseEditor()));
    return editor;
}

void ConsoleItemDelegate::setEditorData(QWidget *editor,
                                 const QModelIndex &index) const
{
    ConsoleEditor *edtr = qobject_cast<ConsoleEditor *>(editor);
    edtr->insertPlainText(index.data(Qt::DisplayRole).toString());
}

void ConsoleItemDelegate::setModelData(QWidget *editor,
                                       QAbstractItemModel *model,
                                const QModelIndex &index) const
{
    ConsoleEditor *edtr = qobject_cast<ConsoleEditor *>(editor);
    model->setData(index, edtr->getCurrentScript(), Qt::DisplayRole);
    model->setData(index, edtr->getCurrentScript(), ConsoleItemModel::TypeRole);
}

void ConsoleItemDelegate::updateEditorGeometry(QWidget *editor,
                                               const QStyleOptionViewItem &option,
                                               const QModelIndex &/*index*/) const
{
    QStyleOptionViewItemV4 opt = option;
    editor->setGeometry(QRect(opt.rect.x(), opt.rect.top(),
                              opt.rect.width(), opt.rect.bottom()));
}

void ConsoleItemDelegate::currentChanged(const QModelIndex &current,
                                         const QModelIndex &previous)
{
    emit sizeHintChanged(current);
    emit sizeHintChanged(previous);
}

void ConsoleItemDelegate::commitAndCloseEditor()
{
    ConsoleEditor *editor = qobject_cast<ConsoleEditor *>(sender());
    emit commitData(editor);
    emit closeEditor(editor);
}

qreal ConsoleItemDelegate::layoutText(QTextLayout &tl, int width) const
{
    qreal height = 0;
    tl.beginLayout();
    while (true) {
        QTextLine line = tl.createLine();

        if (!line.isValid())
            break;
        line.setLeadingIncluded(true);
        line.setLineWidth(width);
        line.setPosition(QPoint(0, height));
        height += line.height();
    }
    tl.endLayout();
    return height;
}

} //Internal
} //Debugger
