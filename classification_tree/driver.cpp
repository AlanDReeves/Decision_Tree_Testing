#include"ClassificationTree.h"
#include"ClassificationNode.h"
#include<vector>
#include<utility>
#include<iostream>

void printTopDown(ClassificationNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        std::cout<< "prediction: " << node->getValue() << std::endl;
        return;
    }
    std::cout<< "feature: " << node->getFeatureNum() << " threshold " << node->getThreshold() << std::endl;
    printTopDown((node->getLeft()));
    printTopDown((node->getRight()));
}

int main() {
    std::vector<std::vector<int>> features = {
        {1, 50, 3},
        {2, 51, 51},
        {3, 52, 90},
        {4, 60, 50},
        {5, 69, 99}
    };

    std::vector<int> results = {1, 1, 3, 2, 2};

    ClassificationTree testTree = ClassificationTree(features, results);

    // explore tree
    std::cout<< "\n\n\n";
    std::cout << "Tree structure inorder walk" << std::endl;

    ClassificationNode* cursor = testTree.getRoot();
    printTopDown(cursor);
    

    return 1;
}