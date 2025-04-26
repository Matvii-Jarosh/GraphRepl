/*
 * Copyright (c) 2025 Matvii Jarosh
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
*/
#include "lisphighlighter.h"

LispHighlighter::LispHighlighter(QTextDocument *parent) : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    atomFormat.setForeground(QColor("#4EC9B0"));  // Teal
    rule.pattern = QRegularExpression(R"((?<=\s|\(|\)|'|`|,|")([^\s()\[\]{}",'`;]+)(?=\s|\)|\(|$))");
    rule.format = atomFormat;
    highlightingRules.append(rule);

    // Numbers
    numberFormat.setForeground(QColor("#B5CEA8"));  // Light green
    rule.pattern = QRegularExpression(R"((?<=\s|\(|\)|'|`|,|")(-?\d+\.?\d*)(?=\s|\)|\(|$))");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    // Strings
    stringFormat.setForeground(QColor("#CE9178"));  // Orange
    rule.pattern = QRegularExpression(R"("(?:[^"\\]|\\.)*")");
    rule.format = stringFormat;
    highlightingRules.append(rule);

    // Special atoms (true, false, nil)
    specialAtomFormat.setForeground(QColor("#569CD6"));  // Blue
    QStringList specialAtomPatterns;
    specialAtomPatterns << R"(\btrue\b)" << R"(\bfalse\b)" << R"(\bnil\b)";
    for (const QString &pattern : specialAtomPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = specialAtomFormat;
        highlightingRules.append(rule);
    }

    // Comments
    commentFormat.setForeground(QColor("#6A9955"));  // Green
    rule.pattern = QRegularExpression(R"(;.*$)");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    // Parentheses
    parenFormat.setForeground(QColor("#D4D4D4"));  // Light gray
}

void LispHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : highlightingRules) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    for (int i = 0; i < text.length(); ++i) {
        if (text[i] == '(' || text[i] == ')') {
            setFormat(i, 1, parenFormat);
        }
    }
}
