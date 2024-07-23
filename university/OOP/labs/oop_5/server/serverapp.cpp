#include "serverapp.h"
#include "squarematrix.h"
#include "communicator.h"

#include <QDebug>
#include <QTextStream>
#include <iostream>
#include <sstream>
#include <QString>


ServerApp::ServerApp(int argc, char *argv[])
    : QCoreApplication(argc, argv) {

    TCommParams pars = { QHostAddress("127.0.0.1"), 10000,
                        QHostAddress("127.0.0.1"), 10001 };
    comm = new TCommunicator(pars, this);

    connect(comm, &TCommunicator::received, this, &ServerApp::receive);
    qDebug() << "Сервер запущен.";
}

void ServerApp::receive(QByteArray message) {
    QString answer;
    TRational rational;

    int firstNewlineIndex = message.indexOf('\n');
    int size = QString(message.left(firstNewlineIndex)).toInt();

    int lastNewlineIndex = message.lastIndexOf('\n');
    int option = QString(message.mid(lastNewlineIndex + 1)).toInt();

    SquareMatrix squareMatrix(size);

    message = message.mid(firstNewlineIndex + 1, lastNewlineIndex - firstNewlineIndex - 1);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            message >> rational;
            squareMatrix.setAt(i, j, rational);
        }
    }

    switch (option) {
    case 0:
        answer << squareMatrix.calculateDeterminant();
        qDebug() << "Действие: Вычисление определителя";
        break;
    case 1: {
        std::stringstream ss;
        std::streambuf *coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        squareMatrix.printMatrix();

        std::cout.rdbuf(coutbuf);
        std::string matrixString = ss.str();

        answer += QString::fromStdString(matrixString);

        qDebug() << "Действие: Печать матрицы";
        break;
    }
    case 2:
        answer += QString().setNum(squareMatrix.calculateRank());
        qDebug() << "Действие: Вычисление ранга";
        break;
    case 3: {
        std::stringstream ss;
        std::streambuf *coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(ss.rdbuf());

        squareMatrix.transpose().printMatrix();

        std::cout.rdbuf(coutbuf);
        std::string matrixString = ss.str();

	answer += "Transposed ";
        answer += QString::fromStdString(matrixString);

        qDebug() << "Действие: Печать обратной матрицы";
        break;
    }
    default:
        return;
    }

    answer += ";";
    answer += QString().setNum(option);

    comm->send(QByteArray().append(answer.toUtf8()));
    qDebug() << "Ответ отправлен\n";
}
