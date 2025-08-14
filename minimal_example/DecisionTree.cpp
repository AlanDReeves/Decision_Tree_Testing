#include "DecisionTree.h"

DecisionTree::DecisionTree(DecisionNode* root) {
    this->root = root;
}

int DecisionTree::decide(int value) {
    DecisionNode* cursor = this->root;
    while (cursor->getValue() == -1) {
        int threshold = cursor->getThreshold();
        if (value <= threshold) {
            if (cursor->getLeft() != NULL) {
                cursor = cursor->getLeft();
            }
            else {
                return -1;
            }
        } else {
            if (cursor->getRight() != NULL) {
                cursor = cursor->getRight();
            }
            else {
                return -1;
            }
        }
    }
    return cursor->getValue();
}