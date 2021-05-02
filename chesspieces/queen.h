#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(QVector2D pos, int chessPiece, short id);
    QVector<ChessMove> possibleMoves(std::shared_ptr<ChessPiece>* board) const;
    virtual std::unique_ptr<ChessPiece> clone() const;
};

#endif // QUEEN_H
