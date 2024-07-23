#include "directedgraph.h"
#include <cmath>
#include <QDebug>


DirectedGraph::DirectedGraph(const QStringList& values)
    : numVertices(sqrt(values.size()))
    , matrix(numVertices, numVertices) {
    createMatrix(values);
    matrixToGraph();
}


void DirectedGraph::createMatrix(const QStringList& values) {
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            bool ok;
            int value = values[i * numVertices + j].toInt(&ok);
            if (ok) {
                matrix.setAt(i, j, value);
            }
        }
    }
}

void DirectedGraph::matrixToGraph() {
    vertices.clear();
    edges.clear();

    for (int i = 0; i < numVertices; i++) {
        addVertex(i);
    }

    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            if (matrix.getAt(i, j)) {
                addEdge(vertices[i], vertices[j]);
            }
        }
    }
}

void DirectedGraph::addVertex(const int vertex) {
    qreal angle = 2 * M_PI * vertex / numVertices;
    qreal x = 250 + 130 * cos(angle);
    qreal y = 250 + 130 * sin(angle);
    vertices.append(QPointF(x, y));
}


void DirectedGraph::addEdge(const QPointF& from, const QPointF& to) {
    edges.append(qMakePair(from, to));
}

QVector<QPointF> DirectedGraph::getVertices() const {
    return vertices;
}

QVector<QPair<QPointF, QPointF>> DirectedGraph::getEdges() const {
    return edges;
}

void DirectedGraph::draw(QPainter& painter) {
    qreal radius = 30;

    QPen edgePen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(edgePen);

    for (const QPair<QPointF, QPointF>& edge : edges) {
        int index = std::distance(edges.begin(), std::find(edges.begin(), edges.end(), edge));
        drawArrow(painter, edge.first, edge.second, radius, index);
    }

    QPen vertexPen(Qt::black, 2);
    QBrush vertexBrush(Qt::lightGray, Qt::SolidPattern);
    painter.setPen(vertexPen);
    painter.setBrush(vertexBrush);

    for (const QPointF& vertex : vertices) {
        drawVertex(painter, vertex, radius);
    }
}

void DirectedGraph::drawVertex(QPainter& painter, const QPointF& vertex, const qreal radius) {
    painter.drawEllipse(vertex, radius, radius);

    QFont font("Arial", 18);
    painter.setFont(font);
    QFontMetrics fontMetrics(font);

    QString label = QString::number(vertices.indexOf(vertex));
    qreal labelWidth = fontMetrics.horizontalAdvance(label);
    QRectF labelRect = QRectF(vertex - QPointF(labelWidth / 2, 0), QSizeF(labelWidth, 20));

    painter.drawText(labelRect, Qt::AlignCenter, label);
}

void DirectedGraph::drawArrow(QPainter& painter, const QPointF& start, const QPointF& end, const qreal radius, const int currentIndex) {
    qreal arrowHeadSize = 10.0;

    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter.setPen(pen);

    QPolygonF arrowHead;
    QPointF arrowHeadTip, arrowHeadLeft, arrowHeadRight, arrowHeadDirection, arrowHeadBase;

    if (start == end) {
        qreal vertexAngle = 2 * M_PI * currentIndex / numVertices;

        qreal loopRadius = radius * 0.5;
        QPointF loopCenter = start + QPointF(radius * std::cos(vertexAngle),
                                             radius * std::sin(vertexAngle));

        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(loopCenter, loopRadius, loopRadius);

        arrowHeadDirection = QPointF(std::cos(vertexAngle), std::sin(vertexAngle));
        arrowHeadDirection *= arrowHeadSize / 2;

        QPointF arrowHeadBase = loopCenter + arrowHeadDirection +
                                QPointF(loopRadius * 0.8 * std::cos(vertexAngle + M_PI / 2),
                                        loopRadius * 0.8 * std::sin(vertexAngle + M_PI / 2));
        arrowHeadTip = loopCenter + 2 * arrowHeadDirection +
                       QPointF(loopRadius * 0.8 * std::cos(vertexAngle + M_PI / 2),
                               loopRadius * 0.8 * std::sin(vertexAngle + M_PI / 2));
        arrowHeadLeft = arrowHeadBase + QPointF(-arrowHeadDirection.y(),
                                                arrowHeadDirection.x());
        arrowHeadRight = arrowHeadBase + QPointF(arrowHeadDirection.y(),
                                                 -arrowHeadDirection.x());
    } else {
        qreal angle = std::atan2(end.y() - start.y(), end.x() - start.x());
        QPointF segmentStart = start + QPointF(radius * std::cos(angle),
                                               radius * std::sin(angle));
        QPointF segmentEnd = end + QPointF(radius * std::cos(angle + M_PI),
                                           radius * std::sin(angle + M_PI));


        QPointF direction = segmentEnd - segmentStart;
        qreal length = std::hypot(direction.x(), direction.y());

        direction /= length; // normalize the direction vector

        painter.drawLine(segmentStart, segmentEnd);

        arrowHeadDirection = direction * arrowHeadSize;
        arrowHeadBase = segmentEnd - arrowHeadDirection;
        arrowHeadTip = segmentEnd;
        arrowHeadLeft = arrowHeadBase + QPointF(-arrowHeadDirection.y(), arrowHeadDirection.x());
        arrowHeadRight = arrowHeadBase + QPointF(arrowHeadDirection.y(), -arrowHeadDirection.x());
    }

    arrowHead << arrowHeadLeft << arrowHeadTip << arrowHeadRight;
    painter.setBrush(Qt::black);
    painter.drawPolygon(arrowHead);
}

