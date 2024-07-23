#pragma once

#include "graphwindow.h"
#include "directedgraph.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStackedLayout>
#include <QRadioButton>
#include <QFileDialog>


class TInterface : public QWidget {
    Q_OBJECT

    GraphWindow *graphWindow;
    DirectedGraph *directedGraph;


    /* BASE (FIRST) LAYOUT */

    /// CREATE WIDGET
    QLabel* inputLabel;
    QLineEdit* matrixSizeInput;
    QPushButton* createBtn;
    QPushButton *loadBtn;

    QHBoxLayout* baseLayout;
    QWidget* baseWidget;

    QHBoxLayout *firstLayout;


    /* ACTION (SECOND) LAYOUT */

    /// MATRIX WIDGET:
    QGridLayout* matrixLayout;
    QWidget* matrixWidget;


    /// ACTIONS WIDGET:
    QPushButton *saveBtn;
    QPushButton *createGraphBtn;
    QWidget* actionsWidget;
    QHBoxLayout* actionsLayout;


    /// WIDGET COMBINING
    QVBoxLayout* secondLayout;


    /* LAYOUT COMBINING */
    QWidget* firstLayoutWidget;
    QWidget* secondLayoutWidget;
    QStackedLayout* stackedLayout;

    /* MATRIX EDITOR */
    QWidget* createEditor(const int size);

    QStringList getFromEditor();
    void fillEditor(const QStringList &values);
    bool isCorrectMatrix(const QStringList &values);
    void clearMatrixLayout();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private slots:
    void createButtonClicked();
    void saveToFile();
    void loadFromFile();
    void createGraph();
};
