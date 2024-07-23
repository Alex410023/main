#pragma once

#include "table.h"
#include "rack.h"
#include "bookitem.h"

#include "parameterswidget.h"
#include "actionswidget.h"
#include "viewwidget.h"

#include <QMainWindow>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

    Table* table;
    Rack* rack;

    ParametersWidget* parametersWidget;
    ActionsWidget* actionsWidget;
    ViewWidget* viewWidget;

    QHBoxLayout* mainLayout;

    QWidget* centralWidget;

    int getStackNumber();
    void read(BookItem* bookItem);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createInterface();
    void createObjects();

public slots:
    void generateButtonPressed();
    void placeButtonPressed();

    void moveToShelfPressed();
    void moveToStackPressed();
    void readButtonPressed();

    void handleSelected(BookItem* bookItem);
};
