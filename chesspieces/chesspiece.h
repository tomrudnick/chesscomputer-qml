#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QVector2D>
#include "chessHelper.h"
#include "chessmove.h"
#include <QVector>

class ChessPiece
{
public:
    ChessPiece(QVector2D pos, int chessPiece, short id);
    //virtual ~ChessPiece();
    virtual QVector<ChessMove> possibleMoves(ChessPiece** board) = 0;
    virtual ChessPiece* clone() const = 0;


    void updatePos(QVector2D newPos);

    bool getCaptured() const;
    void setCaptured(bool value);

    int getChessPiece() const;
    void setChessPiece(int value);



    QVector2D getLastPos() const;
    QVector2D getCurrentPos() const;

    ChessHelper::color getColor() const;

    bool getMoved() const;

    void setMoved(bool value);

    short getId() const;

protected:
    QVector2D lastPos;
    QVector2D currentPos;
    ChessHelper::color color;
    bool captured;
    bool moved;

private:
    int chessPiece;
    short id;

};

#endif // CHESSPIECE_H
