#include "../../include/algorithms/PathFinder.h"

PathFinder::PathFinder(RouteStrategy *strategy) : strategy(strategy) {}

void PathFinder::setStrategy(RouteStrategy *strategy)
{
    this->strategy = strategy;
}

RouteResult PathFinder::findRoute(const Graph &graph, const std::string &start, const std::string &end, const std::string &criteria)
{
    if (strategy)
        return strategy->findRoute(graph, start, end, criteria);

    // Return invalid route result if no strategy is set
    RouteResult emptyResult;
    emptyResult.isValid = false;
    return emptyResult;
}
