#ifndef CLASSTREE
#define CLASSTREE
#include <vector>

class ClassificationTree
{
private:
    int findBestFeature();
    float calcGini();
public:
    ClassificationTree(std::vector<std::vector<int>> features, std::vector<int> results);

    std::pair<std::vector<std::vector<int>>, std::vector<int>> SortByFeature(
    std::vector<std::vector<int>> features, 
    int featureNum, 
    std::vector<int> results,
    int left,
    int right);

    float calcGini(std::vector<int> sortedResults);
};
#endif