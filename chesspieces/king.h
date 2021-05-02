#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King : public ChessPiece
{
public:
    King(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // KING_H
