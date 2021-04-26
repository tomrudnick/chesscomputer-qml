#include "chessmove.h"
#include "chessHelper.h"
#include <QVariant>


ChessMove::ChessMove(QVector2D from, QVector2D to) : ChessMove(from, to, ChessHelper::MoveStatus::standardMove)
{

}

ChessMove::ChessMove(QVector2D from, QVector2D to, ChessHelper::MoveStatus status)
{
    this->start = from;
    this->end = to;
    this->status = status;
}

QVector2D ChessMove::getStart() const
{
    return start;
}

QVector2D ChessMove::getEnd() const
{
    return end;
}

ChessHelper::MoveStatus ChessMove::getStatus()
{
    return status;
}

ChessMove ChessMove::parseChessMove(QString move)
{
    if(move.length() != 4) {
        //Todo throw error
    }
    QVector2D from = QVector2D(ChessHelper::chessLetterToNumber(move.at(0)), move.at(1).digitValue() - 1);
    QVector2D to = QVector2D(ChessHelper::chessLetterToNumber(move.at(2)), move.at(3).digitValue() - 1);
    //qInfo() << "Parsed move: " << move << " to: "
    return ChessMove(from, to);
}

QString ChessMove::toString() const
{
    QString chessMove;
    chessMove.append(ChessHelper::numberToChessLetter(start.x()));
    chessMove.append(QVariant(start.y() + 1).toString());
    chessMove.append(ChessHelper::numberToChessLetter(end.x()));
    chessMove.append(QVariant(end.y() + 1).toString());
    return chessMove;
}




bool operator==(const ChessMove& a, const ChessMove& b) {
    return a.start == b.start && b.end == a.end;
}

bool operator!=(const ChessMove& a, const ChessMove& b) {
    return !(a == b);
}




