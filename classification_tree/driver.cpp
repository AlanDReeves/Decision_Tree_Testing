#include"ClassificationTree.h"
#include"ClassificationNode.h"
#include<vector>
#include<utility>
#include<iostream>

void printInorder(ClassificationNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->getLeft() == nullptr && node->getRight() == nullptr) {
        std::cout<< "feature: " << node->getFeatureNum() << " threshold " << node->getThreshold() << std::endl;
        return;
    }
    printInorder((node->getLeft()));
    std::cout<< "feature: " << node->getFeatureNum() << " threshold " << node->getThreshold() << std::endl;
    printInorder((node->getRight()));
}

int main() {
    std::vector<std::vector<int>> features = {
        {1, 50},
        {2, 51},
        {3, 52},
        {4, 60},
        {5, 69}
    };

    std::vector<int> results = {1, 1, 1, 2, 2};

    ClassificationTree testTree = ClassificationTree(features, results);

    // explore tree
    std::cout<< "\n\n\n";
    std::cout << "Tree structure inorder walk" << std::endl;

    ClassificationNode* cursor = testTree.getRoot();
    printInorder(cursor);
    

    return 1;
}