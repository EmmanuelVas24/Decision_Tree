#include "DecisionTree.h"
#include "TreeData.h"
#include "Node.h"
#include <vector>
#include<iostream>
#include <string>
#include <fstream>
#include <algorithm>

DecisionTree::DecisionTree()
{
    //constructor
}

void DecisionTree::readTestSet()
{
    string filename = "car_test.txt";
    string line;
    ifstream myfile(filename.c_str());

    if(!myfile) //Always test the file open.
    {
        cout<<"Error opening output file"<< endl;
    }

    while (std::getline(myfile, line))
    {
        test_lines.push_back(line);
    }


}

void DecisionTree::makeTestObjects()
{
    // There are 20  car objects

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

    test_cars.push_back(car_1);
    test_cars.push_back(car_2);
    test_cars.push_back(car_3);
    test_cars.push_back(car_4);
    test_cars.push_back(car_5);
    test_cars.push_back(car_6);
    test_cars.push_back(car_7);
    test_cars.push_back(car_8);
    test_cars.push_back(car_9);
    test_cars.push_back(car_10);

    test_cars.push_back(car_11);
    test_cars.push_back(car_12);
    test_cars.push_back(car_13);
    test_cars.push_back(car_14);
    test_cars.push_back(car_15);
    test_cars.push_back(car_16);
    test_cars.push_back(car_17);
    test_cars.push_back(car_18);
    test_cars.push_back(car_19);
    test_cars.push_back(car_20);

}

void DecisionTree::makeTestCars()
{
    int i = 0;
    vector<string> temp_vec;

    size_t start_pos = 0;
    size_t comma_pos = 0;

    string s;

    while(i < (int)test_lines.size())
    {
        comma_pos = test_lines[i].find(',');

        while(comma_pos != std::string::npos)
        {
            s  = test_lines[i].substr(start_pos,(comma_pos-start_pos));
            //cout<<s;
            temp_vec.push_back(s);

            start_pos = comma_pos + 1;
            comma_pos = test_lines[i].find(',',start_pos);

        }

        s  = test_lines[i].substr(start_pos,(comma_pos-start_pos));
        //cout<<s;
        temp_vec.push_back(s);

        test_cars[i] = TreeData(temp_vec[0],atoi(temp_vec[1].c_str()),atoi(temp_vec[2].c_str()),atoi(temp_vec[3].c_str()),atoi(temp_vec[4].c_str()),atof(temp_vec[5].c_str()),atoi(temp_vec[6].c_str()),temp_vec[7]);

        temp_vec.clear();
        //cout<<endl;
        start_pos = 0;
        comma_pos = 0;
        i++;
    }
    test_lines.clear();


}

void DecisionTree::make_predictions(vector<Node> Tree)
{
    string prediction;
    string actual;
    TreeData td = TreeData();

    for(int i = 0; i<test_cars.size(); i++)
    {
        if(td.get_cyl(test_cars[i]) == 4)
        {
            if(td.get_year(test_cars[i]) < (76-3))
            {
                if(td.get_wt(test_cars[i]) < (2892-817))
                {
                    if(Tree[7].bad_count > Tree[7].ok_count && Tree[7].bad_count > Tree[7].good_count)
                    {prediction = "Bad";}
                    else if(Tree[7].good_count > Tree[7].ok_count && Tree[7].good_count > Tree[7].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
                else if(td.get_wt(test_cars[i]) > (2892-817) && td.get_wt(test_cars[i]) < (2892+817))
                {
                    if(Tree[8].bad_count > Tree[8].ok_count && Tree[8].bad_count > Tree[8].good_count)
                    {prediction = "Bad";}
                    else if(Tree[8].good_count > Tree[8].ok_count && Tree[8].good_count > Tree[8].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
                else
                {
                    if(Tree[8].bad_count > Tree[8].ok_count && Tree[8].bad_count > Tree[8].good_count)
                    {prediction = "Bad";}
                    else if(Tree[8].good_count > Tree[8].ok_count && Tree[8].good_count > Tree[8].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
            }
            else if(td.get_year(test_cars[i]) > (76-3) && td.get_year(test_cars[i]) < (76+3))
            {
                if(Tree[5].bad_count > Tree[5].ok_count && Tree[5].bad_count > Tree[5].good_count)
                {prediction = "Bad";}
                else if(Tree[5].good_count > Tree[5].ok_count && Tree[5].good_count > Tree[5].bad_count)
                {prediction = "Good";}
                else
                {prediction = "OK";}
                actual = td.get_mpg(test_cars[i]);
                cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
            }
            else
            {
                if(td.get_acc(test_cars[i]) < (15.9-2.0725))
                {
                    if(Tree[10].bad_count > Tree[10].ok_count && Tree[10].bad_count > Tree[10].good_count)
                    {prediction = "Bad";}
                    else if(Tree[10].good_count > Tree[10].ok_count && Tree[10].good_count > Tree[10].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
                else if(td.get_acc(test_cars[i]) > (15.9-2.0725) && td.get_acc(test_cars[i]) < (15.9+2.0725))
                {
                    if(Tree[11].bad_count > Tree[11].ok_count && Tree[11].bad_count > Tree[11].good_count)
                    {prediction = "Bad";}
                    else if(Tree[11].good_count > Tree[11].ok_count && Tree[11].good_count > Tree[11].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
                else
                {
                    if(Tree[12].bad_count > Tree[12].ok_count && Tree[12].bad_count > Tree[12].good_count)
                    {prediction = "Bad";}
                    else if(Tree[12].good_count > Tree[12].ok_count && Tree[12].good_count > Tree[12].bad_count)
                    {prediction = "Good";}
                    else
                    {prediction = "OK";}
                    actual = td.get_mpg(test_cars[i]);
                    cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
                }
            }
        }
        else if(td.get_cyl(test_cars[i]) == 6)
        {
            if(Tree[2].bad_count > Tree[2].ok_count && Tree[2].bad_count > Tree[2].good_count)
            {prediction = "Bad";}
            else if(Tree[2].good_count > Tree[2].ok_count && Tree[2].good_count > Tree[2].bad_count)
            {prediction = "Good";}
            else
            {prediction = "OK";}
            actual = td.get_mpg(test_cars[i]);
            cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
        }
        else
        {
            if(Tree[3].bad_count > Tree[3].ok_count && Tree[3].bad_count > Tree[3].good_count)
            {prediction = "Bad";}
            else if(Tree[3].good_count > Tree[3].ok_count && Tree[3].good_count > Tree[3].bad_count)
            {prediction = "Good";}
            else
            {prediction = "OK";}
            actual = td.get_mpg(test_cars[i]);
            cout<<"Prediction = " <<prediction <<" ,Actual = " <<actual <<endl;
        }
    }



    /*
    TreeData td = TreeData();
    Node node = Node();

    cout<<endl <<endl;

    for(int i = 0; i<Tree[2].node_data.size();i++)
    {
        cout<<"Year = " <<td.get_cyl(Tree[2].node_data[i]) <<", " <<td.get_mpg(Tree[2].node_data[i]) <<endl;
    }

    */

}




