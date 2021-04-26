#include "chessHelper.h"
#include <QtMath>
#include <QDebug>

namespace ChessHelper {
    int vectToIndex(QVector2D pos) {
        return 64 - (pos.y() + 1) * 8 + pos.x();
    }
    QVector2D indexToVect(int index) {
        //int y = qCeil(((64 - index) / 8) - 1);
        //qInfo() << "Index: " << QString::number(index) << " y: " << QString::number(y);
        return QVector2D(index % 8, qCeil(((64 - index) / 8.f) - 1.f));
        //return QVector2D(index % 8, qFloor(((64 - index) / 8)));
    }


    int chessLetterToNumber(QChar letter)
    {
        return letter.toLower().toLatin1() - 97;

    }

    QChar numberToChessLetter(int index) {
        return QChar((char) (index + 97));
    }


}


