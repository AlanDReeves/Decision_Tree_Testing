#include "ClassificationTree.h"
#include<vector>
#include<utility>
#include<cmath>

#include<iostream>

ClassificationTree::ClassificationTree(std::vector<std::vector<int>> features, std::vector<int> results) {
    int numPoints = features.size();
    int numFeatures = features[0].size();
    // find feature value that divides results most evenly
    std::vector<std::pair<int, float>> featureScores = scoreFeatures(features, results);

    // create a node to divide input in half
    // find next best dividing feature and split on that
    // repeat until all features are used
    std::cout << "constructor complete" << std::endl;
}

std::vector<std::pair<int, float>> ClassificationTree::scoreFeatures(std::vector<std::vector<int>> features, std::vector<int> results) {
    int numFeatures = features[0].size();
    std::vector<std::pair<int, float>> vectorScores;
    for (int i = 0; i < numFeatures; i++) {// for each feature
            std::pair<std::vector<std::vector<int>>, std::vector<int>> sortResults = SortByFeature(features, i, results, 0, results.size());// sort by that feature
            std::vector<std::pair<int, int>> classCounts = getClassCounts(sortResults.second);// generate class counts
            std::pair<int, float> giniScore = findBestGiniVal(sortResults.first, i, sortResults.second, classCounts); // calculate best gini
            vectorScores.push_back(giniScore); // place in vector
            // find some way to include class value in this
    return vectorScores; // return the vector
    }
}

std::vector<std::pair<int, int>> ClassificationTree::getClassCounts(std::vector<int> results) {
    std::vector<std::pair<int, int>> classCounts;
    for (int i = 0; i < results.size(); i++) {
        int classVal = results[i];
        bool found = false;
        for (int j = 0; j < classCounts.size(); j++) {
            if (classCounts[j].first == classVal) {
                classCounts[j].second++;
                found = true;
            }
        }
        if (!found) {
            classCounts.push_back(std::make_pair(classVal, 1));
        }
        found = false;
    }
    return classCounts;
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

std::pair<int, float> ClassificationTree::findBestGiniVal(std::vector<std::vector<int>> sortedFeatures, int featureNum, std::vector<int> sortedResults, std::vector<std::pair<int, int>> classCounts) {
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
    return std::make_pair(bestValue, bestGini);
}
