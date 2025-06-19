#include "../../include/preferences/UserPreferences.h"
#include <iostream>
#include <fstream>
#include <sstream>

// Constructor for DecisionTreeNode (internal node)
DecisionTreeNode::DecisionTreeNode(const std::string &question, const std::string &attribute, double threshold)
    : question(question), attribute(attribute), threshold(threshold), isLeaf(false), decision("") {}

// Constructor for DecisionTreeNode (leaf node)
DecisionTreeNode::DecisionTreeNode(const std::string &decision, const PreferenceCriteria &criteria)
    : question(""), attribute(""), threshold(0), isLeaf(true), decision(decision), leafCriteria(criteria) {}

// Destructor
DecisionTreeNode::~DecisionTreeNode() {}

// Getter methods
std::string DecisionTreeNode::getQuestion() const { return question; }
std::string DecisionTreeNode::getAttribute() const { return attribute; }
double DecisionTreeNode::getThreshold() const { return threshold; }
bool DecisionTreeNode::getIsLeaf() const { return isLeaf; }
std::string DecisionTreeNode::getDecision() const { return decision; }
PreferenceCriteria DecisionTreeNode::getLeafCriteria() const { return leafCriteria; }

// Setter methods
void DecisionTreeNode::setLeftChild(std::shared_ptr<DecisionTreeNode> child) { leftChild = child; }
void DecisionTreeNode::setRightChild(std::shared_ptr<DecisionTreeNode> child) { rightChild = child; }

// Evaluate decision tree
PreferenceCriteria DecisionTreeNode::evaluate(const std::map<std::string, double> &userInput) const
{
    if (isLeaf)
        return leafCriteria;

    // Try to find the attribute in userInput
    auto it = userInput.find(attribute);
    if (it != userInput.end())
    {
        if (it->second <= threshold && leftChild)
            return leftChild->evaluate(userInput);
        else if (rightChild)
            return rightChild->evaluate(userInput);
    }

    // Default: if we can't evaluate, return default criteria
    return PreferenceCriteria();
}

// Print decision tree
void DecisionTreeNode::printTree(int depth) const
{
    std::string indent(depth * 2, ' ');
    if (isLeaf)
    {
        std::cout << indent << "LEAF: " << decision << " [";
        std::cout << "time=" << leafCriteria.timeWeight << ", ";
        std::cout << "distance=" << leafCriteria.distanceWeight << ", ";
        std::cout << "cost=" << leafCriteria.costWeight << ", ";
        std::cout << "transfers=" << leafCriteria.transferWeight << "]" << std::endl;
    }
    else
    {
        std::cout << indent << "NODE: " << question << " [" << attribute << " <= " << threshold << "]" << std::endl;
        if (leftChild)
        {
            std::cout << indent << "  Left: ";
            leftChild->printTree(depth + 1);
        }
        if (rightChild)
        {
            std::cout << indent << "  Right: ";
            rightChild->printTree(depth + 1);
        }
    }
}

std::string DecisionTreeNode::toString(int depth) const
{
    std::string result;
    std::string indent(depth * 2, ' ');

    if (isLeaf)
    {
        result += indent + "LEAF: " + decision + " [";
        result += "time=" + std::to_string(leafCriteria.timeWeight) + ", ";
        result += "distance=" + std::to_string(leafCriteria.distanceWeight) + ", ";
        result += "cost=" + std::to_string(leafCriteria.costWeight) + ", ";
        result += "transfers=" + std::to_string(leafCriteria.transferWeight) + "]\n";
    }
    else
    {
        result += indent + "NODE: " + question + " [" + attribute + " <= " + std::to_string(threshold) + "]\n";
        if (leftChild)
        {
            result += indent + "  Left: \n";
            result += leftChild->toString(depth + 1);
        }
        if (rightChild)
        {
            result += indent + "  Right: \n";
            result += rightChild->toString(depth + 1);
        }
    }
    return result;
}

// UserPreferences implementation

// Constructor
UserPreferences::UserPreferences() : preferenceMode("simple")
{
    // Initialize with default values
    currentCriteria = PreferenceCriteria();

    // Create a simple decision tree
    decisionTree = PreferenceManager::createDefaultDecisionTree();
}

// Constructor with initial criteria
UserPreferences::UserPreferences(const PreferenceCriteria &criteria) : preferenceMode("weighted"), currentCriteria(criteria)
{
    // Create a simple decision tree
    decisionTree = PreferenceManager::createDefaultDecisionTree();
}

// Destructor
UserPreferences::~UserPreferences() {}

// Get current preference mode
std::string UserPreferences::getPreferenceMode() const
{
    return preferenceMode;
}

// Set preference mode
void UserPreferences::setPreferenceMode(const std::string &mode)
{
    if (mode == "simple" || mode == "weighted" || mode == "tree")
        preferenceMode = mode;
}

// Get current criteria
PreferenceCriteria UserPreferences::getCriteria() const
{
    return currentCriteria;
}

// Set criteria
void UserPreferences::setCriteria(const PreferenceCriteria &criteria)
{
    currentCriteria = criteria;
}

// Update specific weight
void UserPreferences::updateWeight(const std::string &criterion, double weight)
{
    if (criterion == "time")
        currentCriteria.timeWeight = weight;
    else if (criterion == "distance")
        currentCriteria.distanceWeight = weight;
    else if (criterion == "cost")
        currentCriteria.costWeight = weight;
    else if (criterion == "transfers")
        currentCriteria.transferWeight = weight;
}

// Get main preference
std::string UserPreferences::getMainPreference() const
{
    return currentCriteria.primaryCriterion;
}

// PreferenceManager implementation

std::shared_ptr<DecisionTreeNode> PreferenceManager::createDefaultDecisionTree()
{
    // Create a simple default decision tree
    // Root: Budget concern check
    auto root = std::make_shared<DecisionTreeNode>(
        "Is budget your main concern? (1-5 scale, <=2 means yes)",
        "budget_concern",
        2.0);

    // Left branch: Budget is main concern
    PreferenceCriteria budgetFocused;
    budgetFocused.costWeight = 0.5;
    budgetFocused.timeWeight = 0.2;
    budgetFocused.distanceWeight = 0.2;
    budgetFocused.transferWeight = 0.1;
    budgetFocused.primaryCriterion = "cost";
    auto budgetLeaf = std::make_shared<DecisionTreeNode>("Budget Focused", budgetFocused);

    // Right branch: Budget is not main concern
    PreferenceCriteria timeFocused;
    timeFocused.timeWeight = 0.5;
    timeFocused.costWeight = 0.1;
    timeFocused.distanceWeight = 0.2;
    timeFocused.transferWeight = 0.2;
    timeFocused.primaryCriterion = "time";
    auto timeLeaf = std::make_shared<DecisionTreeNode>("Time Focused", timeFocused);

    root->setLeftChild(budgetLeaf);
    root->setRightChild(timeLeaf);

    return root;
}

PreferenceCriteria PreferenceManager::createTemplate(const std::string &templateName)
{
    PreferenceCriteria criteria;

    if (templateName == "fastest")
    {
        criteria.timeWeight = 0.6;
        criteria.transferWeight = 0.2;
        criteria.distanceWeight = 0.1;
        criteria.costWeight = 0.1;
        criteria.primaryCriterion = "time";
    }
    else if (templateName == "cheapest")
    {
        criteria.costWeight = 0.6;
        criteria.transferWeight = 0.2;
        criteria.timeWeight = 0.1;
        criteria.distanceWeight = 0.1;
        criteria.primaryCriterion = "cost";
    }
    else if (templateName == "comfortable")
    {
        criteria.transferWeight = 0.4;
        criteria.distanceWeight = 0.3;
        criteria.timeWeight = 0.2;
        criteria.costWeight = 0.1;
        criteria.primaryCriterion = "transfers";
    }
    else if (templateName == "shortest")
    {
        criteria.distanceWeight = 0.5;
        criteria.timeWeight = 0.2;
        criteria.transferWeight = 0.2;
        criteria.costWeight = 0.1;
        criteria.primaryCriterion = "distance";
    }
    else
    {
        // Default balanced
        criteria.timeWeight = 0.25;
        criteria.distanceWeight = 0.25;
        criteria.costWeight = 0.25;
        criteria.transferWeight = 0.25;
        criteria.primaryCriterion = "time";
    }

    return criteria;
}

std::vector<std::string> PreferenceManager::getAvailableTemplates()
{
    return {"fastest", "cheapest", "comfortable", "shortest", "balanced"};
}

bool PreferenceManager::validateWeights(const PreferenceCriteria &criteria)
{
    double total = criteria.timeWeight + criteria.distanceWeight +
                   criteria.costWeight + criteria.transferWeight;

    // Allow some tolerance for floating point arithmetic
    return (total >= 0.95 && total <= 1.05) &&
           criteria.timeWeight >= 0 && criteria.distanceWeight >= 0 &&
           criteria.costWeight >= 0 && criteria.transferWeight >= 0;
}

// File I/O operations for UserPreferences
bool UserPreferences::saveToFile(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    // Simple JSON-like format
    file << "{\n";
    file << "  \"timeWeight\": " << currentCriteria.timeWeight << ",\n";
    file << "  \"distanceWeight\": " << currentCriteria.distanceWeight << ",\n";
    file << "  \"costWeight\": " << currentCriteria.costWeight << ",\n";
    file << "  \"transferWeight\": " << currentCriteria.transferWeight << ",\n";
    file << "  \"primaryCriterion\": \"" << currentCriteria.primaryCriterion << "\",\n";
    file << "  \"preferenceMode\": \"" << preferenceMode << "\"\n";
    file << "}\n";

    return true;
}

bool UserPreferences::loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return false;
    }

    std::string line;
    PreferenceCriteria newCriteria;
    std::string newMode = "simple";

    // Simple parsing for JSON-like format
    while (std::getline(file, line))
    {
        // Remove whitespace and find key-value pairs
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos)
        {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);

            // Remove quotes, spaces, commas
            key.erase(0, key.find_first_not_of(" \t\""));
            key.erase(key.find_last_not_of(" \t\"") + 1);
            value.erase(0, value.find_first_not_of(" \t\""));
            value.erase(value.find_last_not_of(" \t\",") + 1);

            if (key == "timeWeight")
            {
                newCriteria.timeWeight = std::stod(value);
            }
            else if (key == "distanceWeight")
            {
                newCriteria.distanceWeight = std::stod(value);
            }
            else if (key == "costWeight")
            {
                newCriteria.costWeight = std::stod(value);
            }
            else if (key == "transferWeight")
            {
                newCriteria.transferWeight = std::stod(value);
            }
            else if (key == "primaryCriterion")
            {
                newCriteria.primaryCriterion = value;
            }
            else if (key == "preferenceMode")
            {
                newMode = value;
            }
        }
    }

    // Validate and apply
    if (PreferenceManager::validateWeights(newCriteria))
    {
        currentCriteria = newCriteria;
        preferenceMode = newMode;
        return true;
    }

    return false;
}
