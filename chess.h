#ifndef CHESS_H
#define CHESS_H

#include <QVector>
#include <QVector2D>
#include <QPair>
#include <memory>

#include "chesspieces/chesspiece.h"
#include "chessmove.h"
#include "uci/uci.h"

struct ChessHistory{
    std::unique_ptr<ChessPiece> chessBoard[64];
    ChessMove move;
    ChessHelper::color whosTurn;
    ChessHelper::Check check;
    bool whiteQueenSideCastled;
    bool whiteKingSideCastled;
    bool blackQueenSideCastled;
    bool blackKingSideCastled;

    ChessHistory(std::unique_ptr<ChessPiece> chessBoard[64],
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
            this->chessBoard[i] = std::move(chessBoard[i]);
        }
    }
    //move constructor
    ChessHistory(ChessHistory&& history) : move(history.move),
                                                whosTurn(history.whosTurn), check(history.check),
                                                whiteQueenSideCastled(history.whiteQueenSideCastled),
                                                whiteKingSideCastled(history.whiteKingSideCastled),
                                                blackQueenSideCastled(history.blackQueenSideCastled),
                                                blackKingSideCastled(history.blackKingSideCastled){

        for(int i = 0; i < 64; i++) {
            if(history.chessBoard[i] == NULL)
                this->chessBoard[i] = NULL;
            else
                this->chessBoard[i] = std::move(history.chessBoard[i]);
        }

    }
    //copy constructor
    ChessHistory(const ChessHistory& history) : move(history.move),
                                                whosTurn(history.whosTurn), check(history.check),
                                                whiteQueenSideCastled(history.whiteQueenSideCastled),
                                                whiteKingSideCastled(history.whiteKingSideCastled),
                                                blackQueenSideCastled(history.blackQueenSideCastled),
                                                blackKingSideCastled(history.blackKingSideCastled){

        for(int i = 0; i < 64; i++) {
            //this->chessBoard[i] = std::move(history.chessBoard[i]);
            if(history.chessBoard[i] == NULL)
                this->chessBoard[i] = NULL;
            else
                this->chessBoard[i] = history.chessBoard[i]->clone();
        }

    }
    ChessHistory& operator=(const ChessHistory& other) {
        if(this != &other)  {
            this->move = other.move;
            this->whosTurn = other.whosTurn;
            this->check = other.check;
            this->blackKingSideCastled = other.blackKingSideCastled;
            this->whiteKingSideCastled = other.whiteKingSideCastled;
            this->whiteQueenSideCastled = other.whiteQueenSideCastled;
            this->blackQueenSideCastled = other.blackQueenSideCastled;
            for(int i = 0; i < 64; i++) {
                if(other.chessBoard[i] == NULL)
                    this->chessBoard[i] = NULL;
                else
                    this->chessBoard[i] = other.chessBoard[i]->clone();
            }
        }
        return *this;
    }
};


class Chess
{
public:
    Chess();
    bool makeMove(int fromIndex, int toIndex);
    bool makeMove(ChessMove move);
    QVector<std::shared_ptr<const ChessPiece>> getUpdates();
    QVector<ChessMove> getMoves();
    QVector<QPair<QVector2D, short>> getIds();
    bool undo();

private:

    enum hit {
        now,
        nextMove
    };

    std::shared_ptr<ChessPiece> chessBoard[64];
    QVector<std::shared_ptr<ChessPiece>> updatedPieces;
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
