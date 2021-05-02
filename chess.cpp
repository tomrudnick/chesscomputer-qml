#include "chess.h"
#include "chessHelper.h"
#include "chesspieces/bishop.h"
#include "chesspieces/king.h"
#include "chesspieces/pawn.h"
#include "chesspieces/knight.h"
#include "chesspieces/queen.h"
#include "chesspieces/rook.h"
#include <QDebug>

Chess::Chess()
{

    whosTurn = ChessHelper::white;
    check = ChessHelper::noCheck;
    blackKingSideCastled = false;
    blackQueenSideCastled = false;
    whiteKingSideCastled = false;
    whiteQueenSideCastled = false;



    int chessSetup[64] = {-4, -2, -3, -5, -6, -3, -2, -4,
                         -1, -1, -1, -1, -1, -1, -1, -1,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         0, 0, 0, 0, 0, 0, 0, 0,
                         1, 1, 1, 1, 1, 1, 1, 1,
                         4, 2, 3, 5, 6, 3, 2, 4
                        };

    for(int i = 0; i < 64; i++) {
        if(chessSetup[i] != 0) {
               QVector2D pos = ChessHelper::indexToVect(i);
               switch (chessSetup[i]) {
                    case -1: chessBoard[i] = std::make_shared<Pawn>(Pawn(pos, chessSetup[i], i)); break;
                    case 1 : chessBoard[i] = std::make_shared<Pawn>(Pawn(pos, chessSetup[i], i)); break;
                    case -2 : chessBoard[i] = std::make_shared<Knight>(Knight(pos, chessSetup[i], i)); break;
                    case 2 : chessBoard[i] = std::make_shared<Knight>(Knight(pos, chessSetup[i], i)); break;
                    case -3 : chessBoard[i] = std::make_shared<Bishop>(Bishop(pos, chessSetup[i], i)); break;
                    case 3 : chessBoard[i] = std::make_shared<Bishop>(Bishop(pos, chessSetup[i], i)); break;
                    case -4 : chessBoard[i] = std::make_shared<Rook>(Rook(pos, chessSetup[i], i)); break;
                    case 4 : chessBoard[i] = std::make_shared<Rook>(Rook(pos, chessSetup[i], i)); break;
                    case -5 : chessBoard[i] = std::make_shared<Queen>(Queen(pos, chessSetup[i], i)); break;
                    case 5 : chessBoard[i] = std::make_shared<Queen>(Queen(pos, chessSetup[i], i)); break;
                    case -6 : chessBoard[i] = std::make_shared<King>(King(pos, chessSetup[i], i)); break;
                    case 6 : chessBoard[i] = std::make_shared<King>(King(pos, chessSetup[i], i)); break;
               }
        } else {
            chessBoard[i] = NULL;
        }
    }
    addBoardToHistory(ChessMove(QVector2D(0,0), QVector2D(0,0), ChessHelper::invalidMove));
}



bool Chess::makeMove(int fromIndex, int toIndex) {

    if(chessBoard[fromIndex] == NULL) {
        return false;
    }

    std::shared_ptr<ChessPiece> movingPiece = chessBoard[fromIndex];

    if(whosTurn != movingPiece->getColor())
        return false;

    int foundMove = -1;

    QVector<ChessMove> possibleMoves = movingPiece->possibleMoves(this->chessBoard);
    for(int i = 0; i < possibleMoves.size(); i++) {
        if(ChessHelper::vectToIndex(possibleMoves.at(i).getEnd()) == toIndex) {
            foundMove = i;
            break;
        }
    }

    if(foundMove == -1)
        return false;

    ChessMove validMove = possibleMoves.at(foundMove);

    if(validMove.getStatus() == ChessHelper::castle) {
        switch (ChessHelper::vectToIndex(validMove.getEnd())) {
            case 2:
                if(!castlingCheck(&blackQueenSideCastled, validMove, 3, 0, ChessHelper::black)) return false;
                else break;
             case 6:
                if(!castlingCheck(&blackKingSideCastled, validMove, 5, 7, ChessHelper::black)) return false;
                else break;
             case 62:
                if(!castlingCheck(&whiteKingSideCastled, validMove, 61, 63, ChessHelper::white)) return false;
                else break;
             case 58:
                if(!castlingCheck(&whiteQueenSideCastled, validMove, 59, 56, ChessHelper::white)) return false;
                else break;
       }
    } else if(validMove.getStatus() == ChessHelper::enPassent) {
        if(history.size() > 1) {
            ChessMove lastMove = history.at(history.size() - 1).move;
            std::unique_ptr<ChessMove> calculatedNeededMove;
            int capturedPawnIndex = -1;
            if(whosTurn == ChessHelper::white) {
                QVector2D to(validMove.getEnd().x(), 4);
                capturedPawnIndex = ChessHelper::vectToIndex(to);
                if(chessBoard[capturedPawnIndex] == NULL || chessBoard[capturedPawnIndex]->getChessPiece() != -1)
                    return false;
                calculatedNeededMove = std::make_unique<ChessMove>(QVector2D(validMove.getEnd().x(), 6), to);

            } else {
                QVector2D to (validMove.getEnd().x(), 3);
                capturedPawnIndex = ChessHelper::vectToIndex(to);
                if(chessBoard[capturedPawnIndex] == NULL || chessBoard[capturedPawnIndex]->getChessPiece() != 1)
                    return false;
                calculatedNeededMove = std::make_unique<ChessMove>(QVector2D(validMove.getEnd().x(), 1), to);
            }

            if(lastMove != *calculatedNeededMove)
                return false;

            std::shared_ptr<ChessPiece> capturedPiece = chessBoard[capturedPawnIndex];
            chessBoard[capturedPawnIndex] = NULL;
            chessBoard[fromIndex] = NULL;
            chessBoard[toIndex] = movingPiece;

            if(canHit(hit::now)) {
                chessBoard[capturedPawnIndex] = capturedPiece;
                chessBoard[fromIndex] = chessBoard[toIndex];
                chessBoard[toIndex] = NULL;
                return false;
            }
            capturedPiece->setCaptured(true);
            chessBoard[toIndex]->updatePos(ChessHelper::indexToVect(toIndex));
            updatedPieces.append(movingPiece);
            updatedPieces.append(capturedPiece);

        }
    } else if(validMove.getStatus() == ChessHelper::promotion) {
        //TODO: das hier machen ^
        //hab aber kein bock
    } else if(validMove.getStatus() == ChessHelper::capturePiece) {
        std::shared_ptr<ChessPiece> capturedPiece = chessBoard[toIndex];

        chessBoard[fromIndex] = NULL;
        chessBoard[toIndex] = movingPiece;


        if(canHit(hit::now)) {
            chessBoard[fromIndex] = chessBoard[toIndex];
            chessBoard[toIndex] = capturedPiece;
            return false;
        }

        capturedPiece->setCaptured(true);
        chessBoard[toIndex]->updatePos(ChessHelper::indexToVect(toIndex));
        updatedPieces.append(movingPiece);
        updatedPieces.append(capturedPiece);
    } else if(validMove.getStatus() == ChessHelper::standardMove) {
        chessBoard[fromIndex] = NULL;
        chessBoard[toIndex] = movingPiece;
        if(canHit(hit::now)) {
            chessBoard[fromIndex] = chessBoard[toIndex];
            chessBoard[toIndex] = NULL;
            return false;
        }
        chessBoard[toIndex]->updatePos(ChessHelper::indexToVect(toIndex));
        updatedPieces.append(movingPiece);
    }

    if(canHit(hit::nextMove)) {
        if(whosTurn == ChessHelper::white) {
            check = ChessHelper::blackCheck;
        } else {
            check = ChessHelper::whiteCheck;
        }
    } else {
        check = ChessHelper::noCheck;
    }


    if(whosTurn == ChessHelper::white)
        whosTurn = ChessHelper::black;
    else
        whosTurn = ChessHelper::white;
    //moves.append(ChessMove(ChessHelper::indexToVect(fromIndex), ChessHelper::indexToVect(toIndex)));
    addBoardToHistory(ChessMove(ChessHelper::indexToVect(fromIndex), ChessHelper::indexToVect(toIndex)));


    return true;
}

bool Chess::makeMove(ChessMove move)
{
    return makeMove(ChessHelper::vectToIndex(move.getStart()), ChessHelper::vectToIndex(move.getEnd()));
}

QVector<std::shared_ptr<const ChessPiece>> Chess::getUpdates()
{

    QVector<std::shared_ptr<const ChessPiece>> updates;

    for(int i = 0; i < this->updatedPieces.size(); i++) {
        updates.append(updatedPieces.at(i));
    }

    this->updatedPieces.clear();
    return updates;
}

QVector<ChessMove> Chess::getMoves()
{
    QVector<ChessMove> moves;
    //The first move is invalid and will be therefore skipped
    for(int i = 1; i < history.size(); i++) {
        moves.append(history.at(i).move);
    }
    return moves;
}

QVector<QPair<QVector2D, short> > Chess::getIds()
{
    QVector<QPair<QVector2D, short>> ids;
    for(int i = 0; i < 64; i++) {
        if(chessBoard[i] != NULL)
            ids.append(QPair<QVector2D, short>(chessBoard[i]->getCurrentPos(), chessBoard[i]->getId()));
    }
    return ids;
}

bool Chess::undo()
{
    if(history.size() <= 2)
        return false;
    //int x = history.size();
    //We allways want to undo two moves
    //ChessHistory tmpHistory = history.at(history.size() - 1);
    /*for(int i = 0; i < 64; i++) {
        if(tmpHistory.chessBoard[i] != NULL)
            delete tmpHistory.chessBoard[i];
    }*/

    int historyIndex = history.size() - 3;

    this->whiteKingSideCastled = history.at(historyIndex).whiteKingSideCastled;
    this->whiteQueenSideCastled = history.at(historyIndex).whiteQueenSideCastled;
    this->blackKingSideCastled = history.at(historyIndex).blackKingSideCastled;
    this->blackQueenSideCastled = history.at(historyIndex).blackQueenSideCastled;
    this->whosTurn = history.at(historyIndex).whosTurn;
    this->check = history.at(historyIndex).check;

    for(int i = 0; i < 64; i++) {
        //copying old board to current board
        if(history.at(historyIndex).chessBoard[i] != NULL) {
            this->chessBoard[i] = history.at(historyIndex).chessBoard[i]->clone();
        } else {
            this->chessBoard[i] = NULL;
        }
        //adding all pieces of old board to updatedPieces list
        if(this->chessBoard[i] != NULL)
            updatedPieces.append(this->chessBoard[i]);
    }

    history.pop_back();
    history.pop_back();

    return true;
}

bool Chess::canHit(hit hit)
{
    QVector<std::shared_ptr<ChessPiece>> allMovablePieces;
    QVector<ChessMove> allPossibleMoves;
    int kingPosition = -1;
    for(int i = 0; i < 64; i++) {
        if(chessBoard[i] != NULL )  {
            if((chessBoard[i]->getColor() != whosTurn && hit == now) || (chessBoard[i]->getColor() == whosTurn && hit == nextMove)) {
                allMovablePieces.append(chessBoard[i]);
            } else if(qAbs(chessBoard[i]->getChessPiece()) == 6)
                kingPosition = i;
        }
    }

    for(int i = 0; i < allMovablePieces.size(); i++) {
        allPossibleMoves.append(allMovablePieces.at(i)->possibleMoves(this->chessBoard));
    }

    for(int i = 0; i < allPossibleMoves.size(); i++) {
        if(allPossibleMoves.at(i).getEnd() == ChessHelper::indexToVect(kingPosition)) {
            return true;
        }
    }

    return false;

}

bool Chess::castlingCheck(bool *castleSide, ChessMove kingMove, int kingCheckPos, int rookPos, ChessHelper::color color)
{
    int piece = 4 * (color == ChessHelper::black ? -1 : 1);
    if(!*castleSide &&
        !((check == ChessHelper::blackCheck && color == ChessHelper::black) ||
          (check == ChessHelper::whiteCheck && color == ChessHelper::white)) &&
        chessBoard[rookPos] != NULL &&
        chessBoard[rookPos]->getChessPiece() == piece &&
        chessBoard[rookPos]->getMoved() == false) {

        int startPos = ChessHelper::vectToIndex(kingMove.getStart());
        int endPos = ChessHelper::vectToIndex(kingMove.getEnd());

        chessBoard[kingCheckPos] = chessBoard[startPos];
        chessBoard[startPos] = NULL;
        if(canHit(hit::now)) {
            chessBoard[startPos] = chessBoard[kingCheckPos];
            chessBoard[kingCheckPos] = NULL;
            return false;
        }

        chessBoard[endPos] = chessBoard[kingCheckPos];
        chessBoard[kingCheckPos] = NULL;

        if(canHit(hit::now)) {
            chessBoard[startPos] = chessBoard[endPos];
            chessBoard[endPos] = NULL;
            return false;
        }

        chessBoard[kingCheckPos] = chessBoard[rookPos];
        chessBoard[rookPos] = NULL;

        chessBoard[kingCheckPos]->updatePos(ChessHelper::indexToVect(kingCheckPos));
        chessBoard[endPos]->updatePos(ChessHelper::indexToVect(endPos));

        *castleSide = true;

        updatedPieces.append(chessBoard[endPos]);
        updatedPieces.append(chessBoard[kingCheckPos]);

        return true;

    }
    return false;
}

void Chess::addBoardToHistory(const ChessMove& move)
{
    std::unique_ptr<ChessPiece> tmpBoard[64];
    for(int i = 0; i < 64; i++) {
        if(chessBoard[i] == NULL)
            tmpBoard[i] = NULL;
        else {
            tmpBoard[i] = chessBoard[i]->clone();
        }
    }



    history.append(ChessHistory(tmpBoard, move, whosTurn, check,
                                whiteQueenSideCastled, whiteKingSideCastled,
                                blackQueenSideCastled, blackKingSideCastled));

}




