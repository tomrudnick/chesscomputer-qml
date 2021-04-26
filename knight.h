#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(ChessPiece** board);
    ChessPiece* clone() const;
};

#endif // KNIGHT_H
