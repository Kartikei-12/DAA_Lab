//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com
/*----------------------------------------------------
    Remember to overload following operators for data() type T.
        >
        <
        ==
        =
        <<
        >>
----------------------------------------------------*/
#include<iostream>
#include<vector>
#include<algorithm>
    using namespace std;
#define MAX_DOUBLE 1e15
#define DEGREE 8
#define MAX_NODE DEGREE+1

#define NodePtr Node<T>*
#define EdgePtr Edge<T>*

template<typename T>
class Edge;

template<typename T>
class Node
{
    T Data;
public:
    bool visited;
    vector<EdgePtr> Links;

    Node(T a): visited(false), Data(a) {
        Links.reserve(DEGREE);
    }
    T data() { return Data; }
    int degree() { return Links.size(); }
    bool operator==(Node n) { return Data==n.Data; }
    void add_e(EdgePtr e) {
        Links.insert(lower_bound(Links.begin(), Links.end(), e), e);
    }
};

template<typename T>
class Edge
{
    long double value;
public:
    NodePtr n1; NodePtr n2;//Just simple names graph is undirected
    
    Edge(NodePtr t1, NodePtr t2, long double v=0): n1(t1), n2(t2), value(v) {;}
    long double get_value() { return value; }
    bool operator<(Edge e) { return value<e.value; }
    bool operator>(Edge e) { return value>e.value; }
};

template<typename T>
EdgePtr min_edge(vector<EdgePtr> Ed)
{//Finding min
    long double min = MAX_DOUBLE;
    EdgePtr e = NULL;
    for(EdgePtr i:Ed)
        if(min > i->get_value())
            e = i, min = i->get_value();
    cout<<"\tProcessing Edge: "
        <<e->n1->data()<<" "
        <<e->n2->data()<<" "
        <<e->get_value()<<endl;
    return e;
}

template<typename T>
class Graph
{
    int num_edge;
    vector<NodePtr> N;
public:
    Graph(): num_edge(0) { N.reserve(MAX_NODE); }
    int num_nodes() { return N.size(); }
    void reset_visited() { for(int i=0; i<num_nodes(); ++i) N[i]->visited = false; }
//-------Insertion Methods----------------------------------------------------------------
    NodePtr add_node(T d)
    {
        if(num_nodes() >= MAX_NODE) {
            cerr<<"Maximum number of Nodes reached."; return NULL;
        }
        NodePtr temp = new Node<T>(d);
        N.push_back(temp);
        return temp;
    }
    void add_edge(EdgePtr e)
    {
        if(num_edge >= DEGREE*MAX_NODE) {
            cerr<<"\nCannot add any more edges."; return ;
        }
        e->n1->add_e(e);
        e->n2->add_e(e);
        ++num_edge;
    }
    void add_edge(NodePtr f, NodePtr t, long double val=0)
    {
        if(num_edge >= DEGREE*MAX_NODE) {
            cerr<<"\nCannot add any more edges."; return ;
        }
        add_edge(new Edge<T>(f, t, val));
    }
//-------Insertion Methods ENDS-------------------------------------------------------
//-------Search Methods---------------------------------------------------------------
    NodePtr get_node_from_data(T d)
    {
        for(int i=0; i<num_nodes(); ++i)
            if(d == N[i]->data())
                return N[i];
        return add_node(d);
    }

    int get_node_index(NodePtr n)
    {
        for(int i=0; i<num_nodes(); ++i)
            if(N[i]->data() == n->data())
                return i;
        return -1;
    }
//-------Search Methods ENDS------------------------------------------------------------
//-------Utility Method(Perform Actual Task)--------------------------------------------
    void DFT_util(NodePtr root)
    {
        root->visited = true;
        cout<<"Data: "<<root->data()<<endl;
        for(int i=0; i<root->degree(); ++i)
        {
            NodePtr nextNode = (root->Links[i]->n1 == root)? 
                                    root->Links[i]->n2 : root->Links[i]->n1;
            if(!nextNode->visited) DFT_util(nextNode);
        }
    }

    vector<long double> dijSSSP_util(
        NodePtr root,
        vector<EdgePtr> &Ed,
        vector<long double> &distance
    ) {
        int new_node_index, old_node_index;
        EdgePtr minEdge = NULL;
        long double new_dist = MAX_DOUBLE;
        
        root->visited = true;
        cout<<"Processing node: "<<root->data()<<endl;
        
        for(int i=0; i<root->degree(); ++i)
        {
            NodePtr nextNode=(root->Links[i]->n1==root)? 
                        root->Links[i]->n2 : root->Links[i]->n1;
            if(!nextNode->visited)
                Ed.push_back(root->Links[i]);
            old_node_index = get_node_index(root);
            new_node_index = get_node_index(nextNode);
            new_dist = distance[old_node_index] + root->Links[i]->get_value(); 
            if(distance[new_node_index] > new_dist)
                distance[new_node_index] = new_dist;
        }    
        do {
            minEdge = min_edge<T>(Ed);
            Ed.erase(remove(Ed.begin(), Ed.end(), minEdge), Ed.end());
        }while(Ed.size() && minEdge->n1->visited && minEdge->n2->visited);
        // On Last vible node
        
        if(Ed.size()==0) return distance;//Edges exhausted

        NodePtr visitedNode = (minEdge->n1->visited)? minEdge->n1 : minEdge->n2;
        NodePtr notVisitedNode = (minEdge->n1->visited)? minEdge->n2 : minEdge->n1;
        if(!minEdge->n1->visited || !minEdge->n2->visited)
        {
            old_node_index = get_node_index(visitedNode);
            new_node_index = get_node_index(notVisitedNode);
            new_dist = distance[old_node_index] + minEdge->get_value();        
            if(distance[new_node_index] > new_dist)
                distance[new_node_index] = new_dist;
            distance = dijSSSP_util(notVisitedNode, Ed, distance);
        }
        return distance;
    }
    Graph primsMST_util(Graph &g, NodePtr root, vector<EdgePtr> &Ed)
    {
        EdgePtr minEdge = NULL;
        root->visited = true;
        cout<<"Processing node: "<<root->data()<<endl;
        
        for(int i=0; i<root->degree(); ++i)
        {
            NodePtr nextNode=(root->Links[i]->n1==root)? 
                        root->Links[i]->n2 : root->Links[i]->n1;
            if(!nextNode->visited)
                Ed.push_back(root->Links[i]);
        }

        do {
            minEdge = min_edge<T>(Ed);
            Ed.erase(remove(Ed.begin(), Ed.end(), minEdge), Ed.end());
        }while(Ed.size() && minEdge->n1->visited && minEdge->n2->visited);
        
        if(Ed.size()==0) return g;//Edges exhausted
        g.add_edge(
            g.get_node_from_data(minEdge->n1->data()),
            g.get_node_from_data(minEdge->n2->data()),
            minEdge->get_value()
        );
        
        if(!minEdge->n1->visited || !minEdge->n2->visited)
            g = primsMST_util(
                    g,
                    (minEdge->n1->visited)? minEdge->n2 : minEdge->n1, Ed
                );
        return g;
    }
    bool isCyclic_util(NodePtr root, bool &iscycle, NodePtr paraent_node)
    {
        root->visited = true; //Data: root->data()
        for(int i=0; i<root->degree() && !iscycle; ++i)
        {
            NodePtr nextNode=(root->Links[i]->n1==root)? 
                        root->Links[i]->n2 : root->Links[i]->n1;
            if(!nextNode->visited)
                iscycle = isCyclic_util(nextNode, iscycle, root);
            else if(nextNode != paraent_node)
                return true;// Cycle found
        }
        return iscycle;
    }
//-------Utility Methods ENDS------------------------------------------------------------
    void DFT(NodePtr root = NULL)
    {
        reset_visited();
        if(root == NULL) root = N[0];
        DFT_util(root);
        
        cout<<"\nNo. of nodes: "<<num_nodes()
            <<"\nNo. of edges: "<<num_edge<<endl;
    }

    void dijikstra(NodePtr root = NULL)
    {
        vector<EdgePtr> Ed;
        Ed.reserve(MAX_NODE*DEGREE);
        vector<long double> distance(num_nodes(), MAX_DOUBLE);
        reset_visited();
        if(root == NULL) root = N[0];
        distance[0] = 0;
        distance = dijSSSP_util(root, Ed, distance);
        
        cout<<"\nDistances: \n";
        for(int i=0; i<num_nodes(); ++i)
            cout<<root->data()<<" - "
                <<N[i]->data()<<" : "
                <<distance[i]<<endl;
    }
    Graph primsMST(NodePtr root = NULL)
    {
        Graph<T> g;
        vector<EdgePtr> Ed;
        Ed.reserve(MAX_NODE*DEGREE);
        reset_visited();
        if(root == NULL) root = N[0];
        return primsMST_util(g, root, Ed);
    }
    bool isCyclic(NodePtr root = NULL)
    {
        bool a = false;
        if(root == NULL) root = N[0];
        for(int i=0; i<num_nodes(); ++i) N[i]->visited = false;
        return isCyclic_util(root, a, NULL);
    }
};


int main(int argc, char const *argv[])
{
    if(argc!=2) {
        cerr<<"Invalid argument!"<<endl; return 0;
    }
    Edge<char>* ed[11];
    Node<char>* no[7];
    Graph<char> G;

    for(int i=0; i<7; ++i)
        no[i] = G.add_node(i+65);

    ed[0] = new Edge<char>(no[0], no[1], 5.0);
    ed[1] = new Edge<char>(no[0], no[2], 4.0);
    ed[2] = new Edge<char>(no[1], no[2], 3.0);
    ed[3] = new Edge<char>(no[1], no[4], 7.0);
    ed[4] = new Edge<char>(no[1], no[3], 4.0);
    ed[5] = new Edge<char>(no[2], no[3], 2.0);
    ed[6] = new Edge<char>(no[2], no[5], 6.0);
    ed[7] = new Edge<char>(no[3], no[5], 1.0);
    ed[8] = new Edge<char>(no[3], no[4], 5.0);
    ed[9] = new Edge<char>(no[4], no[6], 6.0);
    ed[10] = new Edge<char>(no[5], no[6], 7.0);
    
    for(int i=0; i<11; ++i)
        G.add_edge(ed[i]);
    
    if(*argv[1]=='1')
        G.DFT();
    else if(*argv[1]=='2')
    {
        cout<<"\n\nPrinting minimum spanning tree:"<<endl;
        G.primsMST().DFT();
    }
    else if(*argv[1]=='3')
        cout<<"\nIscyclic: "<<G.isCyclic()<<endl;
    else if(*argv[1]=='4')
        G.dijikstra();
    else
        cerr<<"Unknown case!"<<endl;
    return 0;
}