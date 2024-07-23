#include "communicator.h"

TCommunicator::TCommunicator(TCommParams& pars, QObject *parent)
    : QUdpSocket(parent) {
    params = pars;
    ready = bind(params.rHost, params.rPort,
                 QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
    if (ready) {
        connect(this, SIGNAL(readyRead()), this, SLOT(receive()));
    }
}

bool TCommunicator::isReady() {
    return ready;
}

void TCommunicator::send(QByteArray message) {
    if (ready) {
        writeDatagram(message, params.sHost, params.sPort);
    }
}

void TCommunicator::receive() {
    if (hasPendingDatagrams()) {
        quint64 size = pendingDatagramSize();
        QByteArray message(size,'\0');
        readDatagram(message.data(), size);

        emit received(message);
    }
}
