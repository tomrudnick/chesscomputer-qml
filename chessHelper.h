#ifndef CHESSHELPER_H
#define CHESSHELPER_H

#include <QString>
#include <QVector2D>


namespace ChessHelper {
    enum MoveStatus {
        standardMove,
        invalidMove,
        enPassent,
        castle,
        capturePiece,
        promotion
    };



    enum color {
        white,
        black,
    };

    enum Check {
        noCheck,
        whiteCheck,
        blackCheck
    };


    int vectToIndex(QVector2D pos);
    QVector2D indexToVect(int index);
    int chessLetterToNumber(QChar letter);
    QChar numberToChessLetter(int index);
}

#endif // CHESSHELPER_H
