#include"ClassificationTree.h"
#include<vector>
#include<utility>
#include<iostream>

int main() {
    std::vector<std::vector<int>> features = {
        {1, 4, 1},
        {1, 4, 2},
        {3, 4, 3},
        {4, 4, 4},
        {5, 4, 5}
    };

    std::vector<int> results = {1, 1, 2, 2, 2};

    ClassificationTree testTree = ClassificationTree(features, results);

    return 1;
}