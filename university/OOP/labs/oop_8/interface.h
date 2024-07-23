#pragma once

#include "graphwindow.h"
#include "stategraph.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStackedLayout>
#include <QRadioButton>
#include <QFileDialog>
#include <QComboBox>


class TInterface : public QWidget {
    Q_OBJECT

    GraphWindow* graphWindow;
    StateGraph* stateGraph;


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

    QLabel* activeVertex;
    QComboBox* verticesAvailableBox;
    QHBoxLayout* activeVertextLayout;

    QLabel* eventsLabel;
    QHBoxLayout* eventsLayout;


    /// WIDGET COMBINING
    QVBoxLayout* secondLayout;


    /* LAYOUT COMBINING */
    QWidget* firstLayoutWidget;
    QWidget* secondLayoutWidget;
    QStackedLayout* stackedLayout;

    /* MATRIX EDITOR */
    void createEditor(const int size);

    QStringList getFromEditor();
    void fillEditor(const QStringList &values);
    bool isCorrectMatrix(const QStringList &values);
    void clearMatrixLayout();
    void createEventsItems();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

    QHBoxLayout *getEventsLayout() const;
    void setEventsLayout(QHBoxLayout *newEventsLayout);

private slots:
    void createButtonClicked();
    void saveToFile();
    void loadFromFile();
    void createGraph();
};
