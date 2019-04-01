//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com
//KMP String Matching
#define MrRex_version true
#include<bits/stdc++.h>

vector<int> prefix_func(string ptr)
{
    int M = ptr.length(), curr = 0;
    vector<int> lps(ptr.length(), 0);

    for(int i=1; i<M; ++i)
        if(ptr[i] == ptr[curr])
            lps[i] = ++curr;
        else if(curr != 0)
        {
            curr = lps[curr-1];
            --i;//Do not move forward, next iteration check again
        }
    return lps;
}

void kmp(string text, string ptr)
{
    int M = ptr.length(),
        N = text.length(),
        matchCount = 0, j = 1;
    vector<int> lps = prefix_func(ptr);

    int i=0;
    while(i<N)
    {
        if(text[i]==ptr[j])
        {
            ++j;
            ++i;
        }
        if(j==M)
        {
            cout<<"Pattern found at: "<<i<<endl;
            j = lps.at(j - 1);
            ++matchCount;
        }
        else if(i<N && ptr[j] != text[i])
            if(j)
                j = lps.at(j - 1);
            else
                ++i;
    }
}

int main(int argc, char const *argv[])
{   cout<<endl;
    
    // string s = "";
    // int t = 4000;
    
    // std::uniform_int_distribution<uint32_t> alpha_select(65, 91);
    // while(t--)
    // {
    //     bool flag = false;
    //     
    //     for(int i=0; i<a; ++i)
    //         s += (char )(alpha_select(rng));
    //     vector<int> lps1 = prefix_func(s), lps2 = prefix_func2(s);
    //     for(int i=0; i<a; ++i)
    //         if(lps1[i] != lps2[i])
    //         {
    //             flag = true;
    //             break;
    //         }
    //     if(flag)
    //     {
    //         cout<<s<<endl<<lps1<<endl<<lps2;
    //         cin>>a;
    //         if(a==0)
    //             return 0;
    //     }
    // }

    if(argc!=4)
    {
        cerr<<"Invalid Number of arguments."<<endl;
        return 0;
    }
    string text = argv[1], ptr = argv[2];
    if(*argv[3] == '1')
        kmp(text, ptr);
    else
        cerr<<"Invalid Argument"<<endl;
    
    cout<<endl; return 0;
}