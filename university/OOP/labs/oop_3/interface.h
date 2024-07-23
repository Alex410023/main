#pragma once

#include "rational.h"

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStackedLayout>


class TInterface : public QWidget {
    Q_OBJECT

    /* BASE (FIRST) LAYOUT */

    QLabel* inputLabel;
    QLineEdit* matrixSizeInput;
    QPushButton* createBtn;
    QHBoxLayout* baseLayout;
    QWidget* baseWidget;

    QHBoxLayout *firstLayout;


    /* ACTION (SECOND) LAYOUT */

    /// MATRIX WIDGET:
    QGridLayout* matrixLayout;
    QWidget* matrixWidget;


    /// ACTIONS WIDGET:
    QPushButton* detBtn;
    QPushButton* transposeBtn;
    QPushButton* rankBtn;
    QPushButton* printBtn;
    QWidget* actionsWidget;
    QHBoxLayout* actionsLayout;

    /// OUTPUT
    QLabel* output;

    /// WIDGET COMBINING
    QVBoxLayout* secondLayout;


    /* LAYOUT COMBINING */
    QWidget* firstLayoutWidget;
    QWidget* secondLayoutWidget;
    QStackedLayout* stackedLayout;

    /* MATRIX EDITOR */
    QWidget* createRationalEditor(TRational* rational);

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

private slots:
    void createButtonClicked();
    void detButtonClicked();
    void transposeButtonClicked();
    void rankButtonClicked();
    void printButtonClicked();
};
