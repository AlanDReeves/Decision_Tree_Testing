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
        {1, 1, 0},
        {0, 3, 0},
        {0, 1, 4},
        {0, 5, 6},
        {0, 6, 1},
        {0, 11, 12},
        {0, 15, 14},
        {0, 13, 20}
    };

    std::vector<int> results = {1, 1, 1, 1, 1, 2, 2, 2};

    ClassificationTree testTree = ClassificationTree(features, results);

    // explore tree
    std::cout<< "\n\n\n";
    std::cout << "Tree structure inorder walk" << std::endl;

    ClassificationNode* cursor = testTree.getRoot();
    printTopDown(cursor);
    

    return 1;
}