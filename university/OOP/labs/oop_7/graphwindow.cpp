#include "graphwindow.h"

#include <QPainter>

GraphWindow::GraphWindow(DirectedGraph* graph, QWidget* parent)
    : QMainWindow(parent)
    , graph(graph) {
    setWindowTitle("Ориентированный граф");
    resize(500, 500);
}

void GraphWindow::paintEvent(QPaintEvent* event) {
    QMainWindow::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    graph->draw(painter);
}
