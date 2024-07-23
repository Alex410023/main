#include "graphwindow.h"

#include <QPainter>

GraphWindow::GraphWindow(StateGraph* graph, QWidget* parent)
    : QMainWindow(parent)
    , graph(graph) {
    setWindowTitle("Граф состояний");
    resize(500, 500);
}

void GraphWindow::updateGraph(StateGraph *newGraph) {
    delete graph;
    graph = newGraph;
    update();
}

void GraphWindow::paintEvent(QPaintEvent* event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    graph->draw(painter, graph->getActiveVertex());
}
