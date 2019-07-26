#include "solver.h"

bool Solver::isLegal(const Board *board, const int &row, const int &col)
{
    /* Check for occurance in horizontal and vertical positions */
    for (int i = 0; i < 9; i++)
    {
        if ((*board)(i, col) == (*board)(row, col) && i != row)
            return false;
        if ((*board)(row, i) == (*board)(row, col) && i != col)
            return false;
    }

    /* Check for occurance in sub table */
    for (int i = (row / 3) * 3; i < (row / 3) * 3 + 3; i++)
        for (int j = (col / 3) * 3; j < (col / 3) * 3 + 3; j++)
            if ((*board)(i, j) == (*board)(row, col) && i != row && j != col)
                return false;

    return true;
}

bool Solver::solve(Board &board, const int &idx)
{
    /* Base case */
    if (idx >= 81)
        return true;

    /* Backtracking */
    else
    {
        if (board.board[idx] == 0)
        {
            board.board[idx] = 1;
            while (board.board[idx] <= 9)
            {
                if (Solver::isLegal(&board, idx / 9, idx % 9))
                {
                    if (Solver::solve(board, idx + 1))
                        return true;
                    else
                        board.board[idx]++;
                }
                else
                    board.board[idx]++;
            }
            board.board[idx] = 0;
        }
        else
            if (Solver::solve(board, idx + 1))
                return true;
    }
    return false;
}

bool Solver::isValid(const Board *board)
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (!isLegal(board, i, j) && (*board)(i, j) != 0)
                return false;
    return true;
}
