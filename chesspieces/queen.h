#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(ChessPiece** board);
    ChessPiece* clone() const;
};

#endif // QUEEN_H
