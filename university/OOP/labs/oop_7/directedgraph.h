#pragma once

#include "matrix.h"

#include <QVector>
#include <QPointF>
#include <QPainter>

class DirectedGraph {
private:
    int numVertices;
    QVector<QPointF> vertices;
    QVector<QPair<QPointF, QPointF>> edges;

    Matrix<int> matrix;

    void createMatrix(const QStringList& values);
    void matrixToGraph();

public:
    DirectedGraph(const QStringList& values);

    void addVertex(const int vertex);
    void addEdge(const QPointF& from, const QPointF& to);

    QVector<QPointF> getVertices() const;
    QVector<QPair<QPointF, QPointF>> getEdges() const;

    void draw(QPainter& painter);
    void drawVertex(QPainter& painter, const QPointF& vertex, const qreal radius);
    void drawArrow(QPainter& painter, const QPointF& start, const QPointF& end, const qreal radius, const int currentIndex);

};

