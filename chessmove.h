#ifndef CHESSMOVE_H
#define CHESSMOVE_H

#include <QVector2D>
#include "chessHelper.h"

class ChessMove
{
public:
    ChessMove(QVector2D from, QVector2D to);
    ChessMove(QVector2D from, QVector2D to, ChessHelper::MoveStatus status);

    QVector2D getStart() const;
    QVector2D getEnd() const;
    ChessHelper::MoveStatus getStatus();
    static ChessMove parseChessMove(QString move);
    QString toString() const;

    friend bool operator==(const ChessMove& a, const ChessMove& b);
    friend bool operator!=(const ChessMove& a, const ChessMove& b);

private:
    QVector2D start;
    QVector2D end;
    ChessHelper::MoveStatus status;

};

#endif // CHESSMOVE_H
