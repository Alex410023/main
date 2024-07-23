#pragma once

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QStackedLayout>
#include <QRadioButton>


class TInterface : public QWidget {
    Q_OBJECT

    /* BASE (FIRST) LAYOUT */

    /// CREATE WIDGET
    QLabel* inputLabel;
    QLineEdit* matrixSizeInput;
    QPushButton* createBtn;
    QHBoxLayout* baseLayout;
    QWidget* baseWidget;

    /// OPTION MODE WIDGET
    QRadioButton* realBtn;
    QRadioButton* complexBtn;
    QRadioButton* rationalBtn;
    QVBoxLayout* optionBtnLayout;
    QWidget* optionBtnWidget;


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
    QWidget* createEditor();

public:
    TInterface(QWidget *parent = nullptr);
    ~TInterface();

public slots:
    void answer(QString answer);

private slots:
    void createButtonClicked();
    void formRequest();

signals:
    void request(QString request);
};
