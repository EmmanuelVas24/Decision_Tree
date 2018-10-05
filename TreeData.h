#ifndef TREEDATA_H
#define TREEDATA_H

#include <string>
#include <vector>

using namespace std;

class TreeData
{
    public:
        TreeData();
        TreeData(string milespergallon,int cyl,int disp,int hpwr,int wt,double acc,int mYear,string mkr);
        initializeData(TreeData *p);
        void makeCarObjects();
        addData();
        void readToVector(string filename);
        vector<string> lines;
        void stringToInstance();
        void instanceToString(int car_number);
        vector<TreeData> cars;
        string get_mpg(TreeData td);
        int get_cyl(TreeData td);
        int get_disp(TreeData td);
        int get_hp(TreeData td);
        int get_wt(TreeData td);
        double get_acc(TreeData td);
        int get_year(TreeData td);
        string get_mk(TreeData td);


    protected:

    private:
        string mpg;
        int cylinders;
        int displacement;
        int horsepower;
        int weight;
        double acceleration;
        int modelYear;
        string maker;

};

#endif // TREEDATA_H
