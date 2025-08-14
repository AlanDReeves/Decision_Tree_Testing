#include "ClassificationTree.h"
#include<vector>
#include<utility>

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

int ClassificationTree::findBestFeature() {
    // for each feature
            // sort by that feature
            // calculate best gini - must do this incrementally or efficiency is destroyed
    // find the lowest gini score
    // return the feature that gave that score
    return -1;
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

float ClassificationTree::calcGini(std::vector<int> sortedResults) {
    return -1.0;
}




