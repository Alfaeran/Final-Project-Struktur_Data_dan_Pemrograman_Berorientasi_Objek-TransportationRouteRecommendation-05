#pragma once
#include "RouteStrategy.h"

class DijkstraStrategy : public RouteStrategy
{
public:
    RouteResult findRoute(const Graph &graph, const std::string &start, const std::string &end, const std::string &criteria) override;
};
