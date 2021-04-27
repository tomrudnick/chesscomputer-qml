#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(QVector2D pos, int chessPiece, short id);
    ~Rook();
    QVector<ChessMove> possibleMoves(ChessPiece** board);
    ChessPiece* clone() const;
};

#endif // ROOK_H
