//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com

#include<bits/stdc++.h>
    using namespace std;
#define MAX_WEIGHT 50

class item
{
public:
    bool isIncluded;
    double weight, benefit;
    item(double a, double b): benefit(a), weight(b), isIncluded(false) {}
};

inline double current_weight(vector<item> input)
{
    double ans = 0;
    for(int i=0; i<input.size(); ++i)
        if(input[i].isIncluded)
            ans += input[i].weight;
    return ans;
}

inline void knapsack(vector<item> &input, double weight)
{
    
}

inline void print_knapsack(vector<item> input)
{

}

int main(int argc, char const *argv[])
{
    cout<<"Hiiii";

    vector<item> input;

    item i1(60, 10), i2(100, 20), i3(120, 30);
    input.push_back(i1);
    input.push_back(i2);
    input.push_back(i3);
    knapsack(input, MAX_WEIGHT);

    cout<<endl;
    return 0;
}