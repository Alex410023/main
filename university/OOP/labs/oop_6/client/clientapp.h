#pragma once

#include "interface.h"
#include "communicator.h"

#include <QObject>
#include <QApplication>

class ClientApp : public QApplication {
    Q_OBJECT

    TCommunicator *comm;
    TInterface *interface;

public:
    ClientApp(int argc, char *argv[]);

public slots:
    void fromCommunicator(QByteArray message);
    void toCommunicator(QString message);
};
