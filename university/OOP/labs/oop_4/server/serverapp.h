#pragma once

#include <QObject>
#include <QCoreApplication>

#include "communicator.h"

class ServerApp : public QCoreApplication {
    Q_OBJECT

    TCommunicator *comm;

public:
    ServerApp(int argc, char *argv[]);

public slots:
    void receive(QByteArray message);
};

