#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class ActionsWidget : public QWidget {
    Q_OBJECT

    QPushButton* generateButton;
    QPushButton* placeOnTableButton;

    QPushButton* moveToStackButton;
    QPushButton* moveToShelfButton;
    QPushButton* readButton;

    QVBoxLayout* buttonLayout;

public:
    explicit ActionsWidget(QWidget *parent = nullptr);
    ~ActionsWidget();

private slots:
    void generateBooks();
    void placeBooksOnTable();

    void moveToShelf();
    void moveToStack();
    void readABook();


signals:
    void generateButtonPressed();
    void placeButtonPressed();

    void moveToShelfPressed();
    void moveToStackPressed();
    void readButtonPressed();
};

