#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(ChessPiece** board);
    ChessPiece* clone() const;
};

#endif // BISHOP_H
