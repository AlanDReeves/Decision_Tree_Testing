#include"DecisionTree.h"
#include"DecisionNode.h"
#include<iostream>

int main() {
    DecisionNode nodeA = DecisionNode(NULL, NULL, "test", 5);
    DecisionNode nodeB = DecisionNode(NULL, NULL, "test", NULL, 0);
    DecisionNode nodeC = DecisionNode(NULL, NULL, "test", NULL, 1);

    nodeA.setLeft(&nodeB);
    nodeA.setRight(&nodeC);

    DecisionTree tree = DecisionTree(&nodeA);
    std::cout << tree.decide(6) << std::endl;
}
