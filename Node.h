#ifndef NODE_H
#define NODE_H

#include "TreeData.h"
#include <string>
#include <vector>


class Node : public TreeData
{
    public:
        Node();
        Node(string attribute,vector<TreeData> data,double entpy,int good,int ok,int bad,Node* par,Node* b1,Node* b2,Node* b3);
        void get_best_split(Node* node_obj); // set best split variable = 2, then decrement in node creation. used split = 1
        void create_root_node();
        void create_child_nodes(Node* parent, double ent1, double ent2, double ent3, string attr_name, double bad1, double bad2, double bad3, double ok1, double ok2, double ok3, double good1, double good2, double good3,vector<TreeData> vec1,vector<TreeData> vec2,vector<TreeData> vec3);      // base cases, avoid overfitting
        void set_ranges(Node* node_obj);
        void store_nodes();
        void split_child();         // decides which child node to split
        string get_attribute(Node n);
        void display_tree();

        int split_cylinder = 0,split_displacement = 0,split_horsepower = 0,split_weight = 0,split_acceleration = 0,split_year = 0,split_maker = 0;
        int displacement_mean = 0, horsepower_mean = 0, weight_mean = 0, year_mean = 0;
        int displacement_dev = 0, horsepower_dev = 0, weight_dev = 0, year_dev = 0;
        double acceleration_mean = 0, acceleration_dev = 0;
        int node_count = 0;
        double max_info_gain = 0.0;
        int run_best_split = 0;
        int run_split_child = 0;

        vector<Node> nodes;
        vector<TreeData> v1;
        vector<TreeData> v2;
        vector<TreeData> v3;

    protected:

    private:
        friend class DecisionTree;
        string attribute_name;
        vector<TreeData> node_data;     // at root, node_data = cars, then gets split up at lower nodes
        double entropy;
        int good_count;
        int ok_count;
        int bad_count;
        Node* Parent_node;
        Node* Branch1;
        Node* Branch2;
        Node* Branch3;

};

#endif // NODE_H
