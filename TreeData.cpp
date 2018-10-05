#include "TreeData.h"

#include <cstdlib>
#include<iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

TreeData::TreeData()
{
    mpg = "";
    cylinders = 0;
    displacement = 0;
    horsepower = 0;
    weight = 0;
    acceleration = 0.0;
    modelYear = 0;
    maker = "";
}


TreeData::TreeData(string milespergallon,int cyl,int disp,int hpwr,int wt,double acc,int mYear,string mkr)
{
    mpg = milespergallon;
    cylinders = cyl;
    displacement = disp;
    horsepower = hpwr;
    weight = wt;
    acceleration = acc;
    modelYear = mYear;
    maker = mkr;
}

TreeData::initializeData(TreeData *p)
{

    cout<<p->acceleration <<endl;
}

void TreeData::readToVector(string filename)
{
    string line;
    ifstream myfile(filename.c_str());

    if(!myfile) //Always test the file open.
    {
        cout<<"Error opening output file"<< endl;
    }

    while (std::getline(myfile, line))
    {
        lines.push_back(line);
    }

}

void TreeData::makeCarObjects()
{
    // There are 42 car objects

    TreeData car_1 = TreeData();
    TreeData car_2 = TreeData();
    TreeData car_3 = TreeData();
    TreeData car_4 = TreeData();
    TreeData car_5 = TreeData();
    TreeData car_6 = TreeData();
    TreeData car_7 = TreeData();
    TreeData car_8 = TreeData();
    TreeData car_9 = TreeData();
    TreeData car_10 = TreeData();

    TreeData car_11 = TreeData();
    TreeData car_12 = TreeData();
    TreeData car_13 = TreeData();
    TreeData car_14 = TreeData();
    TreeData car_15 = TreeData();
    TreeData car_16 = TreeData();
    TreeData car_17 = TreeData();
    TreeData car_18 = TreeData();
    TreeData car_19 = TreeData();
    TreeData car_20 = TreeData();

    TreeData car_21 = TreeData();
    TreeData car_22 = TreeData();
    TreeData car_23 = TreeData();
    TreeData car_24 = TreeData();
    TreeData car_25 = TreeData();
    TreeData car_26 = TreeData();
    TreeData car_27 = TreeData();
    TreeData car_28 = TreeData();
    TreeData car_29 = TreeData();
    TreeData car_30 = TreeData();

    TreeData car_31 = TreeData();
    TreeData car_32 = TreeData();
    TreeData car_33 = TreeData();
    TreeData car_34 = TreeData();
    TreeData car_35 = TreeData();
    TreeData car_36 = TreeData();
    TreeData car_37 = TreeData();
    TreeData car_38 = TreeData();
    TreeData car_39 = TreeData();
    TreeData car_40 = TreeData();

    TreeData car_41 = TreeData();
    TreeData car_42 = TreeData();

    cars.push_back(car_1);
    cars.push_back(car_2);
    cars.push_back(car_3);
    cars.push_back(car_4);
    cars.push_back(car_5);
    cars.push_back(car_6);
    cars.push_back(car_7);
    cars.push_back(car_8);
    cars.push_back(car_9);
    cars.push_back(car_10);

    cars.push_back(car_11);
    cars.push_back(car_12);
    cars.push_back(car_13);
    cars.push_back(car_14);
    cars.push_back(car_15);
    cars.push_back(car_16);
    cars.push_back(car_17);
    cars.push_back(car_18);
    cars.push_back(car_19);
    cars.push_back(car_20);

    cars.push_back(car_21);
    cars.push_back(car_22);
    cars.push_back(car_23);
    cars.push_back(car_24);
    cars.push_back(car_25);
    cars.push_back(car_26);
    cars.push_back(car_27);
    cars.push_back(car_28);
    cars.push_back(car_29);
    cars.push_back(car_30);

    cars.push_back(car_31);
    cars.push_back(car_32);
    cars.push_back(car_33);
    cars.push_back(car_34);
    cars.push_back(car_35);
    cars.push_back(car_36);
    cars.push_back(car_37);
    cars.push_back(car_38);
    cars.push_back(car_39);
    cars.push_back(car_40);

    cars.push_back(car_41);
    cars.push_back(car_42);

    // Created the vector with empty car objects
    // They will be populated in the stringToInstance function



}

void TreeData::stringToInstance()
{
    int i = 0;
    vector<string> temp_vec;

    size_t start_pos = 0;
    size_t comma_pos = 0;

    string s;

    while(i < (int)lines.size())
    {
        comma_pos = lines[i].find(',');

        while(comma_pos != std::string::npos)
        {
            s  = lines[i].substr(start_pos,(comma_pos-start_pos));
            //cout<<s;
            temp_vec.push_back(s);

            start_pos = comma_pos + 1;
            comma_pos = lines[i].find(',',start_pos);

        }

        s  = lines[i].substr(start_pos,(comma_pos-start_pos));
        //cout<<s;
        temp_vec.push_back(s);

        cars[i] = TreeData(temp_vec[0],atoi(temp_vec[1].c_str()),atoi(temp_vec[2].c_str()),atoi(temp_vec[3].c_str()),atoi(temp_vec[4].c_str()),atof(temp_vec[5].c_str()),atoi(temp_vec[6].c_str()),temp_vec[7]);

        temp_vec.clear();
        //cout<<endl;
        start_pos = 0;
        comma_pos = 0;
        i++;
    }
    lines.clear();
}

void TreeData::instanceToString(int car_number)
{

    cout<<"Acceleration = ";
    cout<<cars[car_number].acceleration;
    cout<<endl;
}

int TreeData::get_cyl(TreeData td)
{
    return td.cylinders;
}

string TreeData::get_mpg(TreeData td)
{
    return td.mpg;
}

int TreeData::get_disp(TreeData td)
{
    return td.displacement;
}

int TreeData::get_hp(TreeData td)
{
    return td.horsepower;
}

int TreeData::get_wt(TreeData td)
{
    return td.weight;
}

double TreeData::get_acc(TreeData td)
{
    return td.acceleration;
}

int TreeData::get_year(TreeData td)
{
    return td.modelYear;
}

string TreeData::get_mk(TreeData td)
{
    return td.maker;
}



