#include "clientapp.h"

ClientApp::ClientApp(int argc, char *argv[])
    : QApplication(argc, argv) {

    TCommParams pars = { QHostAddress("127.0.0.1"), 10001,
                        QHostAddress("127.0.0.1"), 10000 };
    comm = new TCommunicator(pars, this);

    interface = new TInterface();
    interface->show();

    connect(comm, &TCommunicator::received, this, &ClientApp::fromCommunicator);
    connect(interface, &TInterface::request, this, &ClientApp::toCommunicator);

}

void ClientApp::fromCommunicator(QByteArray message) {
    interface->answer(QString(message));
}

void ClientApp::toCommunicator(QString message) {
    comm->send(QByteArray().append(message.toUtf8()));
}
