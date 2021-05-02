#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // ROOK_H
