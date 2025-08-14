#ifndef NODE
#define NODE

#include<string>

class DecisionNode
{
private:
    DecisionNode *left, *right;
    std::string feature;
    int threshold; // if x less than threshold, go left, if more, go right
    int value; // represents the class prediction
public:
    DecisionNode(DecisionNode* left = NULL, DecisionNode* right = NULL, std::string feature = NULL, int threshold = NULL, int value = NULL);
    ~DecisionNode();

    bool setLeft(DecisionNode* node);
    bool setRight(DecisionNode* node);
    DecisionNode* getLeft();
    DecisionNode* getRight();
    std::string getFeature();
    int getThreshold();
    int getValue();
};

#endif 