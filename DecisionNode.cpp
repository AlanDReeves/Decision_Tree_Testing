#include "DecisionNode.h"

DecisionNode::DecisionNode(DecisionNode* left = NULL, DecisionNode* right = NULL, std::string feature = NULL, int threshold = NULL, int value = NULL) {
    this->left = left;
    this->right = right;
    this->feature = feature;
    this->threshold = threshold;
    this->value = value;
}

DecisionNode::~DecisionNode() {
    delete(this);
}

bool DecisionNode::setLeft(DecisionNode* node) {
    this->left = node;
}

bool DecisionNode::setRight(DecisionNode* node) {
    this->right = right;
}

DecisionNode* DecisionNode::getLeft() {
    return this->left;
}

DecisionNode* DecisionNode::getRight() {
    return this->right;
}

std::string DecisionNode::getFeature() {
    return this->feature;
}

int DecisionNode::getThreshold() {
    return this->threshold;
}

int DecisionNode::getValue() {
    return this->value;
}