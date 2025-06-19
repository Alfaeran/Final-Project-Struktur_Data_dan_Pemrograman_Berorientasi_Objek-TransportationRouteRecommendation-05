#ifndef USER_PREFERENCES_H
#define USER_PREFERENCES_H

#include <string>
#include <map>
#include <vector>
#include <memory>

/**
 * @struct PreferenceCriteria
 * @brief Represents user preference criteria for route selection
 */
struct PreferenceCriteria
{
    double timeWeight;            ///< Weight for time optimization (0.0 - 1.0)
    double distanceWeight;        ///< Weight for distance optimization (0.0 - 1.0)
    double costWeight;            ///< Weight for cost optimization (0.0 - 1.0)
    double transferWeight;        ///< Weight for transfer optimization (0.0 - 1.0)
    std::string primaryCriterion; ///< Primary optimization criterion

    PreferenceCriteria() : timeWeight(0.25), distanceWeight(0.25),
                           costWeight(0.25), transferWeight(0.25),
                           primaryCriterion("time") {}
};

/**
 * @class DecisionTreeNode
 * @brief Node for decision tree-based preference system
 */
class DecisionTreeNode
{
private:
    std::string question;                         ///< Question asked at this node
    std::string attribute;                        ///< Attribute being tested
    double threshold;                             ///< Threshold value for comparison
    std::shared_ptr<DecisionTreeNode> leftChild;  ///< Left child (for <= threshold)
    std::shared_ptr<DecisionTreeNode> rightChild; ///< Right child (for > threshold)
    bool isLeaf;                                  ///< Whether this is a leaf node
    std::string decision;                         ///< Decision if this is a leaf
    PreferenceCriteria leafCriteria;              ///< Preference criteria if leaf

public:
    /**
     * @brief Constructor for internal node
     */
    DecisionTreeNode(const std::string &question, const std::string &attribute, double threshold);

    /**
     * @brief Constructor for leaf node
     */
    DecisionTreeNode(const std::string &decision, const PreferenceCriteria &criteria);

    /**
     * @brief Destructor
     */
    ~DecisionTreeNode();

    // Getter methods
    std::string getQuestion() const;
    std::string getAttribute() const;
    double getThreshold() const;
    bool getIsLeaf() const;
    std::string getDecision() const;
    PreferenceCriteria getLeafCriteria() const;

    // Setter methods
    void setLeftChild(std::shared_ptr<DecisionTreeNode> child);
    void setRightChild(std::shared_ptr<DecisionTreeNode> child);

    /**
     * @brief Evaluate the decision tree with given input
     * @param userInput Map of attribute values
     * @return Preference criteria based on decision tree
     */
    PreferenceCriteria evaluate(const std::map<std::string, double> &userInput) const;

    /**
     * @brief Print the decision tree structure
     * @param depth Current depth for indentation
     */
    void printTree(int depth = 0) const;

    /**
     * @brief Get string representation of the subtree
     * @param depth Current depth for indentation
     * @return String representation
     */
    std::string toString(int depth = 0) const;
};

/**
 * @class UserPreferences
 * @brief Manages user preferences for route optimization
 */
class UserPreferences
{
private:
    PreferenceCriteria currentCriteria;               ///< Current preference criteria
    std::shared_ptr<DecisionTreeNode> decisionTree;   ///< Decision tree for preferences
    std::string preferenceMode;                       ///< Mode: "simple", "weighted", "tree"
    std::map<std::string, std::string> userProfile;   ///< User profile information
    std::vector<PreferenceCriteria> savedPreferences; ///< Saved preference sets

public:
    /**
     * @brief Default constructor
     */
    UserPreferences();

    /**
     * @brief Constructor with initial criteria
     */
    UserPreferences(const PreferenceCriteria &criteria);

    /**
     * @brief Destructor
     */
    ~UserPreferences();

    // Preference criteria management
    /**
     * @brief Set preference criteria
     * @param criteria New preference criteria
     */
    void setCriteria(const PreferenceCriteria &criteria);

    /**
     * @brief Get current preference criteria
     * @return Current preference criteria
     */
    PreferenceCriteria getCriteria() const;

    /**
     * @brief Update specific weight
     * @param criterion Criterion name (time, distance, cost, transfer)
     * @param weight New weight value
     */
    void updateWeight(const std::string &criterion, double weight);

    /**
     * @brief Normalize weights to sum to 1.0
     */
    void normalizeWeights();

    // Decision tree management
    /**
     * @brief Set decision tree for preference evaluation
     * @param tree Root node of the decision tree
     */
    void setDecisionTree(std::shared_ptr<DecisionTreeNode> tree);

    /**
     * @brief Build simple decision tree based on user input
     */
    void buildSimpleDecisionTree();

    /**
     * @brief Build interactive decision tree through user input
     */
    void buildInteractiveDecisionTree();

    /**
     * @brief Evaluate preferences using decision tree
     * @param userInput Map of user input values
     * @return Evaluated preference criteria
     */
    PreferenceCriteria evaluateWithTree(const std::map<std::string, double> &userInput) const;

    // Preference mode management
    /**
     * @brief Set preference mode
     * @param mode Preference mode (simple, weighted, tree)
     */
    void setPreferenceMode(const std::string &mode);

    /**
     * @brief Get current preference mode
     * @return Current preference mode
     */
    std::string getPreferenceMode() const;

    // User profile management
    /**
     * @brief Set user profile information
     * @param key Profile key
     * @param value Profile value
     */
    void setUserProfile(const std::string &key, const std::string &value);

    /**
     * @brief Get user profile information
     * @param key Profile key
     * @return Profile value
     */
    std::string getUserProfile(const std::string &key) const;

    // Preference persistence
    /**
     * @brief Save current preferences to the saved list
     * @param name Name for the preference set
     */
    void saveCurrentPreferences(const std::string &name);

    /**
     * @brief Load saved preferences by index
     * @param index Index of saved preferences
     * @return True if successfully loaded
     */
    bool loadSavedPreferences(int index);

    /**
     * @brief Get list of saved preference names
     * @return Vector of preference names
     */
    std::vector<std::string> getSavedPreferenceNames() const;

    // Interactive preference setup
    /**
     * @brief Interactive setup of preferences through console
     */
    void interactiveSetup();

    /**
     * @brief Quick setup with predefined templates
     * @param templateName Template name (fast, cheap, comfortable, balanced)
     */
    void quickSetup(const std::string &templateName);

    // Utility methods
    /**
     * @brief Print current preferences
     */
    void printPreferences() const;

    /**
     * @brief Get string representation of preferences
     * @return String representation
     */
    std::string toString() const;

    /**
     * @brief Validate preference criteria
     * @return True if valid, false otherwise
     */
    bool validateCriteria() const; /**
                                    * @brief Reset preferences to default
                                    */
    void resetToDefault();

    /**
     * @brief Get the main preference criterion
     * @return The primary preference criterion as a string
     */
    std::string getMainPreference() const; /**
                                            * @brief Calculate preference score for a route
                                            * @param distance Route distance
                                            * @param time Route time
                                            * @param cost Route cost
                                            * @param transfers Route transfers
                                            * @return Preference score (lower is better)
                                            */
    double calculatePreferenceScore(double distance, int time, double cost, int transfers) const;

    // File I/O operations
    /**
     * @brief Save preferences to file
     * @param filename Filename to save to
     * @return True if successful, false otherwise
     */
    bool saveToFile(const std::string &filename) const;

    /**
     * @brief Load preferences from file
     * @param filename Filename to load from
     * @return True if successful, false otherwise
     */
    bool loadFromFile(const std::string &filename);
};

/**
 * @class PreferenceManager
 * @brief Factory and utility class for preference management
 */
class PreferenceManager
{
public:
    /**
     * @brief Create default decision tree
     * @return Root node of default decision tree
     */
    static std::shared_ptr<DecisionTreeNode> createDefaultDecisionTree();

    /**
     * @brief Create preference template
     * @param templateName Template name
     * @return Preference criteria for the template
     */
    static PreferenceCriteria createTemplate(const std::string &templateName);

    /**
     * @brief Get available template names
     * @return Vector of template names
     */
    static std::vector<std::string> getAvailableTemplates();

    /**
     * @brief Validate preference weights
     * @param criteria Preference criteria to validate
     * @return True if valid, false otherwise
     */
    static bool validateWeights(const PreferenceCriteria &criteria);
};

#endif // USER_PREFERENCES_H