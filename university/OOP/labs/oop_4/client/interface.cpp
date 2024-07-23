#include "interface.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QIntValidator>

#include <QDebug>


TInterface::TInterface(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Работа №3");
    resize(700, 400);

    /*
     * BASE (FIRST) LAYOUT
     */

    inputLabel = new QLabel("Введите размер матрицы");
    matrixSizeInput = new QLineEdit;
    createBtn = new QPushButton("Создать");

    connect(createBtn, &QPushButton::clicked, this, &TInterface::createButtonClicked);

    baseLayout = new QHBoxLayout;
    baseLayout->addWidget(inputLabel);
    baseLayout->addWidget(matrixSizeInput);
    baseLayout->addWidget(createBtn);

    baseWidget = new QWidget;
    baseWidget->setLayout(baseLayout);

    firstLayout = new QHBoxLayout;
    firstLayout->addWidget(baseWidget);

    firstLayoutWidget = new QWidget;
    firstLayoutWidget->setLayout(firstLayout);

    /*
     * ACTION (SECOND) LAYOUT
     */

    /// MATRIX WIDGET:

    /* Matrix itself is created in 'detButtonClicked()' method */

    matrixLayout = new QGridLayout;
    matrixWidget = new QWidget;
    matrixWidget->setLayout(matrixLayout);
    matrixLayout->setSpacing(40);


    /// ACTIONS WIDGET:

    detBtn = new QPushButton("Печать определителя");
    connect(detBtn, &QPushButton::clicked, this, &TInterface::formRequest);

    transposeBtn = new QPushButton("Печать транспонированной матрицы");
    connect(transposeBtn, &QPushButton::clicked, this, &TInterface::formRequest);

    rankBtn = new QPushButton("Печать ранга");
    connect(rankBtn, &QPushButton::clicked, this, &TInterface::formRequest);

    printBtn = new QPushButton("Печать матрицы");
    connect(printBtn, &QPushButton::clicked, this, &TInterface::formRequest);


    actionsLayout = new QHBoxLayout;
    actionsLayout->addWidget(detBtn);
    actionsLayout->addWidget(transposeBtn);
    actionsLayout->addWidget(rankBtn);
    actionsLayout->addWidget(printBtn);

    actionsWidget = new QWidget;
    actionsWidget->setLayout(actionsLayout);


    /// OUTPUT
    output = new QLabel(this);


    /// WIDGET COMBINING

    secondLayout = new QVBoxLayout;
    secondLayout->addWidget(matrixWidget);
    secondLayout->addWidget(actionsWidget);
    secondLayout->addWidget(output);

    secondLayout->setAlignment(output, Qt::AlignCenter);

    secondLayoutWidget = new QWidget;
    secondLayoutWidget->setLayout(secondLayout);


    /*
     * LAYOUT COMBINING
     */

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(firstLayoutWidget);
    stackedLayout->addWidget(secondLayoutWidget);

    // The main layout for the widget
    setLayout(stackedLayout);

}


TInterface::~TInterface() {
    delete inputLabel;
    delete matrixSizeInput;
    delete createBtn;
    delete baseLayout;
    delete baseWidget;

    delete firstLayout;

    delete matrixLayout;
    delete matrixWidget;

    delete detBtn;
    delete transposeBtn;
    delete rankBtn;
    delete printBtn;
    delete actionsWidget;
    delete actionsLayout;

    delete output;

    delete secondLayout;

    delete firstLayoutWidget;
    delete secondLayoutWidget;
    delete stackedLayout;
}

void TInterface::createButtonClicked() {
    if (matrixSizeInput->text().toInt() > 0) {
        int size = matrixSizeInput->text().toInt();

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                matrixLayout->addWidget(createRationalEditor(), i, j);
            }
        }

        stackedLayout->setCurrentIndex(1);
    } else {
        QMessageBox::critical(this, "Ошибка", "Была введена неверная размерность. Введите положительное целое число.");
    }
}

void TInterface::formRequest() {
    QString message;

    int size = matrixSizeInput->text().toInt();

    message += QString::number(size);
    message += "\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QLayoutItem* item = matrixLayout->itemAtPosition(i, j);
            if (item) {
                QWidget* widget = item->widget();
                if (QLineEdit* numeratorEditor = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("numeratorEditor"))) {
                    int numerator = numeratorEditor->text().toInt();
                    if (QLineEdit* denominatorEditor = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("denominatorEditor"))) {
                        int denominator = denominatorEditor->text().toInt();
                        message += QString::number(numerator);
                        message += "/";
                        message += QString::number(denominator);
                        message += ";";
                    }
                }
            }
        }
    }
    message += "\n";


    QPushButton *sendBtn = (QPushButton*)sender();
    if (sendBtn == detBtn) {
        message += QString::number(0);
    }
    if (sendBtn == printBtn) {
        message += QString::number(1);
    }
    if (sendBtn == rankBtn) {
        message += QString::number(2);
    }
    if (sendBtn == transposeBtn) {
        message += QString::number(3);
    }

    emit request(message);
}

void TInterface::answer(QString message) {
    QString text;

    int lastSemiColonIndex = message.lastIndexOf(';');
    int option = message.mid(lastSemiColonIndex + 1).toInt();
    QString data = message.left(lastSemiColonIndex);

    switch (option) {
    case 0:
        text += "Determinant: ";
        break;
    case 2:
        text += "Rank: ";
        output->setText(text);
        break;
    default:
        break;
    }

    text += data;
    output->setText(text);
}

QWidget* TInterface::createRationalEditor() {
    QWidget* editor = new QWidget;
    QHBoxLayout* editorLayout = new QHBoxLayout(editor);
    editorLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit* numeratorEditor = new QLineEdit;
    numeratorEditor->setAlignment(Qt::AlignCenter);
    numeratorEditor->setObjectName("numeratorEditor");
    numeratorEditor->setValidator(new QIntValidator(numeratorEditor));
    numeratorEditor->setText("0");

    editorLayout->addWidget(numeratorEditor);

    QLabel* divider = new QLabel("/");
    divider->setAlignment(Qt::AlignVCenter);
    editorLayout->addWidget(divider);

    QLineEdit* denominatorEditor = new QLineEdit;
    denominatorEditor->setAlignment(Qt::AlignCenter);
    denominatorEditor->setObjectName("denominatorEditor");
    denominatorEditor->setValidator(new QIntValidator(denominatorEditor));
    denominatorEditor->setText("1");

    editorLayout->addWidget(denominatorEditor);

    return editor;
}
