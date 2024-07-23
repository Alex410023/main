#include "stategraph.h"

StateGraph::StateGraph(const QStringList& values)
    : DirectedGraph(values)
    , activeVertex(-1) {}

int StateGraph::getActiveVertex() const {
    return activeVertex;
}

void StateGraph::setActiveVertex(const int vertex) {
    activeVertex = vertex;
}
