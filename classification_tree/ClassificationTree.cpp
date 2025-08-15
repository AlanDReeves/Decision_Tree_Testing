#include "ClassificationTree.h"
#include "ClassificationNode.h"
#include<vector>
#include<utility>
#include<tuple>
#include<cmath>
#include<set>

#include<iostream>

ClassificationTree::ClassificationTree(std::vector<std::vector<int>> features, std::vector<int> results) {
    std::cout << "constructor called" << std::endl;
    int numFeatures = features[0].size();
    std::set<int> featuresUsed;
    int size = results.size();

    root = makeTree(features, results, featuresUsed, 0, size);

    std::cout << "constructor complete" << std::endl;
}

ClassificationNode ClassificationTree::makeTree(
    std::vector<std::vector<int>>& features, 
    std::vector<int>& results, 
    std::set<int> featuresUsed, 
    int leftIndex, 
    int rightIndex) {
        int numFeatures = features.size();
        if (featuresUsed.size() == numFeatures) { // if all features have been used
            return nullptr; // return early, base case
        }

        // else, find the best feature to split the data set
        std::vector<std::tuple<int, float, int, int>> featureScores = scoreFeatures(features, results, featuresUsed);
        // featureScores - vector{bestValue, bestGini, featureNumber, bestIndex}
        int bestValueNum = -1;
        int bestGini = 1000; // arbitrary high number one worse than the fail number in gini calculation func
        int bestFeatureNum = -1;
        int bestIndex = -1;
        
        for (int i = 0; i < numFeatures; i++) {
            if (std::get<1>(featureScores[i]) < bestGini) {
                bestValueNum = std::get<0>(featureScores[i]);
                bestGini = std::get<0>(featureScores[i]);
                bestFeatureNum = std::get<2>(featureScores[i]);
                bestIndex = std::get<3>(featureScores[i]);
            }
        }

        // make a node that represents splitting at this feature
        ClassificationNode root = new ClassificationNode(nullptr, nullptr, bestFeatureNum, bestValueNum, -1);
        // null left, null right, feature = bestFeatureNum, threshold = bestFeatureNum, prediction value = -1 (sentinel)
        featuresUsed.insert(bestFeatureNum); // include bestFeatureNum so it isn't included in future calculations

        ClassificationNode leftChild = makeTree(
            features, 
            results,
            featuresUsed,
            leftIndex,
            bestIndex
        );
        ClassificationNode rightChild = makeTree(
            features,
            results,
            featuresUsed,
            bestIndex,
            rightIndex
        );

        root.setLeft(&leftChild);
        root.setRight(&rightChild);

        return root;
}

std::vector<std::tuple<int, float, int, int>> ClassificationTree::scoreFeatures(std::vector<std::vector<int>>& features, std::vector<int>& results, std::set<int>& featuresUsed) {
    int numFeatures = int(features[0].size());
    std::cout << "scoreFeatures called numFeatures: ";
    std::cout << numFeatures << std::endl;
    std::vector<std::tuple<int, float, int, int>> vectorScores; // {value to split on, gini score, feature number, splitIndex}
    for (int i = 0; i < numFeatures; i++) {// for each feature
            if (featuresUsed.count(i) != 0) {
                std::tuple<int, float, int, int> junkTuple = std::make_tuple(-1, 999, -1, -1);
                vectorScores.push_back(junkTuple); // push a tuple with a gini score so bad it will not be selected
            }
            std::cout << "scoreFeatures loop: i = " << i << std::endl;
            std::pair<std::vector<std::vector<int>>, std::vector<int>> sortResults = SortByFeature(features, i, results, 0, results.size() - 1);// sort by that feature
            std::vector<std::pair<int, int>> classCounts = getClassCounts(sortResults.second);// generate class counts
            std::tuple<int, float, int> giniScore = findBestGiniVal(sortResults.first, i, sortResults.second, classCounts); // calculate best gini
            // giniScore tuple - {bestValue, bestGini, bestIndex}

            std::tuple<int, float, int, int> vectorTuple = std::make_tuple(std::get<0>(giniScore), std::get<1>(giniScore), i, std::get<3>(giniScore));
            // vectorTuple - {bestValue, bestGini, featureNumber, bestIndex}
            vectorScores.push_back(vectorTuple); // place in vector
    }
    return vectorScores; // return the vector
}

std::vector<std::pair<int, int>> ClassificationTree::getClassCounts(std::vector<int> results) {
    std::vector<std::pair<int, int>> classCounts;
    int resultsSize = int(results.size());
    for (int i = 0; i < resultsSize; i++) {
        int classVal = results[i];
        bool found = false;
        int classCountsSize = int(classCounts.size());
        for (int j = 0; j < classCountsSize; j++) {
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
    std::vector<std::vector<int>>& features, 
    int featureNum, 
    std::vector<int>& results,
    int left,
    int right) {
    // Quick sort by feature
    
    std::cout << "SortByFeature called" << std::endl;
    std::cout<< "left: " << left << " right: " << right << std::endl;
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

          std::cout << "inside loop i = " << i << " left = " << left << " right = " << right << std::endl;

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

    std::cout << "recursive call reached" << std::endl;

    // quicksort recursively
    ClassificationTree::SortByFeature(features, featureNum, results, left, pivotLocation - 1);
    ClassificationTree::SortByFeature(features, featureNum, results, pivotLocation + 1, right);
    
    std::cout<< "SortByFeature complete" << std::endl;
    return {features, results};
}

float ClassificationTree::calcGini(std::vector<std::pair<int, int>> classCounts, std::vector<std::pair<int, int>> splitCounts) {
    float leftPi = 0;
    float rightPi = 0;
    int splitCountsSize = int(splitCounts.size());
    for (int i = 0; i < splitCountsSize; i++) {
        int leftCount = splitCounts[i].second;
        int totalCount = classCounts[i].second;
        int rightCount = totalCount - leftCount;

        leftPi += std::pow((leftCount / float(totalCount)), 2); // fraction of class in left squared
        rightPi += std::pow((rightCount / float(totalCount)), 2); // fraction of class in right squared
    }
    return leftPi + rightPi;
}

std::tuple<int, float, int> ClassificationTree::findBestGiniVal(std::vector<std::vector<int>> sortedFeatures, int featureNum, std::vector<int> sortedResults, std::vector<std::pair<int, int>> classCounts) {
    // initialize starting gini score and feature value
    float bestGini = 999.0;
    int bestValue = -999;
    int bestIndex = -1;

    // set up class split counts for iterative Gini counting
        std::vector<std::pair<int, int>> splitCounts;
        int classCountsSize = int(classCounts.size());
        for (int i = 0; i < classCountsSize; i++) {
            int cls = classCounts[i].first;
            splitCounts.push_back(std::make_pair(cls, 0)); // start counts for all classes at 0
        }
    // iterate through feature values for featureNum
    int sortedResultsSize = int(sortedResults.size());
    int splitCountsSize = int(splitCounts.size());
    for (int i = 1; i < sortedResultsSize; i++) {
        // add each class passed to class count
        int classSeen = sortedResults[i];
        for (int i = 0; i < splitCountsSize; i++) { // iterating through to find class values in case they do not match index
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
                bestIndex = i;
            }
        }
    }
    // return feature value at best split
    return std::make_tuple(bestValue, bestGini, bestIndex);
}
