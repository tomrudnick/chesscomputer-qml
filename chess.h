#ifndef CHESS_H
#define CHESS_H

#include <QVector>
#include <QVector2D>
#include <QPair>

#include "chesspiece.h"
#include "chessmove.h"
#include "uci.h"

struct ChessHistory{
    ChessPiece* chessBoard[64];
    ChessMove move;
    ChessHelper::color whosTurn;
    ChessHelper::Check check;
    bool whiteQueenSideCastled;
    bool whiteKingSideCastled;
    bool blackQueenSideCastled;
    bool blackKingSideCastled;

    ChessHistory(ChessPiece *chessBoard[64],
                 const ChessMove& move,
                 ChessHelper::color whosTurn,
                 ChessHelper::Check check,
                 bool wQSC, bool wKSC, bool bQSC, bool bKSC) : move(move),
                                                               whosTurn(whosTurn), check(check),
                                                               whiteQueenSideCastled(wQSC),
                                                               whiteKingSideCastled(wKSC),
                                                               blackQueenSideCastled(bQSC),
                                                               blackKingSideCastled(bKSC){
        for(int i = 0; i < 64; i++) {
            this->chessBoard[i] = chessBoard[i];
        }
    }
};


class Chess
{
public:
    Chess();
    bool makeMove(int fromIndex, int toIndex);
    bool makeMove(ChessMove move);
    QVector<const ChessPiece*> getUpdates();
    QVector<ChessMove> getMoves();
    QVector<QPair<QVector2D, short>> getIds();
    bool undo();

private:

    enum hit {
        now,
        nextMove
    };

    ChessPiece* chessBoard[64];
    QVector<ChessPiece*> updatedPieces;
    QVector<ChessHistory> history;

    bool whiteQueenSideCastled;
    bool whiteKingSideCastled;
    bool blackQueenSideCastled;
    bool blackKingSideCastled;

    bool canHit(hit hit);
    bool castlingCheck(bool *castleSide, ChessMove kingMove, int kingCheckPos, int rookPos, ChessHelper::color color);
    void addBoardToHistory(const ChessMove& move);

    ChessHelper::color whosTurn;
    ChessHelper::Check check;





};

#endif // CHESS_H
