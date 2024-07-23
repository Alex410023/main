#pragma once

#include "directedgraph.h"

#include <QMainWindow>

class GraphWindow : public QMainWindow {
    Q_OBJECT

    DirectedGraph* graph;

public:
    explicit GraphWindow(DirectedGraph* graph, QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};


