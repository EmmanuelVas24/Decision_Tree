#include "Node.h"
#include "TreeData.h"
#include <math.h>
#include <vector>
#include<iostream>
#include <string>

Node::Node()
{
    attribute_name = "";
    //node_data = ;
    entropy = 0.0;
    good_count = 0;
    ok_count = 0;
    bad_count = 0;
    Parent_node = NULL;
    Branch1 = NULL;
    Branch2 = NULL;
    Branch3 = NULL;
}

Node::Node(string attribute,vector<TreeData> data,double entpy,int good,int ok,int bad,Node* par,Node* b1,Node* b2,Node* b3)
{
    attribute_name = attribute;
    entropy = entpy;
    good_count = good;
    ok_count = ok;
    bad_count = bad;
    Parent_node = par;
    Branch1 = b1;
    Branch2 = b2;
    Branch3 = b3;
    for (int i=0; i<data.size(); i++)
    {
        node_data.push_back(data[i]);
    }

}


void Node::get_best_split(Node* node_obj)
{
    cout<<"In best split function" <<endl;
    int parent_total = node_obj->bad_count + node_obj->good_count + node_obj->ok_count;


    double avg_entropy = 0.0;
    double info_gain = 0.0;
    //double max_info_gain = 0.0;

    double good1 = 0,ok1 = 0,bad1 = 0,good2 = 0,ok2 = 0,bad2 = 0,good3 = 0,ok3 = 0,bad3 = 0;
    double n1 = 0,n2 = 0,n3 = 0;
    double p1 = 0,p2 = 0,p3 = 0;
    double e1 = 0,e2 = 0,e3 = 0;

    int ub_low_range = 0, lb_high_range = 0;

    // ---------------------------------------------------------------------------------------------------------------------

    if(split_cylinder == 0)             // split on cylinder
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_cyl(node_obj->node_data[i]) == 4 && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);   bad1++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 4 && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);   ok1++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 4 && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);   good1++;}

            if(node_obj->get_cyl(node_obj->node_data[i]) == 6 && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v2.push_back(node_obj->node_data[i]);   bad2++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 6 && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v2.push_back(node_obj->node_data[i]);   ok2++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 6 && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v2.push_back(node_obj->node_data[i]);   good2++;}

            if(node_obj->get_cyl(node_obj->node_data[i]) == 8 && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);   bad3++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 8 && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);   ok3++;}
            if(node_obj->get_cyl(node_obj->node_data[i]) == 8 && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);   good3++;}
        }


        n1 = bad1+ok1+good1;

        if(n1 == 0)
        {p1=1;p2=1;p3=1;}
        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;

        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;

        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}


        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_cylinder = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Cylinders",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }

        cout<<"Info Gain on cylinders = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }
    // ------------------------------------------------------------------------------------------------------------------

    ub_low_range = displacement_mean - displacement_dev;
    lb_high_range = displacement_mean + displacement_dev;

    if(split_displacement == 0)             // split on displacement
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_disp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);  bad1++;}
            if(node_obj->get_disp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);  ok1++;}
            if(node_obj->get_disp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);  good1++;}

            if((node_obj->get_disp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_disp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Bad"))
            {v2.push_back(node_obj->node_data[i]);  bad2++;}
            if((node_obj->get_disp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_disp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "OK"))
            {v2.push_back(node_obj->node_data[i]);  ok2++;}
            if((node_obj->get_disp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_disp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Good"))
            {v2.push_back(node_obj->node_data[i]);  good2++;}

            if(node_obj->get_disp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);  bad3++;}
            if(node_obj->get_disp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);  ok3++;}
            if(node_obj->get_disp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);  good3++;}
        }

        ub_low_range = 0; lb_high_range = 0;

        n1 = bad1+ok1+good1;

        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;

        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;

        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_displacement = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Displacement",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on displacement = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }
    // ------------------------------------------------------------------------------------------------------------------

    ub_low_range = horsepower_mean - horsepower_dev;
    lb_high_range = horsepower_mean + horsepower_dev;

    if(split_horsepower == 0)             // split on horsepower
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_hp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);  bad1++;}
            if(node_obj->get_hp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);  ok1++;}
            if(node_obj->get_hp(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);  good1++;}

            if((node_obj->get_hp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_hp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Bad"))
            {v2.push_back(node_obj->node_data[i]);  bad2++;}
            if((node_obj->get_hp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_hp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "OK"))
            {v2.push_back(node_obj->node_data[i]);  ok2++;}
            if((node_obj->get_hp(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_hp(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Good"))
            {v2.push_back(node_obj->node_data[i]);  good2++;}

            if(node_obj->get_hp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);  bad3++;}
            if(node_obj->get_hp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);  ok3++;}
            if(node_obj->get_hp(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);  good3++;}
        }

        ub_low_range = 0; lb_high_range = 0;

        n1 = bad1+ok1+good1;

        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;
        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;
        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_horsepower = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Horsepower",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on horsepower = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }

    // ------------------------------------------------------------------------------------------------------------------

    ub_low_range = weight_mean - weight_dev;
    lb_high_range = weight_mean + weight_dev;

    if(split_weight == 0)             // split on weight
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_wt(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);  bad1++;}
            if(node_obj->get_wt(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);  ok1++;}
            if(node_obj->get_wt(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);  good1++;}

            if((node_obj->get_wt(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_wt(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Bad"))
            {v2.push_back(node_obj->node_data[i]); bad2++;}
            if((node_obj->get_wt(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_wt(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "OK"))
            {v2.push_back(node_obj->node_data[i]);  ok2++;}
            if((node_obj->get_wt(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_wt(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Good"))
            {v2.push_back(node_obj->node_data[i]);  good2++;}

            if(node_obj->get_wt(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);  bad3++;}
            if(node_obj->get_wt(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);  ok3++;}
            if(node_obj->get_wt(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);  good3++;}
        }

        ub_low_range = 0; lb_high_range = 0;

        n1 = bad1+ok1+good1;
        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;
        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;
        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        cout<<"Info gain weight = " <<info_gain <<endl;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_weight = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Weight",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on weight = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }

    // -----------------------------------------------------------------------------------------------------------------------------------

    ub_low_range = year_mean - year_dev;
    lb_high_range = year_mean + year_dev;

    if(split_year == 0)             // split on year
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_year(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);  bad1++;}
            if(node_obj->get_year(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);  ok1++;}
            if(node_obj->get_year(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);  good1++;}

            if((node_obj->get_year(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_year(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Bad"))
            {v2.push_back(node_obj->node_data[i]);  bad2++;}
            if((node_obj->get_year(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_year(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "OK"))
            {v2.push_back(node_obj->node_data[i]);  ok2++;}
            if((node_obj->get_year(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_year(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Good"))
            {v2.push_back(node_obj->node_data[i]);  good2++;}

            if(node_obj->get_year(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);  bad3++;}
            if(node_obj->get_year(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);  ok3++;}
            if(node_obj->get_year(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);  good3++;}
        }

        ub_low_range = 0; lb_high_range = 0;

        n1 = bad1+ok1+good1;
        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;
        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;
        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_year = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Year",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on year = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }

    // -----------------------------------------------------------------------------------------------------------------

    ub_low_range = acceleration_mean - acceleration_dev;
    lb_high_range = acceleration_mean + acceleration_dev;

    if(split_acceleration == 0)             // split on acceleration
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_acc(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);  bad1++;}
            if(node_obj->get_acc(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);  ok1++;}
            if(node_obj->get_acc(node_obj->node_data[i]) < (ub_low_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);  good1++;}

            if((node_obj->get_acc(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_acc(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Bad"))
            {v2.push_back(node_obj->node_data[i]);  bad2++;}
            if((node_obj->get_acc(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_acc(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "OK"))
            {v2.push_back(node_obj->node_data[i]);  ok2++;}
            if((node_obj->get_acc(node_obj->node_data[i]) > (ub_low_range)) && (node_obj->get_acc(node_obj->node_data[i]) < (lb_high_range)) && (node_obj->get_mpg(node_obj->node_data[i]) == "Good"))
            {v2.push_back(node_obj->node_data[i]);  good2++;}

            if(node_obj->get_acc(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);  bad3++;}
            if(node_obj->get_acc(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);  ok3++;}
            if(node_obj->get_acc(node_obj->node_data[i]) > (lb_high_range) && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);  good3++;}
        }

        ub_low_range = 0; lb_high_range = 0;


        n1 = bad1+ok1+good1;
        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;
        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;
        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_acceleration = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Acceleration",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on acceleration = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }

    // --------------------------------------------------------------------------------------------------------------------------------------------

    if(split_maker == 0)             // split on maker
    {
        for (int i=0; i<node_obj->node_data.size(); i++)
        {
            if(node_obj->get_mk(node_obj->node_data[i]) == "America" && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v1.push_back(node_obj->node_data[i]);   bad1++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "America" && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v1.push_back(node_obj->node_data[i]);   ok1++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "America" && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v1.push_back(node_obj->node_data[i]);   good1++;}

            if(node_obj->get_mk(node_obj->node_data[i]) == "Asia" && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v2.push_back(node_obj->node_data[i]);   bad2++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "Asia" && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v2.push_back(node_obj->node_data[i]);   ok2++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "Asia" && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v2.push_back(node_obj->node_data[i]);   good2++;}

            if(node_obj->get_mk(node_obj->node_data[i]) == "Europe" && node_obj->get_mpg(node_obj->node_data[i]) == "Bad")
            {v3.push_back(node_obj->node_data[i]);   bad3++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "Europe" && node_obj->get_mpg(node_obj->node_data[i]) == "OK")
            {v3.push_back(node_obj->node_data[i]);   ok3++;}
            if(node_obj->get_mk(node_obj->node_data[i]) == "Europe" && node_obj->get_mpg(node_obj->node_data[i]) == "Good")
            {v3.push_back(node_obj->node_data[i]);   good3++;}
        }

        n1 = bad1+ok1+good1;
        if(n1 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad1/n1;
        p2 = ok1/n1;
        p3 = good1/n1;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e1 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e1 = " <<e1 <<endl;
        p1 = 0; p2 = 0; p3 = 0;


        n2 = bad2+ok2+good2;
        if(n2 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad2/n2;
        p2 = ok2/n2;
        p3 = good2/n2;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e2 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e2 = " <<e2 <<endl;
        p1 = 0; p2 = 0; p3 = 0;

        n3 = bad3+ok3+good3;
        if(n3 == 0)
        {p1=1;p2=1;p3=1;}

        else
        {p1 = bad3/n3;
        p2 = ok3/n3;
        p3 = good3/n3;}

        if(p1 == 0)
        {p1 = 1;}
        if(p2 == 0)
        {p2 = 1;}
        if(p3 == 0)
        {p3 = 1;}

        e3 = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));

        cout<<"e3 = " <<e3 <<endl;

        avg_entropy = ((n1/parent_total)*e1) + ((n2/parent_total)*e2) + ((n3/parent_total)*e3);

        cout<<"avg entropy = " <<avg_entropy <<endl;

        info_gain = node_obj->entropy - avg_entropy;

        if(info_gain == max_info_gain && info_gain != 0 && run_best_split != 0)
        {
            split_maker = 1;
            create_child_nodes(node_obj,e1,e2,e3,"Maker",bad1,bad2,bad3,ok1,ok2,ok3,good1,good2,good3,v1,v2,v3);
            return;
        }

        if(info_gain > max_info_gain)
        {
            max_info_gain = info_gain;
        }
        cout<<"Info Gain on maker = "<<info_gain <<endl;

        avg_entropy = 0; info_gain = 0;
        bad1 = 0; bad2 = 0; bad3 = 0; ok1 = 0; ok2 = 0; ok3 = 0; good1 = 0; good2 = 0; good3 = 0;
        p1 = 0; p2 = 0; p3 = 0; e1 = 0; e2 = 0; e3 = 0; n1 = 0; n2 = 0; n3 = 0;
        v1.clear(); v2.clear(); v3.clear();

        cout<<"Max Info Gain = "<<max_info_gain <<endl <<endl;
    }

    if(run_best_split == 0)                                              // run it twice
    {run_best_split++; get_best_split(node_obj);}

}

void Node::create_root_node()       // entropy on good,bad,ok
{
    TreeData cars_obj = TreeData();
    cars_obj.readToVector("car.txt");
    cars_obj.makeCarObjects();
    cars_obj.stringToInstance();        // Create the vector of car objects

    // Create the root node

    Node root_node = Node();
    int good = 0, ok = 0, bad = 0;

    for (int i=0; i<cars_obj.cars.size(); i++)
    {
        if(cars_obj.get_mpg(cars_obj.cars[i]) == "Bad")
        {   bad++;}
        if(cars_obj.get_mpg(cars_obj.cars[i]) == "OK")
        {   ok++;}
        if(cars_obj.get_mpg(cars_obj.cars[i]) == "Good")
        {  good++;}
    }

    double n = 0, p1 = 0, p2 = 0, p3 = 0, entpy = 0;

    n = bad + good + ok;
    p1 = bad/n;
    p2 = ok/n;
    p3 = good/n;

    entpy = ((-1)*p1*(log(p1)/log(2))) + ((-1)*p2*(log(p2)/log(2))) + ((-1)*p3*(log(p3)/log(2)));
    cout<<"Entropy of root node = " <<entpy <<endl;

    vector<TreeData> vec;

    for (int i=0; i<cars_obj.cars.size(); i++)
    {
        vec.push_back(cars_obj.cars[i]);
    }

    Node* null_branch = NULL;

    root_node = Node("",vec,entpy,good,ok,bad,null_branch,null_branch,null_branch,null_branch);

    set_ranges(&root_node);
    nodes.push_back(root_node);
    store_nodes();
    get_best_split(&root_node);

    split_child();

    for(int i = 0; i<nodes.size();i++)
    {
        cout<<"[" <<i <<"] :" <<"Entropy = " <<nodes[i].entropy <<", " <<nodes[i].attribute_name <<", Size = " <<nodes[i].node_data.size() <<endl;
        //cout<<"Children: " <<nodes[i].Branch1->attribute_name <<", " <<nodes[i].Branch2->attribute_name <<", " <<nodes[i].Branch3->attribute_name <<endl <<endl;
    }

    //display_tree();

}

void Node::set_ranges(Node* node_obj)
{
    int num_cars = node_obj->node_data.size();
    int sum_disp = 0, sum_hp = 0, sum_wt = 0, sum_year = 0;
    double sum_acc = 0;

    for (int i=0; i<num_cars; i++)
    {
        sum_disp += node_obj->get_disp(node_obj->node_data[i]);
        sum_hp += node_obj->get_hp(node_obj->node_data[i]);
        sum_wt += node_obj->get_wt(node_obj->node_data[i]);
        sum_year += node_obj->get_year(node_obj->node_data[i]);
        sum_acc += node_obj->get_acc(node_obj->node_data[i]);
    }

    displacement_mean = sum_disp/num_cars;
    horsepower_mean = sum_hp/num_cars;
    weight_mean = sum_wt/num_cars;
    year_mean = sum_year/num_cars;
    acceleration_mean = sum_acc/num_cars;

    for(int i = 0; i < num_cars; i++ )
    {
        displacement_dev += (node_obj->get_disp(node_obj->node_data[i]) - displacement_mean) * (node_obj->get_disp(node_obj->node_data[i]) - displacement_mean);
        horsepower_dev += (node_obj->get_hp(node_obj->node_data[i]) - horsepower_mean) * (node_obj->get_hp(node_obj->node_data[i]) - horsepower_mean);
        weight_dev += (node_obj->get_wt(node_obj->node_data[i]) - weight_mean) * (node_obj->get_wt(node_obj->node_data[i]) - weight_mean);
        year_dev += (node_obj->get_year(node_obj->node_data[i]) - year_mean) * (node_obj->get_year(node_obj->node_data[i]) - year_mean);
        acceleration_dev += (node_obj->get_acc(node_obj->node_data[i]) - acceleration_mean) * (node_obj->get_acc(node_obj->node_data[i]) - acceleration_mean);
    }
    displacement_dev /= num_cars;
    horsepower_dev /= num_cars;
    weight_dev /= num_cars;
    year_dev /= num_cars;
    acceleration_dev /= num_cars;

    displacement_dev = sqrt(displacement_dev);
    horsepower_dev = sqrt(horsepower_dev);
    weight_dev = sqrt(weight_dev);
    year_dev = sqrt(year_dev);
    acceleration_dev = sqrt(acceleration_dev);

}

void Node::store_nodes()
{
    //Node node_obj = Node();

    Node n1 = Node();
    Node n2 = Node();
    Node n3 = Node();
    Node n4 = Node();
    Node n5 = Node();
    Node n6 = Node();
    Node n7 = Node();
    Node n8 = Node();
    Node n9 = Node();
    Node n10 = Node();

    Node n11 = Node();
    Node n12 = Node();
    Node n13 = Node();
    Node n14 = Node();
    Node n15 = Node();
    Node n16 = Node();
    Node n17 = Node();
    Node n18 = Node();
    Node n19 = Node();
    Node n20 = Node();

    nodes.push_back(n1);
    nodes.push_back(n2);
    nodes.push_back(n3);
    nodes.push_back(n4);
    nodes.push_back(n5);
    nodes.push_back(n6);
    nodes.push_back(n7);
    nodes.push_back(n8);
    nodes.push_back(n9);
    nodes.push_back(n10);

    nodes.push_back(n11);
    nodes.push_back(n12);
    nodes.push_back(n13);
    nodes.push_back(n14);
    nodes.push_back(n15);
    nodes.push_back(n16);
    nodes.push_back(n17);
    nodes.push_back(n18);
    nodes.push_back(n19);
    nodes.push_back(n20);
}

void Node::create_child_nodes(Node* parent, double ent1, double ent2, double ent3, string attr_name, double bad1, double bad2, double bad3, double ok1, double ok2, double ok3, double good1, double good2, double good3,vector<TreeData> vec1,vector<TreeData> vec2,vector<TreeData> vec3)
{
    if(node_count == 0)
    {
        nodes[0].attribute_name = attr_name;
    }

    node_count = node_count + 3;        // create 3 new child nodes

    parent->attribute_name = attr_name;
    parent->Branch1 = &nodes[node_count-2];
    parent->Branch2 = &nodes[node_count-1];
    parent->Branch3 = &nodes[node_count];

    if(node_count == 3)
    {
        nodes[0].Branch1 = &nodes[node_count-2];
        nodes[0].Branch2 = &nodes[node_count-1];
        nodes[0].Branch3 = &nodes[node_count];
    }

    Node* null_branch = NULL;

    nodes[node_count-2] = Node("",vec1,ent1,good1,ok1,bad1,parent,null_branch,null_branch,null_branch);               // initialize nodes, set stopping condition
    nodes[node_count-1]= Node("",vec2,ent2,good2,ok2,bad2,parent,null_branch,null_branch,null_branch);
    nodes[node_count]= Node("",vec3,ent3,good3,ok3,bad3,parent,null_branch,null_branch,null_branch);

    max_info_gain = 0.0;

    /*

    cout<<endl <<"Entropy = " <<nodes[node_count].entropy <<endl;

    for (int i=0; i < nodes[node_count-1].node_data.size(); i++)
    {
        cout<<get_mpg(nodes[node_count-1].node_data[i]) <<",";
    }
    cout<<endl;

    */

}

void Node::split_child()
{
    run_split_child++;

    double max_entropy = 0;
    int i;

    for(i = 0;i<node_count+1;i++)
    {
        if(nodes[i].attribute_name == "")
        {
            if(nodes[i].entropy > max_entropy)
            {
                max_entropy =  nodes[i].entropy;
            }
        }
    }

    int split_node;

    for(i = 0;i<node_count+1;i++)
    {
        if(nodes[i].entropy == max_entropy)
        {
            split_node = i;
            break;
        }
    }

    if(nodes[split_node].entropy != 0)
    {
        run_best_split = 0;
        get_best_split(&nodes[split_node]);
    }
    cout<<"Node split" <<endl;


    max_entropy = 0;
    for(int i = 0;i<node_count+1;i++)
    {
        if(nodes[i].attribute_name != "")
        {
            cout<<nodes[i].attribute_name <<endl;
        }
    }

    cout<<"Node count = " <<node_count <<endl;


    if(run_split_child < 4)
    {
        split_child();
    }


}

string Node::get_attribute(Node n)
{
    return n.attribute_name;
}

void Node::display_tree()
{



}








