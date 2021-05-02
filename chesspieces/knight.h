#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // KNIGHT_H
