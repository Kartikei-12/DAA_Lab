#include<iostream>
#include<vector>
#include<algorithm>
    using namespace std;
//Implementation of BFS and DFS with
//maximum degree defined using adjancey array.
#define degree 5
#define maxNode 10

template <typename T>
class Node
{
public:
    T data;
    vector<Node<T>*> Links;
    bool visited;
    Node(T a)
    {
        data=a;
        for(int i=0; i<degree; ++i)
            Links[i] = NULL;
        visited = false;
    }
};

template <typename T>
class Graph
{
    Node<T>* nodes[maxNode];
    void DFS_util(Node<T>* root=nodes[0])
    {
        root->visited=true;
        cout<<"Data: "<<root->data<<endl;
        for(int i=0; i<degree && root->Links[i]!=NULL; ++i)
            if(!(root->Links[i]->visited))
                DFS(root->Links[i]);
    }
public:
    Graph()
    {
        for(int i=0; i<maxNode; ++i)
            nodes[i] = NULL;
    }

    void insert_node(T data)
    {
        if(nodes[maxNode-1] != NULL)
        {
            cerr<<"Maximum number of Nodes reached"<<endl;
            return ;
        }
        int i=0;
        for(; i<maxNode && nodes[i]!=NULL; ++i)
        nodes[i] = new Node(data);
    }

    void insert_edge(T from, T to)

    void DFS(Node<T>* root)
    {
        for(int i=0; i<maxNode && nodes[i]!=NULL; ++i)
            nodes[i]->visited = false;
        DFS(root);
    }
};


int main()
{
    Graph<char> G;
    for(int i=0; i<6; ++i)
        G.insert_node('A'+i);
        
    a1->Links[0] = a3;
    a1->Links[1] = a2;

    a2->Links[0] = a1;
    a2->Links[1] = a3;
    a2->Links[2] = a5;
    a2->Links[3] = a4;
    
    a3->Links[0] = a1;
    a3->Links[1] = a5;
    a3->Links[2] = a4;
    a3->Links[3] = a2;
    
    a4->Links[0] = a2;
    a4->Links[1] = a3;
    a4->Links[2] = a5;
    a4->Links[3] = a6;

    a5->Links[0] = a6;
    a5->Links[1] = a4;
    a5->Links[2] = a2;
    a5->Links[3] = a3;

    a6->Links[0] = a4;
    a6->Links[1] = a5;

    DFS(a1);

    return 0;
}