#include "parameterswidget.h"
#include "constants.h"

#include <QIntValidator>


ParametersWidget::ParametersWidget(QWidget *parent)
    : QWidget{parent} {
    colsLayout = new QHBoxLayout;
    labelsLayout = new QVBoxLayout;
    fieldsLayout = new QVBoxLayout;
    parametersLayout = new QHBoxLayout;

    fillLabelsLayout();
    fillFieldsLayout();
    fillParametersLayout();

    setLayout(parametersLayout);
    setMaximumWidth(150);
}

ParametersWidget::~ParametersWidget() {
    for (int i = 0; i < numLabels; i++) {
        QLabel* label = labels[i];
        delete label;
        labels[i] = nullptr;
    }

    for (int i = 0; i < numFields; i++) {
        QLineEdit* field = fields[i];
        delete field;
        fields[i] = nullptr;
    }

    delete colsLayout;
    delete labelsLayout;
    delete fieldsLayout;
    delete parametersLayout;
}

int ParametersWidget::getStackNumber()  {
    return fields[stackNumberField]->text().toInt();
}

int ParametersWidget::getVolumesNumber()  {
    return fields[volumesNumberField]->text().toInt();
}

int ParametersWidget::getWidth()  {
    return fields[widthField]->text().toInt();
}

int ParametersWidget::getHeight()  {
    return fields[heightField]->text().toInt();
}

int ParametersWidget::getW1()  {
    return fields[W1Field]->text().toInt();
}

int ParametersWidget::getW2()  {
    return fields[W2Field]->text().toInt();
}

int ParametersWidget::getShelvesNumber()  {
    return fields[shelvesNumberField]->text().toInt();
}


void ParametersWidget::fillLabelsLayout() {
    labels[stackNumber] = new QLabel("Стопки:");
    labels[volumesNumber] = new QLabel("Томов:");
    labels[width] = new QLabel("Ширина:");
    labels[height] = new QLabel("Высота:");
    labels[W1] = new QLabel("W1:");
    labels[W2] = new QLabel("W2:");
    labels[shelvesNumber] = new QLabel("Полки:");

    for (int i = 0; i < numLabels; i++) {
        labelsLayout->addWidget(labels[i]);
    }
}

void ParametersWidget::fillFieldsLayout() {
    fields[stackNumberField] = new QLineEdit(QString::number(constants::S));
    fields[volumesNumberField] = new QLineEdit(QString::number(constants::N));
    fields[widthField] = new QLineEdit(QString::number(constants::L));
    fields[heightField] = new QLineEdit(QString::number(constants::H));
    fields[W1Field] = new QLineEdit(QString::number(constants::W1));
    fields[W2Field] = new QLineEdit(QString::number(constants::W2));
    fields[shelvesNumberField] = new QLineEdit(QString::number(constants::M));

    for (int i = 0; i < numFields; i++) {
        fields[i]->setValidator(new QIntValidator(fields[i]));
    }

    for (int i = 0; i < numLabels; i++) {
        labels[i]->setFixedHeight(fields[i]->sizeHint().height());
    }

    for (int i = 0; i < numFields; i++) {
        fieldsLayout->addWidget(fields[i]);
    }
}

void ParametersWidget::fillParametersLayout() {
    colsLayout->addLayout(labelsLayout);
    colsLayout->addLayout(fieldsLayout);
    parametersLayout->addLayout(colsLayout);
}

bool ParametersWidget::hasCorrectData() {
    for (int i = 0; i < numFields; i++) {
        if (fields[i]->text().toInt() <= 0) {
            return false;
        }
    }
    return true;
}
