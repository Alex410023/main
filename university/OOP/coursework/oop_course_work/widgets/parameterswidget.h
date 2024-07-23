#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>


class ParametersWidget : public QWidget {
    Q_OBJECT

    enum LabelName {
        stackNumber,
        volumesNumber,
        width,
        height,
        W1,
        W2,
        shelvesNumber,
        numLabels = 7
    };

    QLabel* labels[numLabels];

    enum FieldName {
        stackNumberField,
        volumesNumberField,
        widthField,
        heightField,
        W1Field,
        W2Field,
        shelvesNumberField,
        numFields = 7
    };

    QLineEdit* fields[numFields];

    QHBoxLayout* colsLayout;
    QVBoxLayout* labelsLayout;
    QVBoxLayout* fieldsLayout;
    QHBoxLayout* parametersLayout;


    void fillLabelsLayout();
    void fillFieldsLayout();
    void fillParametersLayout();

public:
    explicit ParametersWidget(QWidget *parent = nullptr);
    ~ParametersWidget();

    int getStackNumber() ;
    int getVolumesNumber() ;
    int getWidth() ;
    int getHeight() ;
    int getThickness() ;
    int getW1() ;
    int getW2() ;
    int getShelvesNumber() ;

    bool hasCorrectData();
};
