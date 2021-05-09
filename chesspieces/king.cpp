#include "king.h"
#include <QtMath>

King::King(QVector2D pos, int chessPiece, short id) : ChessPiece(pos, chessPiece, id)
{

}



QVector<ChessMove> King::possibleMoves(std::shared_ptr<ChessPiece>* board) const
{
    int offsets[8][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, 1}, {-1, 1}, {1, -1}, {-1, -1}};
    QVector<ChessMove> possibleMoveList;
    for(int i = 0; i < 8; i++) {
        QVector2D tmp = QVector2D(currentPos.x() + offsets[i][0], currentPos.y() + offsets[i][1]);
        if(tmp.x() < 0 || tmp.x() > 7 || tmp.y() < 0 || tmp.y() > 7)
            continue;
        if(board[ChessHelper::vectToIndex(tmp)] == nullptr)
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::standardMove));
        else if(board[ChessHelper::vectToIndex(tmp)]->getColor() != this->color) {
            possibleMoveList.append(ChessMove(currentPos, tmp, ChessHelper::MoveStatus::capturePiece));
        }
    }

    if(moved == false) {
        int currentIndex = ChessHelper::vectToIndex(currentPos);
        if(board[currentIndex + 2] == nullptr && board[currentIndex + 1] == nullptr)
            possibleMoveList.append(ChessMove(currentPos, QVector2D(currentPos.x() + 2, currentPos.y()), ChessHelper::MoveStatus::castle));
        if(board[currentIndex - 3] == nullptr && board[currentIndex - 2] == nullptr && board[currentIndex - 1] == nullptr)
            possibleMoveList.append(ChessMove(currentPos, QVector2D(currentPos.x() - 2, currentPos.y()), ChessHelper::MoveStatus::castle));
    }

    return possibleMoveList;

}

std::unique_ptr<ChessPiece> King::clone() const
{
    return std::make_unique<King>(*this);
}
