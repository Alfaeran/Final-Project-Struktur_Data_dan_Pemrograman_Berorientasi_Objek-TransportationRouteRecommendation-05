#pragma once
#include "UserPreferences.h"
#include <iostream>
#include <memory>

class DecisionTree
{
public:
    DecisionTree();
    ~DecisionTree();

    void buildTree();
    PreferenceCriteria evaluate(const std::map<std::string, double> &userInputs) const;
    void displayTree() const;
    std::string getTreeVisualization() const;

private:
    std::shared_ptr<DecisionTreeNode> root;

    // Helper methods for building tree
    std::shared_ptr<DecisionTreeNode> createTimeBasedBranch();
    std::shared_ptr<DecisionTreeNode> createCostBasedBranch();
    std::shared_ptr<DecisionTreeNode> createComfortBasedBranch();
    std::shared_ptr<DecisionTreeNode> createQuickBranch();
};
