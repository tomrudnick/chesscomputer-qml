#include "pawn.h"
#include <QtMath>


Pawn::Pawn(QVector2D pos, int chessPiece, short id) : ChessPiece(pos, chessPiece, id)
{

}

QVector<ChessMove> Pawn::possibleMoves(std::shared_ptr<ChessPiece>* board) const
{
    QVector<ChessMove> possibleMoveList;
    int offset = this->color == ChessHelper::color::white ? 1 : -1;

    //standard move
    QVector2D tmp = QVector2D(currentPos.x(), currentPos.y() + 1 * offset);
    if(tmp.y() < 8 && tmp.y() >= 0 && board[ChessHelper::vectToIndex(tmp)] == nullptr) {

        if(tmp.y() == 7)
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::promotion));
        else
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::standardMove));

        //first move
        tmp.setY(tmp.y() + 1 * offset);
        if(!moved && board[ChessHelper::vectToIndex(tmp)] == nullptr) {
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::standardMove));
        }
    }

    //capturing piece
    tmp = QVector2D(currentPos.x() + 1, currentPos.y() + 1 * offset);
    if(tmp.y() < 8 && tmp.y() >= 0 && tmp.x() < 8 &&
            board[ChessHelper::vectToIndex(tmp)] != nullptr &&
            board[ChessHelper::vectToIndex(tmp)]->getColor() != this->getColor()) {
        possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::capturePiece));
    }

    tmp = QVector2D(currentPos.x() - 1, currentPos.y() + 1 * offset);

    if(tmp.y() < 8 && tmp.y() >= 0 && tmp.x() >= 0 &&
            board[ChessHelper::vectToIndex(tmp)] != nullptr &&
            board[ChessHelper::vectToIndex(tmp)]->getColor() != this->getColor()) {
        possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::capturePiece));
    }

    //En-passent

    if((currentPos.y() == 4 && this->color == ChessHelper::color::white) ||
            (currentPos.y() == 3 && this->color == ChessHelper::color::black)) {
        tmp = QVector2D(currentPos.x() - 1, currentPos.y());
        std::shared_ptr<const ChessPiece> tmpPiece = board[ChessHelper::vectToIndex(tmp)];
        if(tmp.x() >= 0 && tmpPiece != nullptr && qAbs(tmpPiece->getChessPiece()) == 1 && tmpPiece->getColor() != this->color){
            tmp.setY(tmp.y() + 1 * offset);
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::enPassent));
        }

        tmp = QVector2D(currentPos.x() + 1, currentPos.y());
        tmpPiece = board[ChessHelper::vectToIndex(tmp)];
        if(tmp.x() < 8 && tmpPiece != nullptr && qAbs(tmpPiece->getChessPiece()) == 1 && tmpPiece->getColor() != this->color) {
            tmp.setY(tmp.y() + 1 * offset);
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::enPassent));
        }
    }


    return possibleMoveList;
}

std::unique_ptr<ChessPiece> Pawn::clone() const
{
    return std::make_unique<Pawn>(*this);
}
