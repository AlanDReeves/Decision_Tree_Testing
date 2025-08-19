#include "ClassificationTree.h"

class RandomForest {
    private:
        std::vector<ClassificationTree*> treesVector;
    public:
        RandomForest(
            std::vector<std::vector<int>> features, 
            std::vector<int> results);

        ~RandomForest();

        int predict(std::vector<int> features);

        std::vector<int> predictMany(std::vector<std::vector<int>> features2D);
};