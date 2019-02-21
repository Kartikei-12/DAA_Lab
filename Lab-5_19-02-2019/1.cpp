//@author: Kartikei Mittal
//email: kartikeimittal@gmail.com

#include<iostream>
    using namespace std;
#include<vector>
#include<algorithm>
#include<iterator>

#define DEGREE 8
#define MAX_NODE DEGREE+1

#define NodePtr Node<T>*
#define EdgePtr Edge<T>*

template<typename T>
class Edge;

template<typename T>
class Node
{
public:
    bool visited;
    T data;
    vector<EdgePtr> Links;

    Node(T a): visited(false), data(a) {
        Links.reserve(DEGREE);
    }
    void add_e(EdgePtr e) {
        Links.insert(lower_bound(Links.begin(), Links.end(), e), e);
    }
    int degree() { return Links.size(); }
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
class Graph
{
    int num_nodes, num_edge;
    NodePtr paraent_node;
    NodePtr N[MAX_NODE];
public:
    Graph(): num_nodes(0), num_edge(0) {
        for(int i=0; i<MAX_NODE; ++i) N[i] = NULL;
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
        ++num_edge;
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
    
    NodePtr get_node_from_data(T d)
    {
        for(int i=0; i<num_nodes; ++i)
            if(d == N[i]->data)
                return N[i];
        return add_node(d);
    }
    
    EdgePtr minEdge(vector<EdgePtr> Ed)
    {//Finding min
        long double min = 999999.0;
        EdgePtr e = NULL;
        for(EdgePtr i:Ed)
            if(min > i->get_value())
                e = i, min = i->get_value();
        cout<<"\tProcessing Edge: "
            <<e->n1->data<<" "
            <<e->n2->data<<" "
            <<e->get_value()<<endl;
        return e;
    }

    void DFT_util(NodePtr root)
    {
        root->visited = true;
        cout<<"Data: "<<root->data<<endl;
        for(int i=0; i<root->degree(); ++i)
            if(root->Links[i]->n1 == root && !(root->Links[i]->n2->visited))
                DFT_util(root->Links[i]->n2);
            else if(!(root->Links[i]->n1->visited))
                DFT_util(root->Links[i]->n1);
    }

    void DFT(NodePtr root = NULL)
    {
        if(root == NULL) root = N[0];
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        DFT_util(root);
        cout<<"\nNo. of nodes: "<<num_nodes
            <<"\nNo. of edges: "<<num_edge<<endl;
    }

    int get_node_index(NodePtr n)
    {
        for(int i=0; i<num_nodes; ++i)
            if(N[i]->data == n->data)
                return i;
        return -1;
    }

    vector<long double> dijSSSP_util(
        NodePtr root,
        vector<EdgePtr> &Ed,
        vector<long double> &distance
    ) {
        int new_node_index=-1, old_node_index=-1;
        EdgePtr minE = NULL;
        long double new_dist = 0.0;
        root->visited = true;
        cout<<"Processing node: "<<root->data<<endl;
        
        for(int i=0; i<root->degree(); ++i) {
            EdgePtr temp = root->Links[i];
            if((temp->n1 == root && !temp->n2->visited) ||
               (temp->n2 == root && !temp->n1->visited))
                Ed.push_back(temp);
        }
        
        do {
            minE = minEdge(Ed);
            Ed.erase(remove(Ed.begin(), Ed.end(), minE), Ed.end());
        }while(Ed.size() && minE->n1->visited && minE->n2->visited);
        // On Last vible node
        
        if(Ed.size()==0) return distance;//Edges exhausted

        if(minE->n1->visited && !minE->n2->visited)
        {
            old_node_index = get_node_index(minE->n1);
            new_node_index = get_node_index(minE->n2);
            new_dist = distance[old_node_index]+minE->get_value();        
            if(distance[new_node_index] > new_dist)
                distance[new_node_index] = new_dist;
            distance = dijSSSP_util(minE->n2, Ed, distance);
        }
        else if(minE->n2->visited && !minE->n1->visited)
        {
            old_node_index = get_node_index(minE->n2);
            new_node_index = get_node_index(minE->n1);
            new_dist = distance[old_node_index]+minE->get_value();        
            if(distance[new_node_index] > new_dist)
                distance[new_node_index] = new_dist;
            distance = dijSSSP_util(minE->n1, Ed, distance);
        }
        return distance;
    }

    Graph<T> dijikstra(NodePtr root = NULL)
    {
        vector<EdgePtr> Ed;
        Ed.reserve(MAX_NODE*DEGREE);
        vector<long double> distance(num_nodes, 99999);

        distance[0] = 0;
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        if(root == NULL) root = N[0];

        distance = dijSSSP_util(root, Ed, distance);
        cout<<"\nDistances: \n";
        for(int i=0; i<num_nodes; ++i)
            cout<<root->data<<" - "
                <<N[i]->data<<" : "
                <<distance[i]<<endl;
    }
    
    Graph primsMST_util(Graph &g, NodePtr root, vector<EdgePtr> &Ed)
    {
        EdgePtr minE = NULL;
        root->visited = true;
        cout<<"Processing node: "<<root->data<<endl;
        
        for(int i=0; i<root->degree(); ++i) {
            EdgePtr temp = root->Links[i];
            if((temp->n1 == root && !temp->n2->visited) ||
               (temp->n2 == root && !temp->n1->visited))
                Ed.push_back(temp);
        }
        
        do {
            minE = minEdge(Ed);
            Ed.erase(remove(Ed.begin(), Ed.end(), minE), Ed.end());
        }while(Ed.size() && minE->n1->visited && minE->n2->visited);
        // On Last vible node
        
        if(Ed.size()==0) return g;//Edges exhausted

        g.add_edge(
            g.get_node_from_data(minE->n1->data),
            g.get_node_from_data(minE->n2->data),
            minE->get_value()
        );
        
        if(minE->n1->visited && !minE->n2->visited)
            g = primsMST_util(g, minE->n2, Ed);
        else if(minE->n2->visited && !minE->n1->visited)
            g = primsMST_util(g, minE->n1, Ed);
        return g;
    }
    Graph primsMST(NodePtr root = NULL)
    {
        Graph<T> g;
        vector<EdgePtr> Ed;
        Ed.reserve(MAX_NODE*DEGREE);
        for(int i=0; i<num_nodes; ++i) N[i]->visited = false;
        if(root == NULL) root = N[0];
        return primsMST_util(g, root, Ed);
    }
    
    bool isCyclic_util(NodePtr root, bool &iscycle) {
        if(!iscycle)
        {
            root->visited = true; // cout<<"Data: "<<root->data<<endl;
            for(int i=0; i<root->degree() && !iscycle; ++i)
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
};


int main(int argc, char const *argv[])
{  
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
    
    
    

    G.dijikstra();
    // G.DFT();
    // cout<<"AA"<<no[0]->degree();
    
    // Graph<char> l = G.dijikstra_shotest_path();
    // cout<<"\n\nPrinting Shotest path:\n";
    // l.print_path();
    
    
    // Graph<char> l = G.primsMST();
    // cout<<"\n\nPrinting minimum spanning tree:\n";
    // l.DFT();
    // cout<<"\nIscyclic: "<<l.isCyclic()<<endl;
    //cout<<"A "<<l.num_nodes<<" A "<<l.num_edge;
    return 0;
}