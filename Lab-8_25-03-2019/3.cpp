//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com
//Fractional Knapsack
#include<bits/stdc++.h>
    using namespace std;
#define MAX_WEIGHT 50

class item
{
public:
    int id;
    double isIncluded;
    double wei, ben;
    item(double a, double b, int c): id(c), ben(a), wei(b), isIncluded(0) {}
    bool operator>(const item &b) { return ((ben/wei) > (b.ben/b.wei))? 1:0; }
    bool operator<(const item &b) { return ((ben/wei) < (b.ben/b.wei))? 1:0; }
};

inline double current_wei(vector<item> input)
{
    double ans = 0;
    for(int i=0; i<input.size(); ++i)
        ans += input[i].wei * input[i].isIncluded;
    return ans;
}

inline void print_knapsack(vector<item> input, double wei)
{
    double c_wei = 0, c_ben = 0;
    for(int i=0; i<input.size(); ++i)    
    {
        cout<<"Item:"<<endl
            <<" Weight="<<input[i].wei
            <<" ben="<<input[i].ben
            <<" Included="<<input[i].isIncluded
            <<endl<<endl;
        c_wei += input[i].wei * input[i].isIncluded;
        c_ben += input[i].ben * input[i].isIncluded;
    }
    cout<<"Total wei: "<<c_wei<<endl
        <<"Total ben: "<<c_ben<<endl
        <<"Max Weight: "<<wei<<endl;
}

inline void knapsack(vector<item> input, double wei, int k)
{
    vector<item> out = input;
    sort(input.begin(), input.end());
    int i;
    for(i=input.size()-1; i>=0; --i)
        if(wei >= (input[i].wei + current_wei(input)))
            input[i].isIncluded = 1;
        else
            break;
    if(k==1 && i!=-1)
        input[i].isIncluded = (wei-current_wei(input))/input[i].wei;
    for(int i=0; i<input.size(); ++i)
        if(input[i].isIncluded)
        {
            int a = input[i].id;
            for(int j=0; j<out.size(); ++j)
                if(out[j].id == a)
                {
                    out[j].isIncluded = input[i].isIncluded;
                    break;
                }
        }
    print_knapsack(out, MAX_WEIGHT);
}

int main(int argc, char const *argv[])
{
    cout<<"Hiiii"<<endl;

    vector<item> input;

    item i1(60, 10, 1), i2(100, 20, 2), i3(120, 30, 3);
    input.push_back(i1);
    input.push_back(i2);
    input.push_back(i3);
    knapsack(input, MAX_WEIGHT, 0);
    cout<<endl<<"--------------------------------------------------------------------------------"<<endl;
    knapsack(input, MAX_WEIGHT, 1);
    cout<<endl;
    return 0;
}