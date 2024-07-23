#pragma once

#include "directedgraph.h"

class StateGraph : public DirectedGraph {
    int activeVertex;
public:
    StateGraph(const QStringList& values);

    int getActiveVertex() const;
    void setActiveVertex(const int vertexNum);
};
