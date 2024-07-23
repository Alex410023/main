#include "actionswidget.h"

ActionsWidget::ActionsWidget(QWidget *parent)
    : QWidget{parent} {

    generateButton = new QPushButton("Generate");
    placeOnTableButton = new QPushButton("Place on screen");

    moveToShelfButton = new QPushButton("Move to shelf");
    moveToStackButton = new QPushButton("Move to stack");
    readButton = new QPushButton("Read a book");

    buttonLayout = new QVBoxLayout;

    buttonLayout->addWidget(generateButton);
    buttonLayout->addWidget(placeOnTableButton);

    buttonLayout->addWidget(moveToShelfButton);
    buttonLayout->addWidget(moveToStackButton);
    buttonLayout->addWidget(readButton);

    connect(generateButton, &QPushButton::clicked, this, &ActionsWidget::generateBooks);
    connect(placeOnTableButton, &QPushButton::clicked, this, &ActionsWidget::placeBooksOnTable);

    connect(moveToShelfButton, &QPushButton::clicked, this, &ActionsWidget::moveToShelf);
    connect(moveToStackButton, &QPushButton::clicked, this, &ActionsWidget::moveToStack);
    connect(readButton, &QPushButton::clicked, this, &ActionsWidget::readABook);

    setLayout(buttonLayout);
    setMaximumWidth(150);
}

ActionsWidget::~ActionsWidget() {
    delete generateButton;
    delete placeOnTableButton;

    delete moveToStackButton;
    delete moveToShelfButton;
    delete readButton;

    delete buttonLayout;
}

void ActionsWidget::generateBooks() {
    emit generateButtonPressed();
}

void ActionsWidget::placeBooksOnTable() {
    emit placeButtonPressed();
}

void ActionsWidget::moveToShelf() {
    emit moveToShelfPressed();
}

void ActionsWidget::moveToStack() {
    emit moveToStackPressed();
}

void ActionsWidget::readABook() {
    emit readButtonPressed();
}
