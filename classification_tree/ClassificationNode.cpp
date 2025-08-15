#include<ClassificationNode.h>

ClassificationNode::ClassificationNode(
    ClassificationNode* left = nullptr, 
    ClassificationNode* right = nullptr, 
    int featureNumber = -1, 
    int threshold = -1, 
    int value = -1) {
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
