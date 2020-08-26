#include "codeedit.h"

#include <iostream>

#include <QPainter>
#include <QTextBlock>

#include "linenumberarea.h"

CodeEdit::CodeEdit(QWidget *parent)
    : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEdit::textChanged,
            this, &CodeEdit::handleCodeHasChanged);
    connect(this, &CodeEdit::blockCountChanged,
            this, &CodeEdit::updateLineNumberAreaWidth);
    connect(this, &CodeEdit::updateRequest,
            this, &CodeEdit::updateLineNumberArea);
    connect(this, &CodeEdit::cursorPositionChanged,
            this, &CodeEdit::highlightCurrentLine);

    // Set Tab key to four spaces
    setTabStopDistance(QFontMetrics(font()).horizontalAdvance(' ') * 4);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEdit::lineNumberAreaWidth()
{
    int digits = 3;
    int max = qMax(1, blockCount());
    while (max >= 10)
    {
        max /= 10;
        ++digits;
    }
    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;

    return space;
}

void CodeEdit::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEdit::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth(0);
}

void CodeEdit::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEdit::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor("#1d2024");

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    setExtraSelections(extraSelections);
}

void CodeEdit::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), QColor("#181b1e"));

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());

    while (block.isValid() && top <= event->rect().bottom())
    {
        if (block.isVisible() && bottom >= event->rect().top())
        {
            QString number = QString::number(blockNumber + 1).append(" ");
            painter.setPen(QColor("#9299a1"));
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}

void CodeEdit::handleCodeHasChanged()
{
    code.clear();
    code.append(this->document()->toPlainText().toStdString());

    if (compiler.compileGLSLFromCode(code.data(), "comp"))
    {
        spirV = compiler.getSpirV();

        emit shaderCompiledSuccessfully();
    }
    else
    {
        std::cout << "Shader is not valid: " << std::endl;
        std::cout << compiler.getError() << std::endl;

    }
    emit requestErrorMessageUpdate(compiler.getError());
}
