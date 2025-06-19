#include "include/preferences/MultiCriteriaScoring.h"

double MultiCriteriaScoring::scoreRoute(const PreferenceCriteria &criteria, const std::vector<double> &routeMetrics)
{
    // routeMetrics: [time, distance, cost, transfers]
    if (routeMetrics.size() < 4)
        return 0.0;
    return criteria.timeWeight * routeMetrics[0] +
           criteria.distanceWeight * routeMetrics[1] +
           criteria.costWeight * routeMetrics[2] +
           criteria.transferWeight * routeMetrics[3];
}
