#include "lib/GameClient.h"
#include <QTime>

GameClient::GameClient(QObject *parent) :
    QObject(parent), nextBlockSize(0), connected(false)
{
}

void GameClient::slotReadyRead()
{
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_7);

    for (;;) {
        if (!nextBlockSize) {
            if (tcpSocket->bytesAvailable() < sizeof(quint16))
                break;

            in >> nextBlockSize;
        }

        if (tcpSocket->bytesAvailable() < nextBlockSize)
            break;

        QTime time;
        QString msg;
        QVariant msgArgs;

        in >> time >> msg >> msgArgs;

        parseResponse(msg, msgArgs);

        nextBlockSize = 0;
    }
}

void GameClient::slotConnected()
{
    connected = true;
    emit connectionSucceeded();
}

void GameClient::slotError(QAbstractSocket::SocketError err)
{
    QString strError = "Error: " + (err == QAbstractSocket::HostNotFoundError ?
                                        "The host was not found" :
                                        err == QAbstractSocket::RemoteHostClosedError ?
                                            "The remote host is closed" :
                                            err == QAbstractSocket::ConnectionRefusedError ?
                                                "The connection was refused" :
                                                QString(tcpSocket->errorString()));

    emit connectionError();
    qDebug() << strError;
    connected = false;
}

void GameClient::sendToServer(const QString& msg, const QVariant& msgArgs)
{
    if (!connected)
        return;

    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_7);
    out << quint16(0) << msg << msgArgs;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    tcpSocket->write(arrBlock);

    qDebug() << "SEND: " + msg;
}

void GameClient::parseResponse(const QString& msg, const QVariant& msgArgs)
{
    qDebug() << "RECEIVE: " + msg;

    if (msg == "rspAuth")
        emit rspAuth(msgArgs.toBool());
    else if (msg == "rspCharacterInfo")
        emit rspCharacterInfo(msgArgs.toMap());
    else if (msg == "rspQuests")
        emit rspQuests(msgArgs.toList());
    else if (msg == "rspMove")
        emit rspMove(msgArgs.toMap());
    else if (msg == "rspCellContent")
        emit rspCellContent(msgArgs.toMap());
    else if (msg == "rspCharacterItems")
        emit rspCharacterItems(msgArgs.toList());
}

void GameClient::connectToServer(const QString &server)
{
    serverAddr = server;
    int socketNumber = 2327;

    tcpSocket = new QTcpSocket(this);
    tcpSocket->connectToHost(serverAddr, socketNumber);

    connect(tcpSocket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(tcpSocket, SIGNAL(readyRead()), SLOT(slotReadyRead()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            SLOT(slotError(QAbstractSocket::SocketError)));
}
