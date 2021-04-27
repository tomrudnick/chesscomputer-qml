#include "uci.h"
#include <QMap>


UCI::UCI(QObject *parent) : QObject(parent)
{
    connect(&uci_process, &QProcess::readyReadStandardOutput, this, &UCI::readyReadStandardOutput);
    connect(&uci_process, &QProcess::readyReadStandardError, this, &UCI::readyReadStandardError);
    connect(&uci_process, &QProcess::errorOccurred, this, &UCI::errorOccurred);
    connect(&uci_process, &QProcess::started, this, &UCI::started);
    movetime = 1000;
    status = UCI_STATUS::stopped;
}


UCI::~UCI()
{
    qInfo() << "Calling UCI Destructor";
    stop();
}

void UCI::setMovetime(int movetime)
{
    this->movetime = movetime;
}

bool UCI::setOption(QString option, QString value)
{
    if(status == UCI_STATUS::ready) {
        uci_process.write(QString("setoption name " + option + " value " + value + "\n").toLocal8Bit());
        options.insert(option, value);
        return true;
    } else {
        return false;
    }
}

bool UCI::setPosition(QVector<ChessMove> moves)
{
    if(status != UCI_STATUS::ready)
        return false;
    QString movesString;
    for(int i = 0; i < moves.size(); i++) {
        movesString.append(moves.at(i).toString());
        if((i + 1) != moves.size())
            movesString.append(" ");
    }
    uci_process.write(QString("position startpos moves " + movesString + "\n").toLocal8Bit());
    return true;
}

bool UCI::computeNextMove()
{
    if(status != UCI_STATUS::ready)
        return false;
    QString tmp = QString("go movetime " + QString::number(movetime) + "\n");
    qInfo() << tmp;
    uci_process.write(tmp.toLocal8Bit());
    status = UCI_STATUS::calculating;
    engineReady = false;
    return true;
}

void UCI::stop()
{
    if(status != UCI_STATUS::stopped) {
        uci_process.write("quit\n");
        uci_process.write("exit\n");
        uci_process.waitForFinished();
        uci_process.close();
    }
    status = UCI_STATUS::stopped;
}




void UCI::start()
{
    uci_process.start("bash", QStringList() << "-c" << "stockfish");
    status = UCI_STATUS::running;
}

void UCI::readyReadStandardOutput()
{
    QString data = QString(uci_process.readAllStandardOutput());

    if(data == stockFishIntro) {
        qInfo() << "Stockfish Intro detected...";
        uci_process.write("uci\n");
        status = UCI_STATUS::setup;
    } else if(data.endsWith("uciok\n")) {
        qInfo() << "UCI OK detected";
        uci_process.write("isready\n");
    } else if(data == "readyok\n") {
        qInfo() << "UCI is ready";
        uci_process.write("ucinewgame\n");
        status = UCI_STATUS::ready;
    } else if(data.contains("bestmove")) {
        qInfo() << data;
        respones.append(data);
        status = UCI_STATUS::ready;
        parsingBestMove(data);
    } else {
        respones.append(data);
    }

    //qInfo() << data;
}


void UCI::errorOccurred(QProcess::ProcessError error) {
    qInfo() << Q_FUNC_INFO << error;
}

void UCI::readyReadStandardError() {
    qInfo() << uci_process.readAllStandardError();
}

void UCI::started() {
    qInfo() << "UCI started";
}


void UCI::parsingInfo()
{

    for(int i = 0; i < respones.size(); i++) {
        qInfo() << respones.at(i);
    }

    int multiPV = 1;
    if(options.contains("MultiPV")) {
        multiPV = options.value("MultiPV").toInt();
    }

    QString bestMove;

    while(multiPV > 0) {
        bestMove.append(respones.at(respones.size() - 1));
        multiPV -= bestMove.count("info");
        respones.pop_back();
    }

    respones.clear();

    QVector<UCI_MOVE_RESPOND> uci_responds;
    QStringList moves = bestMove.split(QString("info"), Qt::SkipEmptyParts);
    for(int i = 0; i < moves.size(); i++) {
        QString localInfo = moves.at(i);
        localInfo.replace("info", "");
        localInfo.replace("score cp", "scorecp");
        localInfo.replace("upperbound nodes", "upperboundNodes");
        localInfo.replace("lowerbound nodes", "lowerboundNodes");
        localInfo.replace("\n", " ");
        QStringList uciList = localInfo.split(" ", Qt::SkipEmptyParts);
        QMap<QString, QString> map;
        for(int i = 0; i < uciList.size(); i+=2) {
            if(uciList[i].simplified() == "pv") {
                QString pvValue;
                for(int j = i + 1; j < uciList.size(); j++) {
                    if(uciList[j].simplified().length() != 4)
                        break;
                    pvValue.append(uciList[j].simplified());
                    if((j + 1) < uciList.size())
                        pvValue.append(" ");
                }
                map.insert("pv", pvValue);
                break;
            } else {
                map.insert(uciList[i].simplified(), uciList[i+1].simplified());
            }
        }

        ChessMove parsedMove = ChessMove::parseChessMove(map.value("pv").simplified().leftRef(4).toString());
        uci_responds.append(UCI_MOVE_RESPOND(map.value("depth").toInt(), map.value("scorecp").toFloat() / 100, parsedMove));
    }
    emit info(uci_responds);
}

void UCI::parsingBestMove(QString bestMoveString)
{
    QRegExp bestMoveReg("bestmove [a-h]\\d[a-h]\\d");
    int pos = bestMoveReg.indexIn(bestMoveString);
    ChessMove parsedMove = ChessMove::parseChessMove(bestMoveString.midRef(pos + 9, 4).toString());

    emit bestMove(parsedMove);
}
