#ifndef TREE
#define Tree
#include "DecisionNode.h"

class DecisionTree
{
private:
    DecisionNode *root;
public:
    DecisionTree(DecisionNode* root);

    int decide(int value);
};

#endif