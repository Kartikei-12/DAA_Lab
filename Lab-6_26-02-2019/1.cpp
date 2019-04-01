//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com
/*
String Matching Algorithm
    Brute Force
    Rabin Karp
*/
#include<iostream>
    using namespace std;

#define PRIME 101
#define NO_CHRACTER 256

int brute_force_string_match(string text, string ptr)
{
    int matchCount=0, M=text.length(), N=ptr.length();
    for(int i=0; i<(M-N+1); ++i)
    {
        int j=0;
        for(; j<N && text[i+j]==ptr[j]; ++j);
        if(j==N)
        {
            cout<<"Pattern found at: "<<i<<endl;
            ++matchCount;
        }
    }
    cout<<"Total matches: "<<matchCount<<endl;
    return matchCount;
}

int rabin_karp(string text, string ptr)
{
    int matchCount=0, N=text.length(), M=ptr.length(),
        p = 0, t = 0, h = 1, q = PRIME, d = NO_CHRACTER;

    for(int i = 0; i < M-1; ++i)
        h = (h*d)%q;
    // cout<<"\n"<<h<<"\n";
    for(int i = 0; i < M; ++i) 
    { 
        p = (d*p + ptr[i])%q; 
        t = (d*t + text[i])%q; 
    } 
    
    for(int i=0; i<(N-M+1); ++i)
    {
        if(p == t) 
        {
            int j=0;
            for(; j<M && text[i+j]==ptr[j]; j++);
            if (j == M)
            {
                cout<<"Pattern found at: "<<i<<endl;
                ++matchCount;
            } 
        }
        t = ( d*(t-text[i]*h) + text[i+M])%q; 
        if(t < 0)
            t += q; 
    
    }
    cout<<"Total matches : "<<matchCount<<endl;
    return matchCount;
}

int main(int argc, char const *argv[])
{
    cout<<endl;
    if(argc!=4)
    {
        cerr<<"Invalid Number of arguments."<<endl;
        return 0;
    }
    string text = argv[1], ptr = argv[2];
    if(*argv[3] == '1')
        brute_force_string_match(text, ptr);
    else if(*argv[3] == '2')
        rabin_karp(text, ptr);
    else
        cerr<<"Invalid Argument"<<endl;
    cout<<endl;
    return 0;
}