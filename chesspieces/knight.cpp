#include "knight.h"


Knight::Knight(QVector2D pos, int chessPiece, short id) : ChessPiece(pos, chessPiece, id)
{

}

QVector<ChessMove> Knight::possibleMoves(std::shared_ptr<ChessPiece>* board) const
{
    QVector<ChessMove> possibleMoveList;
    int offsets[8][2] = {{1, 2}, {2, 1}, {2, -1}, {1, -2}, {-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}};

    for(int i = 0; i < 8; i++) {
        QVector2D pos = QVector2D(currentPos.x() + offsets[i][0], currentPos.y() + offsets[i][1]);
        if(pos.x() >= 0 && pos.x() < 8 && pos.y() >= 0 && pos.y() < 8) {
            int index = ChessHelper::vectToIndex(pos);
            if(board[index] == NULL) {
                possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::standardMove));
            } else if(board[index]->getColor() != this->color) {
                possibleMoveList.append(ChessMove(currentPos, pos, ChessHelper::MoveStatus::capturePiece));
            }
        }
    }
    return possibleMoveList;

}

std::unique_ptr<ChessPiece> Knight::clone() const
{
    return std::make_unique<Knight>(*this);
}
