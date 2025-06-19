#pragma once
#include "RouteStrategy.h"

class PathFinder
{
public:
    PathFinder(RouteStrategy *strategy);
    void setStrategy(RouteStrategy *strategy);
    RouteResult findRoute(const Graph &graph, const std::string &start, const std::string &end, const std::string &criteria);

private:
    RouteStrategy *strategy;
};
