#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

        keywordFormat.setForeground(QColor("#00b6dd"));
        keywordFormat.setFontWeight(QFont::Bold);
        const QString keywordPatterns[] = {
            QStringLiteral("\\bdefine\\b"), QStringLiteral("\\bundef\\b"), QStringLiteral("\\bif\\b"),
            QStringLiteral("\\bifdef\\b"), QStringLiteral("\\bifndef\\b"), QStringLiteral("\\belse\\b"),
            QStringLiteral("\\belif\\b"), QStringLiteral("\\bendif\\b"), QStringLiteral("\\berror\\b"),
            QStringLiteral("\\bpragma\\b"), QStringLiteral("\\bextension\\b"), QStringLiteral("\\bversion\\b"),
            QStringLiteral("\\bprecision\\b"), QStringLiteral("\\bhighp\\b"), QStringLiteral("\\bmediump\\b"),
            QStringLiteral("\\blowp\\b"), QStringLiteral("\\bbreak\\b"), QStringLiteral("\\bcase\\b"),
            QStringLiteral("\\bcontinue\\b"), QStringLiteral("\\bdefault\\b"), QStringLiteral("\\bdiscard\\b"),
            QStringLiteral("\\bdo\\b"), QStringLiteral("\\belse\\b"), QStringLiteral("\\bfor\\b"),
            QStringLiteral("\\bif\\b"), QStringLiteral("\\breturn\\b"), QStringLiteral("\\bswitch\\b"),
            QStringLiteral("\\bwhile\\b"), QStringLiteral("\\bvoid\\b"), QStringLiteral("\\bbool\\b"),
            QStringLiteral("\\bint\\b"), QStringLiteral("\\buint\\b"), QStringLiteral("\\bfloat\\b"),
            QStringLiteral("\\bdouble\\b"), QStringLiteral("\\bvec[2]\\b"), QStringLiteral("\\bvec[3]\\b"),
            QStringLiteral("\\bvec[4]\\b"), QStringLiteral("\\blayout\\b"), QStringLiteral("\\battribute\\b"),
            QStringLiteral("\\bcentroid\\b"), QStringLiteral("\\bsampler\\b"), QStringLiteral("\\bpatch\\b"),
            QStringLiteral("\\bconst\\b"), QStringLiteral("\\bflat\\b"), QStringLiteral("\\bin\\b"),
            QStringLiteral("\\binout\\b"), QStringLiteral("\\binvariant\\b"), QStringLiteral("\\bnoperspective\\b"),
            QStringLiteral("\\bout\\b"), QStringLiteral("\\bsmooth\\b"), QStringLiteral("\\buniform\\b"),
            QStringLiteral("\\bvarying\\b"), QStringLiteral("\\bbuffer\\b"), QStringLiteral("\\bshared\\b"),
            QStringLiteral("\\bcoherent\\b"), QStringLiteral("\\breadonly\\b"), QStringLiteral("\\bwriteonly\\b"),
            QStringLiteral("\\bvolatile\\b"), QStringLiteral("\\brestrict\\b")
        };
        for (const QString &pattern : keywordPatterns) {
            rule.pattern = QRegularExpression(pattern);
            rule.format = keywordFormat;
            highlightingRules.append(rule);
        }

        classFormat.setFontWeight(QFont::Bold);
        classFormat.setForeground(QColor("#dc4c46"));
        rule.pattern = QRegularExpression(QStringLiteral("\\bQ[A-Za-z]+\\b"));
        rule.format = classFormat;
        highlightingRules.append(rule);

        quotationFormat.setForeground(QColor("#9bcf43"));
        rule.pattern = QRegularExpression(QStringLiteral("\".*\""));
        rule.format = quotationFormat;
        highlightingRules.append(rule);

        functionFormat.setFontItalic(true);
        functionFormat.setForeground(QColor("#00b6dd"));
        rule.pattern = QRegularExpression(QStringLiteral("\\b[A-Za-z0-9_]+(?=\\()"));
        rule.format = functionFormat;
        highlightingRules.append(rule);

        singleLineCommentFormat.setForeground(QColor("#e8514b"));
        rule.pattern = QRegularExpression(QStringLiteral("//[^\n]*"));
        rule.format = singleLineCommentFormat;
        highlightingRules.append(rule);

        multiLineCommentFormat.setForeground(QColor("#dc4c46"));

        commentStartExpression = QRegularExpression(QStringLiteral("/\\*"));
        commentEndExpression = QRegularExpression(QStringLiteral("\\*/"));
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    for (const HighlightingRule &rule : qAsConst(highlightingRules)) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    setCurrentBlockState(0);

    int startIndex = 0;
        if (previousBlockState() != 1)
            startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
            QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
            int endIndex = match.capturedStart();
            int commentLength = 0;
            if (endIndex == -1) {
                setCurrentBlockState(1);
                commentLength = text.length() - startIndex;
            } else {
                commentLength = endIndex - startIndex
                                + match.capturedLength();
            }
            setFormat(startIndex, commentLength, multiLineCommentFormat);
            startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
        }
}
