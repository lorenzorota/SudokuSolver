#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <QTextEdit>

class Cell : public QWidget
{
    Q_OBJECT
public:
    explicit Cell(QWidget *parent = nullptr);
    QTextEdit *getCell();

public slots:
    void enforceConstraints();

protected:
    QTextEdit *cell;
    virtual bool eventFilter(QObject*, QEvent*);
    //virtual void resizeEvent(QResizeEvent*);
};

#endif // CELL_H
