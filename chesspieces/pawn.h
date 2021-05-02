#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // PAWN_H

