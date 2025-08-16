#include"ClassificationNode.h"

ClassificationNode::ClassificationNode(
    ClassificationNode* left, 
    ClassificationNode* right, 
    int featureNumber, 
    int threshold, 
    int value) {
        this->left = left;
        this->right = right;
        this->featureNumber = featureNumber;
        this->threshold = threshold;
        this->value = value;
}

ClassificationNode::~ClassificationNode() {
    if (left == nullptr) {
        delete(this->left);
    }
    if (right == nullptr) {
        delete(this->right);
    }
}

void ClassificationNode::setLeft(ClassificationNode* node) {
    left = node;
}

void ClassificationNode::setRight(ClassificationNode* node) {
    right = node;
}

ClassificationNode* ClassificationNode::getLeft() {
    return left;
}

ClassificationNode* ClassificationNode::getRight() {
    return right;
}

int ClassificationNode::getFeatureNum() {
    return featureNumber;
}

int ClassificationNode::getThreshold() {
    return threshold;
}

int ClassificationNode::getValue() {
    return value;
}
