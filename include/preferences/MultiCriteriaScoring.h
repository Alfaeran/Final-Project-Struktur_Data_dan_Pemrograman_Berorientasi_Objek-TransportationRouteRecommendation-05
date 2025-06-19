#pragma once
#include "UserPreferences.h"
#include <vector>

class MultiCriteriaScoring
{
public:
    static double scoreRoute(const PreferenceCriteria &criteria, const std::vector<double> &routeMetrics);
};
