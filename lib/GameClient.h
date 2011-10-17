#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QObject>
#include <QTcpSocket>

class GameClient : public QObject
{
    Q_OBJECT
public:
    explicit GameClient(QObject *parent = 0);
    void connectToServer(const QString& server);
    void sendToServer(const QString& msg, const QVariant& msgArgs);

signals:
    void rspAuth(bool);
    void rspCharacterInfo(QVariantMap);
    void connectionSucceeded();
    void connectionError();
    void rspQuests(QVariantList);
    void rspMove(QVariantMap);
    void rspCellContent(QVariantMap);
    void rspCharacterItems(QVariantList);

private slots:
    void slotConnected();
    void slotReadyRead();
    void slotError(QAbstractSocket::SocketError);

private:
    void parseResponse(const QString& msg, const QVariant& msgArgs);
    QTcpSocket* tcpSocket;
    quint16 nextBlockSize;
    bool connected;
    QString serverAddr;
};

#endif // GAMECLIENT_H
