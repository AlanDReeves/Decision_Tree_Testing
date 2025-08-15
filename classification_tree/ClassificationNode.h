#ifndef NODE
#define NODE

class ClassificationNode
{
private:
    ClassificationNode *left, *right;
    int featureNumber;
    int threshold; // if x less than threshold, go left, if more, go right
    int value; // represents class prediction
public:
    ClassificationNode(
        ClassificationNode* left = nullptr, 
        ClassificationNode* right = nullptr, 
        int featureNumber = -1, 
        int threshold = -1, 
        int value = -1);
        
    ~ClassificationNode();

    void setLeft(ClassificationNode* node);
    void setRight(ClassificationNode* node);
    ClassificationNode* getLeft();
    ClassificationNode* getRight();
    int getFeatureNum();
    int getThreshold();
    int getValue();
};

#endif