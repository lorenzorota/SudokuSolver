#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "cell.h"
#include "board.h"
#include "solver.h"

#include <QtCore>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Initialize components
    QCoreApplication::setApplicationName( QString("Sudoku Solver"));
    setWindowTitle( QCoreApplication::applicationName() );

    initCellRef();

    // Fix tab ordering
    for (int i = 0; i < 80; i++)
        setTabOrder(cellRef[i]->getCell(), cellRef[i + 1]->getCell());

    // Apply stylesheet to each cell
    for (int i = 0; i < 81; i++)
    {
        cellRef[i]->setStyleSheet(":enabled:hover { background-color: rgb(153, 153, 153); }"
                                  ":enabled { border: 1px solid gray; }"
                                  ":enabled {background-color: rgb(204, 204, 204); }"
                                  ":enabled { font: 24pt \".SF NS Text\"; }"
                                  ":enabled:focus { border: 0px; }"
                                  ":enabled:focus { background-color: rgb(49, 79, 120); }"
                                  ":disabled { border: 1px solid gray; }"
                                  ":disabled { background-color: rgb(153, 153, 153); }");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_solveButton_clicked()
{
    loadValues(cellRef);
    board = new Board(capturedValues);

    if (Solver::isValid(board))
    {
        for (int i = 0; i < 81; i++)
            cellRef[i]->setEnabled(false);

        ui->solveButton->setEnabled(false);
        ui->editButton->setEnabled(true);
        Solver::solve(*board, 0);

        for (int i = 0; i < 81; i++)
        {
            if ((*board)[i] != capturedValues[i])
            {
                cellRef[i]->getCell()->setStyleSheet("color: green;");
                cellRef[i]->getCell()->setPlainText(QString::number((*board)[i]));
                cellRef[i]->getCell()->setAlignment(Qt::AlignCenter);
            }
        }

        ui->statusBar->showMessage(tr("Success!"));
    }
    else
    {
        ui->statusBar->showMessage(tr("Error: Invalid Sudoku entered!"));
    }
}

/*
 *  @brief: Copy addresses of cells (unsafe... I know)
 */
void MainWindow::initCellRef()
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
        {
            QString pos = "cell_" + QString::number(i) + QString::number(j);
            cellRef.push_back(findChild<Cell*>(pos));
        }
}

/*
 *  @brief: Load the input array from cells in UI
 */
void MainWindow::loadValues(QList<Cell*> cellRef)
{
    bool success;
    for (int i = 0; i < 81; i++)
    {
        QString str = cellRef[i]->getCell()->toPlainText();
        if (!QString::compare(str, ""))
            capturedValues[i] = 0;
        else
        {
            int num = QString(str.split(" ")[0]).toInt(&success);
            if (success)
                capturedValues[i] = num;
            else
                throw "Error occured while loading values from cells into array";
        }
    }
}

void MainWindow::on_editButton_clicked()
{
    ui->solveButton->setEnabled(true);
    ui->editButton->setEnabled(false);
    for (int i = 0; i < 81; i++)
    {
        cellRef[i]->setEnabled(true);

        if ((*board)[i] != capturedValues[i])
        {
            cellRef[i]->getCell()->setStyleSheet("color: black");
            cellRef[i]->getCell()->setPlainText("");
            cellRef[i]->getCell()->setAlignment(Qt::AlignCenter);
        }
    }
}

void MainWindow::on_resetButton_clicked()
{
    ui->solveButton->setEnabled(true);
    ui->editButton->setEnabled(false);
    ui->statusBar->showMessage(tr(""));

    for (int i = 0; i < 81; i++)
    {
        cellRef[i]->setEnabled(true);
        cellRef[i]->getCell()->setStyleSheet("color: black");
        cellRef[i]->getCell()->setPlainText("");
        cellRef[i]->getCell()->setAlignment(Qt::AlignCenter);
    }
}
