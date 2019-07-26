#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cell.h"
#include "board.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_solveButton_clicked();
    void on_editButton_clicked();
    void on_resetButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<Cell*> cellRef;
    int capturedValues[81];
    Board *board;
    void initCellRef();
    void loadValues(QList<Cell*>);
};

#endif // MAINWINDOW_H
