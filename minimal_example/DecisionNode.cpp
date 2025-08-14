#include "DecisionNode.h"

DecisionNode::DecisionNode(DecisionNode* left, DecisionNode* right, std::string feature, int threshold, int value) {
    this->left = left;
    this->right = right;
    this->feature = feature;
    this->threshold = threshold;
    this->value = value;
}

bool DecisionNode::setLeft(DecisionNode* node) {
    this->left = node;
    return true;
}

bool DecisionNode::setRight(DecisionNode* node) {
    this->right = node;
    return true;
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