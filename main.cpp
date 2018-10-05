#include "TreeData.h"
#include "Node.h"
#include "DecisionTree.h"

#include <iostream>

using namespace std;

int main()
{
    TreeData car_obj = TreeData();
    //car1.initializeData(&car1);

    //vector<string> vec;

    //car_obj.readToVector("car.txt");
    //car_obj.makeCarObjects();
    //car_obj.stringToInstance();

    //car_obj.instanceToString(1);

    Node node_obj = Node();
    node_obj.create_root_node();

    DecisionTree dt = DecisionTree();
    dt.readTestSet();
    dt.makeTestObjects();
    dt.makeTestCars();
    dt.make_predictions(node_obj.nodes);
    //cout<<"Mean = " <<node_obj.acceleration_mean <<" Dev = " <<node_obj.acceleration_dev <<endl;

    return 0;
}
