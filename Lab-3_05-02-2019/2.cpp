//Author: Kartikei Mittal
//ID: 2017KUCP1032
#include<iostream>
    using namespace std;
//Implementation of cycle detection in undirected graph algorithm with
//maximum degree defined using adjancey array.
#define DEGREE 8
#define MAX_NODE DEGREE+1

#define NodePtr Node<T>*

template<typename T>
class Edge;

template<typename T>
class Node
{
public:
    bool visited;
    int degree;
    T data;
    Edge<T>* Links[DEGREE];

    Node(T a)
    {
        visited = false;
        degree = 0;
        data=a;
        for(int i=0; i<DEGREE; ++i)
            Links[i] = NULL;
    }

    void add_e(Edge<T>* e)
    {
        Links[degree] = e;
        ++degree;
    }
};

template<typename T>
class Edge
{
public:
    //Just simple names graph is undirected
    NodePtr n1;
    NodePtr n2;
    long double value;
    Edge(NodePtr t1, NodePtr t2, long double v=0)
    {
        value = v;
        n1 = t1;
        n2 = t2;
    }
};

template<typename T>
class Graph
{
    int num_nodes;
    NodePtr N[MAX_NODE];
    NodePtr paraent_node;

    void DFT_util(NodePtr root)
    {
        root->visited = true;
        cout<<"Data: "<<root->data<<endl;
        for(int i=0; i<root->degree; ++i)
            if(root->Links[i]->n1 == root && !(root->Links[i]->n2->visited))
                DFT_util(root->Links[i]->n2);
            else if(!(root->Links[i]->n1->visited))
                DFT_util(root->Links[i]->n1);
    }
    bool isCyclic_util(NodePtr root, bool &iscycle)
    {
        if(!iscycle)
        {
            NodePtr next_node = NULL;
            root->visited = true;
            cout<<"Data: "<<root->data<<endl;
            for(int i=0; i<root->degree && !iscycle; ++i)
            {
                if(root->Links[i]->n1 == root)
                    next_node = root->Links[i]->n2;
                else
                    next_node = root->Links[i]->n1;
                /*paraent_node
                root or current node
                next_node*/
                if(!next_node->visited)
                {
                    paraent_node = root;
                    isCyclic_util(next_node, iscycle);
                }
                else if(next_node != paraent_node)
                {
                    cout<<"Cycle found at: "<<next_node->data<<endl;
                    iscycle=true;
                }
            }
        }
        return iscycle;
    }
public:
    Graph()
    {
        num_nodes = 0;
        for(int i=0; i<MAX_NODE; ++i)
            N[i] = NULL;
    }

    NodePtr add_node(T d)
    {
        if(num_nodes >= MAX_NODE)
        {
            cerr<<"Maximum number of Nodes reached.";
            return NULL;
        }
        NodePtr temp = new Node<T>(d);
        N[num_nodes] = temp;
        num_nodes++;
        return temp;
    }

    void add_edge(NodePtr f, NodePtr t, long double val=0)
    {
        Edge<T>* temp = new Edge<T>(f, t, val);
        f->add_e(temp);
        t->add_e(temp);
    }

    void DFT(NodePtr root = NULL)
    {
        if(root == NULL)
            root = N[0];
        for(int i=0; i<num_nodes; ++i)
            N[i]->visited = false;
        DFT_util(root);
    }

    bool isCyclic(NodePtr root = NULL)
    {
        if(root == NULL)
            root = N[0];
        paraent_node = NULL;
        for(int i=0; i<num_nodes; ++i)
            N[i]->visited = false;
        bool a = false;
        return isCyclic_util(root, a);
    }
};



int main(int argc, char const *argv[])
{
    Node<int>* nodess[6];
    Graph<int> G;
    for(int i=0; i<6; ++i)
        nodess[i] = G.add_node(i);
    G.add_edge(nodess[0], nodess[2]);
    G.add_edge(nodess[2], nodess[4]);
    G.add_edge(nodess[2], nodess[1]);
    G.add_edge(nodess[4], nodess[5]);
    G.add_edge(nodess[1], nodess[3]);
    G.add_edge(nodess[2], nodess[5]);
    G.add_edge(nodess[2], nodess[3]);
    G.add_edge(nodess[3], nodess[5]);
    
    //G.DFT();
    cout<<"Is cyclic:"<<G.isCyclic();
    return 0;
}
