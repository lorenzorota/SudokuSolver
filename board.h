#ifndef BOARD_H
#define BOARD_H


class Board
{
public:
    Board(int input[81]);
    int &operator()(const int&, const int&);
    const int &operator()(const int&, const int&) const;
    int &operator[](const int&);
    int board[81];
};

#endif // BOARD_H
