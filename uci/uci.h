#ifndef UCI_H
#define UCI_H

#include <QObject>
#include <QDebug>
#include <QProcess>

#include "chessmove.h"
#include <QVector>
#include <QMap>

enum UCI_STATUS {
    stopped,
    running,
    setup,
    ready,
    calculating
};

struct UCI_MOVE_RESPOND {
    int depth;
    float score;
    ChessMove move;
    UCI_MOVE_RESPOND(int depth, float score, const ChessMove& move)
        : depth(depth), score(score), move(move) {

    }
};

class UCI : public QObject
{
    Q_OBJECT
public:
    explicit UCI(QObject *parent = nullptr);
    ~UCI();

    void setMovetime(int movetime);
    bool setOption(QString option, QString value);
    bool setPosition(QVector<ChessMove> moves);
    bool computeNextMove();



public slots:
    void start();
    void stop();

signals:
    void output(QString data);
    void info(QVector<UCI_MOVE_RESPOND> respond);
    void bestMove(ChessMove move);

private slots:
    void errorOccurred(QProcess::ProcessError error);
    void readyReadStandardError();
    void readyReadStandardOutput();
    void started();

private:
    void parsingInfo();
    void parsingBestMove(QString bestMove);


    QProcess uci_process;
    QVector<QString> respones;
    QMap<QString, QString> options;
    UCI_STATUS status;
    int movetime;
    bool engineReady = false;
    const QString stockFishIntro = "Stockfish 13 by the Stockfish developers (see AUTHORS file)\n";

};

#endif // UCI_H
