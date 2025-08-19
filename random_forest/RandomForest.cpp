#include "ClassificationTree.h"
#include "RandomForest.h"
#include <random>
#include <unordered_map>

RandomForest::RandomForest(std::vector<std::vector<int>> features, std::vector<int> results) {
    int featuresLength = features.size();
    int resultslength = results.size();
    if (resultslength != featuresLength) return;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, featuresLength - 1); // generates a random number representing the index of a datapoint

    for (int i = 0; i < 100; i++) { // for each tree with 100 trees
        // make the random dataset
        std::vector<std::vector<int>> randomData;
        std::vector<int> randomResults;
        for (int j = 0; j < featuresLength; j++) { // insert featuresLength many features and results at random with replacement
            int randInt = dist(gen);
            randomData.emplace_back(features[randInt]);
            randomResults.emplace_back(results[randInt]);
        }   
        // create a tree
        ClassificationTree* newTree = new ClassificationTree(randomData, randomResults); // pass data by value as original vectors will be deleted at end of loop
        // add the tree to treesVector
        this->treesVector.emplace_back(newTree);
    }
}

RandomForest::~RandomForest() {
    for (ClassificationTree* ptr : this->treesVector) {
        delete(ptr);
    }
}

int RandomForest::predict(std::vector<int> features){
    /*Predicts for a single datapoint using all trees*/
    std::unordered_map<int, int> classVotes;
    for (int i = 0; i < int(this->treesVector.size()); i++) { // ask each tree to make a prediction
        int classVote = treesVector[i]->predict(features);

        if (classVotes.count(classVote) == 0) classVotes[classVote] = 1; // record votes
        else classVotes[classVote]++;
    }

    int MostPopular = -1, highCount = 0; // determine which class got the most votes
    for (auto& pair : classVotes) {
        if (pair.second > highCount) {
            MostPopular = pair.first;
            highCount = pair.second;
        }
    }

    return MostPopular;
}

std::vector<int> RandomForest::predictMany(std::vector<std::vector<int>> features2D) {
    std::vector<int> votesList;
    for (int i = 0; i < int(features2D.size()); i++) { // for each datapoint in features2D
        // get prediction from all trees for that datapoint
        int majorityVote = this->predict(features2D[i]);
        // record prediction in votesList
        votesList.emplace_back(majorityVote);
    }
    return votesList;
}