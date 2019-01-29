//Author: Kartikei Mittal
//Implementation of Graph in C++ using Adjancey matriix.
#include <iostream>
#include <exception>
#include<algorithm>
#include<vector>
#include<queue>
    using namespace std;
//Maximum Number of Vertex
#define maxVertex 10
#define vertex_size vertices.size()

//== Need to be overloaded for given typename T
template <typename T>
class Graph
{
    double adjMat[maxVertex][maxVertex];
    vector<T> vertices;
public:
    Graph()
    {
        for(int i=0; i<maxVertex; ++i)
            for(int j=0; j<maxVertex; ++j)
                adjMat[i][j] = 0.0;
    }
    void add_vertex(T D)
    {
        if(vertex_size == maxVertex)
        {
            cerr<<"Maximum Vertex Reached."<<endl;
            return ;
        }
        vertices.push_back(D);
    }
    int find_vertex_index(T toFind) {
        return std::find(vertices.begin(), vertices.end(), toFind)-vertices.begin();
    }
    void add_edge(T from, T to, double val=1.0)
    {
        int row = find_vertex_index(from);
        int column = find_vertex_index(to);
        
        if(row!=vertex_size && column!=vertex_size)
        {
            adjMat[row][column] = val;
            return ;
        }
        cerr<<"Vertex not found."<<endl;   
    }
    void show_adjMat()
    {
        for(int i=0; i<vertex_size; ++i)
        {
            for(int j=0; j<vertex_size; ++j)
                cout<<"\t"<<adjMat[i][j];
            cout<<endl;
        }
    }
    void BFT(T root)
    {
        cout<<"BFT: ";
        std::queue<T> que;
        vector<bool> visited(vertex_size, false);
        int index = find_vertex_index(root);
        if(index != vertex_size)
        {
            visited[index] = true; 
            que.push(index); 
        
            while(!que.empty())
            { 
                index = que.front();
                cout<<vertices.at(index)<<endl; 
                que.pop();
                for(int i=0; i<vertex_size; ++i) 
                    if(!visited[i] && adjMat[index][i]!=0) 
                    { 
                        visited[i] = true; 
                        que.push(i); 
                    } 
            }
            cout<<endl;
            return ;
        }
        cerr<<"Root does not exist in graph"<<endl;
    }
    void DFT_util(int index, vector<bool> &visited)
    {
        visited[index] = true; 
        cout<<vertices.at(index)<<"\t"; 
        for(int i=0; i<vertex_size; ++i) 
            if(!visited[i] && adjMat[index][i]!=0) 
                DFT_util(i,visited); 
    }
    void DFT(T root)
    {
        cout<<"DFT: ";
        vector<bool> visited(vertex_size, false);
        int index = find_vertex_index(root);
        if(index != vertex_size)
        {
            DFT_util(index, visited);
            cout<<endl; 
            return ;
        }
        cerr<<"Root does not exist in graph"<<endl;
    }
};


 using namespace std;
int main(int argc, char const *argv[])
try
{
    Graph<int> G;
    for(int i=0; i<5; ++i)
        G.add_vertex(i);
    /*
    for(int i=0; i<3; ++i)
        for(int j=2; j<5; ++j)
            G.add_edge(i, j);
    */ 
    //G.BFT(1);
    G.add_edge(0,1);
    G.add_edge(0,2);
    G.add_edge(1,2);
    G.add_edge(2,0);
    G.add_edge(2,3);
    G.DFT(2);
    G.show_adjMat();
    return 0;
}
catch(exception &e) {
    cerr<<"\nException"<<e.what();
}
catch(...) {
    cerr<<"\nUnknown Exception Terminate.";
}