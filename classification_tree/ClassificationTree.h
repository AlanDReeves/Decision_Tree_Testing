#ifndef CLASSTREE
#define CLASSTREE
#include<vector>
#include<set>
#include<tuple>
#include "ClassificationNode.h"

class ClassificationTree
{
private:
    ClassificationNode* root;

    std::pair<std::vector<std::vector<int>>, std::vector<int>> SortByFeature(
        std::vector<std::vector<int>> features, 
        int featureNum, 
        std::vector<int> results,
        int left,
        int right);

    std::vector<std::tuple<int, float, int, int>> scoreFeatures(
        std::vector<std::vector<int>>& features, 
        std::vector<int>& results, 
        std::set<int>& featuresUsed, 
        int leftIndex, 
        int rightIndex);

    std::vector<std::pair<int, int>> getClassCounts(
        std::vector<int> results);

    float calcGini(
        std::vector<std::pair<int, int>> classCounts, 
        std::vector<std::pair<int, int>> splitCounts);

    std::tuple<int, float, int> findBestGiniVal(
        std::vector<std::vector<int>>& sortedFeatures, 
        int featureNum, 
        std::vector<int>& sortedResults, 
        std::vector<std::pair<int, int>>& classCounts,
        int leftIndex);

    ClassificationNode* makeTree(
        std::vector<std::vector<int>>& features, 
        std::vector<int>& results, 
        std::set<int> featuresUsed, 
        int leftIndex, 
        int rightIndex);

    void makePredictionNodes(
        std::vector<std::vector<int>>& features, 
        std::vector<int>& results, 
        int leftIndex, 
        int bestIndex,
        int rightIndex,
        ClassificationNode* node);

    ClassificationNode* makeSinglePredictionNode(
    std::vector<std::vector<int>>& features, 
    std::vector<int>& results, 
    int leftIndex, 
    int rightIndex);

    bool isValidData(std::vector<std::vector<int>>& features, std::vector<int>& results);

public:
    ClassificationTree(
        std::vector<std::vector<int>> features, 
        std::vector<int> results);

    int predict(std::vector<int>);

    ClassificationNode* getRoot();
    
};
#endif