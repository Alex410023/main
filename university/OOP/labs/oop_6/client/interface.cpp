#include "interface.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>

#include <QDebug>


TInterface::TInterface(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Работа №6");
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



    /// OPTION MODE WIDGET ///
    realBtn = new QRadioButton("Вещественные числа", this);
    complexBtn = new QRadioButton("Комплексные числа", this);
    rationalBtn = new QRadioButton("Рациональные числа", this);
    realBtn->setChecked(true);

    optionBtnLayout = new QVBoxLayout;
    optionBtnLayout->addWidget(realBtn);
    optionBtnLayout->addWidget(complexBtn);
    optionBtnLayout->addWidget(rationalBtn);

    optionBtnWidget = new QWidget;
    optionBtnWidget->setLayout(optionBtnLayout);



    firstLayout = new QHBoxLayout;
    firstLayout->addWidget(baseWidget);
    firstLayout->addWidget(optionBtnWidget);

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

    delete realBtn;
    delete complexBtn;
    delete rationalBtn;
    delete optionBtnLayout;
    delete optionBtnWidget;

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
                matrixLayout->addWidget(createEditor(), i, j);
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

    if (realBtn->isChecked()) {
        message += QString::number(0);
    }
    if (complexBtn->isChecked()) {
        message += QString::number(1);
    }
    if (rationalBtn->isChecked()) {
        message += QString::number(2);
    }

    message += "\n";

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QLayoutItem* item = matrixLayout->itemAtPosition(i, j);
            if (item) {
                QWidget* widget = item->widget();
                if (QLineEdit* firstField = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("firstField"))) {
                    QString firstValue = firstField->text();
                    if (rationalBtn->isChecked()) {
                        int firstValueInt = firstValue.toInt();
                        message += QString::number(firstValueInt);
                    } else {
                        firstValue.replace(",", ".");
                        double firstValueDouble = firstValue.toDouble();
                        message += QString::number(firstValueDouble);
                    }

                    if (QLineEdit* secondField = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("secondField"))) {
                        QString secondValue = secondField->text();
                        if (rationalBtn->isChecked()) {
                            int secondValueInt = secondValue.toInt();
                            message += "/";
                            message += QString::number(secondValueInt);
                        } else {
                            double secondValueDouble = secondValue.toDouble();
                            message += ",";
                            message += QString::number(secondValueDouble);
                        }
                    }

                    message += ";";
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

QWidget* TInterface::createEditor() {
    QWidget* editor = new QWidget;
    QHBoxLayout* editorLayout = new QHBoxLayout(editor);
    editorLayout->setContentsMargins(0, 0, 0, 0);

    QLineEdit* firstField = new QLineEdit;
    firstField->setAlignment(Qt::AlignCenter);
    firstField->setObjectName("firstField");
    firstField->setText("0");

    editorLayout->addWidget(firstField);

    if (realBtn->isChecked()) {
        QDoubleValidator* validator = new QDoubleValidator(firstField);
        validator->setLocale(QLocale::C);
        validator->setNotation(QDoubleValidator::StandardNotation);
        firstField->setValidator(validator);
        return editor;
    }

    QLabel* divider = new QLabel();
    divider->setAlignment(Qt::AlignVCenter);

    QLineEdit* secondField = new QLineEdit;
    secondField->setAlignment(Qt::AlignCenter);
    secondField->setObjectName("secondField");

    editorLayout->addWidget(divider);
    editorLayout->addWidget(secondField);

    if (complexBtn->isChecked()) {
        QDoubleValidator* firstValidator = new QDoubleValidator(firstField);
        firstValidator->setLocale(QLocale::C);
        firstValidator->setNotation(QDoubleValidator::StandardNotation);
        firstField->setValidator(firstValidator);

        QDoubleValidator* secondValidator = new QDoubleValidator(secondField);
        secondValidator->setLocale(QLocale::C);
        secondValidator->setNotation(QDoubleValidator::StandardNotation);
        secondField->setValidator(secondValidator);

        divider->setText("+");
        secondField->setText("0");
        QLabel* iLabel = new QLabel("i");
        editorLayout->addWidget(iLabel);
    }

    if (rationalBtn->isChecked()) {
        firstField->setValidator(new QIntValidator(firstField));
        secondField->setValidator(new QIntValidator(secondField));
        divider->setText("/");
        secondField->setText("1");
    }

    return editor;
}
