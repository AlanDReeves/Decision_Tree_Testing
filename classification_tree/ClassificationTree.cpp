#include "ClassificationTree.h"
#include<vector>
#include<utility>
#include<cmath>

#include<iostream>

ClassificationTree::ClassificationTree(std::vector<std::vector<int>> features, std::vector<int> results) {
    int numPoints = features.size();
    int numFeatures = features[0].size();
    // find feature value that divides results most evenly

    // create a node to divide input in half
    // find next best dividing feature and split on that
    // repeat until all features are used
    std::cout << "constructor complete" << std::endl;
}

int ClassificationTree::findBestFeature(std::vector<std::vector<int>> features, std::vector<int> results) {
    int numFeatures = features[0].size();
    // for each feature
            // sort by that feature
            // calculate best gini - must do this incrementally or efficiency is destroyed
    // find the lowest gini score
    // return the feature that gave that score
    std::pair<std::vector<std::vector<int>>, std::vector<int>> sortedBest = SortByFeature(features, 0, results, 0, results.size());
    float sortedBestScore = findBestGini();
    int best = 0;
    for (int i = 1; i < numFeatures; i++) {
        std::pair<std::vector<std::vector<int>>, std::vector<int>> sortedNext = SortByFeature(features, i, results, 0, results.size());
        float sortedNextScore = findBestGini();
        if (sortedNextScore > sortedBestScore) {
            sortedBest = sortedNext;
            sortedBestScore = sortedNextScore;
            best = i;
        }
    }
    return best;
}

std::pair<std::vector<std::vector<int>>, std::vector<int>> ClassificationTree::SortByFeature(
    std::vector<std::vector<int>> features, 
    int featureNum, 
    std::vector<int> results,
    int left,
    int right) {
    // Quick sort by feature
    std::cout << "Sort By Feature called" << std::endl;

    if (left >= right) {
        return {features, results};
    }

    // set up for partition
    std::vector<int> tempFeatures;
    int tempResults;

    int pivot = features[right][featureNum];
    int endLowIndex = left - 1; // highest index of low size
    int i;
    for (i = left; i < right; i++) { // check all values besides pivot
        if (features[i][featureNum] <= pivot) { // if the val belongs on low side
            endLowIndex += 1; // increase size of low side
            tempFeatures = features[i]; // swap new element into low size
            features[i] = features[endLowIndex];
            features[endLowIndex] = tempFeatures;

            // swap results array to match
            tempResults = results[i];
            results[i] = results[endLowIndex];
            results[endLowIndex] = tempResults;
        }
    }
    tempFeatures = features[endLowIndex + 1]; // swap pivot into place
    features[endLowIndex + 1] = features[right];
    features[right] = tempFeatures;
    // copy with results
    tempResults = results[endLowIndex + 1];
    results[endLowIndex + 1] = results[right];
    results[right] = tempResults;

    int pivotLocation = endLowIndex + 1;

    std::cout << "Partition made" << std::endl;

    // quicksort recursively
    ClassificationTree::SortByFeature(features, featureNum, results, left, pivotLocation - 1);
    ClassificationTree::SortByFeature(features, featureNum, results, pivotLocation + 1, right);
    
    return {features, results};
}

float ClassificationTree::calcGini(std::vector<std::pair<int, int>> classCounts, std::vector<std::pair<int, int>> splitCounts) {
    float leftPi = 0;
    float rightPi = 0;
    for (int i = 0; i < splitCounts.size(); i++) {
        int leftCount = splitCounts[i].second;
        int totalCount = classCounts[i].second;
        int rightCount = totalCount - leftCount;

        leftPi += std::pow((leftCount / float(totalCount)), 2); // fraction of class in left squared
        rightPi += std::pow((rightCount / float(totalCount)), 2); // fraction of class in right squared
    }
    return leftPi + rightPi;
}

int ClassificationTree::findBestGiniVal(std::vector<std::vector<int>> sortedFeatures, int featureNum, std::vector<int> sortedResults, std::vector<std::pair<int, int>> classCounts) {
    // initialize starting gini score and feature value
    float bestGini = 999.0;
    int bestValue = -999;

    // set up class split counts for iterative Gini counting
        std::vector<std::pair<int, int>> splitCounts;
        for (int i = 0; i < classCounts.size(); i++) {
            int cls = classCounts[i].first;
            splitCounts.push_back(std::make_pair(cls, 0)); // start counts for all classes at 0
        }
    // iterate through feature values for featureNum
    for (int i = 1; i < sortedResults.size(); i++) {
        // add each class passed to class count
        int classSeen = sortedResults[i];
        for (int i = 0; i < splitCounts.size(); i++) { // iterating through to find class values in case they do not match index
            if (splitCounts[i].first == classSeen) {
                splitCounts[i].second++;
            }
        }

        // when feature values are not equal, calculate gini for splitting there
        if (sortedFeatures[i - 1][featureNum] != sortedFeatures[i][featureNum]) {
            float splitGini = calcGini(classCounts, splitCounts);

            if (splitGini < bestGini) {
                // record best score and value at best score
                bestGini = splitGini;
                bestValue = sortedFeatures[i][featureNum];
            }
        }
    }
    // return feature value at best split
    return bestValue;
}




