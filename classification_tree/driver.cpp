#include"ClassificationTree.h"
#include<vector>
#include<utility>
#include<iostream>

int main() {
    std::vector<std::vector<int>> features = {
        {5, 6},
        {1, 2},
        {3, 4},
    };

    std::vector<int> results = {1, 2, 3};

    ClassificationTree testTree = ClassificationTree(features, results);

    std::pair<std::vector<std::vector<int>>, std::vector<int>> answer = testTree.SortByFeature(features, 1, results, 0, 2);

    for (int i = 0; i < answer.first.size(); i++) {
        std::cout << answer.first[i][0] << std::endl;
    }

    return 1;
}