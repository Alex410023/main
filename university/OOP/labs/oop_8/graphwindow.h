#pragma once

#include "stategraph.h"

#include <QMainWindow>

class GraphWindow : public QMainWindow {
    Q_OBJECT

    StateGraph* graph;

public:
    explicit GraphWindow(StateGraph* graph, QWidget* parent = nullptr);
    void updateGraph(StateGraph* newGraph);

protected:
    void paintEvent(QPaintEvent* event) override;
};


