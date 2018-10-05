#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include "TreeData.h"
#include "Node.h"


class DecisionTree : public Node, public TreeData
{
    public:
        DecisionTree();
        void readTestSet();
        void makeTestObjects();
        void makeTestCars();

        void query_decision_tree();
        void display_decision_tree();
        void create_test_data();    // populate test_cars with test data
        void make_predictions(vector<Node> Tree);    // input results in 3x3 confusion matrix
        void results();             // display confusion matrix, precision, recall, make 2x2 confusion matrices for good,bad,and ok
        int confusion_matrix [3][3];

        vector<string> test_lines;
        vector<TreeData> test_cars;

    protected:

    private:
};

#endif // DECISIONTREE_H
