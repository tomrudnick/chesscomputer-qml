#include "rook.h"



Rook::Rook(QVector2D pos, int chessPiece, short id) : ChessPiece(pos, chessPiece, id)
{

}


QVector<ChessMove> Rook::possibleMoves(std::shared_ptr<ChessPiece>* board) const
{
    QVector<ChessMove> possibleMoveList;

    for(int i = currentPos.x() + 1; i < 8; i++) {
        QVector2D pos = QVector2D(i, currentPos.y());
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == NULL) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }


    for(int i = currentPos.y() + 1; i < 8; i++) {
        QVector2D pos = QVector2D(currentPos.x(), i);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == NULL) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    for(int i = currentPos.x() - 1; i >= 0; i--) {
        QVector2D pos = QVector2D(i, currentPos.y());
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == NULL) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    for(int i = currentPos.y() - 1; i >= 0; i--) {
        QVector2D pos = QVector2D(currentPos.x(), i);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == NULL) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    return possibleMoveList;
}

std::unique_ptr<ChessPiece> Rook::clone() const
{
    return std::make_unique<Rook>(*this);
}
