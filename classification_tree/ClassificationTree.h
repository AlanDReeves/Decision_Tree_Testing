#ifndef CLASSTREE
#define CLASSTREE
#include <vector>

class ClassificationTree
{
private:
    std::vector<std::tuple<int, float, int>> scoreFeatures(std::vector<std::vector<int>> features, std::vector<int> results);
    std::vector<std::pair<int, int>> getClassCounts(std::vector<int> results);
    float calcGini(std::vector<std::pair<int, int>> classCounts, std::vector<std::pair<int, int>> splitCounts);
public:
    ClassificationTree(std::vector<std::vector<int>> features, std::vector<int> results);

    std::pair<std::vector<std::vector<int>>, std::vector<int>> SortByFeature(
    std::vector<std::vector<int>> features, 
    int featureNum, 
    std::vector<int> results,
    int left,
    int right);

    float calcGini(std::vector<std::pair<int, int>> classCounts, std::vector<std::pair<int, int>> splitCounts);
    std::pair<int, float> findBestGiniVal(std::vector<std::vector<int>> sortedFeatures, int featureNum, std::vector<int> sortedResults, std::vector<std::pair<int, int>> classCounts);
};
#endif