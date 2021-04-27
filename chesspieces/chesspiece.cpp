#include "chesspiece.h"

ChessPiece::ChessPiece(QVector2D initialPos, int chessPiece, short id)
{
    this->currentPos = initialPos;
    this->chessPiece = chessPiece;
    this->id = id;
    captured = false;
    moved = false;
    if(chessPiece < 0)
        color = ChessHelper::color::black;
    else
        color = ChessHelper::color::white;
}



void ChessPiece::updatePos(QVector2D newPos)
{
   if(!(newPos.x() == currentPos.x() && newPos.y() == currentPos.y())){
       lastPos = currentPos;
       currentPos = newPos;
       moved = true;
   }


}

bool ChessPiece::getCaptured() const
{
    return captured;
}

void ChessPiece::setCaptured(bool value)
{
    captured = value;
}

int ChessPiece::getChessPiece() const
{
    return chessPiece;
}

void ChessPiece::setChessPiece(int value)
{
    chessPiece = value;
}

QVector2D ChessPiece::getLastPos() const
{
    return lastPos;
}

QVector2D ChessPiece::getCurrentPos() const
{
    return currentPos;
}

ChessHelper::color ChessPiece::getColor() const
{
    return color;
}

bool ChessPiece::getMoved() const
{
    return moved;
}

void ChessPiece::setMoved(bool value)
{
    moved = value;
}

short ChessPiece::getId() const
{
    return id;
}

