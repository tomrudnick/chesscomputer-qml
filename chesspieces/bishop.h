#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // BISHOP_H
