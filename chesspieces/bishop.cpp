#include "bishop.h"

Bishop::Bishop(QVector2D pos, int chessPiece, short id) : ChessPiece(pos, chessPiece, id)
{

}

QVector<ChessMove> Bishop::possibleMoves(std::shared_ptr<ChessPiece>* board) const
{
    QVector<ChessMove> possibleMoveList;
    for(int x = currentPos.x() + 1, y = currentPos.y() + 1; x < 8 && y < 8; x++, y++) {
        QVector2D pos = QVector2D(x, y);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == nullptr) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    for(int x = currentPos.x() - 1, y = currentPos.y() + 1; x >= 0 && y < 8; x--, y++) {
        QVector2D pos = QVector2D(x, y);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == nullptr) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    for(int x = currentPos.x() + 1, y = currentPos.y() - 1; x < 8 && y >= 0; x++, y--) {
        QVector2D pos = QVector2D(x, y);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == nullptr) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
        } else if(board[index]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            break;
        } else {
            break;
        }
    }

    for(int x = currentPos.x() - 1, y = currentPos.y() - 1; x >= 0 && y >= 0; x--, y--) {
        QVector2D pos = QVector2D(x, y);
        int index = ChessHelper::vectToIndex(pos);
        if(board[index] == nullptr) {
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

std::unique_ptr<ChessPiece> Bishop::clone() const
{
    return std::make_unique<Bishop>(*this);
}


