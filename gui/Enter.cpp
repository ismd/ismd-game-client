#include "gui/Enter.h"
#include "ui_Enter.h"
#include <QMap>
#include <QMessageBox>

Enter::Enter(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Enter)
{
    ui->setupUi(this);

    gc = new GameClient;

    connect(gc, SIGNAL(rspAuth(bool)), SLOT(slotAuth(bool)));
    connect(gc, SIGNAL(connectionSucceeded()), SLOT(slotConnectionSucceeded()));
    connect(gc, SIGNAL(connectionError()), SLOT(slotConnectionError()));
    connect(ui->pushButton, SIGNAL(clicked()), SLOT(runGame()));
}

Enter::~Enter()
{
    delete ui;
}

void Enter::runGame()
{
    ui->lProgress->setText("Connecting to server");
    gc->connectToServer(ui->eServerAddr->text());
}

void Enter::slotAuth(bool authResult)
{
    if (authResult) {
        ui->lProgress->setText("Auth succeeded");

        gw = new Game(gc);
        connect(gc, SIGNAL(rspCharacterInfo(QVariantMap)), gw, SLOT(rspCharacterInfo(QVariantMap)));
        connect(gc, SIGNAL(rspCharacterInfo(QVariantMap)), SLOT(openGameWindow()));

        ui->lProgress->setText("Getting user info");
        gc->sendToServer("reqCharacterInfo", QVariant());
    } else {
        ui->lProgress->setText("Bad login or password");

        QMessageBox msgBox(this);
        msgBox.setText(tr("Bad login or password"));
        msgBox.exec();
    }
}

void Enter::openGameWindow()
{
    gw->show();
    close();
}

void Enter::slotConnectionSucceeded()
{
    ui->lProgress->setText("Connection succeeded");

    QVariantMap msgArgs;
    msgArgs["login"] = ui->eLogin->text();
    msgArgs["password"] = ui->ePassword->text();

    gc->sendToServer("reqAuth", msgArgs);
}

void Enter::slotConnectionError()
{
    ui->lProgress->setText("Can't connect to server");

    QMessageBox msgBox(this);
    msgBox.setText(tr("Can't connect to server"));
    msgBox.exec();
}
