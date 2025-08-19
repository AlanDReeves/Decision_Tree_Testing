#include "RandomForest.h"
#include <iostream>

int main(void) {
    std::vector<std::vector<int>> features = {
        {1, 2, 3},
        {1, 2, 4},
        {2, 3, 4},
        {4, 6, 1},
        {3, 2, 4},
        {5, 3, 1},

        {10, 20, 30},
        {10, 20, 40},
        {20, 30, 40},
        {40, 60, 10},
        {30, 20, 40},
        {50, 30, 10}
    };

    std::vector<int> results = {
        0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1
    };

    RandomForest forest = RandomForest(features, results);

    std::vector<int> singlePoint = {2, 2, 2}; // expecting class 0
    std::vector<std::vector<int>> multiPoints = { // expecting all class 0
        {2, 3, 4},
        {4, 5, 1},
        {3, 2, 2}
    };

    std::cout << "single prediction: " << forest.predict(singlePoint) << std::endl;
    std::cout << "multiple predictions: " << std::endl;
    std::vector<int> multiPredictions = forest.predictMany(multiPoints);
    for (auto& result : multiPredictions) {
        std::cout << "prediction: " << result << std::endl;
    }
    return 0;
}