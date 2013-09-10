/****************************************************************************
**
** Copyright (C) 2013 Andre Hartmann <aha_1980@gmx.de>
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

#include <utils/ansiescapecodehandler.h>

#include <QString>
#include <QtTest>

using namespace Utils;

typedef QList<StringFormatPair> ResultList;

Q_DECLARE_METATYPE(QTextCharFormat);
Q_DECLARE_METATYPE(StringFormatPair);
Q_DECLARE_METATYPE(ResultList);

static QString ansiEscape(const QByteArray &sequence)
{
    return QString::fromLatin1("\x1b[" + sequence);
}

class tst_AnsiEscapeCodeHandler : public QObject
{
    Q_OBJECT

public:
    tst_AnsiEscapeCodeHandler();

private Q_SLOTS:
    void testCase1();
    void testCase1_data();

private:
    const QString red;
    const QString bold;
    const QString normal;
    const QString normal1;
};

tst_AnsiEscapeCodeHandler::tst_AnsiEscapeCodeHandler() :
    red(ansiEscape("31m")),
    bold(ansiEscape("1m")),
    normal(ansiEscape("0m")),
    normal1(ansiEscape("m"))
{
}

void tst_AnsiEscapeCodeHandler::testCase1()
{
    QFETCH(QString, text);
    QFETCH(QTextCharFormat, format);
    QFETCH(ResultList, expected);

    AnsiEscapeCodeHandler handler;
    ResultList result = handler.parseText(text, format);
    handler.endFormatScope();

    QCOMPARE(result.size(), expected.size());
    for (int i = 0; i < result.size(); ++i) {
        QCOMPARE(result[i].first, expected[i].first);
        QCOMPARE(result[i].second, expected[i].second);
    }
}

void tst_AnsiEscapeCodeHandler::testCase1_data()
{
    QTest::addColumn<QString>("text");
    QTest::addColumn<QTextCharFormat>("format");
    QTest::addColumn<ResultList>("expected");

    // Test pass-through
    QTextCharFormat defaultFormat;
    QTest::newRow("Pass-through") << "Hello World" << defaultFormat
                       << (ResultList() << StringFormatPair("Hello World", defaultFormat));

    // Test text-color change
    QTextCharFormat redFormat;
    redFormat.setForeground(QColor(170, 0, 0));
    const QString text2 = "This is " + red + "red" + normal + " text";
    QTest::newRow("Text-color change") << text2 << QTextCharFormat()
                       << (ResultList()
                            << StringFormatPair("This is ", defaultFormat)
                            << StringFormatPair("red", redFormat)
                            << StringFormatPair(" text", defaultFormat));

    // Test text format change to bold
    QTextCharFormat boldFormat;
    boldFormat.setFontWeight(QFont::Bold);
    const QString text3 = "A line of " + bold + "bold" + normal + " text";
    QTest::newRow("Text-format change") << text3 << QTextCharFormat()
                       << (ResultList()
                            << StringFormatPair("A line of ", defaultFormat)
                            << StringFormatPair("bold", boldFormat)
                            << StringFormatPair(" text", defaultFormat));

    // Test resetting format to normal with other reset pattern
    const QString text4 = "A line of " + bold + "bold" + normal1 + " text";
    QTest::newRow("Alternative reset pattern (QTCREATORBUG-10132)") << text4 << QTextCharFormat()
                       << (ResultList()
                            << StringFormatPair("A line of ", defaultFormat)
                            << StringFormatPair("bold", boldFormat)
                            << StringFormatPair(" text", defaultFormat));
}

QTEST_APPLESS_MAIN(tst_AnsiEscapeCodeHandler)

#include "tst_ansiescapecodehandler.moc"