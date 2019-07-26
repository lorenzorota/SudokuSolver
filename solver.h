#ifndef SOLVER_H
#define SOLVER_H

#include "board.h"

class Solver
{
public:
    static bool isLegal(const Board*, const int&, const int&);
    static bool solve(Board&, const int&);
    static bool isValid(const Board*);
};

#endif // SOLVER_H
