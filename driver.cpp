#include"DecisionTree.h"
#include"DecisionNode.h"
#include<iostream>

int main() {
    DecisionNode nodeA = DecisionNode(NULL, NULL, "test", 5);
    DecisionNode nodeAB = DecisionNode(NULL, NULL, "test", 2);
    DecisionNode nodeAC = DecisionNode(NULL, NULL, "test", 7);
    DecisionNode nodeB = DecisionNode(NULL, NULL, "test", NULL, 0);
    DecisionNode nodeC = DecisionNode(NULL, NULL, "test", NULL, 1);
    DecisionNode nodeD = DecisionNode(NULL, NULL, "test", NULL, 2);
    DecisionNode nodeE = DecisionNode(NULL, NULL, "test", NULL, 3);

    nodeA.setLeft(&nodeAB);
    nodeA.setRight(&nodeAC);

    nodeAB.setLeft(&nodeB);
    nodeAB.setRight(&nodeC);

    nodeAC.setLeft(&nodeD);
    nodeAC.setRight(&nodeE);

    DecisionTree tree = DecisionTree(&nodeA);
    std::cout << tree.decide(1) << std::endl;
    std::cout << tree.decide(3) << std::endl;
    std::cout << tree.decide(6) << std::endl;
    std::cout << tree.decide(8) << std::endl;
    return 1;
}
