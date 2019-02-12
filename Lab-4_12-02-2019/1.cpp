//Author: Kartikei Mittal
//ID: 2017KUCP1032
#include<iostream>
    using namespace std;


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
    long double value;
    //Just simple names graph is undirected
    NodePtr n1;
    NodePtr n2;
    bool isProcessed;
    Edge(NodePtr t1, NodePtr t2, long double v=0)
    {
        isProcessed = false;
        value = v;
        n1 = t1;
        n2 = t2;
    }
};


template<typename T>
class Graph
{
public:
    int num_nodes, num_edge;
    NodePtr paraent_node;
    NodePtr N[MAX_NODE];
    Edge<T>* E[MAX_NODE*DEGREE];


    Graph()
    {
        num_nodes = num_edge = 0;
        for(int i=0; i<MAX_NODE; ++i)
            N[i] = NULL;
        for(int i=0; i<MAX_NODE*DEGREE; ++i)
            E[i] = NULL;
    }

    Edge<T>* minEdge(Edge<T>* Ed[])
    {
        Edge<T>* e = Ed[0];
        for(int i=1; Ed[i]!=NULL; ++i)
            if(!Ed[i]->isProcessed && e->value > Ed[i]->value)
                e = Ed[i];
        if(e->isProcessed)
            e = NULL;
        return e;
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
        if(num_edge >= DEGREE*MAX_NODE)
        {
            cerr<<"\nCannot add any more edges.";
            return ;
        }
        Edge<T>* temp = new Edge<T>(f, t, val);
        f->add_e(temp);
        t->add_e(temp);
        E[num_edge] = temp;
        ++num_edge;
    }

    void add_edge(Edge<T>* e)
    {
        if(num_edge >= DEGREE*MAX_NODE)
        {
            cerr<<"\nCannot add any more edges.";
            return ;
        }
        e->n1->add_e(e);
        e->n2->add_e(e);
        E[num_edge] = e;
        ++num_edge;
    }

    Graph primsMST_util(Graph &g, NodePtr root, Edge<T>* Ed[])
    {
        int a=0;
        for(; Ed[a]!=NULL; ++a)
        for(int j=0; j<root->degree; ++j)
        {
            Ed[a] = root->Links[j];
            ++a;
        }
        Edge<T>* minE = minEdge(Ed);
        if(minE == NULL)
            return g;
        Graph A=g;
        A.add_edge(minE);
        minE->isProcessed = true;
        if(A.isCyclic())
        {
            

        }
        
        if(minE->n1 == root)
            primsMST_util(g, minE->n2, Ed);
        else
            primsMST_util(g, minE->n1, Ed);
    }

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
            root->visited = true;
            //cout<<"Data: "<<root->data<<endl;
            for(int i=0; i<root->degree && !iscycle; ++i)
                if(root->Links[i]->n1 == root)
                    if(!(root->Links[i]->n2->visited))
                    {
                        paraent_node = root;
                        isCyclic_util(root->Links[i]->n2, iscycle);
                    }
                    else if(root->Links[i]->n2 != paraent_node)
                    {
                        //cout<<"Cycle found at: "<<root->Links[i]->n2->data<<endl;
                        iscycle=true;
                    }
                else if(root->Links[i]->n2 == root)
                    if(!(root->Links[i]->n1->visited))
                    {
                        paraent_node = root;
                        isCyclic_util(root->Links[i]->n1, iscycle);
                    }
                    else if(root->Links[i]->n1 != paraent_node)
                    {
                        //cout<<"1Cycle found at: "<<root->Links[i]->n1->data<<endl;
                        iscycle=true;
                    }
        }
        return iscycle;
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

    Graph primsMST(NodePtr root = NULL)
    {
        Edge<T>* Ed[num_edge*4];
        Graph g;
        
        if(root == NULL)
            root = N[0];
        for(int i=0; i<num_edge; ++i)
        {
            Ed[i] = NULL;
            E[i]->isProcessed = false;
        }
        return primsMST_util(g, root, Ed);
    }
};



int main(int argc, char const *argv[])
{  
    Edge<int>* edgess[9];
    Node<int>* nodess[6];
    Graph<int> G;

    for(int i=0; i<6; ++i)
        nodess[i] = G.add_node(i);
    
    edgess[0] = new Edge<int>(nodess[0], nodess[1], 5);
    edgess[1] = new Edge<int>(nodess[1], nodess[2], 2);
    edgess[2] = new Edge<int>(nodess[2], nodess[3], 5);
    edgess[3] = new Edge<int>(nodess[3], nodess[4], 3);
    edgess[4] = new Edge<int>(nodess[2], nodess[4], 6);
    edgess[5] = new Edge<int>(nodess[2], nodess[5], 12);
    edgess[6] = new Edge<int>(nodess[5], nodess[4], 1);
    edgess[7] = new Edge<int>(nodess[1], nodess[5], 10);
    edgess[8] = new Edge<int>(nodess[0], nodess[5], 4);

    for(int i=0; i<9; ++i)
        G.add_edge(edgess[i]);
 
    cout<<"Is cyclic:"<<G.primsMST().isCyclic()<<endl;
    return 0;
}
