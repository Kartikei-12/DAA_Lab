//Author: Kartikei Mittal
//ID: 2017KUCP1032
#include<iostream>
#include<vector>
#include<algorithm>
    using namespace std;
//Note: datatype T used in defination must have properly
//overloaded assignment(=) operator.
#define DEGREE 8
#define MAX_NODE DEGREE+1

#define NodePtr Node<T>*
#define EdgePtr Edge<T>*

template<typename T>
class Edge;

template<typename T>
class Node
{public:
    bool visited;
    int degree;
    T data;
    EdgePtr Links[DEGREE];

    Node(T a): visited(false), degree(0), data(a) {
        for(int i=0; i<DEGREE; ++i)
            Links[i] = NULL;
    }
    void add_e(EdgePtr e) {
        Links[degree] = e;
        ++degree;
    }
};

template<typename T>
class Edge
{
public:
    long double value;
    NodePtr n1; NodePtr n2;//Just simple names graph is undirected
    Edge(NodePtr t1, NodePtr t2, long double v=0): n1(t1), n2(t2), value(v) {;}
};


template<typename T>
class Graph
{
    int num_nodes, num_edge;
    NodePtr paraent_node;
    NodePtr N[MAX_NODE];
    EdgePtr E[MAX_NODE*DEGREE];
public:
    Graph() 
    {
        num_nodes = num_edge = 0;
        for(int i=0; i<MAX_NODE; ++i) N[i] = NULL;
        for(int i=0; i<MAX_NODE*DEGREE; ++i) E[i] = NULL;
    }
    NodePtr add_node(T d)
    {
        if(num_nodes >= MAX_NODE) {
            cerr<<"Maximum number of Nodes reached."; return NULL;
        }
        NodePtr temp = new Node<T>(d);
        N[num_nodes] = temp;
        num_nodes++;
        return temp;
    }
    void add_edge(NodePtr f, NodePtr t, long double val=0)
    {
        if(num_edge >= DEGREE*MAX_NODE) {
            cerr<<"\nCannot add any more edges."; return ;
        }
        EdgePtr temp = new Edge<T>(f, t, val);
        f->add_e(temp);
        t->add_e(temp);
        E[num_edge] = temp;
        ++num_edge;
    }
    void add_edge(EdgePtr e)
    {
        if(num_edge >= DEGREE*MAX_NODE) {
            cerr<<"\nCannot add any more edges."; return ;
        }
        e->n1->add_e(e);
        e->n2->add_e(e);
        E[num_edge] = e;
        ++num_edge;
    }
    
    NodePtr get_node_from_data(T d)
    {
        for(int i=0; i<num_nodes; ++i)
            if(d == N[i]->data)
                return N[i];
        return add_node(d);
    }
    EdgePtr minEdge(vector<EdgePtr> Ed)
    {// cout<<"\nFinding min\n";
        EdgePtr e = Ed.at(0);
        for(EdgePtr i:Ed)
            if(e->value > i->value)
                e = i;
        cout<<"\tProcessing Edge: "
            <<e->n1->data<<" "
            <<e->n2->data<<" "
            <<e->value<<endl;
        return e;
    }
    
    Graph primsMST_util(Graph &g, NodePtr root, vector<EdgePtr> &Ed)
    {
        cout<<"Processing node: "<<root->data<<endl;
        if(root->visited)//cerr<<"Visited Node found.";
            return g;     
        root->visited = true;

        EdgePtr minE = NULL;
        EdgePtr temp = NULL;
        g.get_node_from_data(root->data);//NodePtr temp = 

        for(int i=0; i<root->degree; ++i)
        {
            temp = root->Links[i];
            if((temp->n1 == root && !temp->n2->visited) ||
               (temp->n2 == root && !temp->n1->visited))
                Ed.push_back(temp);
        }
        // cout<<"\n Edges exhausted"<<endl;
        if(Ed.size()==0) return g;
        
        minE = minEdge(Ed);

        //cout<<"On Last vible node, abondaining current edge."<<endl;
        if(minE->n1->visited && minE->n2->visited) return g;
        
        g.add_edge(
            g.get_node_from_data(minE->n1->data),
            g.get_node_from_data(minE->n2->data),
            minE->value
        );//Remove processed edge
        Ed.erase(remove(Ed.begin(), Ed.end(), minE), Ed.end());

        if(minE->n1->visited)
            primsMST_util(g, minE->n2, Ed);
        else if(minE->n2->visited)
            primsMST_util(g, minE->n1, Ed);
        return g;
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
    bool isCyclic_util(NodePtr root, bool &iscycle) {
        if(!iscycle)
        {
            root->visited = true; // cout<<"Data: "<<root->data<<endl;
            for(int i=0; i<root->degree && !iscycle; ++i)
                if(root->Links[i]->n1 == root)
                    if(!(root->Links[i]->n2->visited))
                    {
                        paraent_node = root;
                        iscycle = isCyclic_util(root->Links[i]->n2, iscycle);
                    }
                    else if(root->Links[i]->n2 != paraent_node)
                        return true;// Cycle found
                else if(root->Links[i]->n2 == root)
                    if(!(root->Links[i]->n1->visited))
                    {
                        paraent_node = root;
                        iscycle = isCyclic_util(root->Links[i]->n1, iscycle);
                    }
                    else if(root->Links[i]->n1 != paraent_node)
                        return true;// Cycle found
        }
        return iscycle;
    }

    bool isCyclic(NodePtr root = NULL)
    {
        bool a = false;
        paraent_node = NULL;
        if(root == NULL) root = N[0];
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        return isCyclic_util(root, a);
    }
    void DFT(NodePtr root = NULL)
    {
        if(root == NULL) root = N[0];
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        DFT_util(root);
        cout<<"\nNo. of nodes: "<<num_nodes
            <<"\nNo. of edges: "<<num_edge<<endl;
    }
    Graph primsMST(NodePtr root = NULL)
    {
        Graph<T> g;
        vector<EdgePtr> Ed;//(MAX_NODE*DEGREE)
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        if(root == NULL) root = N[0];
        return primsMST_util(g, root, Ed);
    }
};



int main(int argc, char const *argv[])
{  
    Edge<char>* edgess[9];
    Node<char>* nodess[6];
    Graph<char> G;

    for(int i=0; i<6; ++i)
        nodess[i] = G.add_node(i+65);
    edgess[0] = new Edge<char>(nodess[0], nodess[1], 5.0);
    edgess[1] = new Edge<char>(nodess[1], nodess[2], 2.0);
    edgess[2] = new Edge<char>(nodess[2], nodess[3], 5.0);
    edgess[3] = new Edge<char>(nodess[3], nodess[4], 3.0);
    edgess[4] = new Edge<char>(nodess[2], nodess[4], 6.0);
    edgess[5] = new Edge<char>(nodess[2], nodess[5], 12.0);
    edgess[6] = new Edge<char>(nodess[5], nodess[4], 1.0);
    edgess[7] = new Edge<char>(nodess[1], nodess[5], 10.0);
    edgess[8] = new Edge<char>(nodess[0], nodess[5], 4.0);
    for(int i=0; i<9; ++i)
        G.add_edge(edgess[i]);
    
    // G.DFT();
    
    Graph<char> l = G.primsMST();
    cout<<"\n\nPrinting minimum spanning tree:\n";
    l.DFT();
    // cout<<"\nIscyclic: "<<l.isCyclic()<<endl;
    //cout<<"A "<<l.num_nodes<<" A "<<l.num_edge;
    return 0;
}
