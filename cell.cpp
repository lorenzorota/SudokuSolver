#include "cell.h"

#include <QtCore>
#include <QBoxLayout>
#include <QMouseEvent>

Cell::Cell(QWidget *parent) : QWidget(parent)
{
    QBoxLayout *container = new QBoxLayout(QBoxLayout::TopToBottom);
    container->setContentsMargins(0,0,0,0);

    cell = new QTextEdit();

    // Configuration
    cell->setCursorWidth(0);
    cell->setAlignment(Qt::AlignCenter);
    cell->setStyleSheet("color: black");
    cell->installEventFilter(this);
    cell->setContextMenuPolicy(Qt::NoContextMenu);
    cell->viewport()->setCursor(Qt::PointingHandCursor);
    cell->setTabChangesFocus(true);
    setFocusPolicy(Qt::TabFocus);
    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    setMinimumSize(50, 50);

    container->addWidget(cell);
    this->setLayout(container);

    QObject::connect(cell, SIGNAL(textChanged()), this, SLOT(enforceConstraints()));
}

QTextEdit *Cell::getCell()
{
    return cell;
}

void Cell::enforceConstraints()
{
    // Allow only integers in range: 1-9
    if (QRegExp("^[^1-9]$").exactMatch(cell->toPlainText()))
    {
        cell->setPlainText(cell->toPlainText().left(cell->toPlainText().length()-1));
        cell->moveCursor(QTextCursor::End);
        cell->setAlignment(Qt::AlignCenter);
    }

    // Allow at most one character
    if (cell->toPlainText().length() > 1)
    {
        cell->setPlainText(cell->toPlainText().right(1));
        cell->moveCursor(QTextCursor::End);
        cell->setAlignment(Qt::AlignCenter);
    }
}

bool Cell::eventFilter(QObject *object, QEvent *event)
{
    if (object == cell)
    {
        // Focus event
        if (event->type() == QEvent::FocusOut)
        {
            cell->setStyleSheet("color: black");
        }
        else if (event->type() == QEvent::FocusIn)
        {
            cell->setStyleSheet("color: white");
        }
        return false;
    }
    return false;
}
