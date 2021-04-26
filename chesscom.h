#ifndef CHESSCOM_H
#define CHESSCOM_H

#include <QObject>
#include <QList>
#include <QString>
#include <QVector>
#include <QVector2D>
#include "chess.h"
#include "uci.h"

class ChessCom : public QObject
{
    Q_OBJECT

public:
    explicit ChessCom(QObject *parent = nullptr);

    Q_INVOKABLE void chessPiecesCreated();

signals:
    void uiMove(int toIndex, int _id);
    void moveOk(bool move_check);
    void removePiece(int index, int _id);
    void setID(int newId, int rectangle);

public slots:
    void moveByUI(int fromIndex, int toIndex);
    void moveByEngine(ChessMove move);
    void undo();

private:
   // QList<QObject*> chessPieces;
   void updateUI();
   Chess chess;
   UCI uci;


};

#endif // CHESSCOM_H
