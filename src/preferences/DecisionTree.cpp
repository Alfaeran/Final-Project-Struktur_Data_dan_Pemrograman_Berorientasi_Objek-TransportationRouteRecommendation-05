#include "../../include/preferences/DecisionTree.h"
#include <iostream>
#include <sstream>

DecisionTree::DecisionTree() : root(nullptr)
{
    buildTree();
}

DecisionTree::~DecisionTree()
{
    // Smart pointers will handle cleanup automatically
}

void DecisionTree::buildTree()
{
    // Root question: What's your primary concern?
    // Budget constraint (1=very tight, 5=no constraint)
    root = std::make_shared<DecisionTreeNode>(
        "Is budget a major concern? (1-5 scale, <=2 means yes)",
        "budget_concern",
        2.0);

    // Left branch: Budget is tight (<=2)
    auto budgetTightNode = std::make_shared<DecisionTreeNode>(
        "Do you prioritize speed over comfort? (1-5 scale, >=3 means yes)",
        "speed_priority",
        3.0);

    // Budget tight + Speed priority (>=3) = Fast & Cheap
    PreferenceCriteria fastCheap;
    fastCheap.costWeight = 0.4;
    fastCheap.timeWeight = 0.4;
    fastCheap.distanceWeight = 0.1;
    fastCheap.transferWeight = 0.1;
    fastCheap.primaryCriterion = "cost";
    auto fastCheapLeaf = std::make_shared<DecisionTreeNode>("Fast & Economical", fastCheap);

    // Budget tight + Comfort priority (<3) = Economical
    PreferenceCriteria economical;
    economical.costWeight = 0.6;
    economical.transferWeight = 0.2;
    economical.timeWeight = 0.1;
    economical.distanceWeight = 0.1;
    economical.primaryCriterion = "cost";
    auto economicalLeaf = std::make_shared<DecisionTreeNode>("Most Economical", economical);

    budgetTightNode->setLeftChild(economicalLeaf); // <3 speed priority
    budgetTightNode->setRightChild(fastCheapLeaf); // >=3 speed priority

    // Right branch: Budget is not tight (>2)
    auto budgetFlexibleNode = std::make_shared<DecisionTreeNode>(
        "Is time very important? (1-5 scale, >=4 means very important)",
        "time_importance",
        4.0);

    // Budget flexible + Time not critical (<4)
    auto comfortNode = std::make_shared<DecisionTreeNode>(
        "Do you prefer fewer transfers? (1-5 scale, >=3 means yes)",
        "comfort_preference",
        3.0);

    // Budget flexible + Time not critical + Comfort priority (>=3) = Comfortable
    PreferenceCriteria comfortable;
    comfortable.transferWeight = 0.4;
    comfortable.distanceWeight = 0.3;
    comfortable.timeWeight = 0.2;
    comfortable.costWeight = 0.1;
    comfortable.primaryCriterion = "transfers";
    auto comfortableLeaf = std::make_shared<DecisionTreeNode>("Most Comfortable", comfortable);

    // Budget flexible + Time not critical + Distance priority (<3) = Scenic
    PreferenceCriteria scenic;
    scenic.distanceWeight = 0.4;
    scenic.transferWeight = 0.3;
    scenic.timeWeight = 0.2;
    scenic.costWeight = 0.1;
    scenic.primaryCriterion = "distance";
    auto scenicLeaf = std::make_shared<DecisionTreeNode>("Scenic Route", scenic);

    comfortNode->setLeftChild(scenicLeaf);       // <3 comfort preference
    comfortNode->setRightChild(comfortableLeaf); // >=3 comfort preference

    // Budget flexible + Time very important (>=4) = Fastest
    PreferenceCriteria fastest;
    fastest.timeWeight = 0.6;
    fastest.transferWeight = 0.2;
    fastest.distanceWeight = 0.1;
    fastest.costWeight = 0.1;
    fastest.primaryCriterion = "time";
    auto fastestLeaf = std::make_shared<DecisionTreeNode>("Fastest Route", fastest);

    budgetFlexibleNode->setLeftChild(comfortNode);  // <4 time importance
    budgetFlexibleNode->setRightChild(fastestLeaf); // >=4 time importance

    // Connect to root
    root->setLeftChild(budgetTightNode);     // <=2 budget concern
    root->setRightChild(budgetFlexibleNode); // >2 budget concern
}

PreferenceCriteria DecisionTree::evaluate(const std::map<std::string, double> &userInputs) const
{
    if (!root)
    {
        // Return default if tree not built
        return PreferenceCriteria();
    }

    return root->evaluate(userInputs);
}

void DecisionTree::displayTree() const
{
    if (!root)
    {
        std::cout << "Decision tree not built yet." << std::endl;
        return;
    }

    std::cout << "\n=== DECISION TREE VISUALIZATION ===" << std::endl;
    root->printTree(0);
    std::cout << "===================================" << std::endl;
}

std::string DecisionTree::getTreeVisualization() const
{
    if (!root)
    {
        return "Decision tree not built yet.";
    }

    std::stringstream ss;
    ss << "\n=== DECISION TREE STRUCTURE ===" << std::endl;
    ss << root->toString(0);
    ss << "===============================" << std::endl;
    return ss.str();
}
