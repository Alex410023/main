#include "interface.h"
#include "directedgraph.h"
#include "graphwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QIntValidator>
#include <QDoubleValidator>
#include <cmath>

#include <QDebug>


TInterface::TInterface(QWidget *parent)
    : QWidget(parent) {
    setWindowTitle("Работа №7");
    resize(700, 400);

    graphWindow = nullptr;

    /*
     * BASE (FIRST) LAYOUT
     */

    inputLabel = new QLabel("Введите размер матрицы");
    matrixSizeInput = new QLineEdit;
    createBtn = new QPushButton("Создать");

    connect(createBtn, &QPushButton::clicked, this, &TInterface::createButtonClicked);

    loadBtn = new QPushButton("Загрузить из файла");
    connect(loadBtn, &QPushButton::clicked, this, &TInterface::loadFromFile);

    baseLayout = new QHBoxLayout;
    baseLayout->addWidget(inputLabel);
    baseLayout->addWidget(matrixSizeInput);
    baseLayout->addWidget(createBtn);
    baseLayout->addWidget(loadBtn);

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

    /* Matrix itself is created in 'createButtonClicked()' method */

    matrixLayout = new QGridLayout;
    matrixWidget = new QWidget;
    matrixWidget->setLayout(matrixLayout);
    matrixLayout->setSpacing(40);


    /// ACTIONS WIDGET:
    saveBtn = new QPushButton("Сохранить в файл");
    connect(saveBtn, &QPushButton::clicked, this, &TInterface::saveToFile);

    createGraphBtn = new QPushButton("Создать ориентированный граф");
    connect(createGraphBtn, &QPushButton::clicked, this, &TInterface::createGraph);

    actionsLayout = new QHBoxLayout;

    actionsLayout->addWidget(saveBtn);
    actionsLayout->addWidget(createGraphBtn);

    actionsWidget = new QWidget;
    actionsWidget->setLayout(actionsLayout);


    /// WIDGET COMBINING

    secondLayout = new QVBoxLayout;
    secondLayout->addWidget(matrixWidget);
    secondLayout->addWidget(actionsWidget);

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
    delete graphWindow;
    delete directedGraph;

    delete inputLabel;
    delete matrixSizeInput;
    delete createBtn;
    delete loadBtn;
    delete baseLayout;
    delete baseWidget;

    delete firstLayout;

    delete matrixLayout;
    delete matrixWidget;

    delete saveBtn;
    delete createGraphBtn;
    delete actionsWidget;
    delete actionsLayout;

    delete secondLayout;

    delete firstLayoutWidget;
    delete secondLayoutWidget;
    delete stackedLayout;
}

void TInterface::createButtonClicked() {
    if (matrixSizeInput->text().toInt() > 0) {
        int size = matrixSizeInput->text().toInt();

        createEditor(size);

        stackedLayout->setCurrentIndex(1);
        baseLayout->removeWidget(loadBtn);
        loadBtn->setParent(nullptr);
        actionsLayout->addWidget(loadBtn);
    } else {
        QMessageBox::critical(this, "Ошибка", "Была введена неверная размерность. Введите положительное целое число.");
    }
}

void TInterface::saveToFile() {
    int size = matrixSizeInput->text().toInt();
    QString data;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QLayoutItem* item = matrixLayout->itemAtPosition(i, j);
            if (item) {
                QWidget* widget = item->widget();
                if (QLineEdit* editField = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("editField"))) {
                    int value = editField->text().toInt();
                    data += QString::number(value);
                    if (j != size - 1) {
                        data += " ";
                    }
                }
            }
        }
        if (i != size - 1) {
            data += "\n";
        }
    }

    QFileDialog *saveDialog = new QFileDialog(this);
    saveDialog->setNameFilter("Text Files (*.txt)");
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);

    if (saveDialog->exec() == QDialog::Accepted) {
        QString fileName = saveDialog->selectedFiles().first();
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            out << data;
            file.close();
        }
    }
}

void TInterface::loadFromFile() {
    QFileDialog *openDialog = new QFileDialog(this);
    openDialog->setNameFilter("Text Files (*.txt)");

    QString data;

    if (openDialog->exec() == QDialog::Accepted) {
        QString fileName = openDialog->selectedFiles().first();
        QFile file(fileName);

        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            data = in.readAll();
            file.close();
        } else {
            QMessageBox::critical(this, "Ошибка", "Ошибка при открытии файла.");
        }

        data.replace("\n", " ");
        data.replace("  ", " ");
        data = data.trimmed();
        QStringList values = data.split(" ");

        if (!isCorrectMatrix(values)) {
            QMessageBox::critical(this, "Ошибка", "Данные в файле не являются корректной матрицей.");
        } else {
            baseLayout->removeWidget(loadBtn);
            loadBtn->setParent(nullptr);
            actionsLayout->addWidget(loadBtn);

            createEditor(sqrt(values.size()));
            fillEditor(values);

            stackedLayout->setCurrentIndex(1);
        }
    }
}

QStringList TInterface::getFromEditor() {
    int size = matrixSizeInput->text().toInt();
    QStringList data;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QLayoutItem* item = matrixLayout->itemAtPosition(i, j);
            if (item) {
                QWidget* widget = item->widget();
                if (QLineEdit* editField = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("editField"))) {
                    int value = editField->text().toInt();
                    data.append(QString::number(value));
                }
            }
        }
    }
    return data;
}

void TInterface::createGraph() {
    if (graphWindow!= nullptr) {
        graphWindow->close();
        delete graphWindow;
    }

    QStringList values = getFromEditor();

    directedGraph = new DirectedGraph(values);

    graphWindow = new GraphWindow(directedGraph);
    graphWindow->show();
}

bool TInterface::isCorrectMatrix(const QStringList &values) {
    if (pow(std::sqrt(values.size()), 2) != values.size()) {    // is a square
        return false;
    }

    for (const QString &value : values) {   // all values are integers
        bool ok;
        value.toInt(&ok);
        if (!ok) {
            return false;
        }
    }

    return true;
}

void TInterface::fillEditor(const QStringList &values) {
    for (int i = 0; i < values.size(); i++) {
        QLayoutItem* item = matrixLayout->itemAt(i);
        if (QWidget* widget = item->widget()) {
            QLineEdit* lineEdit = qobject_cast<QLineEdit*>(widget->findChild<QLineEdit*>("editField"));
            if (lineEdit) {
                lineEdit->setText(values.at(i));
            }
        }
    }
    matrixSizeInput->setText(QString::number(sqrt(values.size())));
}

void TInterface::clearMatrixLayout() {
    while (QLayoutItem* item = matrixLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            delete widget;
        }
        delete item;
    }
}


QWidget* TInterface::createEditor(const int size) {
    clearMatrixLayout();

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            QWidget* editor = new QWidget;
            QHBoxLayout* editorLayout = new QHBoxLayout(editor);
            editorLayout->setContentsMargins(0, 0, 0, 0);

            QLineEdit* editField = new QLineEdit;
            editField->setAlignment(Qt::AlignCenter);
            editField->setObjectName("editField");
            editField->setText("0");

            editorLayout->addWidget(editField);

            QIntValidator* validator = new QIntValidator(editField);
            editField->setValidator(validator);

            matrixLayout->addWidget(editor, i, j);
        }
    }
}
