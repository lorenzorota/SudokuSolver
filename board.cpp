#include "board.h"

#include <QtCore>

Board::Board(int input[81])
{
    for (int i = 0; i < 81; i++)
        board[i] = input[i];
}

int &Board::operator()(const int &row, const int &col)
{
    return board[row*9 + col];
}

const int &Board::operator()(const int &row, const int &col) const
{
    return board[row*9 + col];
}

int &Board::operator[](const int &idx)
{
    return board[idx];
}

