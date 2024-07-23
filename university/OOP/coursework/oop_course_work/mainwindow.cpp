#include "mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QAbstractButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Вариант №5");
    resize(600, 400);

    createInterface();
    createObjects();
}


MainWindow::~MainWindow() {
    delete parametersWidget;
    delete actionsWidget;
    delete viewWidget;

    delete mainLayout;

    delete centralWidget;
}

void MainWindow::createInterface() {
    mainLayout = new QHBoxLayout;
    QVBoxLayout* optionsLayout = new QVBoxLayout;

    parametersWidget = new ParametersWidget(this);
    actionsWidget = new ActionsWidget(this);
    viewWidget = new ViewWidget(this);

    connect(actionsWidget, &ActionsWidget::generateButtonPressed, this, &MainWindow::generateButtonPressed);
    connect(actionsWidget, &ActionsWidget::placeButtonPressed, this, &MainWindow::placeButtonPressed);

    connect(actionsWidget, &ActionsWidget::moveToShelfPressed, this, &MainWindow::moveToShelfPressed);
    connect(actionsWidget, &ActionsWidget::moveToStackPressed, this, &MainWindow::moveToStackPressed);
    connect(actionsWidget, &ActionsWidget::readButtonPressed, this, &MainWindow::readButtonPressed);


    optionsLayout->addWidget(actionsWidget);
    optionsLayout->addWidget(parametersWidget);

    mainLayout->addLayout(optionsLayout);
    mainLayout->addWidget(viewWidget);

    centralWidget = new QWidget;
    centralWidget->setLayout(mainLayout);
    centralWidget->setObjectName("centralWidget");
    setCentralWidget(centralWidget);

    connect(viewWidget, &ViewWidget::bookItemSelected, this, &MainWindow::handleSelected);
}

void MainWindow::createObjects() {
    table = new Table(parametersWidget->getStackNumber());

    qreal shelfWidth = parametersWidget->getVolumesNumber() *
                       parametersWidget->getWidth() * 1.2 /
                       parametersWidget->getShelvesNumber();
    rack = new Rack(parametersWidget->getShelvesNumber(),
                    shelfWidth,
                    parametersWidget->getHeight());
}

void MainWindow::generateButtonPressed() {
    if (parametersWidget->hasCorrectData()) {
        createObjects();

        table->generateBooks(parametersWidget->getVolumesNumber(),
                             parametersWidget->getW1(),
                             parametersWidget->getW2(),
                             parametersWidget->getWidth(),
                             parametersWidget->getHeight());

    } else {
        QMessageBox::critical(this, "Error", "Допустимы только положительные числа");
    }
}

void MainWindow::placeButtonPressed() {
    if (table->booksGenerated()) {
        viewWidget->setTable(table);
        viewWidget->setTable(table);
        viewWidget->setRack(rack, table->getWidth());
        viewWidget->setRack(rack, table->getWidth());
    } else {
        QMessageBox::critical(this, "Error", "Книги не распределены");
    }
}

int MainWindow::getStackNumber() {
    QStringList options;
    for (int i = 0; i < parametersWidget->getStackNumber(); i++) {
        options.append(QString("Stack %1").arg(i));
    }
    options.append("Form new stack");

    bool ok;
    QString selectedOption = QInputDialog::getItem(nullptr, "Book Options",
                                                   "What do you want to do?",
                                                   options, 0, false, &ok);

    if (ok && !selectedOption.isEmpty()) {
        if (selectedOption == "Form new stack") {
            return -1; // new stack
        } else {
            return selectedOption.mid(6).toInt();
        }
    }
    return -1;
}

void MainWindow::read(BookItem* bookItem) {
    if (viewWidget) {
        bookItem->setVisible(false);

        QString str = "Some text example\n";
        str += "Book number is: " + QString::number(bookItem->getBook().getBookNumber());

        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Book");
        msgBox.setText(str);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.exec();

        QObject::connect(&msgBox, &QMessageBox::buttonClicked, [&](QAbstractButton *button) {
            if (button == msgBox.button(QMessageBox::Ok)) {
                bookItem->setVisible(true);
            }
        });
    }
}

void MainWindow::handleSelected(BookItem* bookItem) {
    const Book& book = bookItem->getBook();

    if (viewWidget->getMoveToShelfMode()) {
        if (rack->addBook(book)) {
            table->removeFromTable(book);
            viewWidget->setMoveToShelfMode(false);
        } else {
            QMessageBox::critical(this, "Error", "No space available");
        }

    } else if (viewWidget->getMoveToStackMode()) {
        int stackNumber = getStackNumber();
        table->addToTable(book, stackNumber);
        rack->removeFromRack(book);
        viewWidget->setMoveToStackMode(false);
    } else if (viewWidget->getReadMode()) {
        read(bookItem);
        viewWidget->setReadMode(false);
    }

    viewWidget->setTable(table);
    viewWidget->setRack(rack, table->getWidth());
}

void MainWindow::moveToShelfPressed() {
    if (table->booksGenerated()) {
        QMessageBox::information(this, "MOVE TO SHELF", "Choose a book");
        viewWidget->setMoveToShelfMode(true);
    }
}

void MainWindow::moveToStackPressed() {
    if (table->booksGenerated()) {
        QMessageBox::information(this, "MOVE TO STACK", "Choose a book");
        viewWidget->setMoveToStackMode(true);
    }
}

void MainWindow::readButtonPressed() {
    if (table->booksGenerated()) {
        QMessageBox::information(this, "READ", "Choose a book");
        viewWidget->setReadMode(true);
    }
}
