#include "chesscom.h"
#include "chessHelper.h"
#include "chessmove.h"
#include <QDebug>
#include <QtMath>
#include <QVector>
#include <QPair>
#include <QVector2D>


ChessCom::ChessCom(QObject *parent) : QObject(parent)
{
    connect(&uci, &UCI::bestMove, this, &ChessCom::moveByEngine);
    uci.setMovetime(10);
    uci.start();
}

void ChessCom::chessPiecesCreated()
{
    QVector<QPair<QVector2D, short>> ids = chess.getIds();
    for(int i = 0; i < ids.size(); i++) {
        emit setID(ids.at(i).second, ChessHelper::vectToIndex(ids.at(i).first));
    }
    qInfo() << "Emitted setID to " << QString::number(ids.size()) << " chess pieces";
}



void ChessCom::moveByUI(int fromIndex, int toIndex)
{
    qInfo() << "UI Made move from: " << fromIndex << " to: " << toIndex;

    if(chess.makeMove(fromIndex, toIndex)) {
        qInfo() << "Move OK!";
        //updating other pieces
        updateUI();
        //telling the moved piece that the move was correct
        emit moveOk(true);

        uci.setPosition(chess.getMoves());
        uci.computeNextMove();

    } else {
        qInfo() << "Move not OK";
        emit moveOk(false);
    }


}

void ChessCom::moveByEngine(ChessMove move)
{
    qInfo() << "Found best Move";
    chess.makeMove(move);
    updateUI();
}

void ChessCom::undo()
{
    if(chess.undo()) {
        updateUI();
    }
}

void ChessCom::updateUI()
{
    QVector<std::shared_ptr<const ChessPiece>> updatePieces = chess.getUpdates();
    for(int i = 0; i < updatePieces.size(); i++ ) {
        std::shared_ptr<const ChessPiece> piece = updatePieces.at(i);
        int lastPos = ChessHelper::vectToIndex(piece->getLastPos());
        int newPos = ChessHelper::vectToIndex(piece->getCurrentPos());
        qInfo() << "Piece: " << piece->getChessPiece() << " moved from: " << lastPos << " to: " << newPos;
        if(piece->getCaptured()) {
            qInfo() << "Removing Piece...: " << piece->getChessPiece() << " with id: " << piece->getId();
            emit removePiece(newPos, piece->getId());
        }
        else {
            emit uiMove(newPos, piece->getId());
        }
    }
}

